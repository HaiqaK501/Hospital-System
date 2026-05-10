#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "Nurse.h"
#include "Ward.h"
#include "Validator.h"
#include "FileHandler.h"
#include "InsufficeintFundsException.h"
#include "InvalidInputException.h"
#include "SlotUnavailableException.h"
#include <iostream>

using namespace std;

void Patient::copyString(char*& dest, const char* src)
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

void Patient::resizeDoctorArray(int newSize)
{
    if (newSize <= maxDoctors) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < assignedDoctorCount; i++) newArray[i] = assignedDoctorIds[i];
    for (int i = assignedDoctorCount; i < newSize; i++) newArray[i] = 0;
    delete[] assignedDoctorIds;
    assignedDoctorIds = newArray;
    maxDoctors = newSize;
}

void Patient::resizeAppointmentArray(int newSize)
{
    if (newSize <= maxAppointments) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < appointmentCount; i++) newArray[i] = appointmentIds[i];
    for (int i = appointmentCount; i < newSize; i++) newArray[i] = 0;
    delete[] appointmentIds;
    appointmentIds = newArray;
    maxAppointments = newSize;
}

void Patient::resizeBillArray(int newSize)
{
    if (newSize <= maxBills) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < billCount; i++) newArray[i] = billIds[i];
    for (int i = billCount; i < newSize; i++) newArray[i] = 0;
    delete[] billIds;
    billIds = newArray;
    maxBills = newSize;
}

// ========== CONSTRUCTORS & DESTRUCTOR ==========

Patient::Patient() : Person()
{
    gender = new char[1]; gender[0] = '\0';
    contact = new char[1]; contact[0] = '\0';
    bloodGroup = new char[1]; bloodGroup[0] = '\0';
    emergencyContact = new char[1]; emergencyContact[0] = '\0';
    address = new char[1]; address[0] = '\0';
    medicalHistory = new char[1]; medicalHistory[0] = '\0';
    admissionDate = new char[1]; admissionDate[0] = '\0';
    dischargeDate = new char[1]; dischargeDate[0] = '\0';
    vitalSigns = new char[1]; vitalSigns[0] = '\0';

    age = 0;
    balance = 0.0f;
    isDischarged = false;
    isAdmitted = false;
    wardId = 0;
    assignedNurseId = 0;

    assignedDoctorCount = 0;
    maxDoctors = 5;
    assignedDoctorIds = new int[maxDoctors];
    for (int i = 0; i < maxDoctors; i++) assignedDoctorIds[i] = 0;

    appointmentCount = 0;
    maxAppointments = 20;
    appointmentIds = new int[maxAppointments];
    for (int i = 0; i < maxAppointments; i++) appointmentIds[i] = 0;

    billCount = 0;
    maxBills = 20;
    billIds = new int[maxBills];
    for (int i = 0; i < maxBills; i++) billIds[i] = 0;
}

Patient::Patient(int id, const char* nameVal, const char* passVal, int a, const char* g,
    const char* c, float bal, const char* bg, const char* ec)
    : Person(id, nameVal, passVal)
{
    copyString(gender, g);
    copyString(contact, c);
    copyString(bloodGroup, bg);
    copyString(emergencyContact, ec);
    copyString(address, "");
    copyString(medicalHistory, "");
    copyString(admissionDate, "");
    copyString(dischargeDate, "");
    copyString(vitalSigns, "Not recorded");

    age = a;
    balance = bal;
    isDischarged = false;
    isAdmitted = false;
    wardId = 0;
    assignedNurseId = 0;

    assignedDoctorCount = 0;
    maxDoctors = 5;
    assignedDoctorIds = new int[maxDoctors];
    for (int i = 0; i < maxDoctors; i++) assignedDoctorIds[i] = 0;

    appointmentCount = 0;
    maxAppointments = 20;
    appointmentIds = new int[maxAppointments];
    for (int i = 0; i < maxAppointments; i++) appointmentIds[i] = 0;

    billCount = 0;
    maxBills = 20;
    billIds = new int[maxBills];
    for (int i = 0; i < maxBills; i++) billIds[i] = 0;
}

