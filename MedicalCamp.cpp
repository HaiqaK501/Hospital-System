#include "MedicalCamp.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Volunteer.h"
#include "Patient.h"
#include "Pharmacy.h"
#include <iostream>

using namespace std;

void MedicalCamp::copyString(char*& dest, const char* src)
{
    if (dest)
    {
        delete[] dest;
    }

    if (!src)
    {
        dest = new char[1];
        dest[0] = '\0';
        return;
    }

    int len = 0;
    while (src[len] != '\0')
        len++;

    dest = new char[len + 1];
    for (int i = 0; i < len; i++)
        dest[i] = src[i];
    dest[len] = '\0';
}

void MedicalCamp::resizeDoctorArray(int newSize)
{
    if (newSize <= maxDoctors) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < doctorCount; i++)
        newArray[i] = doctorIds[i];
    for (int i = doctorCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] doctorIds;
    doctorIds = newArray;
    maxDoctors = newSize;
}

void MedicalCamp::resizeNurseArray(int newSize)
{
    if (newSize <= maxNurses) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < nurseCount; i++)
        newArray[i] = nurseIds[i];
    for (int i = nurseCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] nurseIds;
    nurseIds = newArray;
    maxNurses = newSize;
}

void MedicalCamp::resizeVolunteerArray(int newSize)
{
    if (newSize <= maxVolunteers) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < volunteerCount; i++)
        newArray[i] = volunteerIds[i];
    for (int i = volunteerCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] volunteerIds;
    volunteerIds = newArray;
    maxVolunteers = newSize;
}

void MedicalCamp::resizePatientArray(int newSize)
{
    if (newSize <= maxPatients) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < patientCount; i++)
        newArray[i] = patientIds[i];
    for (int i = patientCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] patientIds;
    patientIds = newArray;
    maxPatients = newSize;
}

void MedicalCamp::resizeServicesArray(int newSize)
{
    if (newSize <= maxServices) return;

    char** newArray = new char* [newSize];
    for (int i = 0; i < serviceCount; i++)
    {
        newArray[i] = new char[100];
        copyString(newArray[i], servicesOffered[i]);
    }
    for (int i = serviceCount; i < newSize; i++)
        newArray[i] = nullptr;

    for (int i = 0; i < serviceCount; i++)
        delete[] servicesOffered[i];
    delete[] servicesOffered;

    servicesOffered = newArray;
    maxServices = newSize;
}

void MedicalCamp::resizePharmacyArray(int newSize)
{
    if (newSize <= maxPharmacies) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < pharmacyCount; i++)
        newArray[i] = pharmacyIds[i];
    for (int i = pharmacyCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] pharmacyIds;
    pharmacyIds = newArray;
    maxPharmacies = newSize;
}

MedicalCamp::MedicalCamp()
{
    campName = new char[1];
    campName[0] = '\0';
    location = new char[1];
    location[0] = '\0';
    startDate = new char[1];
    startDate[0] = '\0';
    endDate = new char[1];
    endDate[0] = '\0';
    organizer = new char[1];
    organizer[0] = '\0';

    campId = 0;
    budget = 0.0f;
    expenses = 0.0f;
    isCompleted = false;

    doctorCount = 0;
    maxDoctors = 20;
    doctorIds = new int[maxDoctors];
    for (int i = 0; i < maxDoctors; i++)
        doctorIds[i] = 0;

    nurseCount = 0;
    maxNurses = 20;
    nurseIds = new int[maxNurses];
    for (int i = 0; i < maxNurses; i++)
        nurseIds[i] = 0;

    volunteerCount = 0;
    maxVolunteers = 30;
    volunteerIds = new int[maxVolunteers];
    for (int i = 0; i < maxVolunteers; i++)
        volunteerIds[i] = 0;

    patientCount = 0;
    maxPatients = 500;
    patientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++)
        patientIds[i] = 0;

    serviceCount = 0;
    maxServices = 20;
    servicesOffered = new char* [maxServices];
    for (int i = 0; i < maxServices; i++)
        servicesOffered[i] = nullptr;

    pharmacyCount = 0;
    maxPharmacies = 10;
    pharmacyIds = new int[maxPharmacies];
    for (int i = 0; i < maxPharmacies; i++)
        pharmacyIds[i] = 0;
}

