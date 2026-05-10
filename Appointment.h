#pragma once

#include <iostream>
using namespace std;

class Doctor;
class Patient;
class Nurse;
class Ward;
class MedicalCamp;
class Bill;
class Prescription;

class Appointment
{
private:
    int appointmentId;
    int patientId;
    int doctorId;
    int nurseId;
    int wardId;
    int medicalCampId;
    int billId;
    int prescriptionId;
    char* date;
    char* timeSlot;
    char* status;
    char* symptoms;
    char* diagnosis;
    char* remarks;
    bool isEmergency;
    int waitingNumber;
    float consultationFee;

public:
    Appointment();
    Appointment(int id, int patientId, int doctorId, const char* date,
        const char* timeSlot, const char* status, bool emergency);
    Appointment(const Appointment& other);
    Appointment& operator=(const Appointment& other);
    ~Appointment();

    int getAppointmentId() const;
    int getID() const { return appointmentId; }
    int getPatientId() const;
    int getDoctorId() const;
    int getNurseId() const;
    int getWardId() const;
    int getMedicalCampId() const;
    int getBillId() const;
    int getPrescriptionId() const;
    const char* getDate() const;
    const char* getTimeSlot() const;
    const char* getStatus() const;
    const char* getSymptoms() const;
    const char* getDiagnosis() const;
    const char* getRemarks() const;
    bool getIsEmergency() const;
    int getWaitingNumber() const;
    float getConsultationFee() const;

    void setStatus(const char* newStatus);
    void setSymptoms(const char* sym);
    void setDiagnosis(const char* diag);
    void setRemarks(const char* rem);
    void setNurseId(int id);
    void setWardId(int id);
    void setMedicalCampId(int id);
    void setBillId(int id);
    void setPrescriptionId(int id);
    void setWaitingNumber(int num);
    void setConsultationFee(float fee);

    bool assignNurse(const Nurse& nurse);
    bool assignWard(const Ward& ward);
    bool assignToMedicalCamp(const MedicalCamp& camp);
    bool assignBill(const Bill& bill);
    bool assignPrescription(const Prescription& pres);

    bool isConflict(const Appointment& other) const;
    bool canBeCompleted() const;
    void markCompleted();
    void markCancelled();
    void markNoShow();

    bool operator==(const Appointment& other) const;
    friend ostream& operator<<(ostream& os, const Appointment& app);

    void display() const;
    void displayFullDetails(const Doctor& doctor, const Patient& patient) const;

private:
    void copyString(char*& dest, const char* src);
};