Patient::Patient(const Patient& other) : Person(other)
{
    copyString(gender, other.gender);
    copyString(contact, other.contact);
    copyString(bloodGroup, other.bloodGroup);
    copyString(emergencyContact, other.emergencyContact);
    copyString(address, other.address);
    copyString(medicalHistory, other.medicalHistory);
    copyString(admissionDate, other.admissionDate);
    copyString(dischargeDate, other.dischargeDate);
    copyString(vitalSigns, other.vitalSigns);

    age = other.age;
    balance = other.balance;
    isDischarged = other.isDischarged;
    isAdmitted = other.isAdmitted;
    wardId = other.wardId;
    assignedNurseId = other.assignedNurseId;

    assignedDoctorCount = other.assignedDoctorCount;
    maxDoctors = other.maxDoctors;
    assignedDoctorIds = new int[maxDoctors];
    for (int i = 0; i < maxDoctors; i++) assignedDoctorIds[i] = other.assignedDoctorIds[i];

    appointmentCount = other.appointmentCount;
    maxAppointments = other.maxAppointments;
    appointmentIds = new int[maxAppointments];
    for (int i = 0; i < maxAppointments; i++) appointmentIds[i] = other.appointmentIds[i];

    billCount = other.billCount;
    maxBills = other.maxBills;
    billIds = new int[maxBills];
    for (int i = 0; i < maxBills; i++) billIds[i] = other.billIds[i];
}

Patient& Patient::operator=(const Patient& other)
{
    if (this == &other) return *this;
    Person::operator=(other);

    copyString(gender, other.gender);
    copyString(contact, other.contact);
    copyString(bloodGroup, other.bloodGroup);
    copyString(emergencyContact, other.emergencyContact);
    copyString(address, other.address);
    copyString(medicalHistory, other.medicalHistory);
    copyString(admissionDate, other.admissionDate);
    copyString(dischargeDate, other.dischargeDate);
    copyString(vitalSigns, other.vitalSigns);

    age = other.age;
    balance = other.balance;
    isDischarged = other.isDischarged;
    isAdmitted = other.isAdmitted;
    wardId = other.wardId;
    assignedNurseId = other.assignedNurseId;

    assignedDoctorCount = other.assignedDoctorCount;
    if (maxDoctors < other.maxDoctors)
    {
        delete[] assignedDoctorIds;
        maxDoctors = other.maxDoctors;
        assignedDoctorIds = new int[maxDoctors];
    }
    for (int i = 0; i < maxDoctors; i++) assignedDoctorIds[i] = other.assignedDoctorIds[i];

    appointmentCount = other.appointmentCount;
    if (maxAppointments < other.maxAppointments)
    {
        delete[] appointmentIds;
        maxAppointments = other.maxAppointments;
        appointmentIds = new int[maxAppointments];
    }
    for (int i = 0; i < maxAppointments; i++) appointmentIds[i] = other.appointmentIds[i];

    billCount = other.billCount;
    if (maxBills < other.maxBills)
    {
        delete[] billIds;
        maxBills = other.maxBills;
        billIds = new int[maxBills];
    }
    for (int i = 0; i < maxBills; i++) billIds[i] = other.billIds[i];

    return *this;
}

Patient::~Patient()
{
    delete[] gender; delete[] contact; delete[] bloodGroup; delete[] emergencyContact;
    delete[] address; delete[] medicalHistory; delete[] admissionDate; delete[] dischargeDate;
    delete[] vitalSigns;
    delete[] assignedDoctorIds; delete[] appointmentIds; delete[] billIds;
}

// ========== GETTERS ==========

int Patient::getAge() const { return age; }
const char* Patient::getGender() const { return gender; }
const char* Patient::getContact() const { return contact; }
float Patient::getBalance() const { return balance; }
const char* Patient::getBloodGroup() const { return bloodGroup; }
const char* Patient::getEmergencyContact() const { return emergencyContact; }
const char* Patient::getAddress() const { return address; }
const char* Patient::getMedicalHistory() const { return medicalHistory; }
const char* Patient::getAdmissionDate() const { return admissionDate; }
const char* Patient::getDischargeDate() const { return dischargeDate; }
bool Patient::getIsDischarged() const { return isDischarged; }
bool Patient::getIsAdmitted() const { return isAdmitted; }
int Patient::getWardId() const { return wardId; }
int Patient::getAssignedNurseId() const { return assignedNurseId; }
const char* Patient::getVitalSigns() const { return vitalSigns; }
int Patient::getAssignedDoctorCount() const { return assignedDoctorCount; }
int Patient::getAppointmentCount() const { return appointmentCount; }
int Patient::getBillCount() const { return billCount; }

// ========== SETTERS ==========

