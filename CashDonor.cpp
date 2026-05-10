#include "CashDonor.h"
#include "Patient.h"
#include <iostream>

using namespace std;

void CashDonor::copyString(char*& dest, const char* src)
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

void CashDonor::resizeSponsoredArray(int newSize)
{
    if (newSize <= maxSponsoredPatients) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < sponsoredPatientCount; i++)
        newArray[i] = sponsoredPatientIds[i];
    for (int i = sponsoredPatientCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] sponsoredPatientIds;
    sponsoredPatientIds = newArray;
    maxSponsoredPatients = newSize;
}

CashDonor::CashDonor() : Donor()
{
    donationPurpose = new char[1];
    donationPurpose[0] = '\0';
    taxId = new char[1];
    taxId[0] = '\0';

    totalCashDonated = 0.0f;
    thisYearDonation = 0.0f;
    isAnonymous = false;

    sponsoredPatientCount = 0;
    maxSponsoredPatients = 5;
    sponsoredPatientIds = new int[maxSponsoredPatients];
    for (int i = 0; i < maxSponsoredPatients; i++)
        sponsoredPatientIds[i] = 0;

    copyString(donorType, "Cash Donor");
}

CashDonor::CashDonor(int id, const char* nameVal, const char* passVal, const char* contact,
    const char* addr, bool anonymous)
    : Donor(id, nameVal, passVal, "Cash Donor", contact, addr)
{
    copyString(donationPurpose, "General Hospital Fund");
    copyString(taxId, "");

    totalCashDonated = 0.0f;
    thisYearDonation = 0.0f;
    isAnonymous = anonymous;

    sponsoredPatientCount = 0;
    maxSponsoredPatients = 5;
    sponsoredPatientIds = new int[maxSponsoredPatients];
    for (int i = 0; i < maxSponsoredPatients; i++)
        sponsoredPatientIds[i] = 0;
}

CashDonor::CashDonor(const CashDonor& other) : Donor(other)
{
    copyString(donationPurpose, other.donationPurpose);
    copyString(taxId, other.taxId);

    totalCashDonated = other.totalCashDonated;
    thisYearDonation = other.thisYearDonation;
    isAnonymous = other.isAnonymous;

    sponsoredPatientCount = other.sponsoredPatientCount;
    maxSponsoredPatients = other.maxSponsoredPatients;
    sponsoredPatientIds = new int[maxSponsoredPatients];
    for (int i = 0; i < maxSponsoredPatients; i++)
        sponsoredPatientIds[i] = other.sponsoredPatientIds[i];
}

CashDonor& CashDonor::operator=(const CashDonor& other)
{
    if (this == &other)
        return *this;

    Donor::operator=(other);

    copyString(donationPurpose, other.donationPurpose);
    copyString(taxId, other.taxId);

    totalCashDonated = other.totalCashDonated;
    thisYearDonation = other.thisYearDonation;
    isAnonymous = other.isAnonymous;

    sponsoredPatientCount = other.sponsoredPatientCount;
    if (maxSponsoredPatients < other.maxSponsoredPatients)
    {
        delete[] sponsoredPatientIds;
        maxSponsoredPatients = other.maxSponsoredPatients;
        sponsoredPatientIds = new int[maxSponsoredPatients];
    }
    for (int i = 0; i < maxSponsoredPatients; i++)
        sponsoredPatientIds[i] = other.sponsoredPatientIds[i];

    return *this;
}

CashDonor::~CashDonor()
{
    delete[] donationPurpose;
    delete[] taxId;
    delete[] sponsoredPatientIds;
}

float CashDonor::getTotalCashDonated() const { return totalCashDonated; }
float CashDonor::getThisYearDonation() const { return thisYearDonation; }
int CashDonor::getSponsoredPatientCount() const { return sponsoredPatientCount; }
const char* CashDonor::getDonationPurpose() const { return donationPurpose; }
bool CashDonor::getIsAnonymous() const { return isAnonymous; }
const char* CashDonor::getTaxId() const { return taxId; }