MedicalCamp::MedicalCamp(int id, const char* name, const char* loc, const char* start, const char* end, const char* org, float bud)
{
    copyString(campName, name);
    copyString(location, loc);
    copyString(startDate, start);
    copyString(endDate, end);
    copyString(organizer, org);

    campId = id;
    budget = bud;
    expenses = 0.0f;
    isCompleted = false;

    doctorCount = 0;
    maxDoctors = 20;
    doctorIds = new int[maxDoctors];
    for (int i = 0; i < maxDoctors; i++)
        doctorIds[i] = 0;

    nurseCount = 0;
    maxNurses = 20;
    nurseIds = new int[maxNurses];
    for (int i = 0; i < maxNurses; i++)
        nurseIds[i] = 0;

    volunteerCount = 0;
    maxVolunteers = 30;
    volunteerIds = new int[maxVolunteers];
    for (int i = 0; i < maxVolunteers; i++)
        volunteerIds[i] = 0;

    patientCount = 0;
    maxPatients = 500;
    patientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++)
        patientIds[i] = 0;

    serviceCount = 0;
    maxServices = 20;
    servicesOffered = new char* [maxServices];
    for (int i = 0; i < maxServices; i++)
        servicesOffered[i] = nullptr;

    pharmacyCount = 0;
    maxPharmacies = 10;
    pharmacyIds = new int[maxPharmacies];
    for (int i = 0; i < maxPharmacies; i++)
        pharmacyIds[i] = 0;
}

MedicalCamp::MedicalCamp(const MedicalCamp& other)
{
    copyString(campName, other.campName);
    copyString(location, other.location);
    copyString(startDate, other.startDate);
    copyString(endDate, other.endDate);
    copyString(organizer, other.organizer);

    campId = other.campId;
    budget = other.budget;
    expenses = other.expenses;
    isCompleted = other.isCompleted;

    doctorCount = other.doctorCount;
    maxDoctors = other.maxDoctors;
    doctorIds = new int[maxDoctors];
    for (int i = 0; i < maxDoctors; i++)
        doctorIds[i] = other.doctorIds[i];

    nurseCount = other.nurseCount;
    maxNurses = other.maxNurses;
    nurseIds = new int[maxNurses];
    for (int i = 0; i < maxNurses; i++)
        nurseIds[i] = other.nurseIds[i];

    volunteerCount = other.volunteerCount;
    maxVolunteers = other.maxVolunteers;
    volunteerIds = new int[maxVolunteers];
    for (int i = 0; i < maxVolunteers; i++)
        volunteerIds[i] = other.volunteerIds[i];

    patientCount = other.patientCount;
    maxPatients = other.maxPatients;
    patientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++)
        patientIds[i] = other.patientIds[i];

    serviceCount = other.serviceCount;
    maxServices = other.maxServices;
    servicesOffered = new char* [maxServices];
    for (int i = 0; i < serviceCount; i++)
    {
        servicesOffered[i] = new char[100];
        copyString(servicesOffered[i], other.servicesOffered[i]);
    }
    for (int i = serviceCount; i < maxServices; i++)
        servicesOffered[i] = nullptr;

    pharmacyCount = other.pharmacyCount;
    maxPharmacies = other.maxPharmacies;
    pharmacyIds = new int[maxPharmacies];
    for (int i = 0; i < maxPharmacies; i++)
        pharmacyIds[i] = other.pharmacyIds[i];
}

MedicalCamp& MedicalCamp::operator=(const MedicalCamp& other)
{
    if (this == &other)
        return *this;

    copyString(campName, other.campName);
    copyString(location, other.location);
    copyString(startDate, other.startDate);
    copyString(endDate, other.endDate);
    copyString(organizer, other.organizer);

    campId = other.campId;
    budget = other.budget;
    expenses = other.expenses;
    isCompleted = other.isCompleted;

    doctorCount = other.doctorCount;
    if (maxDoctors < other.maxDoctors)
    {
        delete[] doctorIds;
        maxDoctors = other.maxDoctors;
        doctorIds = new int[maxDoctors];
    }
    for (int i = 0; i < maxDoctors; i++)
        doctorIds[i] = other.doctorIds[i];

    nurseCount = other.nurseCount;
    if (maxNurses < other.maxNurses)
    {
        delete[] nurseIds;
        maxNurses = other.maxNurses;
        nurseIds = new int[maxNurses];
    }
    for (int i = 0; i < maxNurses; i++)
        nurseIds[i] = other.nurseIds[i];

    volunteerCount = other.volunteerCount;
    if (maxVolunteers < other.maxVolunteers)
    {
        delete[] volunteerIds;
        maxVolunteers = other.maxVolunteers;
        volunteerIds = new int[maxVolunteers];
    }
    for (int i = 0; i < maxVolunteers; i++)
        volunteerIds[i] = other.volunteerIds[i];

    patientCount = other.patientCount;
    if (maxPatients < other.maxPatients)
    {
        delete[] patientIds;
        maxPatients = other.maxPatients;
        patientIds = new int[maxPatients];
    }
    for (int i = 0; i < maxPatients; i++)
        patientIds[i] = other.patientIds[i];

    for (int i = 0; i < serviceCount; i++)
        delete[] servicesOffered[i];

    if (maxServices < other.maxServices)
    {
        delete[] servicesOffered;
        maxServices = other.maxServices;
        servicesOffered = new char* [maxServices];
    }

    serviceCount = other.serviceCount;
    for (int i = 0; i < serviceCount; i++)
    {
        servicesOffered[i] = new char[100];
        copyString(servicesOffered[i], other.servicesOffered[i]);
    }
    for (int i = serviceCount; i < maxServices; i++)
        servicesOffered[i] = nullptr;

    pharmacyCount = other.pharmacyCount;
    if (maxPharmacies < other.maxPharmacies)
    {
        delete[] pharmacyIds;
        maxPharmacies = other.maxPharmacies;
        pharmacyIds = new int[maxPharmacies];
    }
    for (int i = 0; i < maxPharmacies; i++)
        pharmacyIds[i] = other.pharmacyIds[i];

    return *this;
}

