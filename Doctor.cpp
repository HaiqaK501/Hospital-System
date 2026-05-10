
#pragma warning(disable : 4996)
#include "Doctor.h"
#include "Patient.h"
#include "Nurse.h"
#include "Ward.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "Validator.h"
#include "FileHandler.h"
#include <iostream>
#include <ctime>
#include "InsufficeintFundsException.h"
#include "InvalidInputException.h"
#include "SlotUnavailableException.h"

using namespace std;

void Doctor::copyString(char*& dest, const char* src)
{
    if (dest) delete[] dest;
    if (!src)
    {
        dest = new char[1];
        dest[0] = '\0';
        return;
    }
    int len = 0;
    while (src[len] != '\0') len++;
    dest = new char[len + 1];
    for (int i = 0; i < len; i++) dest[i] = src[i];
    dest[len] = '\0';
}

void Doctor::resizePatientArray(int newSize)
{
    if (newSize <= maxPatients) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < assignedPatientCount; i++) newArray[i] = assignedPatientIds[i];
    for (int i = assignedPatientCount; i < newSize; i++) newArray[i] = 0;
    delete[] assignedPatientIds;
    assignedPatientIds = newArray;
    maxPatients = newSize;
}

void Doctor::resizeNurseArray(int newSize)
{
    if (newSize <= maxNurses) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < assignedNurseCount; i++) newArray[i] = assignedNurseIds[i];
    for (int i = assignedNurseCount; i < newSize; i++) newArray[i] = 0;
    delete[] assignedNurseIds;
    assignedNurseIds = newArray;
    maxNurses = newSize;
}

void Doctor::resizeWardArray(int newSize)
{
    if (newSize <= maxWards) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < assignedWardCount; i++) newArray[i] = assignedWardIds[i];
    for (int i = assignedWardCount; i < newSize; i++) newArray[i] = 0;
    delete[] assignedWardIds;
    assignedWardIds = newArray;
    maxWards = newSize;
}

void Doctor::resizeAppointmentArray(int newSize)
{
    if (newSize <= maxAppointments) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < appointmentCount; i++) newArray[i] = appointmentIds[i];
    for (int i = appointmentCount; i < newSize; i++) newArray[i] = 0;
    delete[] appointmentIds;
    appointmentIds = newArray;
    maxAppointments = newSize;
}

int Doctor::compareDates(const char* date1, const char* date2) const
{
    int day1 = (date1[0] - '0') * 10 + (date1[1] - '0');
    int month1 = (date1[3] - '0') * 10 + (date1[4] - '0');
    int year1 = (date1[6] - '0') * 1000 + (date1[7] - '0') * 100 + (date1[8] - '0') * 10 + (date1[9] - '0');

    int day2 = (date2[0] - '0') * 10 + (date2[1] - '0');
    int month2 = (date2[3] - '0') * 10 + (date2[4] - '0');
    int year2 = (date2[6] - '0') * 1000 + (date2[7] - '0') * 100 + (date2[8] - '0') * 10 + (date2[9] - '0');

    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}

bool Doctor::isToday(const char* appointmentDate, const char* todayDate) const
{
    return (compareDates(appointmentDate, todayDate) == 0);
}



Doctor::Doctor() : Person()
{
    specialization = new char[1]; specialization[0] = '\0';
    education = new char[1]; education[0] = '\0';
    hospitalBranch = new char[1]; hospitalBranch[0] = '\0';

    consultationFee = 0.0f;
    yearsOfExperience = 0;
    rating = 0.0f;
    totalPatientsTreated = 0;
    isAvailable = true;

    assignedPatientCount = 0;
    maxPatients = 20;
    assignedPatientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++) assignedPatientIds[i] = 0;

    assignedNurseCount = 0;
    maxNurses = 5;
    assignedNurseIds = new int[maxNurses];
    for (int i = 0; i < maxNurses; i++) assignedNurseIds[i] = 0;

    assignedWardCount = 0;
    maxWards = 3;
    assignedWardIds = new int[maxWards];
    for (int i = 0; i < maxWards; i++) assignedWardIds[i] = 0;

    appointmentCount = 0;
    maxAppointments = 30;
    appointmentIds = new int[maxAppointments];
    for (int i = 0; i < maxAppointments; i++) appointmentIds[i] = 0;
}

