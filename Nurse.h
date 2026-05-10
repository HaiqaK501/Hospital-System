#pragma once

#include "Person.h"

class Doctor;
class Patient;
class Admin;

class Nurse : public Person
{
private:
    char* specialization;
    char* shift;
    char* assignedWard;
    float salary;
    int experienceYears;
    int* assignedDoctorIds;
    int assignedDoctorCount;
    int maxDoctors;

    int* assignedPatientIds;
    int assignedPatientCount;
    int maxPatients;

    char** certifications;
    int certificationCount;
    int maxCertifications;

    float overtimeHours;
    int sickLeavesTaken;
    int annualLeavesTaken;
    int performanceRating;
    bool isHeadNurse;

    char* emergencyContact;
    char* bloodGroup;

public:
    Nurse();
    Nurse(int id, const char* name, const char* password, const char* specialization,
        const char* shift, const char* ward, float salary, int experience);
    Nurse(const Nurse& other);
    Nurse& operator=(const Nurse& other);
    virtual ~Nurse();

    const char* getSpecialization() const;
    const char* getShift() const;
    const char* getAssignedWard() const;
    float getSalary() const;
    int getExperience() const;
    float getOvertimeHours() const;
    int getSickLeavesTaken() const;
    int getAnnualLeavesTaken() const;
    int getPerformanceRating() const;
    bool getIsHeadNurse() const;
    const char* getEmergencyContact() const;
    const char* getBloodGroup() const;

    void setSpecialization(const char* spec);
    void setShift(const char* shiftTime);
    void setAssignedWard(const char* ward);
    void setSalary(float sal);
    void setExperience(int years);
    void setOvertimeHours(float hours);
    void setPerformanceRating(int rating);
    void setIsHeadNurse(bool head);
    void setEmergencyContact(const char* contact);
    void setBloodGroup(const char* bg);

    bool assignToDoctor(int doctorId);
    bool removeFromDoctor(int doctorId);
    const int* getAssignedDoctorIds() const;
    int getAssignedDoctorCount() const;

    bool assignToPatient(int patientId);
    bool removeFromPatient(int patientId);
    const int* getAssignedPatientIds() const;
    int getAssignedPatientCount() const;

    bool addCertification(const char* certification);
    bool removeCertification(const char* certification);
    const char** getCertifications() const;
    int getCertificationCount() const;
    bool hasCertification(const char* certification) const;

    void takeSickLeave(int days);
    void takeAnnualLeave(int days);
    int getRemainingLeaves() const;

    float calculateBonus() const;
    bool isEligibleForPromotion() const;
    float calculateOvertimePay() const;
    void addOvertime(float hours);

    void conductTraining(const char* trainingName);
    void receivePerformanceReview(int rating);
    bool requestShiftChange(const char* newShift);

    float getAnnualSalaryWithBonus() const;
    int getTotalPatientsAssigned() const;
    float getPatientPerDoctorRatio() const;

    bool operator==(const Nurse& other) const;
    bool operator<(const Nurse& other) const;
    bool operator>(const Nurse& other) const;
    Nurse& operator+=(float overtimeAmount);
    Nurse& operator-=(int leaveDays);

    void display() const;
    void displayFullDetails() const;
    void displayInfoToBuffer(char* buffer, int bufferSize) const;
    virtual void showMenu();
    virtual void displayInfo() const;

    // Relationship methods with other classes
    bool workWithDoctor(const Doctor& doctor);
    bool careForPatient(const Patient& patient);
    bool reportToAdmin(const Admin& admin);

private:
    void copyString(char*& dest, const char* src);
    void resizeDoctorArray(int newSize);
    void resizePatientArray(int newSize);
    void resizeCertificationArray(int newSize);
};