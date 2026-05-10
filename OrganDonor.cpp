#include "OrganDonor.h"
#include <iostream>

using namespace std;

void OrganDonor::copyString(char*& dest, const char* src)
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

void OrganDonor::resizeOrgansArray(int newSize)
{
    if (newSize <= maxOrgans) return;

    char** newArray = new char* [newSize];
    for (int i = 0; i < organCount; i++)
    {
        newArray[i] = new char[50];
        copyString(newArray[i], organsToDonate[i]);
    }
    for (int i = organCount; i < newSize; i++)
        newArray[i] = nullptr;

    for (int i = 0; i < organCount; i++)
        delete[] organsToDonate[i];
    delete[] organsToDonate;

    organsToDonate = newArray;
    maxOrgans = newSize;
}

int OrganDonor::getLivesPerOrgan(const char* organ) const
{
    const char* vitalOrgans[] = { "Heart", "Liver", "Kidney", "Lungs", "Pancreas" };
    for (int i = 0; i < 5; i++)
    {
        int j = 0;
        bool match = true;
        while (organ[j] != '\0' && vitalOrgans[i][j] != '\0')
        {
            if (organ[j] != vitalOrgans[i][j])
            {
                match = false;
                break;
            }
            j++;
        }
        if (match)
        {
            if (organ[j] == '\0' && vitalOrgans[i][j] == '\0')
            {
                if (i == 0 || i == 1) return 1;
                if (i == 2) return 2;
                if (i == 3) return 2;
                if (i == 4) return 1;
            }
        }
    }
    return 1;
}

OrganDonor::OrganDonor() : Donor()
{
    medicalConsentForm = new char[1];
    medicalConsentForm[0] = '\0';
    organDonationCardNumber = new char[1];
    organDonationCardNumber[0] = '\0';
    preferredHospital = new char[1];
    preferredHospital[0] = '\0';

    organCount = 0;
    maxOrgans = 10;
    organsToDonate = new char* [maxOrgans];
    for (int i = 0; i < maxOrgans; i++)
        organsToDonate[i] = nullptr;

    isFamilyConsented = false;
    isEmergencyOnly = false;

    copyString(donorType, "Organ Donor");
}

OrganDonor::OrganDonor(int id, const char* nameVal, const char* passVal, const char* contact,
    const char* addr, const char* hospital, bool emergencyOnly)
    : Donor(id, nameVal, passVal, "Organ Donor", contact, addr)
{
    copyString(preferredHospital, hospital);
    copyString(medicalConsentForm, "Pending");
    copyString(organDonationCardNumber, "Not Generated");

    organCount = 0;
    maxOrgans = 10;
    organsToDonate = new char* [maxOrgans];
    for (int i = 0; i < maxOrgans; i++)
        organsToDonate[i] = nullptr;

    isFamilyConsented = false;
    isEmergencyOnly = emergencyOnly;
}

OrganDonor::OrganDonor(const OrganDonor& other) : Donor(other)
{
    copyString(medicalConsentForm, other.medicalConsentForm);
    copyString(organDonationCardNumber, other.organDonationCardNumber);
    copyString(preferredHospital, other.preferredHospital);

    organCount = other.organCount;
    maxOrgans = other.maxOrgans;
    organsToDonate = new char* [maxOrgans];
    for (int i = 0; i < organCount; i++)
    {
        organsToDonate[i] = new char[50];
        copyString(organsToDonate[i], other.organsToDonate[i]);
    }
    for (int i = organCount; i < maxOrgans; i++)
        organsToDonate[i] = nullptr;

    isFamilyConsented = other.isFamilyConsented;
    isEmergencyOnly = other.isEmergencyOnly;
}

OrganDonor& OrganDonor::operator=(const OrganDonor& other)
{
    if (this == &other)
        return *this;

    Donor::operator=(other);

    copyString(medicalConsentForm, other.medicalConsentForm);
    copyString(organDonationCardNumber, other.organDonationCardNumber);
    copyString(preferredHospital, other.preferredHospital);

    for (int i = 0; i < organCount; i++)
        delete[] organsToDonate[i];

    if (maxOrgans < other.maxOrgans)
    {
        delete[] organsToDonate;
        maxOrgans = other.maxOrgans;
        organsToDonate = new char* [maxOrgans];
    }

    organCount = other.organCount;
    for (int i = 0; i < organCount; i++)
    {
        organsToDonate[i] = new char[50];
        copyString(organsToDonate[i], other.organsToDonate[i]);
    }
    for (int i = organCount; i < maxOrgans; i++)
        organsToDonate[i] = nullptr;

    isFamilyConsented = other.isFamilyConsented;
    isEmergencyOnly = other.isEmergencyOnly;

    return *this;
}

OrganDonor::~OrganDonor()
{
    delete[] medicalConsentForm;
    delete[] organDonationCardNumber;
    delete[] preferredHospital;

    for (int i = 0; i < organCount; i++)
        delete[] organsToDonate[i];
    delete[] organsToDonate;
}

const char** OrganDonor::getOrgansToDonate() const { return const_cast<const char**>(organsToDonate); }
int OrganDonor::getOrganCount() const { return organCount; }
const char* OrganDonor::getMedicalConsentForm() const { return medicalConsentForm; }
const char* OrganDonor::getOrganDonationCardNumber() const { return organDonationCardNumber; }
bool OrganDonor::getIsFamilyConsented() const { return isFamilyConsented; }
const char* OrganDonor::getPreferredHospital() const { return preferredHospital; }
bool OrganDonor::getIsEmergencyOnly() const { return isEmergencyOnly; }

