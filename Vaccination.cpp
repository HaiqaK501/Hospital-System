#include "Vaccination.h"
#include "Validator.h"
#include <iostream>

using namespace std;

void Vaccination::copyString(char*& dest, const char* src)
{
    if (dest)
    {
        delete[] dest;
    }

    if (!src)
    {
        dest = new char[1];
        dest[0] = '\0';
        return;
    }

    int len = 0;
    while (src[len] != '\0')
        len++;

    dest = new char[len + 1];
    for (int i = 0; i < len; i++)
        dest[i] = src[i];
    dest[len] = '\0';
}

void Vaccination::resizePatientArray(int newSize)
{
    if (newSize <= maxPatients) return;

    int* newPatientIds = new int[newSize];
    int** newDoseDates = new int* [newSize];
    int* newDosesGiven = new int[newSize];

    for (int i = 0; i < patientCount; i++)
    {
        newPatientIds[i] = patientIds[i];
        newDoseDates[i] = doseDates[i];
        newDosesGiven[i] = dosesGiven[i];
    }

    for (int i = patientCount; i < newSize; i++)
    {
        newPatientIds[i] = 0;
        newDoseDates[i] = new int[dosesRequired];
        for (int j = 0; j < dosesRequired; j++)
            newDoseDates[i][j] = 0;
        newDosesGiven[i] = 0;
    }

    delete[] patientIds;
    delete[] dosesGiven;
    delete[] doseDates;

    patientIds = newPatientIds;
    doseDates = newDoseDates;
    dosesGiven = newDosesGiven;
    maxPatients = newSize;
}

void Vaccination::allocateDoseDates()
{
    doseDates = new int* [maxPatients];
    for (int i = 0; i < maxPatients; i++)
    {
        doseDates[i] = new int[dosesRequired];
        for (int j = 0; j < dosesRequired; j++)
            doseDates[i][j] = 0;
    }
}

Vaccination::Vaccination()
{
    vaccineName = new char[1];
    vaccineName[0] = '\0';
    manufacturer = new char[1];
    manufacturer[0] = '\0';
    ageGroup = new char[1];
    ageGroup[0] = '\0';
    sideEffects = new char[1];
    sideEffects[0] = '\0';

    vaccineId = 0;
    dosesRequired = 0;
    intervalDays = 0;
    storageTemperature = 0.0f;
    stockDoses = 0;
    expiryDays = 0;
    price = 0.0f;
    isEmergencyUse = false;

    patientCount = 0;
    maxPatients = 100;
    patientIds = new int[maxPatients];
    dosesGiven = new int[maxPatients];

    for (int i = 0; i < maxPatients; i++)
    {
        patientIds[i] = 0;
        dosesGiven[i] = 0;
    }

    allocateDoseDates();
}

Vaccination::Vaccination(int id, const char* name, const char* manu, int doses, int interval,
    float temp, int stock, int expiry, const char* age, float pr, bool emergency)
{
    if (!Validator::validateVaccineName(name))
        copyString(vaccineName, "Unknown");
    else
        copyString(vaccineName, name);

    copyString(manufacturer, manu);

    if (!Validator::validateVaccineDoses(doses))
        dosesRequired = 2;
    else
        dosesRequired = doses;

    intervalDays = interval;

    if (!Validator::validateVaccineTemperature(temp))
        storageTemperature = 2.0f;
    else
        storageTemperature = temp;

    stockDoses = stock;
    expiryDays = expiry;

    copyString(ageGroup, age);
    copyString(sideEffects, "None reported");

    if (!Validator::validatePositiveFloat(pr))
        price = 1000.0f;
    else
        price = pr;

    isEmergencyUse = emergency;

    patientCount = 0;
    maxPatients = 100;
    patientIds = new int[maxPatients];
    dosesGiven = new int[maxPatients];

    for (int i = 0; i < maxPatients; i++)
    {
        patientIds[i] = 0;
        dosesGiven[i] = 0;
    }

    allocateDoseDates();
}