void Patient::setAge(int a) { age = a; }
void Patient::setGender(const char* g) { copyString(gender, g); }
void Patient::setContact(const char* c) { copyString(contact, c); }
void Patient::setBalance(float bal) { balance = bal; }
void Patient::setBloodGroup(const char* bg) { copyString(bloodGroup, bg); }
void Patient::setEmergencyContact(const char* ec) { copyString(emergencyContact, ec); }
void Patient::setAddress(const char* addr) { copyString(address, addr); }
void Patient::setMedicalHistory(const char* history) { copyString(medicalHistory, history); }
void Patient::setAdmissionDate(const char* date) { copyString(admissionDate, date); }
void Patient::setDischargeDate(const char* date) { copyString(dischargeDate, date); }
void Patient::setIsDischarged(bool discharged) { isDischarged = discharged; }
void Patient::setIsAdmitted(bool admitted) { isAdmitted = admitted; }
void Patient::setWardId(int wId) { wardId = wId; }
void Patient::setAssignedNurseId(int nId) { assignedNurseId = nId; }
void Patient::setVitalSigns(const char* vitals) { copyString(vitalSigns, vitals); }

// ========== DOCTOR MANAGEMENT ==========

bool Patient::assignDoctor(int doctorId)
{
    if (assignedDoctorCount >= maxDoctors) resizeDoctorArray(maxDoctors + 3);
    for (int i = 0; i < assignedDoctorCount; i++)
        if (assignedDoctorIds[i] == doctorId) return false;
    assignedDoctorIds[assignedDoctorCount] = doctorId;
    assignedDoctorCount++;
    return true;
}

bool Patient::removeDoctor(int doctorId)
{
    for (int i = 0; i < assignedDoctorCount; i++)
    {
        if (assignedDoctorIds[i] == doctorId)
        {
            for (int j = i; j < assignedDoctorCount - 1; j++)
                assignedDoctorIds[j] = assignedDoctorIds[j + 1];
            assignedDoctorCount--;
            return true;
        }
    }
    return false;
}

const int* Patient::getAssignedDoctorIds() const { return assignedDoctorIds; }

// ========== APPOINTMENT MANAGEMENT ==========

bool Patient::addAppointment(int appointmentId)
{
    if (appointmentCount >= maxAppointments) resizeAppointmentArray(maxAppointments + 10);
    for (int i = 0; i < appointmentCount; i++)
        if (appointmentIds[i] == appointmentId) return false;
    appointmentIds[appointmentCount] = appointmentId;
    appointmentCount++;
    return true;
}

bool Patient::removeAppointment(int appointmentId)
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

const int* Patient::getAppointmentIds() const { return appointmentIds; }

// ========== BILL MANAGEMENT ==========

bool Patient::addBill(int billId)
{
    if (billCount >= maxBills) resizeBillArray(maxBills + 10);
    for (int i = 0; i < billCount; i++)
        if (billIds[i] == billId) return false;
    billIds[billCount] = billId;
    billCount++;
    return true;
}

bool Patient::removeBill(int billId)
{
    for (int i = 0; i < billCount; i++)
    {
        if (billIds[i] == billId)
        {
            for (int j = i; j < billCount - 1; j++)
                billIds[j] = billIds[j + 1];
            billCount--;
            return true;
        }
    }
    return false;
}

const int* Patient::getBillIds() const { return billIds; }

// ========== NURSE & WARD RELATIONSHIPS ==========

void Patient::admitToWard(int wId, const char* date)
{
    wardId = wId;
    isAdmitted = true;
    isDischarged = false;
    setAdmissionDate(date);
    cout << "Patient admitted to Ward ID: " << wardId << " on " << date << endl;
}

void Patient::dischargeFromWard(const char* date)
{
    wardId = 0;
    assignedNurseId = 0;
    isAdmitted = false;
    isDischarged = true;
    setDischargeDate(date);
    cout << "Patient discharged from ward on " << date << endl;
}

void Patient::assignNurse(int nurseId)
{
    assignedNurseId = nurseId;
    cout << "Nurse ID " << nurseId << " assigned to patient." << endl;
}

void Patient::updateVitalSigns(const char* vitals)
{
    copyString(vitalSigns, vitals);
    cout << "Vital signs updated: " << vitalSigns << endl;
}

// ========== REQUIRED OPERATORS ==========

Patient& Patient::operator+=(float amount)
{
    if (amount > 0) balance += amount;
    return *this;
}

Patient& Patient::operator-=(float amount)
{
    if (amount > 0 && balance >= amount) balance -= amount;
    return *this;
}

bool Patient::operator==(const Patient& other) const
{
    return (id == other.id);
}



