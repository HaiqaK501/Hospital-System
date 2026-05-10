#pragma once

class Vaccination
{
private:
    int vaccineId;
    char* vaccineName;
    char* manufacturer;
    int dosesRequired;
    int intervalDays;
    float storageTemperature;
    int stockDoses;
    int expiryDays;
    int* patientIds;
    int patientCount;
    int maxPatients;
    int** doseDates;
    int* dosesGiven;
    char* ageGroup;
    char* sideEffects;
    float price;
    bool isEmergencyUse;

public:
    Vaccination();
    Vaccination(int id, const char* name, const char* manu, int doses, int interval, float temp, int stock, int expiry, const char* age, float pr, bool emergency);
    Vaccination(const Vaccination& other);
    Vaccination& operator=(const Vaccination& other);
    ~Vaccination();

    int getVaccineId() const;
    int getID() { return vaccineId; }
    const char* getVaccineName() const;
    const char* getManufacturer() const;
    int getDosesRequired() const;
    int getIntervalDays() const;
    float getStorageTemperature() const;
    int getStockDoses() const;
    const char* getAgeGroup() const;
    float getPrice() const;

    void addStock(int doses);
    bool removeStock(int doses);
    bool administerDose(int patientId, const char* date, int doseNumber);
    bool isVaccineExpiringSoon() const;
    int getPatientsFullyVaccinated() const;
    int getPatientsPartiallyVaccinated() const;
    float calculateCoverageRate() const;
    bool isEligibleForAge(int age) const;
    void recordSideEffect(int patientId, const char* effect);
    float calculateRevenue() const;

    void display() const;
    void displayFullDetails() const;

private:
    void copyString(char*& dest, const char* src);
    void resizePatientArray(int newSize);
    void allocateDoseDates();
    int parseDateToInt(const char* date) const;
};