Doctor::Doctor(int id, const char* nameVal, const char* passVal, const char* spec,
    float fee, int experience, const char* edu, const char* branch)
    : Person(id, nameVal, passVal)
{
    copyString(specialization, spec);
    copyString(education, edu);
    copyString(hospitalBranch, branch);

    consultationFee = fee;
    yearsOfExperience = experience;
    rating = 0.0f;
    totalPatientsTreated = 0;
    isAvailable = true;

    assignedPatientCount = 0;
    maxPatients = 20;
    assignedPatientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++) assignedPatientIds[i] = 0;

    assignedNurseCount = 0;
    maxNurses = 5;
    assignedNurseIds = new int[maxNurses];
    for (int i = 0; i < maxNurses; i++) assignedNurseIds[i] = 0;

    assignedWardCount = 0;
    maxWards = 3;
    assignedWardIds = new int[maxWards];
    for (int i = 0; i < maxWards; i++) assignedWardIds[i] = 0;

    appointmentCount = 0;
    maxAppointments = 30;
    appointmentIds = new int[maxAppointments];
    for (int i = 0; i < maxAppointments; i++) appointmentIds[i] = 0;
}

Doctor::Doctor(const Doctor& other) : Person(other)
{
    copyString(specialization, other.specialization);
    copyString(education, other.education);
    copyString(hospitalBranch, other.hospitalBranch);

    consultationFee = other.consultationFee;
    rating = other.rating;
    totalPatientsTreated = other.totalPatientsTreated;
    yearsOfExperience = other.yearsOfExperience;
    isAvailable = other.isAvailable;

    assignedPatientCount = other.assignedPatientCount;
    maxPatients = other.maxPatients;
    assignedPatientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++) assignedPatientIds[i] = other.assignedPatientIds[i];

    assignedNurseCount = other.assignedNurseCount;
    maxNurses = other.maxNurses;
    assignedNurseIds = new int[maxNurses];
    for (int i = 0; i < maxNurses; i++) assignedNurseIds[i] = other.assignedNurseIds[i];

    assignedWardCount = other.assignedWardCount;
    maxWards = other.maxWards;
    assignedWardIds = new int[maxWards];
    for (int i = 0; i < maxWards; i++) assignedWardIds[i] = other.assignedWardIds[i];

    appointmentCount = other.appointmentCount;
    maxAppointments = other.maxAppointments;
    appointmentIds = new int[maxAppointments];
    for (int i = 0; i < maxAppointments; i++) appointmentIds[i] = other.appointmentIds[i];
}

Doctor& Doctor::operator=(const Doctor& other)
{
    if (this == &other) return *this;
    Person::operator=(other);

    copyString(specialization, other.specialization);
    copyString(education, other.education);
    copyString(hospitalBranch, other.hospitalBranch);

    consultationFee = other.consultationFee;
    rating = other.rating;
    totalPatientsTreated = other.totalPatientsTreated;
    yearsOfExperience = other.yearsOfExperience;
    isAvailable = other.isAvailable;

    assignedPatientCount = other.assignedPatientCount;
    if (maxPatients < other.maxPatients)
    {
        delete[] assignedPatientIds;
        maxPatients = other.maxPatients;
        assignedPatientIds = new int[maxPatients];
    }
    for (int i = 0; i < maxPatients; i++) assignedPatientIds[i] = other.assignedPatientIds[i];

    assignedNurseCount = other.assignedNurseCount;
    if (maxNurses < other.maxNurses)
    {
        delete[] assignedNurseIds;
        maxNurses = other.maxNurses;
        assignedNurseIds = new int[maxNurses];
    }
    for (int i = 0; i < maxNurses; i++) assignedNurseIds[i] = other.assignedNurseIds[i];

    assignedWardCount = other.assignedWardCount;
    if (maxWards < other.maxWards)
    {
        delete[] assignedWardIds;
        maxWards = other.maxWards;
        assignedWardIds = new int[maxWards];
    }
    for (int i = 0; i < maxWards; i++) assignedWardIds[i] = other.assignedWardIds[i];

    appointmentCount = other.appointmentCount;
    if (maxAppointments < other.maxAppointments)
    {
        delete[] appointmentIds;
        maxAppointments = other.maxAppointments;
        appointmentIds = new int[maxAppointments];
    }
    for (int i = 0; i < maxAppointments; i++) appointmentIds[i] = other.appointmentIds[i];

    return *this;
}

Doctor::~Doctor()
{
    delete[] specialization;
    delete[] education;
    delete[] hospitalBranch;
    delete[] assignedPatientIds;
    delete[] assignedNurseIds;
    delete[] assignedWardIds;
    delete[] appointmentIds;
}

// ========== GETTERS ==========

const char* Doctor::getSpecialization() const { return specialization; }
float Doctor::getFee() const { return consultationFee; }
const char* Doctor::getEducation() const { return education; }
const char* Doctor::getHospitalBranch() const { return hospitalBranch; }
int Doctor::getYearsOfExperience() const { return yearsOfExperience; }
float Doctor::getRating() const { return rating; }
int Doctor::getTotalPatientsTreated() const { return totalPatientsTreated; }
bool Doctor::getIsAvailable() const { return isAvailable; }
int Doctor::getAssignedPatientCount() const { return assignedPatientCount; }
int Doctor::getAssignedNurseCount() const { return assignedNurseCount; }
int Doctor::getAssignedWardCount() const { return assignedWardCount; }
int Doctor::getAppointmentCount() const { return appointmentCount; }

