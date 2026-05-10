#include "Ward.h"
#include "Validator.h"
#include <iostream>

using namespace std;

void Ward::copyString(char*& dest, const char* src)
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

void Ward::resizePatientArray(int newSize)
{
    if (newSize <= maxPatients) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < patientCount; i++) newArray[i] = patientIds[i];
    for (int i = patientCount; i < newSize; i++) newArray[i] = 0;
    delete[] patientIds;
    patientIds = newArray;
    maxPatients = newSize;
}

void Ward::resizeNurseArray(int newSize)
{
    if (newSize <= maxNurses) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < nurseCount; i++) newArray[i] = nurseIds[i];
    for (int i = nurseCount; i < newSize; i++) newArray[i] = 0;
    delete[] nurseIds;
    nurseIds = newArray;
    maxNurses = newSize;
}

void Ward::resizeEquipmentArray(int newSize)
{
    if (newSize <= maxEquipment) return;
    char** newArray = new char* [newSize];
    for (int i = 0; i < equipmentCount; i++)
    {
        newArray[i] = new char[50];
        copyString(newArray[i], equipmentList[i]);
    }
    for (int i = equipmentCount; i < newSize; i++) newArray[i] = nullptr;
    for (int i = 0; i < equipmentCount; i++) delete[] equipmentList[i];
    delete[] equipmentList;
    equipmentList = newArray;
    maxEquipment = newSize;
}

Ward::Ward()
{
    wardName = new char[1]; wardName[0] = '\0';
    wardType = new char[1]; wardType[0] = '\0';
    nurseInCharge = new char[1]; nurseInCharge[0] = '\0';

    wardId = 0;
    totalBeds = 0;
    occupiedBeds = 0;
    availableBeds = 0;
    dailyRate = 0.0f;
    isIsolationWard = false;

    patientCount = 0;
    maxPatients = 50;
    patientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++) patientIds[i] = 0;

    nurseCount = 0;
    maxNurses = 10;
    nurseIds = new int[maxNurses];
    for (int i = 0; i < maxNurses; i++) nurseIds[i] = 0;

    equipmentCount = 0;
    maxEquipment = 20;
    equipmentList = new char* [maxEquipment];
    for (int i = 0; i < maxEquipment; i++) equipmentList[i] = nullptr;
}

Ward::Ward(int id, const char* name, const char* type, int beds, float rate, const char* nurse, bool isolation)
{
    copyString(wardName, name);
    copyString(wardType, type);
    copyString(nurseInCharge, nurse);

    wardId = id;
    totalBeds = beds;
    occupiedBeds = 0;
    availableBeds = beds;
    dailyRate = rate;
    isIsolationWard = isolation;

    patientCount = 0;
    maxPatients = beds;
    patientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++) patientIds[i] = 0;

    nurseCount = 0;
    maxNurses = 10;
    nurseIds = new int[maxNurses];
    for (int i = 0; i < maxNurses; i++) nurseIds[i] = 0;

    equipmentCount = 0;
    maxEquipment = 20;
    equipmentList = new char* [maxEquipment];
    for (int i = 0; i < maxEquipment; i++) equipmentList[i] = nullptr;
}

Ward::Ward(const Ward& other)
{
    copyString(wardName, other.wardName);
    copyString(wardType, other.wardType);
    copyString(nurseInCharge, other.nurseInCharge);

    wardId = other.wardId;
    totalBeds = other.totalBeds;
    occupiedBeds = other.occupiedBeds;
    availableBeds = other.availableBeds;
    dailyRate = other.dailyRate;
    isIsolationWard = other.isIsolationWard;

    patientCount = other.patientCount;
    maxPatients = other.maxPatients;
    patientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++) patientIds[i] = other.patientIds[i];

    nurseCount = other.nurseCount;
    maxNurses = other.maxNurses;
    nurseIds = new int[maxNurses];
    for (int i = 0; i < maxNurses; i++) nurseIds[i] = other.nurseIds[i];

    equipmentCount = other.equipmentCount;
    maxEquipment = other.maxEquipment;
    equipmentList = new char* [maxEquipment];
    for (int i = 0; i < equipmentCount; i++)
    {
        equipmentList[i] = new char[50];
        copyString(equipmentList[i], other.equipmentList[i]);
    }
    for (int i = equipmentCount; i < maxEquipment; i++) equipmentList[i] = nullptr;
}

Ward& Ward::operator=(const Ward& other)
{
    if (this == &other) return *this;

    copyString(wardName, other.wardName);
    copyString(wardType, other.wardType);
    copyString(nurseInCharge, other.nurseInCharge);

    wardId = other.wardId;
    totalBeds = other.totalBeds;
    occupiedBeds = other.occupiedBeds;
    availableBeds = other.availableBeds;
    dailyRate = other.dailyRate;
    isIsolationWard = other.isIsolationWard;

    patientCount = other.patientCount;
    if (maxPatients < other.maxPatients)
    {
        delete[] patientIds;
        maxPatients = other.maxPatients;
        patientIds = new int[maxPatients];
    }
    for (int i = 0; i < maxPatients; i++) patientIds[i] = other.patientIds[i];

    nurseCount = other.nurseCount;
    if (maxNurses < other.maxNurses)
    {
        delete[] nurseIds;
        maxNurses = other.maxNurses;
        nurseIds = new int[maxNurses];
    }
    for (int i = 0; i < maxNurses; i++) nurseIds[i] = other.nurseIds[i];

    for (int i = 0; i < equipmentCount; i++) delete[] equipmentList[i];

    if (maxEquipment < other.maxEquipment)
    {
        delete[] equipmentList;
        maxEquipment = other.maxEquipment;
        equipmentList = new char* [maxEquipment];
    }

    equipmentCount = other.equipmentCount;
    for (int i = 0; i < equipmentCount; i++)
    {
        equipmentList[i] = new char[50];
        copyString(equipmentList[i], other.equipmentList[i]);
    }
    for (int i = equipmentCount; i < maxEquipment; i++) equipmentList[i] = nullptr;

    return *this;
}