Vaccination::Vaccination(const Vaccination& other)
{
    copyString(vaccineName, other.vaccineName);
    copyString(manufacturer, other.manufacturer);
    copyString(ageGroup, other.ageGroup);
    copyString(sideEffects, other.sideEffects);

    vaccineId = other.vaccineId;
    dosesRequired = other.dosesRequired;
    intervalDays = other.intervalDays;
    storageTemperature = other.storageTemperature;
    stockDoses = other.stockDoses;
    expiryDays = other.expiryDays;
    price = other.price;
    isEmergencyUse = other.isEmergencyUse;

    patientCount = other.patientCount;
    maxPatients = other.maxPatients;
    patientIds = new int[maxPatients];
    dosesGiven = new int[maxPatients];
    doseDates = new int* [maxPatients];

    for (int i = 0; i < maxPatients; i++)
    {
        patientIds[i] = other.patientIds[i];
        dosesGiven[i] = other.dosesGiven[i];
        doseDates[i] = new int[dosesRequired];
        for (int j = 0; j < dosesRequired; j++)
            doseDates[i][j] = other.doseDates[i][j];
    }
}

Vaccination& Vaccination::operator=(const Vaccination& other)
{
    if (this == &other)
        return *this;

    copyString(vaccineName, other.vaccineName);
    copyString(manufacturer, other.manufacturer);
    copyString(ageGroup, other.ageGroup);
    copyString(sideEffects, other.sideEffects);

    vaccineId = other.vaccineId;
    dosesRequired = other.dosesRequired;
    intervalDays = other.intervalDays;
    storageTemperature = other.storageTemperature;
    stockDoses = other.stockDoses;
    expiryDays = other.expiryDays;
    price = other.price;
    isEmergencyUse = other.isEmergencyUse;

    for (int i = 0; i < patientCount; i++)
        delete[] doseDates[i];
    delete[] doseDates;
    delete[] patientIds;
    delete[] dosesGiven;

    patientCount = other.patientCount;
    maxPatients = other.maxPatients;
    patientIds = new int[maxPatients];
    dosesGiven = new int[maxPatients];
    doseDates = new int* [maxPatients];

    for (int i = 0; i < maxPatients; i++)
    {
        patientIds[i] = other.patientIds[i];
        dosesGiven[i] = other.dosesGiven[i];
        doseDates[i] = new int[dosesRequired];
        for (int j = 0; j < dosesRequired; j++)
            doseDates[i][j] = other.doseDates[i][j];
    }

    return *this;
}

Vaccination::~Vaccination()
{
    delete[] vaccineName;
    delete[] manufacturer;
    delete[] ageGroup;
    delete[] sideEffects;
    delete[] patientIds;
    delete[] dosesGiven;

    for (int i = 0; i < maxPatients; i++)
        delete[] doseDates[i];
    delete[] doseDates;
}

int Vaccination::getVaccineId() const { return vaccineId; }
const char* Vaccination::getVaccineName() const { return vaccineName; }
const char* Vaccination::getManufacturer() const { return manufacturer; }
int Vaccination::getDosesRequired() const { return dosesRequired; }
int Vaccination::getIntervalDays() const { return intervalDays; }
float Vaccination::getStorageTemperature() const { return storageTemperature; }
int Vaccination::getStockDoses() const { return stockDoses; }
const char* Vaccination::getAgeGroup() const { return ageGroup; }
float Vaccination::getPrice() const { return price; }

void Vaccination::addStock(int doses)
{
    if (doses > 0)
        stockDoses += doses;
}

bool Vaccination::removeStock(int doses)
{
    if (doses <= 0 || doses > stockDoses) return false;
    stockDoses -= doses;
    return true;
}

int Vaccination::parseDateToInt(const char* date) const
{
    if (!date) return 0;

    int len = 0;
    while (date[len] != '\0') len++;
    if (len != 10) return 0;

    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    return year * 10000 + month * 100 + day;
}