void OrganDonor::addOrgan(const char* organ)
{
    if (organCount >= maxOrgans)
        resizeOrgansArray(maxOrgans + 5);

    if (hasOrgan(organ))
        return;

    organsToDonate[organCount] = new char[50];
    copyString(organsToDonate[organCount], organ);
    organCount++;
    totalDonations++;
    totalDonationValue += 100000.0f;
}

bool OrganDonor::removeOrgan(const char* organ)
{
    for (int i = 0; i < organCount; i++)
    {
        int j = 0;
        bool match = true;
        while (organsToDonate[i][j] != '\0' && organ[j] != '\0')
        {
            if (organsToDonate[i][j] != organ[j])
            {
                match = false;
                break;
            }
            j++;
        }
        if (match && organsToDonate[i][j] == '\0' && organ[j] == '\0')
        {
            delete[] organsToDonate[i];
            for (int k = i; k < organCount - 1; k++)
                organsToDonate[k] = organsToDonate[k + 1];
            organCount--;
            return true;
        }
    }
    return false;
}

bool OrganDonor::hasOrgan(const char* organ) const
{
    for (int i = 0; i < organCount; i++)
    {
        int j = 0;
        bool match = true;
        while (organsToDonate[i][j] != '\0' && organ[j] != '\0')
        {
            if (organsToDonate[i][j] != organ[j])
            {
                match = false;
                break;
            }
            j++;
        }
        if (match && organsToDonate[i][j] == '\0' && organ[j] == '\0')
            return true;
    }
    return false;
}

void OrganDonor::setFamilyConsent(bool consented)
{
    isFamilyConsented = consented;
    if (consented)
        copyString(medicalConsentForm, "Signed");
    else
        copyString(medicalConsentForm, "Not Signed");
}

void OrganDonor::setPreferredHospital(const char* hospital)
{
    copyString(preferredHospital, hospital);
}

void OrganDonor::generateDonationCard()
{
    char cardNumber[20];
    cardNumber[0] = 'O';
    cardNumber[1] = 'R';
    cardNumber[2] = 'G';
    cardNumber[3] = '-';

    int temp = id;
    int digits[10];
    int digitCount = 0;
    while (temp > 0)
    {
        digits[digitCount++] = temp % 10;
        temp /= 10;
    }

    int idx = 4;
    for (int i = digitCount - 1; i >= 0 && idx < 19; i--)
        cardNumber[idx++] = '0' + digits[i];
    cardNumber[idx] = '\0';

    copyString(organDonationCardNumber, cardNumber);
}

int OrganDonor::getPotentialLivesToSave() const
{
    int lives = 0;
    for (int i = 0; i < organCount; i++)
        lives += getLivesPerOrgan(organsToDonate[i]);
    return lives;
}

float OrganDonor::calculateImpactScore() const
{
    float score = 0.0f;
    score += getPotentialLivesToSave() * 100.0f;
    if (isFamilyConsented)
        score += 50.0f;
    if (organCount >= 5)
        score += 200.0f;
    else if (organCount >= 3)
        score += 100.0f;
    return score;
}

void OrganDonor::displayDonorInfo() const
{
    char nameBuffer[100];
    name.display();

    cout << "\n====== ORGAN DONOR DETAILS ======" << endl;
    cout << "Name: " << nameBuffer << endl;
    cout << "Organs to Donate: ";
    if (organCount == 0)
        cout << "None registered";
    else
    {
        for (int i = 0; i < organCount; i++)
        {
            cout << organsToDonate[i];
            if (i < organCount - 1) cout << ", ";
        }
    }
    cout << endl;
    cout << "Potential Lives to Save: " << getPotentialLivesToSave() << endl;
    cout << "Family Consent: " << (isFamilyConsented ? "Yes" : "No") << endl;
    cout << "Consent Form: " << medicalConsentForm << endl;
    cout << "Donation Card: " << organDonationCardNumber << endl;
    cout << "Preferred Hospital: " << preferredHospital << endl;
    cout << "Emergency Only: " << (isEmergencyOnly ? "Yes" : "No") << endl;
    cout << "Impact Score: " << calculateImpactScore() << endl;
    cout << "=================================" << endl;
}

const char* OrganDonor::getDonationType() const
{
    return "Organ";
}

void OrganDonor::display() const
{
    char nameBuffer[100];
    name.display();

    cout << "Donor ID: " << id << " | Name: " << nameBuffer;
    cout << " | Type: " << donorType;
    cout << " | Organs: " << organCount << " | Lives Saved: " << getPotentialLivesToSave() << endl;
}

void OrganDonor::showMenu()
{
    cout << "\n====== ORGAN DONOR MENU ======" << endl;
    cout << "1. Register Organs to Donate" << endl;
    cout << "2. View Registered Organs" << endl;
    cout << "3. Remove Organ from Registry" << endl;
    cout << "4. Update Family Consent" << endl;
    cout << "5. Generate Donation Card" << endl;
    cout << "6. View Impact Score" << endl;
    cout << "7. Update Preferred Hospital" << endl;
    cout << "8. Update Contact Info" << endl;
    cout << "9. Change Password" << endl;
    cout << "10. Logout" << endl;
    cout << "=============================" << endl;
}