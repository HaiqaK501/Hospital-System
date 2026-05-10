#include "Appointment.h"
#include "Doctor.h"
#include "Patient.h"
#include "Nurse.h"
#include "Ward.h"
#include "MedicalCamp.h"
#include "Bill.h"
#include "Prescription.h"
#include <iostream>

using namespace std;

void Appointment::copyString(char*& dest, const char* src)
{
    if (dest) delete[] dest;
    if (!src)
    {
        dest = new char[1];
        dest[0] = '\0';
        return;
    }
    int len = 0;
    while (src[len] != '\0') len++;
    dest = new char[len + 1];
    for (int i = 0; i < len; i++) dest[i] = src[i];
    dest[len] = '\0';
}

Appointment::Appointment()
{
    date = new char[1]; date[0] = '\0';
    timeSlot = new char[1]; timeSlot[0] = '\0';
    status = new char[1]; status[0] = '\0';
    symptoms = new char[1]; symptoms[0] = '\0';
    diagnosis = new char[1]; diagnosis[0] = '\0';
    remarks = new char[1]; remarks[0] = '\0';

    appointmentId = 0;
    patientId = 0;
    doctorId = 0;
    nurseId = 0;
    wardId = 0;
    medicalCampId = 0;
    billId = 0;
    prescriptionId = 0;
    isEmergency = false;
    waitingNumber = 0;
    consultationFee = 0.0f;
}

Appointment::Appointment(int id, int pId, int dId, const char* dt,
    const char* slot, const char* stat, bool emergency)
{
    copyString(date, dt);
    copyString(timeSlot, slot);
    copyString(status, stat);
    copyString(symptoms, "");
    copyString(diagnosis, "");
    copyString(remarks, "");

    appointmentId = id;
    patientId = pId;
    doctorId = dId;
    nurseId = 0;
    wardId = 0;
    medicalCampId = 0;
    billId = 0;
    prescriptionId = 0;
    isEmergency = emergency;
    waitingNumber = 0;
    consultationFee = 0.0f;
}

Appointment::Appointment(const Appointment& other)
{
    copyString(date, other.date);
    copyString(timeSlot, other.timeSlot);
    copyString(status, other.status);
    copyString(symptoms, other.symptoms);
    copyString(diagnosis, other.diagnosis);
    copyString(remarks, other.remarks);

    appointmentId = other.appointmentId;
    patientId = other.patientId;
    doctorId = other.doctorId;
    nurseId = other.nurseId;
    wardId = other.wardId;
    medicalCampId = other.medicalCampId;
    billId = other.billId;
    prescriptionId = other.prescriptionId;
    isEmergency = other.isEmergency;
    waitingNumber = other.waitingNumber;
    consultationFee = other.consultationFee;
}

Appointment& Appointment::operator=(const Appointment& other)
{
    if (this == &other) return *this;

    copyString(date, other.date);
    copyString(timeSlot, other.timeSlot);
    copyString(status, other.status);
    copyString(symptoms, other.symptoms);
    copyString(diagnosis, other.diagnosis);
    copyString(remarks, other.remarks);

    appointmentId = other.appointmentId;
    patientId = other.patientId;
    doctorId = other.doctorId;
    nurseId = other.nurseId;
    wardId = other.wardId;
    medicalCampId = other.medicalCampId;
    billId = other.billId;
    prescriptionId = other.prescriptionId;
    isEmergency = other.isEmergency;
    waitingNumber = other.waitingNumber;
    consultationFee = other.consultationFee;

    return *this;
}

Appointment::~Appointment()
{
    delete[] date;
    delete[] timeSlot;
    delete[] status;
    delete[] symptoms;
    delete[] diagnosis;
    delete[] remarks;
}

// ========== GETTERS ==========

int Appointment::getAppointmentId() const { return appointmentId; }
int Appointment::getPatientId() const { return patientId; }
int Appointment::getDoctorId() const { return doctorId; }
int Appointment::getNurseId() const { return nurseId; }
int Appointment::getWardId() const { return wardId; }
int Appointment::getMedicalCampId() const { return medicalCampId; }
int Appointment::getBillId() const { return billId; }
int Appointment::getPrescriptionId() const { return prescriptionId; }
const char* Appointment::getDate() const { return date; }
const char* Appointment::getTimeSlot() const { return timeSlot; }
const char* Appointment::getStatus() const { return status; }
const char* Appointment::getSymptoms() const { return symptoms; }
const char* Appointment::getDiagnosis() const { return diagnosis; }
const char* Appointment::getRemarks() const { return remarks; }
bool Appointment::getIsEmergency() const { return isEmergency; }
int Appointment::getWaitingNumber() const { return waitingNumber; }
float Appointment::getConsultationFee() const { return consultationFee; }

// ========== SETTERS ==========

void Appointment::setStatus(const char* newStatus) { copyString(status, newStatus); }
void Appointment::setSymptoms(const char* sym) { copyString(symptoms, sym); }
void Appointment::setDiagnosis(const char* diag) { copyString(diagnosis, diag); }
void Appointment::setRemarks(const char* rem) { copyString(remarks, rem); }
void Appointment::setNurseId(int id) { nurseId = id; }
void Appointment::setWardId(int id) { wardId = id; }
void Appointment::setMedicalCampId(int id) { medicalCampId = id; }
void Appointment::setBillId(int id) { billId = id; }
void Appointment::setPrescriptionId(int id) { prescriptionId = id; }
void Appointment::setWaitingNumber(int num) { waitingNumber = num; }
void Appointment::setConsultationFee(float fee) { consultationFee = fee; }

