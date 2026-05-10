#pragma once

#include "Storage.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Nurse.h"
#include "Volunteer.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "Pharmacy.h"
#include "Labatory.h"
#include "Ambulance.h"
#include "Ward.h"
#include "Vaccination.h"
#include "MedicalCamp.h"
#include "BloodDonor.h"
#include "CashDonor.h"
#include "OrganDonor.h"

class FileHandler
{
public:
    static void initializeFiles();

    // Load functions
    static bool loadPatients(Storage<Patient>& storage);
    static bool loadDoctors(Storage<Doctor>& storage);
    static bool loadAdmins(Storage<Admin>& storage);
    static bool loadNurses(Storage<Nurse>& storage);
    static bool loadVolunteers(Storage<Volunteer>& storage);
    static bool loadAppointments(Storage<Appointment>& storage);
    static bool loadBills(Storage<Bill>& storage);
    static bool loadPrescriptions(Storage<Prescription>& storage);
    static bool loadPharmacies(Storage<Pharmacy>& storage);
    static bool loadLaboratories(Storage<Laboratory>& storage);
    static bool loadAmbulances(Storage<Ambulance>& storage);
    static bool loadWards(Storage<Ward>& storage);
    static bool loadVaccinations(Storage<Vaccination>& storage);
    static bool loadMedicalCamps(Storage<MedicalCamp>& storage);
    static bool loadBloodDonors(Storage<BloodDonor>& storage);
    static bool loadCashDonors(Storage<CashDonor>& storage);
    static bool loadOrganDonors(Storage<OrganDonor>& storage);

    // Save functions
    static bool savePatient(const Patient& patient);
    static bool saveDoctor(const Doctor& doctor);
    static bool saveNurse(const Nurse& nurse);
    static bool saveVolunteer(const Volunteer& volunteer);
    static bool saveAppointment(const Appointment& appointment);
    static bool saveBill(const Bill& bill);
    static bool savePrescription(const Prescription& prescription);
    static bool saveBloodDonor(const BloodDonor& donor);
    static bool saveCashDonor(const CashDonor& donor);
    static bool saveOrganDonor(const OrganDonor& donor);

    // Update functions
    static bool updatePatientBalance(int patientId, float newBalance);
    static bool updateAppointmentStatus(int appointmentId, const char* status);
    static bool updateBillStatus(int billId, const char* status);

    // Security functions
    static void logSecurity(const char* role, int enteredId, const char* result, int attemptCount, bool isLocked);
    static bool checkLoginAttempts(int userId, const char* role);
    static void resetLoginAttempts(int userId, const char* role);
    static void incrementLoginAttempt(int userId, const char* role);

    // Utility functions
    static int getNextId(const char* filename);
    static bool deleteRecord(const char* filename, int id, int idColumn);

private:
    static int stringToInt(const char* str);
    static float stringToFloat(const char* str);
    static void intToString(int num, char* buffer);
    static void floatToString(float num, char* buffer);
    static void parseLine(const char* line, char* fields[], int maxFields);
};