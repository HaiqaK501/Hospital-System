#include "BloodDonor.h"
#include <iostream>

using namespace std;

void BloodDonor::copyString(char*& dest, const char* src)
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

BloodDonor::BloodDonor() : Donor()
{
    bloodGroup = new char[1];
    bloodGroup[0] = '\0';
    lastDonationDate = new char[1];
    lastDonationDate[0] = '\0';
    medicalConditions = new char[1];
    medicalConditions[0] = '\0';

    timesDonatedThisYear = 0;
    isEligibleForDonation = true;
    healthScore = 100;

    copyString(donorType, "Blood Donor");
}

BloodDonor::BloodDonor(int id, const char* nameVal, const char* passVal, const char* contact,
    const char* addr, const char* bloodGrp, int health)
    : Donor(id, nameVal, passVal, "Blood Donor", contact, addr)
{
    copyString(bloodGroup, bloodGrp);
    copyString(medicalConditions, "None");
    copyString(lastDonationDate, "Never");

    timesDonatedThisYear = 0;
    isEligibleForDonation = true;
    healthScore = health;
}

BloodDonor::BloodDonor(const BloodDonor& other) : Donor(other)
{
    copyString(bloodGroup, other.bloodGroup);
    copyString(lastDonationDate, other.lastDonationDate);
    copyString(medicalConditions, other.medicalConditions);

    timesDonatedThisYear = other.timesDonatedThisYear;
    isEligibleForDonation = other.isEligibleForDonation;
    healthScore = other.healthScore;
}

BloodDonor& BloodDonor::operator=(const BloodDonor& other)
{
    if (this == &other)
        return *this;

    Donor::operator=(other);

    copyString(bloodGroup, other.bloodGroup);
    copyString(lastDonationDate, other.lastDonationDate);
    copyString(medicalConditions, other.medicalConditions);

    timesDonatedThisYear = other.timesDonatedThisYear;
    isEligibleForDonation = other.isEligibleForDonation;
    healthScore = other.healthScore;

    return *this;
}

BloodDonor::~BloodDonor()
{
    delete[] bloodGroup;
    delete[] lastDonationDate;
    delete[] medicalConditions;
}

const char* BloodDonor::getBloodGroup() const { return bloodGroup; }
const char* BloodDonor::getLastDonationDate() const { return lastDonationDate; }
int BloodDonor::getTimesDonatedThisYear() const { return timesDonatedThisYear; }
bool BloodDonor::getIsEligibleForDonation() const { return isEligibleForDonation; }
int BloodDonor::getHealthScore() const { return healthScore; }
const char* BloodDonor::getMedicalConditions() const { return medicalConditions; }

void BloodDonor::setLastDonationDate(const char* date) { copyString(lastDonationDate, date); }
void BloodDonor::setMedicalConditions(const char* conditions) { copyString(medicalConditions, conditions); }
void BloodDonor::updateHealthScore(int score) { healthScore = score; }

void BloodDonor::recordBloodDonation(const char* date)
{
    timesDonatedThisYear++;
    totalDonations++;
    setLastDonationDate(date);
    isEligibleForDonation = checkEligibility();

    float bloodValue = 5000.0f;
    totalDonationValue += bloodValue;
}

bool BloodDonor::checkEligibility() const
{
    if (healthScore < 50) return false;
    if (timesDonatedThisYear >= 4) return false;
    if (!isActive) return false;
    return true;
}

int BloodDonor::getDonationLimitRemaining() const
{
    return 4 - timesDonatedThisYear;
}

float BloodDonor::calculateImpactScore() const
{
    float score = 0.0f;

    score += totalDonations * 3 * 10.0f;

    if (healthScore >= 90)
        score += 50.0f;
    else if (healthScore >= 70)
        score += 30.0f;

    const char* rareGroups[] = { "AB-", "B-", "A-", "O-" };
    for (int i = 0; i < 4; i++)
    {
        int j = 0;
        bool match = true;
        while (bloodGroup[j] != '\0' && rareGroups[i][j] != '\0')
        {
            if (bloodGroup[j] != rareGroups[i][j])
            {
                match = false;
                break;
            }
            j++;
        }
        if (match)
        {
            score += 100.0f;
            break;
        }
    }

    return score;
}

void BloodDonor::displayDonorInfo() const
{
    char nameBuffer[100];
    name.display();

    cout << "\n====== BLOOD DONOR DETAILS ======" << endl;
    cout << "Name: " << nameBuffer << endl;
    cout << "Blood Group: " << bloodGroup << endl;
    cout << "Last Donation: " << lastDonationDate << endl;
    cout << "Donations This Year: " << timesDonatedThisYear << "/4" << endl;
    cout << "Total Donations: " << totalDonations << endl;
    cout << "Health Score: " << healthScore << "/100" << endl;
    cout << "Eligible: " << (checkEligibility() ? "Yes" : "No") << endl;
    cout << "Impact Score: " << calculateImpactScore() << endl;
    cout << "Medical Conditions: " << medicalConditions << endl;
    cout << "=================================" << endl;
}

const char* BloodDonor::getDonationType() const
{
    return "Blood";
}

void BloodDonor::display() const
{
    char nameBuffer[100];
    name.display();

    cout << "Donor ID: " << id << " | Name: " << nameBuffer;
    cout << " | Type: " << donorType;
    cout << " | Donations: " << totalDonations;
    cout << " | Blood Group: " << bloodGroup;
    cout << " | Eligible: " << (checkEligibility() ? "Yes" : "No") << endl;
}

void BloodDonor::showMenu()
{
    cout << "\n====== BLOOD DONOR MENU ======" << endl;
    cout << "1. Donate Blood" << endl;
    cout << "2. View Donation History" << endl;
    cout << "3. Check Eligibility Status" << endl;
    cout << "4. Update Health Information" << endl;
    cout << "5. View Impact Score" << endl;
    cout << "6. Schedule Next Donation" << endl;
    cout << "7. Update Contact Info" << endl;
    cout << "8. Change Password" << endl;
    cout << "9. Logout" << endl;
    cout << "=============================" << endl;
}