// ========== SETTERS ==========

void Doctor::setSpecialization(const char* spec) { copyString(specialization, spec); }
void Doctor::setFee(float fee) { consultationFee = fee; }
void Doctor::setEducation(const char* edu) { copyString(education, edu); }
void Doctor::setHospitalBranch(const char* branch) { copyString(hospitalBranch, branch); }
void Doctor::setRating(float r) { if (r >= 0 && r <= 5) rating = r; }
void Doctor::setIsAvailable(bool available) { isAvailable = available; }
void Doctor::addExperience(int years) { yearsOfExperience += years; }
void Doctor::incrementPatientsTreated() { totalPatientsTreated++; }

// ========== PATIENT MANAGEMENT ==========

bool Doctor::assignPatient(int patientId)
{
    if (assignedPatientCount >= maxPatients) resizePatientArray(maxPatients + 10);
    for (int i = 0; i < assignedPatientCount; i++)
        if (assignedPatientIds[i] == patientId) return false;
    assignedPatientIds[assignedPatientCount] = patientId;
    assignedPatientCount++;
    return true;
}

bool Doctor::removePatient(int patientId)
{
    for (int i = 0; i < assignedPatientCount; i++)
    {
        if (assignedPatientIds[i] == patientId)
        {
            for (int j = i; j < assignedPatientCount - 1; j++)
                assignedPatientIds[j] = assignedPatientIds[j + 1];
            assignedPatientCount--;
            return true;
        }
    }
    return false;
}

const int* Doctor::getAssignedPatientIds() const { return assignedPatientIds; }
bool Doctor::consultWithPatient(Patient& patient) { return assignPatient(patient.getID()); }

void Doctor::viewAssignedPatients(Storage<Patient>& patientStorage) const
{
    cout << "\n========== ASSIGNED PATIENTS ==========" << endl;
    cout << "Doctor: ";
    const char* docName = getName().get();
    cout << docName << endl;
    cout << "Total Patients: " << assignedPatientCount << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < assignedPatientCount; i++)
    {
        for (int j = 0; j < patientStorage.getCount(); j++)
        {
            Patient* p = patientStorage.getAll()[j];
            if (p && p->getID() == assignedPatientIds[i])
            {
                cout << "ID: " << p->getID() << " | Name: ";
                const char* patName = p->getName().get();
                cout << patName;
                cout << " | Age: " << p->getAge() << endl;
                break;
            }
        }
    }
    cout << "========================================" << endl;
}

// ========== NURSE MANAGEMENT (RELATIONSHIP) ==========

bool Doctor::assignNurse(int nurseId)
{
    if (assignedNurseCount >= maxNurses) resizeNurseArray(maxNurses + 3);
    for (int i = 0; i < assignedNurseCount; i++)
        if (assignedNurseIds[i] == nurseId) return false;
    assignedNurseIds[assignedNurseCount] = nurseId;
    assignedNurseCount++;
    return true;
}

bool Doctor::removeNurse(int nurseId)
{
    for (int i = 0; i < assignedNurseCount; i++)
    {
        if (assignedNurseIds[i] == nurseId)
        {
            for (int j = i; j < assignedNurseCount - 1; j++)
                assignedNurseIds[j] = assignedNurseIds[j + 1];
            assignedNurseCount--;
            return true;
        }
    }
    return false;
}

const int* Doctor::getAssignedNurseIds() const { return assignedNurseIds; }
bool Doctor::superviseNurse(Nurse& nurse) { return assignNurse(nurse.getID()); }

void Doctor::viewAssignedNurses(Storage<Nurse>& nurseStorage) const
{
    cout << "\n========== ASSIGNED NURSES ==========" << endl;
    cout << "Doctor: ";
    const char* docName = getName().get();
    cout << docName << endl;
    cout << "Total Nurses: " << assignedNurseCount << endl;
    cout << "--------------------------------------" << endl;

    for (int i = 0; i < assignedNurseCount; i++)
    {
        for (int j = 0; j < nurseStorage.getCount(); j++)
        {
            Nurse* n = nurseStorage.getAll()[j];
            if (n && n->getID() == assignedNurseIds[i])
            {
                cout << "ID: " << n->getID() << " | Name: ";
                const char* nurseName = n->getName().get();
                cout << nurseName;
                cout << " | Specialization: " << n->getSpecialization() << endl;
                break;
            }
        }
    }
    cout << "======================================" << endl;
}

