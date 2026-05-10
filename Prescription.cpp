#include "Prescription.h"
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "Pharmacy.h"
#include "Validator.h"
#include <iostream>

using namespace std;

void Prescription::copyString(char*& dest, const char* src)
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

void Prescription::resizePharmacyArray(int newSize)
{
    if (newSize <= maxPharmacies) return;
    int* newArray = new int[newSize];
    for (int i = 0; i < pharmacyCount; i++) newArray[i] = pharmacyIds[i];
    for (int i = pharmacyCount; i < newSize; i++) newArray[i] = 0;
    delete[] pharmacyIds;
    pharmacyIds = newArray;
    maxPharmacies = newSize;
}

int Prescription::parseDateToInt(const char* date) const
{
    if (!date) return 0;
    int len = 0;
    while (date[len] != '\0') len++;
    if (len != 10) return 0;

    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
        (date[8] - '0') * 10 + (date[9] - '0');

    return year * 10000 + month * 100 + day;
}

Prescription::Prescription()
{
    date = new char[1];
    date[0] = '\0';
    medicines = new char[1];
    medicines[0] = '\0';
    notes = new char[1];
    notes[0] = '\0';
    dosage = new char[1];
    dosage[0] = '\0';
    duration = new char[1];
    duration[0] = '\0';
    followUpDate = new char[1];
    followUpDate[0] = '\0';

    prescriptionId = 0;
    appointmentId = 0;
    patientId = 0;
    doctorId = 0;
    isFilled = false;
    totalCost = 0.0f;

    pharmacyCount = 0;
    maxPharmacies = 10;
    pharmacyIds = new int[maxPharmacies];
    for (int i = 0; i < maxPharmacies; i++) pharmacyIds[i] = 0;
}

Prescription::Prescription(int id, int appId, int pId, int dId, const char* dt,
    const char* med, const char* nt)
{
    copyString(date, dt);
    copyString(medicines, med);
    copyString(notes, nt);
    copyString(dosage, "As directed");
    copyString(duration, "7 days");
    copyString(followUpDate, "");

    prescriptionId = id;
    appointmentId = appId;
    patientId = pId;
    doctorId = dId;
    isFilled = false;
    totalCost = 0.0f;

    pharmacyCount = 0;
    maxPharmacies = 10;
    pharmacyIds = new int[maxPharmacies];
    for (int i = 0; i < maxPharmacies; i++) pharmacyIds[i] = 0;
}

Prescription::Prescription(const Prescription& other)
{
    copyString(date, other.date);
    copyString(medicines, other.medicines);
    copyString(notes, other.notes);
    copyString(dosage, other.dosage);
    copyString(duration, other.duration);
    copyString(followUpDate, other.followUpDate);

    prescriptionId = other.prescriptionId;
    appointmentId = other.appointmentId;
    patientId = other.patientId;
    doctorId = other.doctorId;
    isFilled = other.isFilled;
    totalCost = other.totalCost;

    pharmacyCount = other.pharmacyCount;
    maxPharmacies = other.maxPharmacies;
    pharmacyIds = new int[maxPharmacies];
    for (int i = 0; i < maxPharmacies; i++) pharmacyIds[i] = other.pharmacyIds[i];
}

Prescription& Prescription::operator=(const Prescription& other)
{
    if (this == &other) return *this;

    copyString(date, other.date);
    copyString(medicines, other.medicines);
    copyString(notes, other.notes);
    copyString(dosage, other.dosage);
    copyString(duration, other.duration);
    copyString(followUpDate, other.followUpDate);

    prescriptionId = other.prescriptionId;
    appointmentId = other.appointmentId;
    patientId = other.patientId;
    doctorId = other.doctorId;
    isFilled = other.isFilled;
    totalCost = other.totalCost;

    pharmacyCount = other.pharmacyCount;
    if (maxPharmacies < other.maxPharmacies)
    {
        delete[] pharmacyIds;
        maxPharmacies = other.maxPharmacies;
        pharmacyIds = new int[maxPharmacies];
    }
    for (int i = 0; i < maxPharmacies; i++) pharmacyIds[i] = other.pharmacyIds[i];

    return *this;
}

Prescription::~Prescription()
{
    delete[] date;
    delete[] medicines;
    delete[] notes;
    delete[] dosage;
    delete[] duration;
    delete[] followUpDate;
    delete[] pharmacyIds;
}