Ward::~Ward()
{
    delete[] wardName;
    delete[] wardType;
    delete[] nurseInCharge;
    delete[] patientIds;
    delete[] nurseIds;
    for (int i = 0; i < equipmentCount; i++) delete[] equipmentList[i];
    delete[] equipmentList;
}

int Ward::getWardId() const { return wardId; }
const char* Ward::getWardName() const { return wardName; }
const char* Ward::getWardType() const { return wardType; }
int Ward::getTotalBeds() const { return totalBeds; }
int Ward::getOccupiedBeds() const { return occupiedBeds; }
int Ward::getAvailableBeds() const { return availableBeds; }
float Ward::getDailyRate() const { return dailyRate; }
const char* Ward::getNurseInCharge() const { return nurseInCharge; }
bool Ward::getIsIsolationWard() const { return isIsolationWard; }

bool Ward::hasAvailableBed() const
{
    return availableBeds > 0;
}

bool Ward::admitPatient(int patientId)
{
    if (!hasAvailableBed()) return false;

    for (int i = 0; i < patientCount; i++)
    {
        if (patientIds[i] == patientId) return false;
    }

    if (patientCount >= maxPatients) resizePatientArray(maxPatients + 10);

    patientIds[patientCount] = patientId;
    patientCount++;
    occupiedBeds++;
    availableBeds--;

    return true;
}

bool Ward::dischargePatient(int patientId)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (patientIds[i] == patientId)
        {
            for (int j = i; j < patientCount - 1; j++)
                patientIds[j] = patientIds[j + 1];
            patientCount--;
            occupiedBeds--;
            availableBeds++;
            return true;
        }
    }
    return false;
}

bool Ward::assignNurse(int nurseId)
{
    for (int i = 0; i < nurseCount; i++)
    {
        if (nurseIds[i] == nurseId) return false;
    }

    if (nurseCount >= maxNurses) resizeNurseArray(maxNurses + 5);

    nurseIds[nurseCount] = nurseId;
    nurseCount++;
    return true;
}

bool Ward::removeNurse(int nurseId)
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

void Ward::addEquipment(const char* equipment)
{
    if (!equipment) return;

    if (equipmentCount >= maxEquipment) resizeEquipmentArray(maxEquipment + 10);

    equipmentList[equipmentCount] = new char[50];
    copyString(equipmentList[equipmentCount], equipment);
    equipmentCount++;
}

float Ward::getOccupancyRate() const
{
    if (totalBeds == 0) return 0.0f;
    return ((float)occupiedBeds / totalBeds) * 100.0f;
}

int Ward::getAvailableIsolationBeds() const
{
    if (!isIsolationWard) return 0;
    return availableBeds;
}

float Ward::calculateMonthlyRevenue() const
{
    return occupiedBeds * dailyRate * 30.0f;
}

void Ward::display() const
{
    cout << "Ward ID: " << wardId << " | " << wardName;
    cout << " | Type: " << wardType;
    cout << " | Beds: " << occupiedBeds << "/" << totalBeds;
    cout << " | Occupancy: " << getOccupancyRate() << "%";
    if (isIsolationWard) cout << " | ISOLATION";
    cout << endl;
}

void Ward::displayFullDetails() const
{
    cout << "\n========== WARD DETAILS ==========" << endl;
    cout << "ID: " << wardId << endl;
    cout << "Name: " << wardName << endl;
    cout << "Type: " << wardType << endl;
    cout << "Total Beds: " << totalBeds << endl;
    cout << "Occupied Beds: " << occupiedBeds << endl;
    cout << "Available Beds: " << availableBeds << endl;
    cout << "Occupancy Rate: " << getOccupancyRate() << "%" << endl;
    cout << "Daily Rate: Rs. " << dailyRate << endl;
    cout << "Monthly Revenue: Rs. " << calculateMonthlyRevenue() << endl;
    cout << "Nurse In-Charge: " << nurseInCharge << endl;
    cout << "Isolation Ward: " << (isIsolationWard ? "Yes" : "No") << endl;
    cout << "Available Isolation Beds: " << getAvailableIsolationBeds() << endl;
    cout << "Assigned Nurses: " << nurseCount << endl;
    cout << "Current Patients: " << patientCount << endl;

    cout << "Equipment: ";
    if (equipmentCount == 0) cout << "None";
    else
    {
        for (int i = 0; i < equipmentCount; i++)
        {
            cout << equipmentList[i];
            if (i < equipmentCount - 1) cout << ", ";
        }
    }
    cout << endl;
    cout << "==================================" << endl;
}