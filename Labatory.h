#pragma once

class Laboratory
{
private:
    int testId;
    char* testName;
    char* testType;
    float cost;
    int processingTimeHours;
    char* normalRange;
    char* unit;
    int* patientIds;
    int patientCount;
    int maxPatients;
    int* appointmentIds;
    int appointmentCount;
    int maxAppointments;
    char** equipmentRequired;
    int equipmentCount;
    int maxEquipment;
    bool isAvailable;

public:
    Laboratory();
    Laboratory(int id, const char* name, const char* type, float cst, int hours, const char* range, const char* u);
    Laboratory(const Laboratory& other);
    Laboratory& operator=(const Laboratory& other);
    ~Laboratory();

    int getTestId() const;
    const char* getTestName() const;
    const char* getTestType() const;
    float getCost() const;
    int getProcessingTime() const;
    const char* getNormalRange() const;
    const char* getUnit() const;
    bool getIsAvailable() const;

    void setCost(float cst);
    void setProcessingTime(int hours);
    void setIsAvailable(bool available);

    bool assignToPatient(int patientId);
    bool removeFromPatient(int patientId);
    bool assignToAppointment(int appointmentId);
    void addEquipment(const char* equipment);
    bool hasEquipment(const char* equipment) const;
    float calculateTotalRevenue() const;
    int getPendingResultsCount() const;

    void display() const;
    void displayFullDetails() const;
    int getID() {
        return testId;
    }

private:
    void copyString(char*& dest, const char* src);
    void resizePatientArray(int newSize);
    void resizeAppointmentArray(int newSize);
    void resizeEquipmentArray(int newSize);
};