ostream& operator<<(ostream& os, const Patient& patient)
{
    os << "Patient: ";
    patient.getName().display();
    os << " (ID: " << patient.getID() << ") - Balance: Rs. " << patient.getBalance();
    return os;
}

// ========== REQUIRED METHODS ==========

bool Patient::hasSufficientFunds(float amount) const
{
    return balance >= amount;
}

float Patient::getTotalOutstandingBalance() const
{
    return 0;
}

int Patient::getUnpaidBillCount() const
{
    return 0;
}

// ========== BALANCE OPERATIONS ==========

void Patient::deductFee(float fee)
{
    if (fee > 0 && balance >= fee) balance -= fee;
}

void Patient::addFunds(float amount)
{
    if (amount > 0) balance += amount;
}

void Patient::topUpBalance()
{
    float amount;
    int attempts = 0;
    bool success = false;

    while (attempts < 3 && !success)
    {
        try
        {
            cout << "Enter amount to add (PKR): ";
            cin >> amount;

            if (amount <= 0)
            {
                throw InvalidInputException("amount");
            }

            *this += amount;
            FileHandler::updatePatientBalance(id, balance);
            cout << "Balance updated. New balance: PKR " << balance << endl;
            success = true;
        }
        catch (InvalidInputException& e)
        {
            attempts++;
            cout << e.what() << endl;
            if (attempts < 3)
            {
                cout << "Please try again. (" << attempts << "/3 attempts used)" << endl;
            }
            else
            {
                cout << "Too many invalid attempts. Returning to menu." << endl;
            }
        }
    }
}

void Patient::payBill(Storage<Bill>& billStorage, Storage<Appointment>& appointmentStorage)
{
    Bill* unpaidBills[100];
    int unpaidCount = 0;

    cout << "\n========== UNPAID BILLS ==========" << endl;
    cout << "Bill ID | Appointment ID | Amount (PKR) | Date" << endl;

    for (int i = 0; i < billStorage.getCount(); i++)
    {
        Bill* bill = billStorage.getAll()[i];
        if (bill && bill->getPatientId() == id && Validator::compareCaseInsensitive(bill->getStatus(), "unpaid"))
        {
            unpaidBills[unpaidCount] = bill;
            unpaidCount++;
            cout << bill->getBillId() << " | " << bill->getAppointmentId() << " | "
                << "Rs. " << bill->getAmount() << " | " << bill->getDate() << endl;
        }
    }

    if (unpaidCount == 0)
    {
        cout << "No unpaid bills." << endl;
        return;
    }

    int billId;
    cout << "\nEnter Bill ID to pay: ";
    cin >> billId;

    Bill* selectedBill = nullptr;
    for (int i = 0; i < unpaidCount; i++)
    {
        if (unpaidBills[i]->getBillId() == billId)
        {
            selectedBill = unpaidBills[i];
            break;
        }
    }

    if (!selectedBill)
    {
        cout << "Invalid bill ID." << endl;
        return;
    }

    float billAmount = selectedBill->getAmount();

    try
    {
        if (!hasSufficientFunds(billAmount))
        {
            throw InsufficientFundsException(billAmount, balance);
        }

        *this -= billAmount;
        selectedBill->setStatus("paid");
        FileHandler::updatePatientBalance(id, balance);
        FileHandler::updateBillStatus(billId, "paid");

        cout << "Bill paid successfully. Remaining balance: Rs. " << balance << endl;
    }
    catch (InsufficientFundsException& e)
    {
        cout << e.what() << endl;
    }
}

// ========== BOOK APPOINTMENT ==========

