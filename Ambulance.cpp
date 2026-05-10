#include "Ambulance.h"
#include <iostream>

using namespace std;

void Ambulance::copyString(char*& dest, const char* src)
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

void Ambulance::resizeEmergencyArray(int newSize)
{
    if (newSize <= maxEmergencies) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < emergencyCount; i++)
        newArray[i] = emergencyCallIds[i];
    for (int i = emergencyCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] emergencyCallIds;
    emergencyCallIds = newArray;
    maxEmergencies = newSize;
}

Ambulance::Ambulance()
{
    vehicleNumber = new char[1];
    vehicleNumber[0] = '\0';
    driverName = new char[1];
    driverName[0] = '\0';
    driverContact = new char[1];
    driverContact[0] = '\0';
    ambulanceType = new char[1];
    ambulanceType[0] = '\0';
    destinationHospital = new char[1];
    destinationHospital[0] = '\0';
    equipmentList = new char[1];
    equipmentList[0] = '\0';

    ambulanceId = 0;
    isAvailable = true;
    latitude = 0.0f;
    longitude = 0.0f;
    currentPatientId = 0;
    estimatedArrivalMinutes = 0;
    fuelLevel = 100.0f;

    lastMaintenanceDate[0] = 1;
    lastMaintenanceDate[1] = 1;
    lastMaintenanceDate[2] = 2024;

    emergencyCount = 0;
    maxEmergencies = 100;
    emergencyCallIds = new int[maxEmergencies];
    for (int i = 0; i < maxEmergencies; i++)
        emergencyCallIds[i] = 0;
}

Ambulance::Ambulance(int id, const char* vehicleNo, const char* driver, const char* contact, const char* type, float lat, float lng)
{
    copyString(vehicleNumber, vehicleNo);
    copyString(driverName, driver);
    copyString(driverContact, contact);
    copyString(ambulanceType, type);
    copyString(destinationHospital, "");
    copyString(equipmentList, "Stretcher,Oxygen,Defibrillator,FirstAid");

    ambulanceId = id;
    isAvailable = true;
    latitude = lat;
    longitude = lng;
    currentPatientId = 0;
    estimatedArrivalMinutes = 0;
    fuelLevel = 100.0f;

    lastMaintenanceDate[0] = 1;
    lastMaintenanceDate[1] = 1;
    lastMaintenanceDate[2] = 2024;

    emergencyCount = 0;
    maxEmergencies = 100;
    emergencyCallIds = new int[maxEmergencies];
    for (int i = 0; i < maxEmergencies; i++)
        emergencyCallIds[i] = 0;
}

Ambulance::Ambulance(const Ambulance& other)
{
    copyString(vehicleNumber, other.vehicleNumber);
    copyString(driverName, other.driverName);
    copyString(driverContact, other.driverContact);
    copyString(ambulanceType, other.ambulanceType);
    copyString(destinationHospital, other.destinationHospital);
    copyString(equipmentList, other.equipmentList);

    ambulanceId = other.ambulanceId;
    isAvailable = other.isAvailable;
    latitude = other.latitude;
    longitude = other.longitude;
    currentPatientId = other.currentPatientId;
    estimatedArrivalMinutes = other.estimatedArrivalMinutes;
    fuelLevel = other.fuelLevel;

    lastMaintenanceDate[0] = other.lastMaintenanceDate[0];
    lastMaintenanceDate[1] = other.lastMaintenanceDate[1];
    lastMaintenanceDate[2] = other.lastMaintenanceDate[2];

    emergencyCount = other.emergencyCount;
    maxEmergencies = other.maxEmergencies;
    emergencyCallIds = new int[maxEmergencies];
    for (int i = 0; i < maxEmergencies; i++)
        emergencyCallIds[i] = other.emergencyCallIds[i];
}

Ambulance& Ambulance::operator=(const Ambulance& other)
{
    if (this == &other)
        return *this;

    copyString(vehicleNumber, other.vehicleNumber);
    copyString(driverName, other.driverName);
    copyString(driverContact, other.driverContact);
    copyString(ambulanceType, other.ambulanceType);
    copyString(destinationHospital, other.destinationHospital);
    copyString(equipmentList, other.equipmentList);

    ambulanceId = other.ambulanceId;
    isAvailable = other.isAvailable;
    latitude = other.latitude;
    longitude = other.longitude;
    currentPatientId = other.currentPatientId;
    estimatedArrivalMinutes = other.estimatedArrivalMinutes;
    fuelLevel = other.fuelLevel;

    lastMaintenanceDate[0] = other.lastMaintenanceDate[0];
    lastMaintenanceDate[1] = other.lastMaintenanceDate[1];
    lastMaintenanceDate[2] = other.lastMaintenanceDate[2];

    emergencyCount = other.emergencyCount;
    if (maxEmergencies < other.maxEmergencies)
    {
        delete[] emergencyCallIds;
        maxEmergencies = other.maxEmergencies;
        emergencyCallIds = new int[maxEmergencies];
    }
    for (int i = 0; i < maxEmergencies; i++)
        emergencyCallIds[i] = other.emergencyCallIds[i];

    return *this;
}