// ========== WARD MANAGEMENT (RELATIONSHIP) ==========

bool Doctor::assignToWard(int wardId)
{
    if (assignedWardCount >= maxWards) resizeWardArray(maxWards + 2);
    for (int i = 0; i < assignedWardCount; i++)
        if (assignedWardIds[i] == wardId) return false;
    assignedWardIds[assignedWardCount] = wardId;
    assignedWardCount++;
    return true;
}

bool Doctor::removeFromWard(int wardId)
{
    for (int i = 0; i < assignedWardCount; i++)
    {
        if (assignedWardIds[i] == wardId)
        {
            for (int j = i; j < assignedWardCount - 1; j++)
                assignedWardIds[j] = assignedWardIds[j + 1];
            assignedWardCount--;
            return true;
        }
    }
    return false;
}

const int* Doctor::getAssignedWardIds() const { return assignedWardIds; }
bool Doctor::workInWard(Ward& ward) { return assignToWard(ward.getWardId()); }

void Doctor::viewAssignedWards(Storage<Ward>& wardStorage) const
{
    cout << "\n========== ASSIGNED WARDS ==========" << endl;
    cout << "Doctor: ";
    const char* docName = getName().get();
    cout << docName << endl;
    cout << "Total Wards: " << assignedWardCount << endl;
    cout << "------------------------------------" << endl;

    for (int i = 0; i < assignedWardCount; i++)
    {
        for (int j = 0; j < wardStorage.getCount(); j++)
        {
            Ward* w = wardStorage.getAll()[j];
            if (w && w->getWardId() == assignedWardIds[i])
            {
                cout << "ID: " << w->getWardId() << " | Name: " << w->getWardName()
                    << " | Type: " << w->getWardType() << endl;
                break;
            }
        }
    }
    cout << "====================================" << endl;
}

// ========== APPOINTMENT MANAGEMENT ==========

bool Doctor::addAppointment(int appointmentId)
{
    if (appointmentCount >= maxAppointments) resizeAppointmentArray(maxAppointments + 10);
    for (int i = 0; i < appointmentCount; i++)
        if (appointmentIds[i] == appointmentId) return false;
    appointmentIds[appointmentCount] = appointmentId;
    appointmentCount++;
    return true;
}

bool Doctor::removeAppointment(int appointmentId)
{
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointmentIds[i] == appointmentId)
        {
            for (int j = i; j < appointmentCount - 1; j++)
                appointmentIds[j] = appointmentIds[j + 1];
            appointmentCount--;
            return true;
        }
    }
    return false;
}

const int* Doctor::getAppointmentIds() const { return appointmentIds; }

// ========== REQUIRED FUNCTION 1: VIEW TODAY'S APPOINTMENTS ==========

void Doctor::viewTodayAppointments(Storage<Appointment>& appointmentStorage,
    Storage<Patient>& patientStorage, const char* todayDate)
{
    cout << "\n========== TODAY'S APPOINTMENTS ==========" << endl;
    cout << "Doctor: ";
    const char* docName = getName().get();
    cout << docName << endl;
    cout << "Date: " << todayDate << endl;
    cout << "-------------------------------------------" << endl;

    Appointment* todayApps[50];
    int appCount = 0;

    for (int i = 0; i < appointmentStorage.getCount(); i++)
    {
        Appointment* app = appointmentStorage.getAll()[i];
        if (app && app->getDoctorId() == id && isToday(app->getDate(), todayDate))
        {
            todayApps[appCount] = app;
            appCount++;
        }
    }

    if (appCount == 0)
    {
        cout << "No appointments scheduled for today." << endl;
        cout << "===========================================" << endl;
        return;
    }

    // Sort by time slot ascending
    for (int i = 0; i < appCount - 1; i++)
    {
        for (int j = 0; j < appCount - i - 1; j++)
        {
            if (strcmp(todayApps[j]->getTimeSlot(), todayApps[j + 1]->getTimeSlot()) > 0)
            {
                Appointment* temp = todayApps[j];
                todayApps[j] = todayApps[j + 1];
                todayApps[j + 1] = temp;
            }
        }
    }

    cout << "Appointment ID | Patient Name | Time Slot | Status" << endl;

    for (int i = 0; i < appCount; i++)
    {
        Appointment* app = todayApps[i];
        const char* patientName = "Unknown";

        for (int j = 0; j < patientStorage.getCount(); j++)
        {
            Patient* p = patientStorage.getAll()[j];
            if (p && p->getID() == app->getPatientId())
            {
                patientName = p->getName().get();
                break;
            }
        }

        cout << "  " << app->getAppointmentId() << " | " << patientName
            << " | " << app->getTimeSlot() << " | " << app->getStatus() << endl;
    }
    cout << "===========================================" << endl;
}

