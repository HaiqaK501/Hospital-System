#pragma once

#include <iostream>

#include "Person.h"
#include <ctime>
#include "Storage.h" 

using namespace std;


class Patient;
class Nurse;
class Ward;
class Appointment;
class Bill;
class Prescription;

class Doctor : public Person
{
private:
    // Professional Information
    char* specialization;
    float consultationFee;
    char* education;
    char* hospitalBranch;
    int yearsOfExperience;
    float rating;
    int totalPatientsTreated;
    bool isAvailable;

    // Relationships
    int* assignedPatientIds;
    int assignedPatientCount;
    int maxPatients;

    int* assignedNurseIds;
    int assignedNurseCount;
    int maxNurses;

    int* assignedWardIds;
    int assignedWardCount;
    int maxWards;

    int* appointmentIds;
    int appointmentCount;
    int maxAppointments;

public:
    // Constructors
    Doctor();
    Doctor(int id, const char* name, const char* password, const char* specialization,
        float fee, int experience, const char* education, const char* branch);
    Doctor(const Doctor& other);
    Doctor& operator=(const Doctor& other);
    virtual ~Doctor();

    // Getters
    const char* getSpecialization() const;
    float getFee() const;
    const char* getEducation() const;
    const char* getHospitalBranch() const;
    int getYearsOfExperience() const;
    float getRating() const;
    int getTotalPatientsTreated() const;
    bool getIsAvailable() const;
    int getAssignedPatientCount() const;
    int getAssignedNurseCount() const;
    int getAssignedWardCount() const;
    int getAppointmentCount() const;

    // Setters
    void setSpecialization(const char* spec);
    void setFee(float fee);
    void setEducation(const char* edu);
    void setHospitalBranch(const char* branch);
    void setRating(float r);
    void setIsAvailable(bool available);
    void addExperience(int years);
    void incrementPatientsTreated();

    // Patient Management
    bool assignPatient(int patientId);
    bool removePatient(int patientId);
    const int* getAssignedPatientIds() const;
    bool consultWithPatient(Patient& patient);
    void viewAssignedPatients(Storage<Patient>& patientStorage) const;

    // Nurse Management (Relationship)
    bool assignNurse(int nurseId);
    bool removeNurse(int nurseId);
    const int* getAssignedNurseIds() const;
    bool superviseNurse(Nurse& nurse);
    void viewAssignedNurses(Storage<Nurse>& nurseStorage) const;

    // Ward Management (Relationship)
    bool assignToWard(int wardId);
    bool removeFromWard(int wardId);
    const int* getAssignedWardIds() const;
    bool workInWard(Ward& ward);
    void viewAssignedWards(Storage<Ward>& wardStorage) const;

    // Appointment Management
    bool addAppointment(int appointmentId);
    bool removeAppointment(int appointmentId);
    const int* getAppointmentIds() const;

    // REQUIRED FUNCTIONS
    void viewTodayAppointments(Storage<Appointment>& appointmentStorage,
        Storage<Patient>& patientStorage, const char* todayDate);
    void markAppointmentComplete(Storage<Appointment>& appointmentStorage,
        Storage<Bill>& billStorage);
    void markAppointmentNoShow(Storage<Appointment>& appointmentStorage,
        Storage<Bill>& billStorage);
    void writePrescription(Storage<Appointment>& appointmentStorage,
        Storage<Prescription>& prescriptionStorage,
        Storage<Patient>& patientStorage);
    void viewPatientMedicalHistory(Storage<Patient>& patientStorage,
        Storage<Prescription>& prescriptionStorage,
        Storage<Doctor>& doctorStorage);

    // Additional Features
    void updateAvailability();
    void viewMyStatistics() const;
    void viewFinancialSummary() const;
    bool canTakeMorePatients() const;
    void updateRating(float newRating);
    float getSuccessRate() const;
    bool isTopPerformer() const;
    float calculateBonus() const;
    float calculateAnnualEarnings() const;
    int getTodayAppointmentCount(const char* todayDate, Storage<Appointment>& appointmentStorage) const;
    bool isAvailableForAppointment(const char* date, const char* timeSlot) const;

    // Required Operators
    bool operator==(const Doctor& other) const;
    friend ostream& operator<<(ostream& out, const Doctor& doctor);

    // Display Methods
    virtual void display() const;
    virtual void showMenu();
    virtual void displayInfo() const;
    void displayFullDetails() const;
    void displayInfoToBuffer(char* buffer, int bufferSize) const;

private:
    void copyString(char*& dest, const char* src);
    void resizePatientArray(int newSize);
    void resizeNurseArray(int newSize);
    void resizeWardArray(int newSize);
    void resizeAppointmentArray(int newSize);

    // Helper for date comparison
    bool isToday(const char* appointmentDate, const char* todayDate) const;
    int compareDates(const char* date1, const char* date2) const;
};