void Patient::bookAppointment(Storage<Doctor>& doctorStorage, Storage<Appointment>& appointmentStorage,
    Storage<Bill>& billStorage, const char* currentDate, int currentYear)
{
    char specialization[100];
    cout << "Enter specialization to search (e.g., Cardiology): ";
    cin >> specialization;

    bool found = false;
    for (int i = 0; i < doctorStorage.getCount(); i++)
    {
        Doctor* doc = doctorStorage.getAll()[i];
        if (!doc) continue;

        if (Validator::compareCaseInsensitive(specialization, doc->getSpecialization()))
        {
            found = true;
            cout << "Doctor ID: " << doc->getID() << " | Name: ";
            doc->getName().display();
            cout << " | Fee: Rs. " << doc->getFee() << endl;
        }
    }

    if (!found)
    {
        cout << "No doctors available for that specialization." << endl;
        return;
    }

    int doctorId;
    cout << "Enter Doctor ID: ";
    cin >> doctorId;

    Doctor* selectedDoctor = nullptr;
    for (int i = 0; i < doctorStorage.getCount(); i++)
    {
        Doctor* doc = doctorStorage.getAll()[i];
        if (doc && doc->getID() == doctorId)
        {
            selectedDoctor = doc;
            break;
        }
    }

    if (!selectedDoctor)
    {
        cout << "Doctor not found." << endl;
        return;
    }

    char date[20];
    int dateAttempts = 0;
    bool validDate = false;

    while (dateAttempts < 3 && !validDate)
    {
        cout << "Enter date (DD-MM-YYYY): ";
        cin >> date;

        if (!Validator::validateDate(date))
        {
            dateAttempts++;
            cout << "Invalid date. Use format DD-MM-YYYY." << endl;
            continue;
        }

        int year = Validator::stringToInt(&date[6]);
        if (year < currentYear)
        {
            dateAttempts++;
            cout << "Invalid date. Year must be current year or later." << endl;
            continue;
        }

        validDate = true;
    }

    if (!validDate)
    {
        cout << "Too many invalid attempts. Returning to menu." << endl;
        return;
    }

    const char* allSlots[] = { "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00" };
    bool availableSlots[8];

    cout << "\nAvailable time slots:" << endl;
    for (int i = 0; i < 8; i++)
    {
        availableSlots[i] = true;

        for (int j = 0; j < appointmentStorage.getCount(); j++)
        {
            Appointment* app = appointmentStorage.getAll()[j];
            if (app && app->getDoctorId() == doctorId &&
                Validator::compareCaseInsensitive(app->getDate(), date) &&
                Validator::compareCaseInsensitive(app->getTimeSlot(), allSlots[i]))
            {
                const char* status = app->getStatus();
                bool isCancelled = false;
                for (int k = 0; status[k] != '\0'; k++)
                {
                    char c = status[k];
                    if (c >= 'A' && c <= 'Z') c = c + 32;
                    if (c == 'c')
                    {
                        isCancelled = true;
                        break;
                    }
                }
                if (!isCancelled)
                {
                    availableSlots[i] = false;
                    break;
                }
            }
        }

        if (availableSlots[i])
            cout << "  " << allSlots[i] << " - Available" << endl;
        else
            cout << "  " << allSlots[i] << " - Booked" << endl;
    }

    char timeSlot[10];
    bool slotSelected = false;

    while (!slotSelected)
    {
        cout << "Enter time slot (e.g., 09:00): ";
        cin >> timeSlot;

        if (!Validator::validateTimeSlot(timeSlot))
        {
            cout << "Invalid time slot format." << endl;
            continue;
        }

        int slotIndex = -1;
        for (int i = 0; i < 8; i++)
        {
            if (Validator::compareCaseInsensitive(timeSlot, allSlots[i]))
            {
                slotIndex = i;
                break;
            }
        }

        if (slotIndex == -1)
        {
            cout << "Invalid time slot. Please choose from the listed slots." << endl;
            continue;
        }

        if (!availableSlots[slotIndex])
        {
            cout << "Slot is already booked. Please choose another slot." << endl;
            continue;
        }

        slotSelected = true;
    }

    float doctorFee = selectedDoctor->getFee();

    try
    {
        if (!hasSufficientFunds(doctorFee))
        {
            throw InsufficientFundsException(doctorFee,balance);
        }

        *this -= doctorFee;

        int newAppointmentId = 1;
        for (int i = 0; i < appointmentStorage.getCount(); i++)
        {
            Appointment* app = appointmentStorage.getAll()[i];
            if (app && app->getAppointmentId() >= newAppointmentId)
                newAppointmentId = app->getAppointmentId() + 1;
        }

        Appointment* newAppointment = new Appointment(newAppointmentId, id, doctorId, date, timeSlot, "pending", false);
        appointmentStorage.add(newAppointment);

        int newBillId = 1;
        for (int i = 0; i < billStorage.getCount(); i++)
        {
            Bill* bill = billStorage.getAll()[i];
            if (bill && bill->getBillId() >= newBillId)
                newBillId = bill->getBillId() + 1;
        }

        Bill* newBill = new Bill(newBillId, id, newAppointmentId, doctorFee, date);
        newBill->setStatus("unpaid");
        billStorage.add(newBill);

        FileHandler::updatePatientBalance(id, balance);
        FileHandler::saveAppointment(*newAppointment);
        FileHandler::saveBill(*newBill);

        cout << "Appointment booked successfully. Appointment ID: " << newAppointmentId << endl;
    }
    catch (InsufficientFundsException& e)
    {
        cout << e.what() << endl;
    }
}