bool Vaccination::administerDose(int patientId, const char* date, int doseNumber)
{
    if (stockDoses <= 0) return false;
    if (doseNumber > dosesRequired) return false;
    if (!Validator::validateDate(date)) return false;

    int patientIndex = -1;
    for (int i = 0; i < patientCount; i++)
    {
        if (patientIds[i] == patientId)
        {
            patientIndex = i;
            break;
        }
    }

    if (patientIndex == -1)
    {
        if (patientCount >= maxPatients)
            resizePatientArray(maxPatients + 50);

        patientIndex = patientCount;
        patientIds[patientCount] = patientId;
        dosesGiven[patientCount] = 0;
        patientCount++;
    }

    if (doseNumber != dosesGiven[patientIndex] + 1) return false;

    int dateInt = parseDateToInt(date);
    dosesGiven[patientIndex]++;
    doseDates[patientIndex][doseNumber - 1] = dateInt;
    stockDoses--;

    return true;
}

bool Vaccination::isVaccineExpiringSoon() const
{
    return expiryDays <= 30;
}

int Vaccination::getPatientsFullyVaccinated() const
{
    int count = 0;
    for (int i = 0; i < patientCount; i++)
    {
        if (dosesGiven[i] == dosesRequired)
            count++;
    }
    return count;
}

int Vaccination::getPatientsPartiallyVaccinated() const
{
    int count = 0;
    for (int i = 0; i < patientCount; i++)
    {
        if (dosesGiven[i] > 0 && dosesGiven[i] < dosesRequired)
            count++;
    }
    return count;
}

float Vaccination::calculateCoverageRate() const
{
    if (patientCount == 0) return 0;
    return (float)getPatientsFullyVaccinated() / patientCount * 100;
}

bool Vaccination::isEligibleForAge(int age) const
{
    if (ageGroup[0] == '\0') return true;
    if (age < 0) return false;

    int minAge = 0;
    int maxAge = 999;
    int i = 0;

    while (ageGroup[i] >= '0' && ageGroup[i] <= '9')
    {
        minAge = minAge * 10 + (ageGroup[i] - '0');
        i++;
    }

    if (ageGroup[i] == '+')
    {
        return age >= minAge;
    }
    else if (ageGroup[i] == '-')
    {
        i++;
        while (ageGroup[i] >= '0' && ageGroup[i] <= '9')
        {
            maxAge = maxAge * 10 + (ageGroup[i] - '0');
            i++;
        }
        return (age >= minAge && age <= maxAge);
    }

    return true;
}

void Vaccination::recordSideEffect(int patientId, const char* effect)
{
    copyString(sideEffects, effect);
}

float Vaccination::calculateRevenue() const
{
    return getPatientsFullyVaccinated() * price * dosesRequired;
}

void Vaccination::display() const
{
    cout << "Vaccine ID: " << vaccineId << " | " << vaccineName;
    cout << " | Stock: " << stockDoses;
    cout << " | Fully Vaccinated: " << getPatientsFullyVaccinated() << endl;
}

void Vaccination::displayFullDetails() const
{
    cout << "\n========== VACCINE DETAILS ==========" << endl;
    cout << "ID: " << vaccineId << endl;
    cout << "Name: " << vaccineName << endl;
    cout << "Manufacturer: " << manufacturer << endl;
    cout << "Doses Required: " << dosesRequired << endl;
    cout << "Interval Between Doses: " << intervalDays << " days" << endl;
    cout << "Storage Temperature: " << storageTemperature << "°C" << endl;
    cout << "Stock Available: " << stockDoses << " doses" << endl;
    cout << "Expiry: " << expiryDays << " days remaining" << endl;
    if (isVaccineExpiringSoon()) cout << "WARNING: Expiring soon!" << endl;
    cout << "Age Group: " << ageGroup << endl;
    cout << "Price per Dose: Rs. " << price << endl;
    cout << "Emergency Use Approved: " << (isEmergencyUse ? "Yes" : "No") << endl;
    cout << "Total Patients: " << patientCount << endl;
    cout << "Fully Vaccinated: " << getPatientsFullyVaccinated() << endl;
    cout << "Partially Vaccinated: " << getPatientsPartiallyVaccinated() << endl;
    cout << "Coverage Rate: " << calculateCoverageRate() << "%" << endl;
    cout << "Revenue Generated: Rs. " << calculateRevenue() << endl;
    cout << "=====================================" << endl;
}