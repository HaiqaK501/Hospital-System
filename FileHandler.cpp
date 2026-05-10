
#pragma warning(disable : 4996)
#include "FileHandler.h"
#include <fstream>
#include <ctime>
#include <cstdio>

using namespace std;

static const int MAX_LINE_LEN = 1024;
static const int MAX_FIELDS = 50;
static char parseBuffer[MAX_LINE_LEN];

void FileHandler::initializeFiles()
{
    const char* files[] = {
        "patients.txt", "doctors.txt", "admins.txt", "nurses.txt", "volunteers.txt",
        "appointments.txt", "bills.txt", "prescriptions.txt", "pharmacy.txt",
        "laboratory.txt", "ambulance.txt", "ward.txt", "vaccination.txt",
        "medicalcamp.txt", "blooddonors.txt", "cashdonors.txt", "organdonors.txt",
        "security_log.txt", "login_attempts.txt", "discharged.txt"
    };

    for (int i = 0; i < 20; i++)
    {
        ifstream file(files[i]);
        if (!file.is_open())
        {
            ofstream outFile(files[i]);
            outFile.close();
        }
        else
        {
            file.close();
        }
    }
}

int FileHandler::stringToInt(const char* str)
{
    if (!str) return 0;
    int result = 0;
    int i = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

float FileHandler::stringToFloat(const char* str)
{
    if (!str) return 0.0f;
    float result = 0.0f;
    int i = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
    {
        i++;
        float fraction = 0.1f;
        while (str[i] >= '0' && str[i] <= '9')
        {
            result += (str[i] - '0') * fraction;
            fraction *= 0.1f;
            i++;
        }
    }
    return result;
}

void FileHandler::intToString(int num, char* buffer)
{
    if (!buffer) return;
    if (num == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    int digits[20];
    int count = 0;
    int temp = num;
    while (temp > 0)
    {
        digits[count++] = temp % 10;
        temp /= 10;
    }
    int idx = 0;
    for (int i = count - 1; i >= 0; i--)
        buffer[idx++] = '0' + digits[i];
    buffer[idx] = '\0';
}

void FileHandler::floatToString(float num, char* buffer)
{
    if (!buffer) return;
    int intPart = (int)num;
    int decPart = (int)((num - intPart) * 100);
    if (decPart < 0) decPart = -decPart;
    intToString(intPart, buffer);
    int len = 0;
    while (buffer[len] != '\0') len++;
    buffer[len++] = '.';
    buffer[len++] = '0' + (decPart / 10);
    buffer[len++] = '0' + (decPart % 10);
    buffer[len] = '\0';
}

void FileHandler::parseLine(const char* line, char* fields[], int maxFields)
{
    for (int i = 0; i < maxFields; i++)
        fields[i] = nullptr;

    int i = 0;
    while (line[i] != '\0' && i < MAX_LINE_LEN - 1)
    {
        parseBuffer[i] = line[i];
        i++;
    }
    parseBuffer[i] = '\0';

    int fieldIdx = 0;
    fields[0] = parseBuffer;

    for (int j = 0; parseBuffer[j] != '\0' && fieldIdx < maxFields - 1; j++)
    {
        if (parseBuffer[j] == ',')
        {
            parseBuffer[j] = '\0';
            fieldIdx++;
            fields[fieldIdx] = &parseBuffer[j + 1];
        }
    }
}

int FileHandler::getNextId(const char* filename)
{
    ifstream file(filename);
    if (!file.is_open()) return 1;
    char line[MAX_LINE_LEN];
    int maxId = 0;
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0])
        {
            int id = stringToInt(fields[0]);
            if (id > maxId) maxId = id;
        }
    }
    file.close();
    return maxId + 1;
}

bool FileHandler::deleteRecord(const char* filename, int id, int idColumn)
{
    ifstream file(filename);
    if (!file.is_open()) return false;
    char lines[1000][MAX_LINE_LEN];
    int lineCount = 0;
    while (file.getline(lines[lineCount], MAX_LINE_LEN) && lineCount < 1000)
        lineCount++;
    file.close();
    ofstream outFile(filename);
    if (!outFile.is_open()) return false;
    for (int i = 0; i < lineCount; i++)
    {
        char* fields[MAX_FIELDS];
        parseLine(lines[i], fields, MAX_FIELDS);
        int currentId = (fields[idColumn]) ? stringToInt(fields[idColumn]) : -1;
        if (currentId != id)
            outFile << lines[i] << endl;
    }
    outFile.close();
    return true;
}

