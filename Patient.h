#pragma once

#include "Person.h"
#include "Prescription.h"
#include "Storage.h"

class Doctor;
class Appointment;
class Bill;
class Nurse;
class Ward;


class Patient : public Person
{
private:
    // Personal Information
    int age;
    char* gender;
    char* contact;
    float balance;
    char* bloodGroup;
    char* emergencyContact;
    char* address;
    char* medicalHistory;

    // Admission/Discharge
    char* admissionDate;
    char* dischargeDate;
    bool isDischarged;
    bool isAdmitted;
    int wardId;
    int assignedNurseId;
    char* vitalSigns;

    // Relationships
    int* assignedDoctorIds;
    int assignedDoctorCount;
    int maxDoctors;

    int* appointmentIds;
    int appointmentCount;
    int maxAppointments;

    int* billIds;
    int billCount;
    int maxBills;

public:
    // Constructors
    Patient();
    Patient(int id, const char* name, const char* password, int age, const char* gender,
        const char* contact, float balance, const char* bloodGroup, const char* emergencyContact);
    Patient(const Patient& other);
    Patient& operator=(const Patient& other);
    virtual ~Patient();

    // Getters
    int getAge() const;
    const char* getGender() const;
    const char* getContact() const;
    float getBalance() const;
    const char* getBloodGroup() const;
    const char* getEmergencyContact() const;
    const char* getAddress() const;
    const char* getMedicalHistory() const;
    const char* getAdmissionDate() const;
    const char* getDischargeDate() const;
    bool getIsDischarged() const;
    bool getIsAdmitted() const;
    int getWardId() const;
    int getAssignedNurseId() const;
    const char* getVitalSigns() const;
    int getAssignedDoctorCount() const;
    int getAppointmentCount() const;
    int getBillCount() const;

    // Setters
    void setAge(int a);
    void setGender(const char* g);
    void setContact(const char* c);
    void setBalance(float bal);
    void setBloodGroup(const char* bg);
    void setEmergencyContact(const char* ec);
    void setAddress(const char* addr);
    void setMedicalHistory(const char* history);
    void setAdmissionDate(const char* date);
    void setDischargeDate(const char* date);
    void setIsDischarged(bool discharged);
    void setIsAdmitted(bool admitted);
    void setWardId(int wId);
    void setAssignedNurseId(int nId);
    void setVitalSigns(const char* vitals);

    // Doctor management
    bool assignDoctor(int doctorId);
    bool removeDoctor(int doctorId);
    const int* getAssignedDoctorIds() const;

    // Appointment management
    bool addAppointment(int appointmentId);
    bool removeAppointment(int appointmentId);
    const int* getAppointmentIds() const;

    // Bill management
    bool addBill(int billId);
    bool removeBill(int billId);
    const int* getBillIds() const;

    // Nurse & Ward relationships
    void admitToWard(int wardId, const char* date);
    void dischargeFromWard(const char* date);
    void assignNurse(int nurseId);
    void updateVitalSigns(const char* vitals);

    // Required Operators
    Patient& operator+=(float amount);
    Patient& operator-=(float amount);
    bool operator==(const Patient& other) const;
    
    // Required Methods
    bool hasSufficientFunds(float amount) const;
    float getTotalOutstandingBalance() const;
    int getUnpaidBillCount() const;

    // Balance Operations
    void deductFee(float fee);
    void addFunds(float amount);
    void topUpBalance();
    void payBill(Storage<Bill>& billStorage, Storage<Appointment>& appointmentStorage);
    void cancelAppointment(Storage<Appointment>& appointmentStorage, Storage<Bill>& billStorage, Storage<Doctor>& doctorStorage);
    void bookAppointment(Storage<Doctor>& doctorStorage, Storage<Appointment>& appointmentStorage,
        Storage<Bill>& billStorage, const char* currentDate, int currentYear);

    // View Methods
    void viewMyAppointments(Storage<Appointment>& appointmentStorage, Storage<Doctor>& doctorStorage);
    void viewMyMedicalRecords(Storage<Prescription>& prescriptionStorage, Storage<Doctor>& doctorStorage);
    void viewMyBills(Storage<Bill>& billStorage, Storage<Appointment>& appointmentStorage);
    void viewMedicalRecords() const;
    void viewBills() const;
    void updateMedicalHistory(const char* newEntry);
    void admit(const char* date);
    void discharge(const char* date);

    // Virtual functions
    virtual void showMenu();
    virtual void displayInfo() const;
    void display() const;
    void displayFullDetails() const;

private:
    void copyString(char*& dest, const char* src);
    void resizeDoctorArray(int newSize);
    void resizeAppointmentArray(int newSize);
    void resizeBillArray(int newSize);
};