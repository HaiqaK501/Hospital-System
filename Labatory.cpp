#include "Labatory.h"
#include <iostream>

using namespace std;

void Laboratory::copyString(char*& dest, const char* src)
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

void Laboratory::resizePatientArray(int newSize)
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

void Laboratory::resizeAppointmentArray(int newSize)
{
    if (newSize <= maxAppointments) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < appointmentCount; i++)
        newArray[i] = appointmentIds[i];
    for (int i = appointmentCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] appointmentIds;
    appointmentIds = newArray;
    maxAppointments = newSize;
}

void Laboratory::resizeEquipmentArray(int newSize)
{
    if (newSize <= maxEquipment) return;

    char** newArray = new char* [newSize];
    for (int i = 0; i < equipmentCount; i++)
    {
        newArray[i] = new char[50];
        copyString(newArray[i], equipmentRequired[i]);
    }
    for (int i = equipmentCount; i < newSize; i++)
        newArray[i] = nullptr;

    for (int i = 0; i < equipmentCount; i++)
        delete[] equipmentRequired[i];
    delete[] equipmentRequired;

    equipmentRequired = newArray;
    maxEquipment = newSize;
}

Laboratory::Laboratory()
{
    testName = new char[1];
    testName[0] = '\0';
    testType = new char[1];
    testType[0] = '\0';
    normalRange = new char[1];
    normalRange[0] = '\0';
    unit = new char[1];
    unit[0] = '\0';

    testId = 0;
    cost = 0.0f;
    processingTimeHours = 0;
    isAvailable = true;

    patientCount = 0;
    maxPatients = 50;
    patientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++)
        patientIds[i] = 0;

    appointmentCount = 0;
    maxAppointments = 50;
    appointmentIds = new int[maxAppointments];
    for (int i = 0; i < maxAppointments; i++)
        appointmentIds[i] = 0;

    equipmentCount = 0;
    maxEquipment = 10;
    equipmentRequired = new char* [maxEquipment];
    for (int i = 0; i < maxEquipment; i++)
        equipmentRequired[i] = nullptr;
}

Laboratory::Laboratory(int id, const char* name, const char* type, float cst, int hours, const char* range, const char* u)
{
    copyString(testName, name);
    copyString(testType, type);
    copyString(normalRange, range);
    copyString(unit, u);

    testId = id;
    cost = cst;
    processingTimeHours = hours;
    isAvailable = true;

    patientCount = 0;
    maxPatients = 50;
    patientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++)
        patientIds[i] = 0;

    appointmentCount = 0;
    maxAppointments = 50;
    appointmentIds = new int[maxAppointments];
    for (int i = 0; i < maxAppointments; i++)
        appointmentIds[i] = 0;

    equipmentCount = 0;
    maxEquipment = 10;
    equipmentRequired = new char* [maxEquipment];
    for (int i = 0; i < maxEquipment; i++)
        equipmentRequired[i] = nullptr;
}

Laboratory::Laboratory(const Laboratory& other)
{
    copyString(testName, other.testName);
    copyString(testType, other.testType);
    copyString(normalRange, other.normalRange);
    copyString(unit, other.unit);

    testId = other.testId;
    cost = other.cost;
    processingTimeHours = other.processingTimeHours;
    isAvailable = other.isAvailable;

    patientCount = other.patientCount;
    maxPatients = other.maxPatients;
    patientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++)
        patientIds[i] = other.patientIds[i];

    appointmentCount = other.appointmentCount;
    maxAppointments = other.maxAppointments;
    appointmentIds = new int[maxAppointments];
    for (int i = 0; i < maxAppointments; i++)
        appointmentIds[i] = other.appointmentIds[i];

    equipmentCount = other.equipmentCount;
    maxEquipment = other.maxEquipment;
    equipmentRequired = new char* [maxEquipment];
    for (int i = 0; i < equipmentCount; i++)
    {
        equipmentRequired[i] = new char[50];
        copyString(equipmentRequired[i], other.equipmentRequired[i]);
    }
    for (int i = equipmentCount; i < maxEquipment; i++)
        equipmentRequired[i] = nullptr;
}

