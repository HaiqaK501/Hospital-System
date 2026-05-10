#pragma once

#include <iostream>
using namespace std;

class Doctor;
class Patient;
class Appointment;
class Pharmacy;

class Prescription
{
private:
    int prescriptionId;
    int appointmentId;
    int patientId;
    int doctorId;
    char* date;
    char* medicines;
    char* notes;
    char* dosage;
    char* duration;
    int* pharmacyIds;
    int pharmacyCount;
    int maxPharmacies;
    bool isFilled;
    char* followUpDate;
    float totalCost;

public:
    Prescription();
    Prescription(int id, int appId, int patientId, int doctorId, const char* date,
        const char* medicines, const char* notes);
    Prescription(const Prescription& other);
    Prescription& operator=(const Prescription& other);
    ~Prescription();

    int getPrescriptionId() const;
    int getID() const { return prescriptionId; }
    int getAppointmentId() const;
    int getPatientId() const;
    int getDoctorId() const;
    const char* getDate() const;
    const char* getMedicines() const;
    const char* getNotes() const;
    const char* getDosage() const;
    const char* getDuration() const;
    bool getIsFilled() const;
    const char* getFollowUpDate() const;
    float getTotalCost() const;

    void setMedicines(const char* med);
    void setNotes(const char* note);
    void setDosage(const char* dose);
    void setDuration(const char* dur);
    void setFollowUpDate(const char* date);
    void setTotalCost(float cost);

    bool addPharmacy(int pharmacyId);
    bool removePharmacy(int pharmacyId);
    void markAsFilled();
    bool isExpired(const char* currentDate) const;
    float calculateTotalMedicineCost() const;

    bool operator==(const Prescription& other) const;
    friend ostream& operator<<(ostream& os, const Prescription& pres);

    void display() const;
    void displayFullDetails(const Doctor& doctor, const Patient& patient) const;

private:
    void copyString(char*& dest, const char* src);
    void resizePharmacyArray(int newSize);
    int parseDateToInt(const char* date) const;
};