MedicalCamp::~MedicalCamp()
{
    delete[] campName;
    delete[] location;
    delete[] startDate;
    delete[] endDate;
    delete[] organizer;
    delete[] doctorIds;
    delete[] nurseIds;
    delete[] volunteerIds;
    delete[] patientIds;
    delete[] pharmacyIds;

    for (int i = 0; i < serviceCount; i++)
        delete[] servicesOffered[i];
    delete[] servicesOffered;
}

int MedicalCamp::getCampId() const { return campId; }
const char* MedicalCamp::getCampName() const { return campName; }
const char* MedicalCamp::getLocation() const { return location; }
const char* MedicalCamp::getStartDate() const { return startDate; }
const char* MedicalCamp::getEndDate() const { return endDate; }
float MedicalCamp::getBudget() const { return budget; }
float MedicalCamp::getExpenses() const { return expenses; }
bool MedicalCamp::getIsCompleted() const { return isCompleted; }

void MedicalCamp::addService(const char* service)
{
    if (serviceCount >= maxServices)
        resizeServicesArray(maxServices + 10);

    servicesOffered[serviceCount] = new char[100];
    copyString(servicesOffered[serviceCount], service);
    serviceCount++;
}

bool MedicalCamp::assignDoctor(const Doctor& doctor)
{
    if (doctorCount >= maxDoctors)
        resizeDoctorArray(maxDoctors + 10);

    int doctorId = doctor.getID();

    for (int i = 0; i < doctorCount; i++)
        if (doctorIds[i] == doctorId)
            return false;

    doctorIds[doctorCount] = doctorId;
    doctorCount++;
    return true;
}

bool MedicalCamp::assignNurse(const Nurse& nurse)
{
    if (nurseCount >= maxNurses)
        resizeNurseArray(maxNurses + 10);

    int nurseId = nurse.getID();

    for (int i = 0; i < nurseCount; i++)
        if (nurseIds[i] == nurseId)
            return false;

    nurseIds[nurseCount] = nurseId;
    nurseCount++;
    return true;
}

bool MedicalCamp::assignVolunteer(const Volunteer& volunteer)
{
    if (volunteerCount >= maxVolunteers)
        resizeVolunteerArray(maxVolunteers + 10);

    int volunteerId = volunteer.getID();

    for (int i = 0; i < volunteerCount; i++)
        if (volunteerIds[i] == volunteerId)
            return false;

    volunteerIds[volunteerCount] = volunteerId;
    volunteerCount++;
    return true;
}

bool MedicalCamp::registerPatient(const Patient& patient)
{
    if (patientCount >= maxPatients)
        resizePatientArray(maxPatients + 100);

    int patientId = patient.getID();

    for (int i = 0; i < patientCount; i++)
        if (patientIds[i] == patientId)
            return false;

    patientIds[patientCount] = patientId;
    patientCount++;
    return true;
}

bool MedicalCamp::assignPharmacy(const Pharmacy& pharmacy)
{
    if (pharmacyCount >= maxPharmacies)
        resizePharmacyArray(maxPharmacies + 5);

    int pharmacyId = pharmacy.getMedicineId();

    for (int i = 0; i < pharmacyCount; i++)
        if (pharmacyIds[i] == pharmacyId)
            return false;

    pharmacyIds[pharmacyCount] = pharmacyId;
    pharmacyCount++;
    return true;
}