Laboratory& Laboratory::operator=(const Laboratory& other)
{
    if (this == &other)
        return *this;

    copyString(testName, other.testName);
    copyString(testType, other.testType);
    copyString(normalRange, other.normalRange);
    copyString(unit, other.unit);

    testId = other.testId;
    cost = other.cost;
    processingTimeHours = other.processingTimeHours;
    isAvailable = other.isAvailable;

    patientCount = other.patientCount;
    if (maxPatients < other.maxPatients)
    {
        delete[] patientIds;
        maxPatients = other.maxPatients;
        patientIds = new int[maxPatients];
    }
    for (int i = 0; i < maxPatients; i++)
        patientIds[i] = other.patientIds[i];

    appointmentCount = other.appointmentCount;
    if (maxAppointments < other.maxAppointments)
    {
        delete[] appointmentIds;
        maxAppointments = other.maxAppointments;
        appointmentIds = new int[maxAppointments];
    }
    for (int i = 0; i < maxAppointments; i++)
        appointmentIds[i] = other.appointmentIds[i];

    for (int i = 0; i < equipmentCount; i++)
        delete[] equipmentRequired[i];

    if (maxEquipment < other.maxEquipment)
    {
        delete[] equipmentRequired;
        maxEquipment = other.maxEquipment;
        equipmentRequired = new char* [maxEquipment];
    }

    equipmentCount = other.equipmentCount;
    for (int i = 0; i < equipmentCount; i++)
    {
        equipmentRequired[i] = new char[50];
        copyString(equipmentRequired[i], other.equipmentRequired[i]);
    }
    for (int i = equipmentCount; i < maxEquipment; i++)
        equipmentRequired[i] = nullptr;

    return *this;
}

Laboratory::~Laboratory()
{
    delete[] testName;
    delete[] testType;
    delete[] normalRange;
    delete[] unit;
    delete[] patientIds;
    delete[] appointmentIds;

    for (int i = 0; i < equipmentCount; i++)
        delete[] equipmentRequired[i];
    delete[] equipmentRequired;
}

int Laboratory::getTestId() const { return testId; }
const char* Laboratory::getTestName() const { return testName; }
const char* Laboratory::getTestType() const { return testType; }
float Laboratory::getCost() const { return cost; }
int Laboratory::getProcessingTime() const { return processingTimeHours; }
const char* Laboratory::getNormalRange() const { return normalRange; }
const char* Laboratory::getUnit() const { return unit; }
bool Laboratory::getIsAvailable() const { return isAvailable; }

void Laboratory::setCost(float cst) { cost = cst; }
void Laboratory::setProcessingTime(int hours) { processingTimeHours = hours; }
void Laboratory::setIsAvailable(bool available) { isAvailable = available; }

bool Laboratory::assignToPatient(int patientId)
{
    if (patientCount >= maxPatients)
        resizePatientArray(maxPatients + 20);

    for (int i = 0; i < patientCount; i++)
        if (patientIds[i] == patientId)
            return false;

    patientIds[patientCount] = patientId;
    patientCount++;
    return true;
}

bool Laboratory::removeFromPatient(int patientId)
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

bool Laboratory::assignToAppointment(int appointmentId)
{
    if (appointmentCount >= maxAppointments)
        resizeAppointmentArray(maxAppointments + 20);

    appointmentIds[appointmentCount] = appointmentId;
    appointmentCount++;
    return true;
}

void Laboratory::addEquipment(const char* equipment)
{
    if (equipmentCount >= maxEquipment)
        resizeEquipmentArray(maxEquipment + 5);

    equipmentRequired[equipmentCount] = new char[50];
    copyString(equipmentRequired[equipmentCount], equipment);
    equipmentCount++;
}

bool Laboratory::hasEquipment(const char* equipment) const
{
    for (int i = 0; i < equipmentCount; i++)
    {
        int j = 0;
        bool match = true;
        while (equipmentRequired[i][j] != '\0' && equipment[j] != '\0')
        {
            if (equipmentRequired[i][j] != equipment[j])
            {
                match = false;
                break;
            }
            j++;
        }
        if (match && equipmentRequired[i][j] == '\0' && equipment[j] == '\0')
            return true;
    }
    return false;
}

float Laboratory::calculateTotalRevenue() const
{
    return cost * appointmentCount;
}

int Laboratory::getPendingResultsCount() const
{
    return appointmentCount;
}

void Laboratory::display() const
{
    cout << "Test ID: " << testId << " | " << testName << " | Cost: Rs. " << cost;
    cout << " | Time: " << processingTimeHours << " hrs" << endl;
}

void Laboratory::displayFullDetails() const
{
    cout << "\n========== LAB TEST DETAILS ==========" << endl;
    cout << "ID: " << testId << endl;
    cout << "Test Name: " << testName << endl;
    cout << "Test Type: " << testType << endl;
    cout << "Cost: Rs. " << cost << endl;
    cout << "Processing Time: " << processingTimeHours << " hours" << endl;
    cout << "Normal Range: " << normalRange << " " << unit << endl;
    cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    cout << "Total Patients: " << patientCount << endl;
    cout << "Pending Results: " << appointmentCount << endl;
    cout << "Revenue Generated: Rs. " << calculateTotalRevenue() << endl;
    cout << "Equipment Required: ";
    if (equipmentCount == 0) cout << "None";
    else
    {
        for (int i = 0; i < equipmentCount; i++)
        {
            cout << equipmentRequired[i];
            if (i < equipmentCount - 1) cout << ", ";
        }
    }
    cout << endl;
    cout << "======================================" << endl;
}