// ========== ASSIGNMENT METHODS ==========

bool Appointment::assignNurse(const Nurse& nurse)
{
    nurseId = nurse.getID();
    return true;
}

bool Appointment::assignWard(const Ward& ward)
{
    wardId = ward.getWardId();
    return true;
}

bool Appointment::assignToMedicalCamp(const MedicalCamp& camp)
{
    medicalCampId = camp.getCampId();
    return true;
}

bool Appointment::assignBill(const Bill& bill)
{
    billId = bill.getBillId();
    return true;
}

bool Appointment::assignPrescription(const Prescription& pres)
{
    prescriptionId = pres.getPrescriptionId();
    return true;
}

// ========== CONFLICT DETECTION ==========

bool Appointment::isConflict(const Appointment& other) const
{
    if (this->appointmentId == other.appointmentId)
        return false;

    if (this->doctorId != other.doctorId)
        return false;

    int i = 0;
    while (this->date[i] != '\0' && other.date[i] != '\0')
    {
        if (this->date[i] != other.date[i])
            return false;
        i++;
    }
    if (this->date[i] != '\0' || other.date[i] != '\0')
        return false;

    i = 0;
    while (this->timeSlot[i] != '\0' && other.timeSlot[i] != '\0')
    {
        if (this->timeSlot[i] != other.timeSlot[i])
            return false;
        i++;
    }
    if (this->timeSlot[i] != '\0' || other.timeSlot[i] != '\0')
        return false;

    bool thisCancelled = false;
    bool otherCancelled = false;

    for (i = 0; this->status[i] != '\0'; i++)
    {
        char c = this->status[i];
        if (c >= 'A' && c <= 'Z') c = c + 32;
        if (c == 'c')
        {
            thisCancelled = true;
            break;
        }
    }

    for (i = 0; other.status[i] != '\0'; i++)
    {
        char c = other.status[i];
        if (c >= 'A' && c <= 'Z') c = c + 32;
        if (c == 'c')
        {
            otherCancelled = true;
            break;
        }
    }

    if (thisCancelled || otherCancelled)
        return false;

    return true;
}

bool Appointment::canBeCompleted() const
{
    for (int i = 0; status[i] != '\0'; i++)
    {
        char c = status[i];
        if (c >= 'A' && c <= 'Z') c = c + 32;
        if (c == 'p' && status[i + 1] == 'e' && status[i + 2] == 'n' && status[i + 3] == 'd')
            return true;
    }
    return false;
}

void Appointment::markCompleted()
{
    copyString(status, "completed");
}

void Appointment::markCancelled()
{
    copyString(status, "cancelled");
}

void Appointment::markNoShow()
{
    copyString(status, "no-show");
}

// ========== OPERATORS ==========

bool Appointment::operator==(const Appointment& other) const
{
    return isConflict(other);
}

ostream& operator<<(ostream& os, const Appointment& app)
{
    os << "Appt ID: " << app.appointmentId;
    os << " | " << app.date << " " << app.timeSlot;
    os << " | Status: " << app.status;
    if (app.isEmergency)
        os << " | EMERGENCY";
    return os;
}

// ========== DISPLAY METHODS ==========

void Appointment::display() const
{
    cout << "Appointment ID: " << appointmentId;
    cout << " | Patient: " << patientId;
    cout << " | Doctor: " << doctorId;
    cout << " | Date: " << date;
    cout << " | Time: " << timeSlot;
    cout << " | Status: " << status;
    if (isEmergency)
        cout << " | EMERGENCY";
    cout << endl;
}

void Appointment::displayFullDetails(const Doctor& doctor, const Patient& patient) const
{
    const char* doctorName = doctor.getName().get();
    const char* patientName = patient.getName().get();

    cout << "\n========== APPOINTMENT DETAILS ==========" << endl;
    cout << "ID: " << appointmentId << endl;
    cout << "Date: " << date << endl;
    cout << "Time: " << timeSlot << endl;
    cout << "Status: " << status << endl;
    cout << "Type: " << (isEmergency ? "EMERGENCY" : "Regular") << endl;
    cout << "Waiting #: " << waitingNumber << endl;
    cout << "Fee: Rs. " << consultationFee << endl;

    cout << "\nPatient: " << patientName << " (ID: " << patientId << ")" << endl;
    cout << "Doctor: Dr. " << doctorName << " (ID: " << doctorId << ")" << endl;

    if (nurseId != 0)
        cout << "Assigned Nurse ID: " << nurseId << endl;
    if (wardId != 0)
        cout << "Ward ID: " << wardId << endl;
    if (medicalCampId != 0)
        cout << "Medical Camp ID: " << medicalCampId << endl;
    if (billId != 0)
        cout << "Bill ID: " << billId << endl;
    if (prescriptionId != 0)
        cout << "Prescription ID: " << prescriptionId << endl;

    if (symptoms[0] != '\0')
        cout << "\nSymptoms: " << symptoms << endl;
    if (diagnosis[0] != '\0')
        cout << "Diagnosis: " << diagnosis << endl;
    if (remarks[0] != '\0')
        cout << "Remarks: " << remarks << endl;

    cout << "==========================================" << endl;
}