// ========== REQUIRED FUNCTION 2: MARK APPOINTMENT COMPLETE ==========

void Doctor::markAppointmentComplete(Storage<Appointment>& appointmentStorage,
    Storage<Bill>& billStorage)
{
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char todayDate[11];
    strftime(todayDate, 11, "%d-%m-%Y", t);

    cout << "\n========== TODAY'S PENDING APPOINTMENTS ==========" << endl;

    Appointment* pendingApps[50];
    int pendingCount = 0;

    for (int i = 0; i < appointmentStorage.getCount(); i++)
    {
        Appointment* app = appointmentStorage.getAll()[i];
        if (app && app->getDoctorId() == id && isToday(app->getDate(), todayDate) &&
            Validator::compareCaseInsensitive(app->getStatus(), "pending"))
        {
            pendingApps[pendingCount] = app;
            pendingCount++;
            cout << "  ID: " << app->getAppointmentId() << " | Patient ID: " << app->getPatientId()
                << " | Time: " << app->getTimeSlot() << endl;
        }
    }

    if (pendingCount == 0)
    {
        cout << "No pending appointments for today." << endl;
        return;
    }

    int appointmentId;
    cout << "\nEnter Appointment ID to mark as complete: ";
    cin >> appointmentId;

    Appointment* selectedApp = nullptr;
    for (int i = 0; i < pendingCount; i++)
    {
        if (pendingApps[i]->getAppointmentId() == appointmentId)
        {
            selectedApp = pendingApps[i];
            break;
        }
    }

    if (!selectedApp)
    {
        cout << "Invalid appointment ID." << endl;
        return;
    }

    selectedApp->markCompleted();
    FileHandler::updateAppointmentStatus(appointmentId, "completed");

    cout << "Appointment marked as completed." << endl;
}

// ========== REQUIRED FUNCTION 3: MARK APPOINTMENT NO-SHOW ==========