// ========== CANCEL APPOINTMENT ==========

void Patient::cancelAppointment(Storage<Appointment>& appointmentStorage, Storage<Bill>& billStorage,
    Storage<Doctor>& doctorStorage)
{
    cout << "\nYour Pending Appointments:" << endl;
    cout << "Appointment ID | Doctor Name | Date | Time Slot" << endl;

    int pendingCount = 0;
    int pendingAppointmentIds[50];
    int pendingIndex = 0;

    for (int i = 0; i < appointmentStorage.getCount(); i++)
    {
        Appointment* app = appointmentStorage.getAll()[i];
        if (!app) continue;

        if (app->getPatientId() == id && Validator::compareCaseInsensitive(app->getStatus(), "pending"))
        {
            pendingCount++;
            pendingAppointmentIds[pendingIndex++] = app->getAppointmentId();

            const char* doctorName = "Unknown";
            for (int j = 0; j < doctorStorage.getCount(); j++)
            {
                Doctor* doc = doctorStorage.getAll()[j];
                if (doc && doc->getID() == app->getDoctorId())
                {
                    doctorName = doc->getName().get();
                    break;
                }
            }

            cout << "  " << app->getAppointmentId() << " | " << doctorName
                << " | " << app->getDate() << " | " << app->getTimeSlot() << endl;
        }
    }

    if (pendingCount == 0)
    {
        cout << "You have no pending appointments." << endl;
        return;
    }

    int appointmentId;
    cout << "Enter Appointment ID to cancel: ";
    cin >> appointmentId;

    Appointment* selectedApp = nullptr;
    float doctorFee = 0;

    for (int i = 0; i < appointmentStorage.getCount(); i++)
    {
        Appointment* app = appointmentStorage.getAll()[i];
        if (app && app->getAppointmentId() == appointmentId && app->getPatientId() == id)
        {
            if (Validator::compareCaseInsensitive(app->getStatus(), "pending"))
            {
                selectedApp = app;

                for (int j = 0; j < doctorStorage.getCount(); j++)
                {
                    Doctor* doc = doctorStorage.getAll()[j];
                    if (doc && doc->getID() == app->getDoctorId())
                    {
                        doctorFee = doc->getFee();
                        break;
                    }
                }
                break;
            }
        }
    }

    if (!selectedApp)
    {
        cout << "Invalid appointment ID." << endl;
        return;
    }

    selectedApp->setStatus("cancelled");
    *this += doctorFee;

    for (int i = 0; i < billStorage.getCount(); i++)
    {
        Bill* bill = billStorage.getAll()[i];
        if (bill && bill->getAppointmentId() == appointmentId)
        {
            bill->setStatus("cancelled");
            break;
        }
    }

    FileHandler::updatePatientBalance(id, balance);
    FileHandler::updateAppointmentStatus(appointmentId, "cancelled");

    cout << "Appointment cancelled. PKR " << doctorFee << " refunded to your balance." << endl;
}

// ========== VIEW MY APPOINTMENTS ==========