Ambulance::~Ambulance()
{
    delete[] vehicleNumber;
    delete[] driverName;
    delete[] driverContact;
    delete[] ambulanceType;
    delete[] destinationHospital;
    delete[] equipmentList;
    delete[] emergencyCallIds;
}

int Ambulance::getAmbulanceId() const { return ambulanceId; }
const char* Ambulance::getVehicleNumber() const { return vehicleNumber; }
const char* Ambulance::getDriverName() const { return driverName; }
const char* Ambulance::getDriverContact() const { return driverContact; }
const char* Ambulance::getAmbulanceType() const { return ambulanceType; }
bool Ambulance::getIsAvailable() const { return isAvailable; }
float Ambulance::getLatitude() const { return latitude; }
float Ambulance::getLongitude() const { return longitude; }
int Ambulance::getCurrentPatientId() const { return currentPatientId; }
float Ambulance::getFuelLevel() const { return fuelLevel; }

void Ambulance::setAvailability(bool available) { isAvailable = available; }
void Ambulance::setLocation(float lat, float lng) { latitude = lat; longitude = lng; }
void Ambulance::setFuelLevel(float level) { if (level >= 0 && level <= 100) fuelLevel = level; }

void Ambulance::updateDriver(const char* name, const char* contact)
{
    copyString(driverName, name);
    copyString(driverContact, contact);
}

bool Ambulance::dispatchToEmergency(int emergencyId, int patientId)
{
    if (!isAvailable) return false;
    if (fuelLevel < 20) return false;

    if (emergencyCount >= maxEmergencies)
        resizeEmergencyArray(maxEmergencies + 50);

    emergencyCallIds[emergencyCount] = emergencyId;
    emergencyCount++;

    currentPatientId = patientId;
    isAvailable = false;
    return true;
}

bool Ambulance::completeEmergency()
{
    if (isAvailable) return false;

    currentPatientId = 0;
    isAvailable = true;
    estimatedArrivalMinutes = 0;
    return true;
}

float Ambulance::calculateDistanceTo(float targetLat, float targetLng) const
{
    float latDiff = targetLat - latitude;
    float lngDiff = targetLng - longitude;
    return (latDiff * latDiff + lngDiff * lngDiff) * 111.0f;
}

int Ambulance::calculateETA(float targetLat, float targetLng) const
{
    float distance = calculateDistanceTo(targetLat, targetLng);
    return (int)(distance / 60.0f);
}

bool Ambulance::needsMaintenance() const
{
    return fuelLevel < 15;
}

void Ambulance::recordMaintenance(int day, int month, int year)
{
    lastMaintenanceDate[0] = day;
    lastMaintenanceDate[1] = month;
    lastMaintenanceDate[2] = year;
    fuelLevel = 100.0f;
}

int Ambulance::getTotalEmergenciesHandled() const
{
    return emergencyCount;
}

void Ambulance::display() const
{
    cout << "Ambulance ID: " << ambulanceId << " | " << vehicleNumber;
    cout << " | Driver: " << driverName;
    cout << " | Status: " << (isAvailable ? "Available" : "On Route");
    cout << " | Fuel: " << fuelLevel << "%" << endl;
}

void Ambulance::displayFullDetails() const
{
    cout << "\n========== AMBULANCE DETAILS ==========" << endl;
    cout << "ID: " << ambulanceId << endl;
    cout << "Vehicle Number: " << vehicleNumber << endl;
    cout << "Type: " << ambulanceType << endl;
    cout << "Driver: " << driverName << endl;
    cout << "Driver Contact: " << driverContact << endl;
    cout << "Status: " << (isAvailable ? "Available" : "On Emergency") << endl;
    cout << "Current Location: (" << latitude << ", " << longitude << ")" << endl;
    cout << "Fuel Level: " << fuelLevel << "%" << endl;
    cout << "Emergencies Handled: " << emergencyCount << endl;
    cout << "Equipment: " << equipmentList << endl;
    cout << "Last Maintenance: " << lastMaintenanceDate[0] << "/" << lastMaintenanceDate[1] << "/" << lastMaintenanceDate[2] << endl;
    if (needsMaintenance()) cout << "MAINTENANCE REQUIRED!" << endl;
    cout << "=======================================" << endl;
}