void Doctor::markAppointmentNoShow(Storage<Appointment>& appointmentStorage,
    Storage<Bill>& billStorage)
{
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char todayDate[11];
    sprintf(todayDate, "%02d-%02d-%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);

    cout << "\n========== TODAY'S PENDING APPOINTMENTS ==========" << endl;

    Appointment* pendingApps[50];
    int pendingCount = 0;

    for (int i = 0; i < appointmentStorage.getCount(); i++)
    {
        Appointment* app = appointmentStorage.getAll()[i];
        if (app && app->getDoctorId() == id && isToday(app->getDate(), todayDate) &&
            Validator::compareCaseInsensitive(app->getStatus(), "pending"))
        {
            pendingApps[pendingCount] = app;
            pendingCount++;
            cout << "  ID: " << app->getAppointmentId() << " | Patient ID: " << app->getPatientId()
                << " | Time: " << app->getTimeSlot() << endl;
        }
    }

    if (pendingCount == 0)
    {
        cout << "No pending appointments for today." << endl;
        return;
    }

    int appointmentId;
    cout << "\nEnter Appointment ID to mark as no-show: ";
    cin >> appointmentId;

    Appointment* selectedApp = nullptr;
    for (int i = 0; i < pendingCount; i++)
    {
        if (pendingApps[i]->getAppointmentId() == appointmentId)
        {
            selectedApp = pendingApps[i];
            break;
        }
    }

    if (!selectedApp)
    {
        cout << "Invalid appointment ID." << endl;
        return;
    }

    selectedApp->markNoShow();
    FileHandler::updateAppointmentStatus(appointmentId, "no-show");

    for (int i = 0; i < billStorage.getCount(); i++)
    {
        Bill* bill = billStorage.getAll()[i];
        if (bill && bill->getAppointmentId() == appointmentId)
        {
            bill->markAsCancelled();
            FileHandler::updateBillStatus(bill->getBillId(), "cancelled");
            break;
        }
    }

    cout << "Appointment marked as no-show. Bill has been cancelled." << endl;
}

// ========== REQUIRED FUNCTION 4: WRITE PRESCRIPTION ==========

void Doctor::writePrescription(Storage<Appointment>& appointmentStorage,
    Storage<Prescription>& prescriptionStorage,
    Storage<Patient>& patientStorage)
{
    int appointmentId;
    cout << "Enter Appointment ID: ";
    cin >> appointmentId;

    Appointment* selectedApp = nullptr;
    Patient* associatedPatient = nullptr;

    for (int i = 0; i < appointmentStorage.getCount(); i++)
    {
        Appointment* app = appointmentStorage.getAll()[i];
        if (app && app->getAppointmentId() == appointmentId && app->getDoctorId() == id)
        {
            if (Validator::compareCaseInsensitive(app->getStatus(), "completed"))
            {
                selectedApp = app;
                break;
            }
        }
    }

    if (!selectedApp)
    {
        cout << "Invalid appointment ID or appointment not completed." << endl;
        return;
    }

    for (int i = 0; i < prescriptionStorage.getCount(); i++)
    {
        Prescription* pres = prescriptionStorage.getAll()[i];
        if (pres && pres->getAppointmentId() == appointmentId)
        {
            cout << "Prescription already written for this appointment." << endl;
            return;
        }
    }

    for (int i = 0; i < patientStorage.getCount(); i++)
    {
        Patient* p = patientStorage.getAll()[i];
        if (p && p->getID() == selectedApp->getPatientId())
        {
            associatedPatient = p;
            break;
        }
    }

    char medicines[500];
    cout << "Enter medicines (format: Paracetamol 500mg;Amoxicillin 250mg): ";
    cin.ignore();
    cin.getline(medicines, 500);

    char notes[300];
    cout << "Enter notes (max 300 chars): ";
    cin.getline(notes, 300);

    int newPrescriptionId = 1;
    for (int i = 0; i < prescriptionStorage.getCount(); i++)
    {
        Prescription* pres = prescriptionStorage.getAll()[i];
        if (pres && pres->getPrescriptionId() >= newPrescriptionId)
            newPrescriptionId = pres->getPrescriptionId() + 1;
    }

    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char todayDate[11];
    sprintf(todayDate, "%02d-%02d-%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);

    Prescription* newPrescription = new Prescription(newPrescriptionId, appointmentId,
        selectedApp->getPatientId(), id,
        todayDate, medicines, notes);
    prescriptionStorage.add(newPrescription);
    FileHandler::savePrescription(*newPrescription);

    if (associatedPatient)
    {
        associatedPatient->updateMedicalHistory(medicines);
    }

    cout << "Prescription saved. Prescription ID: " << newPrescriptionId << endl;
}

// ========== REQUIRED FUNCTION 5: VIEW PATIENT MEDICAL HISTORY ==========

void Doctor::viewPatientMedicalHistory(Storage<Patient>& patientStorage,
    Storage<Prescription>& prescriptionStorage,
    Storage<Doctor>& doctorStorage)
{
    int patientId;
    cout << "Enter Patient ID: ";
    cin >> patientId;

    Patient* selectedPatient = nullptr;
    bool hasCompletedAppointment = false;

    for (int i = 0; i < patientStorage.getCount(); i++)
    {
        Patient* p = patientStorage.getAll()[i];
        if (p && p->getID() == patientId)
        {
            selectedPatient = p;
            break;
        }
    }

    if (!selectedPatient)
    {
        cout << "Patient not found." << endl;
        return;
    }

    for (int i = 0; i < prescriptionStorage.getCount(); i++)
    {
        Prescription* pres = prescriptionStorage.getAll()[i];
        if (pres && pres->getPatientId() == patientId && pres->getDoctorId() == id)
        {
            hasCompletedAppointment = true;
            break;
        }
    }

    if (!hasCompletedAppointment)
    {
        cout << "Access denied. You can only view records of your own patients." << endl;
        return;
    }

    Prescription* patientPrescriptions[100];
    int presCount = 0;

    for (int i = 0; i < prescriptionStorage.getCount(); i++)
    {
        Prescription* pres = prescriptionStorage.getAll()[i];
        if (pres && pres->getPatientId() == patientId && pres->getDoctorId() == id)
        {
            patientPrescriptions[presCount] = pres;
            presCount++;
        }
    }

    for (int i = 0; i < presCount - 1; i++)
    {
        for (int j = 0; j < presCount - i - 1; j++)
        {
            int day1 = (patientPrescriptions[j]->getDate()[0] - '0') * 10 + (patientPrescriptions[j]->getDate()[1] - '0');
            int month1 = (patientPrescriptions[j]->getDate()[3] - '0') * 10 + (patientPrescriptions[j]->getDate()[4] - '0');
            int year1 = (patientPrescriptions[j]->getDate()[6] - '0') * 1000 +
                (patientPrescriptions[j]->getDate()[7] - '0') * 100 +
                (patientPrescriptions[j]->getDate()[8] - '0') * 10 +
                (patientPrescriptions[j]->getDate()[9] - '0');

            int day2 = (patientPrescriptions[j + 1]->getDate()[0] - '0') * 10 + (patientPrescriptions[j + 1]->getDate()[1] - '0');
            int month2 = (patientPrescriptions[j + 1]->getDate()[3] - '0') * 10 + (patientPrescriptions[j + 1]->getDate()[4] - '0');
            int year2 = (patientPrescriptions[j + 1]->getDate()[6] - '0') * 1000 +
                (patientPrescriptions[j + 1]->getDate()[7] - '0') * 100 +
                (patientPrescriptions[j + 1]->getDate()[8] - '0') * 10 +
                (patientPrescriptions[j + 1]->getDate()[9] - '0');

            int totalDays1 = year1 * 365 + month1 * 30 + day1;
            int totalDays2 = year2 * 365 + month2 * 30 + day2;

            if (totalDays1 < totalDays2)
            {
                Prescription* temp = patientPrescriptions[j];
                patientPrescriptions[j] = patientPrescriptions[j + 1];
                patientPrescriptions[j + 1] = temp;
            }
        }
    }

    cout << "\n========== PATIENT MEDICAL HISTORY ==========" << endl;
    cout << "Patient: ";
    const char* patName = selectedPatient->getName().get();
    cout << patName << endl;
    cout << "Doctor: ";
    const char* docName = getName().get();
    cout << docName << endl;
    cout << "---------------------------------------------" << endl;

    if (presCount == 0)
    {
        cout << "No prescriptions found for this patient." << endl;
    }
    else
    {
        for (int i = 0; i < presCount; i++)
        {
            Prescription* pres = patientPrescriptions[i];
            cout << "Date: " << pres->getDate() << endl;
            cout << "Medicines: " << pres->getMedicines() << endl;
            cout << "Notes: " << pres->getNotes() << endl;
            cout << "---------------------------------------------" << endl;
        }
    }
    cout << "=============================================" << endl;
}

// ========== ADDITIONAL FEATURES ==========

void Doctor::updateAvailability()
{
    isAvailable = !isAvailable;
    cout << "Availability updated. Current status: " << (isAvailable ? "Available" : "Not Available") << endl;
}

void Doctor::viewMyStatistics() const
{
    cout << "\n========== DOCTOR STATISTICS ==========" << endl;
    cout << "Name: ";
    const char* docName = getName().get();
    cout << docName << endl;
    cout << "Specialization: " << specialization << endl;
    cout << "Total Patients Treated: " << totalPatientsTreated << endl;
    cout << "Current Patients: " << assignedPatientCount << endl;
    cout << "Rating: " << rating << "/5.0" << endl;
    cout << "Success Rate: " << getSuccessRate() << "%" << endl;
    cout << "Years of Experience: " << yearsOfExperience << endl;
    cout << "Top Performer: " << (isTopPerformer() ? "Yes" : "No") << endl;
    cout << "Annual Earnings: Rs. " << calculateAnnualEarnings() << endl;
    cout << "=======================================" << endl;
}

void Doctor::viewFinancialSummary() const
{
    cout << "\n========== FINANCIAL SUMMARY ==========" << endl;
    cout << "Doctor: ";
    const char* docName = getName().get();
    cout << docName << endl;
    cout << "Consultation Fee: Rs. " << consultationFee << endl;
    cout << "Total Appointments: " << appointmentCount << endl;
    cout << "Estimated Annual Earnings: Rs. " << calculateAnnualEarnings() << endl;
    cout << "Bonus: Rs. " << calculateBonus() << endl;
    cout << "Total Annual Compensation: Rs. " << (calculateAnnualEarnings() + calculateBonus()) << endl;
    cout << "========================================" << endl;
}

bool Doctor::canTakeMorePatients() const
{
    return assignedPatientCount < maxPatients;
}

void Doctor::updateRating(float newRating)
{
    if (newRating >= 0 && newRating <= 5)
    {
        rating = (rating * totalPatientsTreated + newRating) / (totalPatientsTreated + 1);
        cout << "Rating updated to: " << rating << "/5" << endl;
    }
}

float Doctor::getSuccessRate() const
{
    if (totalPatientsTreated == 0) return 0;
    return (rating / 5.0f) * 100;
}

bool Doctor::isTopPerformer() const
{
    return (rating >= 4.5 && totalPatientsTreated > 100);
}

float Doctor::calculateBonus() const
{
    float bonus = 0;
    if (totalPatientsTreated > 200) bonus += consultationFee * 10;
    else if (totalPatientsTreated > 100) bonus += consultationFee * 5;
    if (rating >= 4.5) bonus += consultationFee * 3;
    else if (rating >= 4.0) bonus += consultationFee * 2;
    if (yearsOfExperience > 10) bonus += consultationFee * 5;
    return bonus;
}

float Doctor::calculateAnnualEarnings() const
{
    float weeklyEarnings = consultationFee * 20;
    return weeklyEarnings * 48;
}

int Doctor::getTodayAppointmentCount(const char* todayDate, Storage<Appointment>& appointmentStorage) const
{
    int count = 0;
    for (int i = 0; i < appointmentStorage.getCount(); i++)
    {
        Appointment* app = appointmentStorage.getAll()[i];
        if (app && app->getDoctorId() == id && isToday(app->getDate(), todayDate))
            count++;
    }
    return count;
}

bool Doctor::isAvailableForAppointment(const char* date, const char* timeSlot) const
{
    return isAvailable;
}

// ========== REQUIRED OPERATORS ==========

bool Doctor::operator==(const Doctor& other) const
{
    return (id == other.id);
}

ostream& operator<<(ostream& os, const Doctor& doctor)
{
    os << "Dr. " << doctor.getName().get();
    os << " (" << doctor.getSpecialization() << ") - Fee: Rs. " << doctor.getFee();
    return os;
}

// ========== DISPLAY METHODS ==========

void Doctor::display() const
{
    cout << "Doctor ID: " << id << " | Dr. ";
    const char* docName = getName().get();
    cout << docName;
    cout << " | Specialization: " << specialization;
    cout << " | Fee: Rs. " << consultationFee;
    cout << " | Rating: " << rating;
    cout << " | Available: " << (isAvailable ? "Yes" : "No") << endl;
}

void Doctor::showMenu()
{
    cout << "\n========== DOCTOR MENU ==========" << endl;
    cout << "1. View Today's Appointments" << endl;
    cout << "2. Mark Appointment Complete" << endl;
    cout << "3. Mark Appointment No-Show" << endl;
    cout << "4. Write Prescription" << endl;
    cout << "5. View Patient Medical History" << endl;
    cout << "6. View My Assigned Patients" << endl;
    cout << "7. View Assigned Nurses" << endl;
    cout << "8. View Assigned Wards" << endl;
    cout << "9. Update Availability" << endl;
    cout << "10. View My Statistics" << endl;
    cout << "11. View Financial Summary" << endl;
    cout << "12. Change Password" << endl;
    cout << "13. Logout" << endl;
    cout << "================================" << endl;
}

void Doctor::displayInfo() const
{
    cout << "ID: " << id << " | Dr. ";
    const char* docName = getName().get();
    cout << docName;
    cout << " | Role: DOCTOR";
    cout << " | Specialization: " << specialization;
    cout << " | Fee: Rs. " << consultationFee;
    cout << " | Rating: " << rating;
    cout << " | Patients: " << assignedPatientCount << endl;
}

void Doctor::displayFullDetails() const
{
    cout << "\n========== DOCTOR FULL DETAILS ==========" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: Dr. ";
    const char* docName = getName().get();
    cout << docName << endl;
    cout << "Specialization: " << specialization << endl;
    cout << "Consultation Fee: Rs. " << consultationFee << endl;
    cout << "Education: " << education << endl;
    cout << "Hospital Branch: " << hospitalBranch << endl;
    cout << "Years of Experience: " << yearsOfExperience << endl;
    cout << "Total Patients Treated: " << totalPatientsTreated << endl;
    cout << "Rating: " << rating << "/5.0" << endl;
    cout << "Success Rate: " << getSuccessRate() << "%" << endl;
    cout << "Status: " << (isAvailable ? "Available" : "Not Available") << endl;
    cout << "Current Patients: " << assignedPatientCount << "/" << maxPatients << endl;
    cout << "Assigned Nurses: " << assignedNurseCount << endl;
    cout << "Assigned Wards: " << assignedWardCount << endl;
    cout << "Total Appointments: " << appointmentCount << endl;
    cout << "Annual Earnings: Rs. " << calculateAnnualEarnings() << endl;
    cout << "Bonus: Rs. " << calculateBonus() << endl;
    cout << "Top Performer: " << (isTopPerformer() ? "Yes" : "No") << endl;
    cout << "==========================================" << endl;
}

void Doctor::displayInfoToBuffer(char* buffer, int bufferSize) const
{
    if (!buffer || bufferSize <= 0) return;
    int idx = 0;
    const char* prefix = "Dr. ";
    for (int i = 0; prefix[i] != '\0' && idx < bufferSize - 1; i++) buffer[idx++] = prefix[i];

    const char* nameStr = getName().get();
    for (int i = 0; nameStr[i] != '\0' && idx < bufferSize - 1; i++) buffer[idx++] = nameStr[i];

    const char* suffix = " (";
    for (int i = 0; suffix[i] != '\0' && idx < bufferSize - 1; i++) buffer[idx++] = suffix[i];

    if (id == 0) buffer[idx++] = '0';
    else
    {
        int digits[10], digitCount = 0, temp = id;
        while (temp > 0) { digits[digitCount++] = temp % 10; temp /= 10; }
        for (int i = digitCount - 1; i >= 0 && idx < bufferSize - 1; i--) buffer[idx++] = '0' + digits[i];
    }
    buffer[idx++] = ')';
    buffer[idx] = '\0';
}