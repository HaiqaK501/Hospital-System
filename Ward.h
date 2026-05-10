#pragma once

class Ward
{
private:
    int wardId;
    char* wardName;
    char* wardType;
    int totalBeds;
    int occupiedBeds;
    int availableBeds;
    int* patientIds;
    int patientCount;
    int maxPatients;
    float dailyRate;
    char* nurseInCharge;
    int* nurseIds;
    int nurseCount;
    int maxNurses;
    char** equipmentList;
    int equipmentCount;
    int maxEquipment;
    bool isIsolationWard;

public:
    Ward();
    Ward(int id, const char* name, const char* type, int beds, float rate, const char* nurse, bool isolation);
    Ward(const Ward& other);
    Ward& operator=(const Ward& other);
    ~Ward();

    int getWardId() const;
    int getID() { return wardId; }
    const char* getWardName() const;
    const char* getWardType() const;
    int getTotalBeds() const;
    int getOccupiedBeds() const;
    int getAvailableBeds() const;
    float getDailyRate() const;
    const char* getNurseInCharge() const;
    bool getIsIsolationWard() const;

    bool admitPatient(int patientId);
    bool dischargePatient(int patientId);
    bool assignNurse(int nurseId);
    bool removeNurse(int nurseId);
    void addEquipment(const char* equipment);
    float getOccupancyRate() const;
    int getAvailableIsolationBeds() const;
    float calculateMonthlyRevenue() const;
    bool hasAvailableBed() const;

    void display() const;
    void displayFullDetails() const;

private:
    void copyString(char*& dest, const char* src);
    void resizePatientArray(int newSize);
    void resizeNurseArray(int newSize);
    void resizeEquipmentArray(int newSize);
};