void Patient::viewMyAppointments(Storage<Appointment>& appointmentStorage, Storage<Doctor>& doctorStorage)
{
    Appointment* patientAppointments[100];
    int appCount = 0;

    for (int i = 0; i < appointmentStorage.getCount(); i++)
    {
        Appointment* app = appointmentStorage.getAll()[i];
        if (app && app->getPatientId() == id)
        {
            patientAppointments[appCount] = app;
            appCount++;
        }
    }

    if (appCount == 0)
    {
        cout << "No appointments found." << endl;
        return;
    }

    for (int i = 0; i < appCount - 1; i++)
    {
        for (int j = 0; j < appCount - i - 1; j++)
        {
            int day1 = (patientAppointments[j]->getDate()[0] - '0') * 10 + (patientAppointments[j]->getDate()[1] - '0');
            int month1 = (patientAppointments[j]->getDate()[3] - '0') * 10 + (patientAppointments[j]->getDate()[4] - '0');
            int year1 = (patientAppointments[j]->getDate()[6] - '0') * 1000 +
                (patientAppointments[j]->getDate()[7] - '0') * 100 +
                (patientAppointments[j]->getDate()[8] - '0') * 10 +
                (patientAppointments[j]->getDate()[9] - '0');

            int day2 = (patientAppointments[j + 1]->getDate()[0] - '0') * 10 + (patientAppointments[j + 1]->getDate()[1] - '0');
            int month2 = (patientAppointments[j + 1]->getDate()[3] - '0') * 10 + (patientAppointments[j + 1]->getDate()[4] - '0');
            int year2 = (patientAppointments[j + 1]->getDate()[6] - '0') * 1000 +
                (patientAppointments[j + 1]->getDate()[7] - '0') * 100 +
                (patientAppointments[j + 1]->getDate()[8] - '0') * 10 +
                (patientAppointments[j + 1]->getDate()[9] - '0');

            int totalDays1 = year1 * 365 + month1 * 30 + day1;
            int totalDays2 = year2 * 365 + month2 * 30 + day2;

            if (totalDays1 > totalDays2)
            {
                Appointment* temp = patientAppointments[j];
                patientAppointments[j] = patientAppointments[j + 1];
                patientAppointments[j + 1] = temp;
            }
        }
    }

    cout << "\n========== MY APPOINTMENTS ==========" << endl;
    cout << "ID | Doctor Name | Specialization | Date | Time Slot | Status" << endl;

    for (int i = 0; i < appCount; i++)
    {
        Appointment* app = patientAppointments[i];

        const char* doctorName = "Unknown";
        const char* doctorSpec = "Unknown";

        for (int j = 0; j < doctorStorage.getCount(); j++)
        {
            Doctor* doc = doctorStorage.getAll()[j];
            if (doc && doc->getID() == app->getDoctorId())
            {
                doctorName = doc->getName().get();
                doctorSpec = doc->getSpecialization();
                break;
            }
        }

        cout << app->getAppointmentId() << " | " << doctorName
            << " | " << doctorSpec << " | " << app->getDate()
            << " | " << app->getTimeSlot() << " | " << app->getStatus() << endl;
    }

    cout << "=====================================" << endl;
}

// ========== VIEW MY MEDICAL RECORDS ==========

