#pragma once

class Ambulance
{
private:
    int ambulanceId;
    char* vehicleNumber;
    char* driverName;
    char* driverContact;
    char* ambulanceType;
    bool isAvailable;
    float latitude;
    float longitude;
    int* emergencyCallIds;
    int emergencyCount;
    int maxEmergencies;
    int currentPatientId;
    char* destinationHospital;
    int estimatedArrivalMinutes;
    char* equipmentList;
    float fuelLevel;
    int lastMaintenanceDate[3];

public:
    Ambulance();
    Ambulance(int id, const char* vehicleNo, const char* driver, const char* contact, const char* type, float lat, float lng);
    Ambulance(const Ambulance& other);
    Ambulance& operator=(const Ambulance& other);
    ~Ambulance();

    int getAmbulanceId() const;
    int getID() { return ambulanceId; }
    const char* getVehicleNumber() const;
    const char* getDriverName() const;
    const char* getDriverContact() const;
    const char* getAmbulanceType() const;
    bool getIsAvailable() const;
    float getLatitude() const;
    float getLongitude() const;
    int getCurrentPatientId() const;
    float getFuelLevel() const;

    void setAvailability(bool available);
    void setLocation(float lat, float lng);
    void setFuelLevel(float level);
    void updateDriver(const char* name, const char* contact);

    bool dispatchToEmergency(int emergencyId, int patientId);
    bool completeEmergency();
    float calculateDistanceTo(float targetLat, float targetLng) const;
    int calculateETA(float targetLat, float targetLng) const;
    bool needsMaintenance() const;
    void recordMaintenance(int day, int month, int year);
    int getTotalEmergenciesHandled() const;

    void display() const;
    void displayFullDetails() const;

private:
    void copyString(char*& dest, const char* src);
    void resizeEmergencyArray(int newSize);
};