bool MedicalCamp::removeDoctor(int doctorId)
{
    for (int i = 0; i < doctorCount; i++)
    {
        if (doctorIds[i] == doctorId)
        {
            for (int j = i; j < doctorCount - 1; j++)
                doctorIds[j] = doctorIds[j + 1];
            doctorCount--;
            return true;
        }
    }
    return false;
}

bool MedicalCamp::removeNurse(int nurseId)
{
    for (int i = 0; i < nurseCount; i++)
    {
        if (nurseIds[i] == nurseId)
        {
            for (int j = i; j < nurseCount - 1; j++)
                nurseIds[j] = nurseIds[j + 1];
            nurseCount--;
            return true;
        }
    }
    return false;
}

bool MedicalCamp::removeVolunteer(int volunteerId)
{
    for (int i = 0; i < volunteerCount; i++)
    {
        if (volunteerIds[i] == volunteerId)
        {
            for (int j = i; j < volunteerCount - 1; j++)
                volunteerIds[j] = volunteerIds[j + 1];
            volunteerCount--;
            return true;
        }
    }
    return false;
}

bool MedicalCamp::removePatient(int patientId)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (patientIds[i] == patientId)
        {
            for (int j = i; j < patientCount - 1; j++)
                patientIds[j] = patientIds[j + 1];
            patientCount--;
            return true;
        }
    }
    return false;
}

bool MedicalCamp::removePharmacy(int pharmacyId)
{
    for (int i = 0; i < pharmacyCount; i++)
    {
        if (pharmacyIds[i] == pharmacyId)
        {
            for (int j = i; j < pharmacyCount - 1; j++)
                pharmacyIds[j] = pharmacyIds[j + 1];
            pharmacyCount--;
            return true;
        }
    }
    return false;
}

void MedicalCamp::addExpense(float amount)
{
    if (amount > 0)
        expenses += amount;
}

float MedicalCamp::getRemainingBudget() const
{
    return budget - expenses;
}

int MedicalCamp::getTotalPatientsServed() const
{
    return patientCount;
}

float MedicalCamp::getCostPerPatient() const
{
    if (patientCount == 0) return 0;
    return expenses / patientCount;
}

void MedicalCamp::completeCamp()
{
    isCompleted = true;
}

bool MedicalCamp::isCampActive() const
{
    return !isCompleted;
}

int MedicalCamp::getDoctorCount() const { return doctorCount; }
int MedicalCamp::getNurseCount() const { return nurseCount; }
int MedicalCamp::getVolunteerCount() const { return volunteerCount; }
int MedicalCamp::getPharmacyCount() const { return pharmacyCount; }
const int* MedicalCamp::getDoctorIds() const { return doctorIds; }
const int* MedicalCamp::getNurseIds() const { return nurseIds; }
const int* MedicalCamp::getVolunteerIds() const { return volunteerIds; }
const int* MedicalCamp::getPatientIds() const { return patientIds; }
const int* MedicalCamp::getPharmacyIds() const { return pharmacyIds; }

void MedicalCamp::display() const
{
    cout << "Camp ID: " << campId << " | " << campName;
    cout << " | Location: " << location;
    cout << " | Patients: " << patientCount;
    cout << " | Status: " << (isCompleted ? "Completed" : "Active") << endl;
}

void MedicalCamp::displayFullDetails() const
{
    cout << "\n========== MEDICAL CAMP DETAILS ==========" << endl;
    cout << "ID: " << campId << endl;
    cout << "Name: " << campName << endl;
    cout << "Location: " << location << endl;
    cout << "Dates: " << startDate << " to " << endDate << endl;
    cout << "Organizer: " << organizer << endl;
    cout << "Budget: Rs. " << budget << endl;
    cout << "Expenses: Rs. " << expenses << endl;
    cout << "Remaining Budget: Rs. " << getRemainingBudget() << endl;
    cout << "Patients Served: " << patientCount << endl;
    cout << "Cost Per Patient: Rs. " << getCostPerPatient() << endl;
    cout << "Doctors Assigned: " << doctorCount << endl;
    cout << "Nurses Assigned: " << nurseCount << endl;
    cout << "Volunteers: " << volunteerCount << endl;
    cout << "Pharmacies/Medicine Camps: " << pharmacyCount << endl;

    cout << "Services Offered: ";
    if (serviceCount == 0) cout << "None";
    else
    {
        for (int i = 0; i < serviceCount; i++)
        {
            cout << servicesOffered[i];
            if (i < serviceCount - 1) cout << ", ";
        }
    }
    cout << endl;

    cout << "Status: " << (isCompleted ? "Completed" : "Active") << endl;
    cout << "==========================================" << endl;
}