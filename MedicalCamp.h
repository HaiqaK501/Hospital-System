#pragma once

class Doctor;
class Nurse;
class Volunteer;
class Patient;
class Pharmacy;

class MedicalCamp
{
private:
    int campId;
    char* campName;
    char* location;
    char* startDate;
    char* endDate;
    char* organizer;
    float budget;
    float expenses;

    int* doctorIds;
    int doctorCount;
    int maxDoctors;

    int* nurseIds;
    int nurseCount;
    int maxNurses;

    int* volunteerIds;
    int volunteerCount;
    int maxVolunteers;

    int* patientIds;
    int patientCount;
    int maxPatients;

    char** servicesOffered;
    int serviceCount;
    int maxServices;

    int* pharmacyIds;
    int pharmacyCount;
    int maxPharmacies;

    bool isCompleted;
   

public:
    MedicalCamp();
    MedicalCamp(int id, const char* name, const char* loc, const char* start, const char* end, const char* org, float bud);
    MedicalCamp(const MedicalCamp& other);
    MedicalCamp& operator=(const MedicalCamp& other);
    ~MedicalCamp();
    int getID() { return campId; }
    int getCampId() const;
    const char* getCampName() const;
    const char* getLocation() const;
    const char* getStartDate() const;
    const char* getEndDate() const;
    float getBudget() const;
    float getExpenses() const;
    bool getIsCompleted() const;

    void addService(const char* service);
    bool assignDoctor(const Doctor& doctor);
    bool assignNurse(const Nurse& nurse);
    bool assignVolunteer(const Volunteer& volunteer);
    bool registerPatient(const Patient& patient);
    bool assignPharmacy(const Pharmacy& pharmacy);

    bool removeDoctor(int doctorId);
    bool removeNurse(int nurseId);
    bool removeVolunteer(int volunteerId);
    bool removePatient(int patientId);
    bool removePharmacy(int pharmacyId);

    void addExpense(float amount);
    float getRemainingBudget() const;
    int getTotalPatientsServed() const;
    float getCostPerPatient() const;
    void completeCamp();
    bool isCampActive() const;

    int getDoctorCount() const;
    int getNurseCount() const;
    int getVolunteerCount() const;
    int getPharmacyCount() const;
    const int* getDoctorIds() const;
    const int* getNurseIds() const;
    const int* getVolunteerIds() const;
    const int* getPatientIds() const;
    const int* getPharmacyIds() const;

    void display() const;
    void displayFullDetails() const;

private:
    void copyString(char*& dest, const char* src);
    void resizeDoctorArray(int newSize);
    void resizeNurseArray(int newSize);
    void resizeVolunteerArray(int newSize);
    void resizePatientArray(int newSize);
    void resizeServicesArray(int newSize);
    void resizePharmacyArray(int newSize);
};