void CashDonor::setDonationPurpose(const char* purpose) { copyString(donationPurpose, purpose); }
void CashDonor::setTaxId(const char* id) { copyString(taxId, id); }

void CashDonor::makeDonation(float amount, const char* purpose)
{
    if (amount <= 0) return;

    totalCashDonated += amount;
    thisYearDonation += amount;
    totalDonationValue += amount;
    totalDonations++;
    setDonationPurpose(purpose);

    incrementDonations();
}

bool CashDonor::sponsorPatient(int patientId)
{
    if (sponsoredPatientCount >= maxSponsoredPatients)
        resizeSponsoredArray(maxSponsoredPatients + 3);

    for (int i = 0; i < sponsoredPatientCount; i++)
        if (sponsoredPatientIds[i] == patientId)
            return false;

    sponsoredPatientIds[sponsoredPatientCount] = patientId;
    sponsoredPatientCount++;
    return true;
}

bool CashDonor::removeSponsoredPatient(int patientId)
{
    for (int i = 0; i < sponsoredPatientCount; i++)
    {
        if (sponsoredPatientIds[i] == patientId)
        {
            for (int j = i; j < sponsoredPatientCount - 1; j++)
                sponsoredPatientIds[j] = sponsoredPatientIds[j + 1];
            sponsoredPatientCount--;
            return true;
        }
    }
    return false;
}

const int* CashDonor::getSponsoredPatientIds() const { return sponsoredPatientIds; }

float CashDonor::calculateTaxBenefit() const
{
    return thisYearDonation * 0.5f;
}

float CashDonor::calculateImpactScore() const
{
    float score = 0.0f;

    score += totalCashDonated / 1000.0f;

    score += sponsoredPatientCount * 50.0f;

    if (totalDonations > 10)
        score += 100.0f;
    else if (totalDonations > 5)
        score += 50.0f;

    return score;
}

void CashDonor::displayDonorInfo() const
{
    cout << "\n====== CASH DONOR DETAILS ======" << endl;
    if (!isAnonymous)
    {
        char nameBuffer[100];
        name.display();
        cout << "Name: " << nameBuffer << endl;
    }
    else
    {
        cout << "Name: ANONYMOUS DONOR" << endl;
    }
    cout << "Total Donations: Rs. " << totalCashDonated << endl;
    cout << "This Year Donations: Rs. " << thisYearDonation << endl;
    cout << "Number of Donations: " << totalDonations << endl;
    cout << "Donation Purpose: " << donationPurpose << endl;
    cout << "Sponsored Patients: " << sponsoredPatientCount << endl;
    cout << "Tax Benefit Available: Rs. " << calculateTaxBenefit() << endl;
    cout << "Impact Score: " << calculateImpactScore() << endl;
    cout << "=================================" << endl;
}

const char* CashDonor::getDonationType() const
{
    return "Cash";
}

void CashDonor::display() const
{
    if (!isAnonymous)
    {
        char nameBuffer[100];
        name.display();

        cout << "Donor ID: " << id << " | Name: " << nameBuffer;
        cout << " | Type: " << donorType;
        cout << " | Donations: " << totalDonations;
        cout << " | Active: " << (isActive ? "Yes" : "No") << endl;
    }
    else
    {
        cout << "Donor ID: " << id << " | Name: ANONYMOUS";
        cout << " | Type: Cash Donor";
        cout << " | Total Donated: Rs. " << totalCashDonated << endl;
    }
}

void CashDonor::showMenu()
{
    cout << "\n====== CASH DONOR MENU ======" << endl;
    cout << "1. Donate Cash to Hospital" << endl;
    cout << "2. Sponsor a Patient" << endl;
    cout << "3. View Sponsored Patients" << endl;
    cout << "4. View Donation History" << endl;
    cout << "5. View Impact Score" << endl;
    cout << "6. View Tax Benefit Summary" << endl;
    cout << "7. Update Donation Purpose" << endl;
    cout << "8. Update Contact Info" << endl;
    cout << "9. Change Password" << endl;
    cout << "10. Logout" << endl;
    cout << "===========================" << endl;
}