int Prescription::getPrescriptionId() const { return prescriptionId; }
int Prescription::getAppointmentId() const { return appointmentId; }
int Prescription::getPatientId() const { return patientId; }
int Prescription::getDoctorId() const { return doctorId; }
const char* Prescription::getDate() const { return date; }
const char* Prescription::getMedicines() const { return medicines; }
const char* Prescription::getNotes() const { return notes; }
const char* Prescription::getDosage() const { return dosage; }
const char* Prescription::getDuration() const { return duration; }
bool Prescription::getIsFilled() const { return isFilled; }
const char* Prescription::getFollowUpDate() const { return followUpDate; }
float Prescription::getTotalCost() const { return totalCost; }

void Prescription::setMedicines(const char* med) { copyString(medicines, med); }
void Prescription::setNotes(const char* note) { copyString(notes, note); }
void Prescription::setDosage(const char* dose) { copyString(dosage, dose); }
void Prescription::setDuration(const char* dur) { copyString(duration, dur); }
void Prescription::setFollowUpDate(const char* dt) { copyString(followUpDate, dt); }
void Prescription::setTotalCost(float cost) { totalCost = cost; }

bool Prescription::addPharmacy(int pharmacyId)
{
    if (pharmacyCount >= maxPharmacies) resizePharmacyArray(maxPharmacies + 5);
    for (int i = 0; i < pharmacyCount; i++)
        if (pharmacyIds[i] == pharmacyId) return false;
    pharmacyIds[pharmacyCount] = pharmacyId;
    pharmacyCount++;
    return true;
}

bool Prescription::removePharmacy(int pharmacyId)
{
    for (int i = 0; i < pharmacyCount; i++)
    {
        if (pharmacyIds[i] == pharmacyId)
        {
            for (int j = i; j < pharmacyCount - 1; j++)
                pharmacyIds[j] = pharmacyIds[j + 1];
            pharmacyCount--;
            return true;
        }
    }
    return false;
}

void Prescription::markAsFilled() { isFilled = true; }

bool Prescription::isExpired(const char* currentDate) const
{
    if (followUpDate[0] == '\0') return false;
    if (!currentDate) return false;

    int followDateInt = parseDateToInt(followUpDate);
    int currentDateInt = parseDateToInt(currentDate);

    return followDateInt < currentDateInt;
}

float Prescription::calculateTotalMedicineCost() const
{
    return totalCost;
}

bool Prescription::operator==(const Prescription& other) const
{
    return (prescriptionId == other.prescriptionId);
}

ostream& operator<<(ostream& os, const Prescription& pres)
{
    os << "Prescription ID: " << pres.prescriptionId;
    os << " | Date: " << pres.date;
    os << " | Medicines: " << pres.medicines;
    os << " | Filled: " << (pres.isFilled ? "Yes" : "No");
    return os;
}

void Prescription::display() const
{
    cout << "Prescription ID: " << prescriptionId;
    cout << " | Patient ID: " << patientId;
    cout << " | Doctor ID: " << doctorId;
    cout << " | Date: " << date;
    cout << " | Medicines: " << medicines;
    cout << " | Filled: " << (isFilled ? "Yes" : "No") << endl;
}

void Prescription::displayFullDetails(const Doctor& doctor, const Patient& patient) const
{
    
    const char* doctorName = doctor.getName().get();
    const char* patientName = patient.getName().get();

    cout << "\n========== PRESCRIPTION DETAILS ==========" << endl;
    cout << "Prescription ID: " << prescriptionId << endl;
    cout << "Date: " << date << endl;
    cout << "Patient: " << patientName << " (ID: " << patientId << ")" << endl;
    cout << "Doctor: Dr. " << doctorName << " (ID: " << doctorId << ")" << endl;
    cout << "Appointment ID: " << appointmentId << endl;
    cout << "Medicines: " << medicines << endl;
    cout << "Dosage: " << dosage << endl;
    cout << "Duration: " << duration << endl;
    cout << "Doctor's Notes: " << notes << endl;
    cout << "Follow-up Date: " << (followUpDate[0] != '\0' ? followUpDate : "Not scheduled") << endl;
    cout << "Total Cost: Rs. " << totalCost << endl;
    cout << "Status: " << (isFilled ? "Filled at Pharmacy" : "Not Yet Filled") << endl;
    cout << "Associated Pharmacies: " << pharmacyCount << endl;
    cout << "===========================================" << endl;
}