bool FileHandler::loadPatients(Storage<Patient>& storage)
{
    ifstream file("patients.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6])
        {
            int id = stringToInt(fields[0]);
            int age = stringToInt(fields[2]);
            float balance = stringToFloat(fields[6]);
            Patient* p = new Patient(id, fields[1], fields[5], age, fields[3], fields[4], balance, "Unknown", "None");
            storage.add(p);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadDoctors(Storage<Doctor>& storage)
{
    ifstream file("doctors.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5])
        {
            int id = stringToInt(fields[0]);
            float fee = stringToFloat(fields[5]);
            Doctor* d = new Doctor(id, fields[1], fields[4], fields[2], fee, 5, "MBBS", "Main Branch");
            storage.add(d);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadAdmins(Storage<Admin>& storage)
{
    ifstream file("admins.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2])
        {
            int id = stringToInt(fields[0]);
            Admin* a = new Admin(id, fields[1], fields[2], "Management", "Full", 1000 + id, 100000.0f, "01-01-2025", false);
            storage.add(a);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadNurses(Storage<Nurse>& storage)
{
    ifstream file("nurses.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6] && fields[7])
        {
            int id = stringToInt(fields[0]);
            float salary = stringToFloat(fields[6]);
            int exp = stringToInt(fields[7]);
            Nurse* n = new Nurse(id, fields[1], fields[2], fields[3], fields[4], fields[5], salary, exp);
            storage.add(n);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadVolunteers(Storage<Volunteer>& storage)
{
    ifstream file("volunteers.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6] && fields[7])
        {
            int id = stringToInt(fields[0]);
            int hours = stringToInt(fields[5]);
            Volunteer* v = new Volunteer(id, fields[1], fields[2], fields[3], fields[4], hours, fields[6], fields[7]);
            storage.add(v);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadAppointments(Storage<Appointment>& storage)
{
    ifstream file("appointments.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5])
        {
            int id = stringToInt(fields[0]);
            int pId = stringToInt(fields[1]);
            int dId = stringToInt(fields[2]);
            bool emergency = false;
            Appointment* a = new Appointment(id, pId, dId, fields[3], fields[4], fields[5], emergency);
            storage.add(a);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadBills(Storage<Bill>& storage)
{
    ifstream file("bills.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5])
        {
            int id = stringToInt(fields[0]);
            int pId = stringToInt(fields[1]);
            int aId = stringToInt(fields[2]);
            float amt = stringToFloat(fields[3]);
            Bill* b = new Bill(id, pId, aId, amt, fields[5]);
            b->setStatus(fields[4]);
            storage.add(b);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadPrescriptions(Storage<Prescription>& storage)
{
    ifstream file("prescriptions.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6])
        {
            int id = stringToInt(fields[0]);
            int aId = stringToInt(fields[1]);
            int pId = stringToInt(fields[2]);
            int dId = stringToInt(fields[3]);
            Prescription* p = new Prescription(id, aId, pId, dId, fields[4], fields[5], fields[6]);
            storage.add(p);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadPharmacies(Storage<Pharmacy>& storage)
{
    ifstream file("pharmacy.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6] && fields[7] && fields[8] && fields[9])
        {
            int id = stringToInt(fields[0]);
            float price = stringToFloat(fields[4]);
            int stock = stringToInt(fields[5]);
            int reorder = stringToInt(fields[6]);
            float tax = stringToFloat(fields[9]);
            bool needRx = (stringToInt(fields[8]) == 1);
            Pharmacy* p = new Pharmacy(id, fields[1], fields[2], fields[3], price, stock, reorder, fields[7], needRx, tax);
            storage.add(p);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadLaboratories(Storage<Laboratory>& storage)
{
    ifstream file("laboratory.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6])
        {
            int id = stringToInt(fields[0]);
            float cost = stringToFloat(fields[3]);
            int hours = stringToInt(fields[4]);
            Laboratory* l = new Laboratory(id, fields[1], fields[2], cost, hours, fields[5], fields[6]);
            storage.add(l);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadAmbulances(Storage<Ambulance>& storage)
{
    ifstream file("ambulance.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6] && fields[7])
        {
            int id = stringToInt(fields[0]);
            float lat = stringToFloat(fields[5]);
            float lng = stringToFloat(fields[6]);
            Ambulance* a = new Ambulance(id, fields[1], fields[2], fields[3], fields[4], lat, lng);
            float fuel = stringToFloat(fields[7]);
            a->setFuelLevel(fuel);
            storage.add(a);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadWards(Storage<Ward>& storage)
{
    ifstream file("ward.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6] && fields[7])
        {
            int id = stringToInt(fields[0]);
            int beds = stringToInt(fields[3]);
            float rate = stringToFloat(fields[5]);
            bool isolation = (stringToInt(fields[7]) == 1);
            Ward* w = new Ward(id, fields[1], fields[2], beds, rate, fields[6], isolation);
            storage.add(w);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadVaccinations(Storage<Vaccination>& storage)
{
    ifstream file("vaccination.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6] && fields[7] && fields[8] && fields[9] && fields[10])
        {
            int id = stringToInt(fields[0]);
            int doses = stringToInt(fields[3]);
            int interval = stringToInt(fields[4]);
            float temp = stringToFloat(fields[5]);
            int stock = stringToInt(fields[6]);
            int expiry = stringToInt(fields[7]);
            float price = stringToFloat(fields[9]);
            bool emergency = (stringToInt(fields[10]) == 1);
            Vaccination* v = new Vaccination(id, fields[1], fields[2], doses, interval, temp, stock, expiry, fields[8], price, emergency);
            storage.add(v);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadMedicalCamps(Storage<MedicalCamp>& storage)
{
    ifstream file("medicalcamp.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6] && fields[7] && fields[8])
        {
            int id = stringToInt(fields[0]);
            float budget = stringToFloat(fields[6]);
            MedicalCamp* c = new MedicalCamp(id, fields[1], fields[2], fields[3], fields[4], fields[5], budget);
            storage.add(c);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadBloodDonors(Storage<BloodDonor>& storage)
{
    ifstream file("blooddonors.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6])
        {
            int id = stringToInt(fields[0]);
            int health = stringToInt(fields[6]);
            BloodDonor* d = new BloodDonor(id, fields[1], fields[2], fields[3], fields[4], fields[5], health);
            storage.add(d);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadCashDonors(Storage<CashDonor>& storage)
{
    ifstream file("cashdonors.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6])
        {
            int id = stringToInt(fields[0]);
            bool anonymous = false;
            CashDonor* d = new CashDonor(id, fields[1], fields[2], fields[3], fields[4], anonymous);
            storage.add(d);
        }
    }
    file.close();
    return true;
}

bool FileHandler::loadOrganDonors(Storage<OrganDonor>& storage)
{
    ifstream file("organdonors.txt");
    if (!file.is_open()) return false;
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char* fields[MAX_FIELDS];
        parseLine(line, fields, MAX_FIELDS);
        if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6])
        {
            int id = stringToInt(fields[0]);
            bool emergency = false;
            OrganDonor* d = new OrganDonor(id, fields[1], fields[2], fields[3], fields[4], fields[5], emergency);
            storage.add(d);
        }
    }
    file.close();
    return true;
}

bool FileHandler::savePatient(const Patient& patient)
{
    ofstream file("patients.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20], ageStr[10], balanceStr[30];
    intToString(patient.getID(), idStr);
    intToString(patient.getAge(), ageStr);
    floatToString(patient.getBalance(), balanceStr);

    const char* nameStr = patient.getName().get();
    const char* genderStr = patient.getGender();
    const char* contactStr = patient.getContact();
    const char* passStr = patient.getPassword().get();

    file << idStr << "," << nameStr << "," << ageStr << ","
        << genderStr << "," << contactStr << ","
        << passStr << "," << balanceStr << endl;
    file.close();
    return true;
}

bool FileHandler::saveDoctor(const Doctor& doctor)
{
    ofstream file("doctors.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20], feeStr[30];
    intToString(doctor.getID(), idStr);
    floatToString(doctor.getFee(), feeStr);

    const char* nameStr = doctor.getName().get();
    const char* specStr = doctor.getSpecialization();
    const char* passStr = doctor.getPassword().get();

    file << idStr << "," << nameStr << "," << specStr << ","
        << "03000000000" << "," << passStr << "," << feeStr << endl;
    file.close();
    return true;
}

bool FileHandler::saveNurse(const Nurse& nurse)
{
    ofstream file("nurses.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20], salaryStr[30], expStr[10];
    intToString(nurse.getID(), idStr);
    floatToString(nurse.getSalary(), salaryStr);
    intToString(nurse.getExperience(), expStr);

    const char* nameStr = nurse.getName().get();
    const char* passStr = nurse.getPassword().get();
    const char* specStr = nurse.getSpecialization();
    const char* shiftStr = nurse.getShift();
    const char* wardStr = nurse.getAssignedWard();

    file << idStr << "," << nameStr << "," << passStr << ","
        << specStr << "," << shiftStr << "," << wardStr << ","
        << salaryStr << "," << expStr << endl;
    file.close();
    return true;
}

bool FileHandler::saveVolunteer(const Volunteer& volunteer)
{
    ofstream file("volunteers.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20], hoursStr[10];
    intToString(volunteer.getID(), idStr);
    intToString(volunteer.getHoursPerWeek(), hoursStr);

    const char* nameStr = volunteer.getName().get();
    const char* passStr = volunteer.getPassword().get();
    const char* deptStr = volunteer.getDepartment();
    const char* shiftStr = volunteer.getShift();
    const char* skillsStr = volunteer.getSkills();
    const char* availStr = volunteer.getAvailability();

    file << idStr << "," << nameStr << "," << passStr << ","
        << deptStr << "," << shiftStr << "," << hoursStr << ","
        << skillsStr << "," << availStr << ",0,0,0" << endl;
    file.close();
    return true;
}

bool FileHandler::saveAppointment(const Appointment& appointment)
{
    ofstream file("appointments.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20], pIdStr[20], dIdStr[20];
    intToString(appointment.getAppointmentId(), idStr);
    intToString(appointment.getPatientId(), pIdStr);
    intToString(appointment.getDoctorId(), dIdStr);

    file << idStr << "," << pIdStr << "," << dIdStr << ","
        << appointment.getDate() << "," << appointment.getTimeSlot() << ","
        << appointment.getStatus() << endl;
    file.close();
    return true;
}

bool FileHandler::saveBill(const Bill& bill)
{
    ofstream file("bills.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20], pIdStr[20], aIdStr[20], amtStr[30];
    intToString(bill.getBillId(), idStr);
    intToString(bill.getPatientId(), pIdStr);
    intToString(bill.getAppointmentId(), aIdStr);
    floatToString(bill.getAmount(), amtStr);

    file << idStr << "," << pIdStr << "," << aIdStr << "," << amtStr << ","
        << bill.getStatus() << "," << bill.getDate() << endl;
    file.close();
    return true;
}

bool FileHandler::savePrescription(const Prescription& prescription)
{
    ofstream file("prescriptions.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20], aIdStr[20], pIdStr[20], dIdStr[20];
    intToString(prescription.getPrescriptionId(), idStr);
    intToString(prescription.getAppointmentId(), aIdStr);
    intToString(prescription.getPatientId(), pIdStr);
    intToString(prescription.getDoctorId(), dIdStr);

    file << idStr << "," << aIdStr << "," << pIdStr << "," << dIdStr << ","
        << prescription.getDate() << "," << prescription.getMedicines() << ","
        << prescription.getNotes() << endl;
    file.close();
    return true;
}

bool FileHandler::saveBloodDonor(const BloodDonor& donor)
{
    ofstream file("blooddonors.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20], healthStr[10];
    intToString(donor.getID(), idStr);
    intToString(donor.getHealthScore(), healthStr);

    const char* nameStr = donor.getName().get();
    const char* passStr = donor.getPassword().get();
    const char* contactStr = donor.getContactNumber();
    const char* addressStr = donor.getAddress();
    const char* bloodStr = donor.getBloodGroup();
    const char* lastDonationStr = donor.getLastDonationDate();

    file << idStr << "," << nameStr << "," << passStr << ","
        << contactStr << "," << addressStr << "," << bloodStr << ","
        << healthStr << "," << donor.getTotalDonations() << "," << lastDonationStr << ",1" << endl;
    file.close();
    return true;
}

bool FileHandler::saveCashDonor(const CashDonor& donor)
{
    ofstream file("cashdonors.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20], totalStr[30], yearStr[30];
    intToString(donor.getID(), idStr);
    floatToString(donor.getTotalCashDonated(), totalStr);
    floatToString(donor.getThisYearDonation(), yearStr);

    const char* nameStr = donor.getName().get();
    const char* passStr = donor.getPassword().get();
    const char* contactStr = donor.getContactNumber();
    const char* addressStr = donor.getAddress();

    file << idStr << "," << nameStr << "," << passStr << ","
        << contactStr << "," << addressStr << "," << totalStr << ","
        << yearStr << "," << (donor.getIsAnonymous() ? 1 : 0) << ","
        << donor.getSponsoredPatientCount() << ",1" << endl;
    file.close();
    return true;
}

bool FileHandler::saveOrganDonor(const OrganDonor& donor)
{
    ofstream file("organdonors.txt", ios::app);
    if (!file.is_open()) return false;

    char idStr[20];
    intToString(donor.getID(), idStr);

    const char* nameStr = donor.getName().get();
    const char* passStr = donor.getPassword().get();
    const char* contactStr = donor.getContactNumber();
    const char* addressStr = donor.getAddress();
    const char* cardStr = donor.getOrganDonationCardNumber();
    const char* hospitalStr = donor.getPreferredHospital();

    file << idStr << "," << nameStr << "," << passStr << ","
        << contactStr << "," << addressStr << ","
        << "Heart;Kidney" << "," << (donor.getIsFamilyConsented() ? 1 : 0) << ","
        << cardStr << "," << hospitalStr << ",1" << endl;
    file.close();
    return true;
}

bool FileHandler::updatePatientBalance(int patientId, float newBalance)
{
    ifstream file("patients.txt");
    if (!file.is_open()) return false;
    char lines[1000][MAX_LINE_LEN];
    int lineCount = 0;
    while (file.getline(lines[lineCount], MAX_LINE_LEN) && lineCount < 1000)
        lineCount++;
    file.close();
    ofstream outFile("patients.txt");
    if (!outFile.is_open()) return false;
    for (int i = 0; i < lineCount; i++)
    {
        char* fields[MAX_FIELDS];
        parseLine(lines[i], fields, MAX_FIELDS);
        int currentId = (fields[0]) ? stringToInt(fields[0]) : -1;
        if (currentId == patientId && fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5])
        {
            char balanceStr[30];
            floatToString(newBalance, balanceStr);
            outFile << fields[0] << "," << fields[1] << "," << fields[2] << ","
                << fields[3] << "," << fields[4] << "," << fields[5] << ","
                << balanceStr << endl;
        }
        else
        {
            outFile << lines[i];
        }
    }
    outFile.close();
    return true;
}

bool FileHandler::updateAppointmentStatus(int appointmentId, const char* status)
{
    ifstream file("appointments.txt");
    if (!file.is_open()) return false;
    char lines[1000][MAX_LINE_LEN];
    int lineCount = 0;
    while (file.getline(lines[lineCount], MAX_LINE_LEN) && lineCount < 1000)
        lineCount++;
    file.close();
    ofstream outFile("appointments.txt");
    if (!outFile.is_open()) return false;
    for (int i = 0; i < lineCount; i++)
    {
        char* fields[MAX_FIELDS];
        parseLine(lines[i], fields, MAX_FIELDS);
        int currentId = (fields[0]) ? stringToInt(fields[0]) : -1;
        if (currentId == appointmentId && fields[0] && fields[1] && fields[2] && fields[3] && fields[4])
        {
            outFile << fields[0] << "," << fields[1] << "," << fields[2] << ","
                << fields[3] << "," << fields[4] << "," << status << endl;
        }
        else
        {
            outFile << lines[i];
        }
    }
    outFile.close();
    return true;
}

bool FileHandler::updateBillStatus(int billId, const char* status)
{
    ifstream file("bills.txt");
    if (!file.is_open()) return false;
    char lines[1000][MAX_LINE_LEN];
    int lineCount = 0;
    while (file.getline(lines[lineCount], MAX_LINE_LEN) && lineCount < 1000)
        lineCount++;
    file.close();
    ofstream outFile("bills.txt");
    if (!outFile.is_open()) return false;
    for (int i = 0; i < lineCount; i++)
    {
        char* fields[MAX_FIELDS];
        parseLine(lines[i], fields, MAX_FIELDS);
        int currentId = (fields[0]) ? stringToInt(fields[0]) : -1;
        if (currentId == billId && fields[0] && fields[1] && fields[2] && fields[3] && fields[5])
        {
            outFile << fields[0] << "," << fields[1] << "," << fields[2] << ","
                << fields[3] << "," << status << "," << fields[5] << endl;
        }
        else
        {
            outFile << lines[i];
        }
    }
    outFile.close();
    return true;
}

void FileHandler::logSecurity(const char* role, int enteredId, const char* result, int attemptCount, bool isLocked)
{
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char timestamp[30];
    sprintf(timestamp, "%02d-%02d-%04d %02d:%02d:%02d",
        t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
        t->tm_hour, t->tm_min, t->tm_sec);
    ofstream file("security_log.txt", ios::app);
    if (file.is_open())
    {
        file << timestamp << "," << role << "," << enteredId << "," << result << ","
            << attemptCount << "," << (isLocked ? "YES" : "NO") << endl;
        file.close();
    }
}

bool FileHandler::checkLoginAttempts(int userId, const char* role)
{
    ifstream file("login_attempts.txt");
    if (!file.is_open())
    {
        ofstream outFile("login_attempts.txt");
        outFile.close();
        return true;
    }
    char lines[1000][MAX_LINE_LEN];
    int lineCount = 0;
    while (file.getline(lines[lineCount], MAX_LINE_LEN) && lineCount < 1000)
        lineCount++;
    file.close();
    for (int i = 0; i < lineCount; i++)
    {
        char* fields[MAX_FIELDS];
        parseLine(lines[i], fields, MAX_FIELDS);
        if (fields[0] && fields[1])
        {
            int id = stringToInt(fields[0]);
            if (id == userId)
            {
                if (fields[3] && fields[3][0] == '1')
                    return false;
                else
                    return true;
            }
        }
    }
    return true;
}

void FileHandler::resetLoginAttempts(int userId, const char* role)
{
    ifstream file("login_attempts.txt");
    if (!file.is_open()) return;
    char lines[1000][MAX_LINE_LEN];
    int lineCount = 0;
    while (file.getline(lines[lineCount], MAX_LINE_LEN) && lineCount < 1000)
        lineCount++;
    file.close();
    ofstream outFile("login_attempts.txt");
    if (!outFile.is_open()) return;
    bool found = false;
    for (int i = 0; i < lineCount; i++)
    {
        char* fields[MAX_FIELDS];
        parseLine(lines[i], fields, MAX_FIELDS);
        int currentId = (fields[0]) ? stringToInt(fields[0]) : -1;
        if (currentId == userId)
        {
            outFile << userId << "," << role << ",0,0" << endl;
            found = true;
        }
        else
        {
            outFile << lines[i];
        }
    }
    if (!found)
        outFile << userId << "," << role << ",0,0" << endl;
    outFile.close();
}

void FileHandler::incrementLoginAttempt(int userId, const char* role)
{
    ifstream file("login_attempts.txt");
    if (!file.is_open())
    {
        ofstream outFile("login_attempts.txt");
        if (outFile.is_open())
        {
            outFile << userId << "," << role << ",1,0" << endl;
            outFile.close();
        }
        return;
    }
    char lines[1000][MAX_LINE_LEN];
    int lineCount = 0;
    while (file.getline(lines[lineCount], MAX_LINE_LEN) && lineCount < 1000)
        lineCount++;
    file.close();
    ofstream outFile("login_attempts.txt");
    if (!outFile.is_open()) return;
    bool found = false;
    for (int i = 0; i < lineCount; i++)
    {
        char* fields[MAX_FIELDS];
        parseLine(lines[i], fields, MAX_FIELDS);
        int currentId = (fields[0]) ? stringToInt(fields[0]) : -1;
        if (currentId == userId)
        {
            int attempts = (fields[2]) ? stringToInt(fields[2]) : 0;
            attempts++;
            int isLocked = (attempts >= 3) ? 1 : 0;
            outFile << userId << "," << role << "," << attempts << "," << isLocked << endl;
            found = true;
        }
        else
        {
            outFile << lines[i];
        }
    }
    if (!found)
        outFile << userId << "," << role << ",1,0" << endl;
    outFile.close();
}