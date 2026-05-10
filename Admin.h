#pragma once



#include "Person.h"

class Doctor;
class Patient;
class Nurse;
class Appointment;
class Bill;
class Pharmacy;
class Laboratory;
class Ambulance;
class Ward;
class Vaccination;
class Volunteer;
class MedicalCamp;
class BloodDonor;
class CashDonor;
class OrganDonor;

class Admin : public Person
{
private:
    char* department;
    char* accessLevel;
    int employeeId;
    float salary;
    char* joinDate;
    bool isSuperAdmin;

    int* managedDoctorIds;
    int managedDoctorCount;
    int maxManagedDoctors;

    int* managedNurseIds;
    int managedNurseCount;
    int maxManagedNurses;

    int* managedVolunteerIds;
    int managedVolunteerCount;
    int maxManagedVolunteers;

    int* auditLogIds;
    int auditLogCount;
    int maxAuditLogs;

public:
    Admin();
    Admin(int id, const char* name, const char* password, const char* dept,
        const char* access, int empId, float sal, const char* join, bool super);
    Admin(const Admin& other);
    Admin& operator=(const Admin& other);
    virtual ~Admin();

    const char* getDepartment() const;
    const char* getAccessLevel() const;
    int getEmployeeId() const;
    float getSalary() const;
    const char* getJoinDate() const;
    bool getIsSuperAdmin() const;

    void setDepartment(const char* dept);
    void setAccessLevel(const char* level);
    void setSalary(float sal);

    // Doctor Management
    bool addDoctor(const Doctor& doctor);
    bool removeDoctor(int doctorId);
    bool updateDoctorFee(int doctorId, float newFee);

    // Nurse Management
    bool addNurse(const Nurse& nurse);
    bool removeNurse(int nurseId);
    bool updateNurseShift(int nurseId, const char* newShift);

    // Volunteer Management
    bool addVolunteer(const Volunteer& volunteer);
    bool removeVolunteer(int volunteerId);
    bool approveVolunteerTraining(int volunteerId);

    // Pharmacy Management
    bool addMedicine(const Pharmacy& medicine);
    bool removeMedicine(int medicineId);
    bool updateMedicineStock(int medicineId, int newStock);
    bool checkLowStockMedicines() const;

    // Laboratory Management
    bool addLabTest(const Laboratory& test);
    bool removeLabTest(int testId);
    bool updateLabTestCost(int testId, float newCost);

    // Ambulance Management
    bool addAmbulance(const Ambulance& ambulance);
    bool removeAmbulance(int ambulanceId);
    bool dispatchAmbulance(int ambulanceId, int emergencyId, int patientId);
    bool checkAmbulanceMaintenance() const;

    // Ward Management
    bool addWard(const Ward& ward);
    bool removeWard(int wardId);
    bool admitPatientToWard(int patientId, int wardId);
    bool dischargePatientFromWard(int patientId, int wardId);
    float getTotalWardRevenue() const;

    // Vaccination Management
    bool addVaccine(const Vaccination& vaccine);
    bool removeVaccine(int vaccineId);
    bool restockVaccine(int vaccineId, int doses);
    void viewVaccinationCampaignReport() const;

    // Medical Camp Management
    bool organizeMedicalCamp(const MedicalCamp& camp);
    bool completeMedicalCamp(int campId);
    bool assignDoctorToCamp(int doctorId, int campId);
    bool assignNurseToCamp(int nurseId, int campId);
    bool assignVolunteerToCamp(int volunteerId, int campId);
    void viewAllMedicalCamps() const;
    float getTotalCampExpenses() const;
    int getTotalCampPatients() const;

    // Donor Management (Blood, Cash, Organ)
    bool registerBloodDonor(const BloodDonor& donor);
    bool registerCashDonor(const CashDonor& donor);
    bool registerOrganDonor(const OrganDonor& donor);
    bool removeDonor(int donorId);
    void viewAllDonors() const;
    void viewBloodDonors() const;
    void viewCashDonors() const;
    void viewOrganDonors() const;
    float getTotalCashDonations() const;
    int getTotalBloodDonations() const;
    int getTotalOrganDonors() const;
    void generateDonorReport() const;

    // Audit and Logging
    void addAuditLog(const char* action);
    void viewSecurityLog() const;

    // Reporting
    bool generateDailyReport(const char* date) const;
    bool generateWeeklyReport() const;
    bool generateMonthlyReport() const;
    void viewAllPatients() const;
    void viewAllDoctors() const;
    void viewAllAppointments() const;
    void viewUnpaidBills() const;
    bool dischargePatient(Patient& patient);

    // Hospital Statistics
    float calculateTotalRevenue() const;
    int getTotalRegisteredPatients() const;
    int getTotalDoctors() const;
    float getHospitalOccupancyRate() const;
    void viewHospitalStatistics() const;
    void viewFinancialSummary() const;

    virtual void display() const;
    virtual void showMenu();
    virtual void displayInfo() const;

    bool operator==(const Admin& other) const;

private:
    void copyString(char*& dest, const char* src);
    void resizeDoctorArray(int newSize);
    void resizeNurseArray(int newSize);
    void resizeVolunteerArray(int newSize);
    void resizeAuditArray(int newSize);
};