void Patient::viewMyMedicalRecords(Storage<Prescription>& prescriptionStorage, Storage<Doctor>& doctorStorage)
{
    Prescription* patientPrescriptions[100];
    int presCount = 0;

    for (int i = 0; i < prescriptionStorage.getCount(); i++)
    {
        Prescription* pres = prescriptionStorage.getAll()[i];
        if (pres && pres->getPatientId() == this->getID())
        {
            patientPrescriptions[presCount] = pres;
            presCount++;
        }
    }

    if (presCount == 0)
    {
        cout << "No medical records found." << endl;
        return;
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

    cout << "\n========== MEDICAL RECORDS ==========" << endl;

    for (int i = 0; i < presCount; i++)
    {
        Prescription* pres = patientPrescriptions[i];

        const char* doctorName = "Unknown";
        for (int j = 0; j < doctorStorage.getCount(); j++)
        {
            Doctor* doc = doctorStorage.getAll()[j];
            if (doc && doc->getID() == pres->getDoctorId())
            {
                doctorName = doc->getName().get();
                break;
            }
        }

        cout << "Date: " << pres->getDate() << endl;
        cout << "Doctor: " << doctorName << endl;
        cout << "Medicines: " << pres->getMedicines() << endl;
        cout << "Notes: " << pres->getNotes() << endl;
        cout << "-----------------------------------" << endl;
    }

    cout << "=====================================" << endl;
}

// ========== VIEW MY BILLS ==========

void Patient::viewMyBills(Storage<Bill>& billStorage, Storage<Appointment>& appointmentStorage)
{
    Bill* patientBills[100];
    int billCount = 0;
    float totalOutstanding = 0.0f;

    for (int i = 0; i < billStorage.getCount(); i++)
    {
        Bill* bill = billStorage.getAll()[i];
        if (bill && bill->getPatientId() == id)
        {
            patientBills[billCount] = bill;
            billCount++;

            if (Validator::compareCaseInsensitive(bill->getStatus(), "unpaid"))
            {
                totalOutstanding += bill->getAmount();
            }
        }
    }

    if (billCount == 0)
    {
        cout << "No bills found." << endl;
        return;
    }

    cout << "\n========== MY BILLS ==========" << endl;
    cout << "Bill ID | Appointment ID | Amount (PKR) | Status | Date" << endl;

    for (int i = 0; i < billCount; i++)
    {
        Bill* bill = patientBills[i];
        cout << bill->getBillId() << " | " << bill->getAppointmentId() << " | "
            << "Rs. " << bill->getAmount() << " | " << bill->getStatus()
            << " | " << bill->getDate() << endl;
    }

    cout << "-----------------------------------" << endl;
    cout << "Total Outstanding Amount: Rs. " << totalOutstanding << endl;
    cout << "=================================" << endl;
}

// ========== OTHER VIEW METHODS ==========

void Patient::viewMedicalRecords() const
{
    cout << "\n========== MEDICAL RECORDS ==========" << endl;
    cout << "Patient: "; name.display(); cout << endl;
    cout << "Blood Group: " << bloodGroup << endl;
    cout << "Medical History: " << medicalHistory << endl;
    cout << "Admission Date: " << admissionDate << endl;
    cout << "Discharged: " << (isDischarged ? "Yes" : "No") << endl;
    if (dischargeDate[0] != '\0')
        cout << "Discharge Date: " << dischargeDate << endl;
    cout << "Vital Signs: " << vitalSigns << endl;
    cout << "=====================================" << endl;
}

void Patient::viewBills() const
{
    cout << "\n========== BILL SUMMARY ==========" << endl;
    cout << "Patient: "; name.display(); cout << endl;
    cout << "Current Balance: Rs. " << balance << endl;
    cout << "Total Bills: " << billCount << endl;
    cout << "==================================" << endl;
}

void Patient::updateMedicalHistory(const char* newEntry)
{
    char* temp = new char[1000];
    int i = 0;

    while (medicalHistory[i] != '\0')
    {
        temp[i] = medicalHistory[i];
        i++;
    }

    if (i > 0)
    {
        temp[i++] = ';';
        temp[i++] = ' ';
    }

    int j = 0;
    while (newEntry[j] != '\0')
    {
        temp[i + j] = newEntry[j];
        j++;
    }
    temp[i + j] = '\0';

    copyString(medicalHistory, temp);
    delete[] temp;
}

void Patient::admit(const char* date)
{
    isDischarged = false;
    copyString(admissionDate, date);
    cout << "Patient admitted on " << date << endl;
}

void Patient::discharge(const char* date)
{
    isDischarged = true;
    copyString(dischargeDate, date);
    cout << "Patient discharged on " << date << endl;
}



void Patient::showMenu()
{
    cout << "\n========== PATIENT MENU ==========" << endl;
    cout << "1. Book Appointment" << endl;
    cout << "2. Cancel Appointment" << endl;
    cout << "3. View My Appointments" << endl;
    cout << "4. View My Medical Records" << endl;
    cout << "5. View My Bills" << endl;
    cout << "6. Pay Bill" << endl;
    cout << "7. Top Up Balance" << endl;
    cout << "8. Logout" << endl;
    cout << "================================" << endl;
}

void Patient::displayInfo() const
{
    cout << "ID: " << id << " | Name: ";
    name.display();
    cout << " | Role: PATIENT | Age: " << age;
    cout << " | Balance: Rs. " << balance;
    cout << " | Status: " << (isDischarged ? "Discharged" : "Active") << endl;
}

void Patient::display() const
{
    cout << "Patient ID: " << id << " | Name: ";
    name.display();
    cout << " | Age: " << age << " | Balance: Rs. " << balance << endl;
}

void Patient::displayFullDetails() const
{
    cout << "\n========== PATIENT FULL DETAILS ==========" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: "; name.display(); cout << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
    cout << "Contact: " << contact << endl;
    cout << "Blood Group: " << bloodGroup << endl;
    cout << "Emergency Contact: " << emergencyContact << endl;
    cout << "Address: " << address << endl;
    cout << "Balance: Rs. " << balance << endl;
    cout << "Status: " << (isDischarged ? "Discharged" : "Active") << endl;
    cout << "Admitted: " << (isAdmitted ? "Yes" : "No") << endl;
    cout << "Ward ID: " << (wardId ? wardId : 0) << endl;
    cout << "Assigned Nurse ID: " << (assignedNurseId ? assignedNurseId : 0) << endl;
    cout << "Vital Signs: " << vitalSigns << endl;
    cout << "Admission Date: " << admissionDate << endl;
    if (dischargeDate[0] != '\0')
        cout << "Discharge Date: " << dischargeDate << endl;
    cout << "Medical History: " << medicalHistory << endl;
    cout << "Assigned Doctors: " << assignedDoctorCount << endl;
    cout << "Total Appointments: " << appointmentCount << endl;
    cout << "Total Bills: " << billCount << endl;
    cout << "==========================================" << endl;
}






