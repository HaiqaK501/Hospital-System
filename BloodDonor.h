#pragma once

#include "Donor.h"

class BloodDonor : public Donor
{
private:
    char* bloodGroup;
    char* lastDonationDate;
    int timesDonatedThisYear;
    bool isEligibleForDonation;
    int healthScore;
    char* medicalConditions;

public:
    BloodDonor();
    BloodDonor(int id, const char* name, const char* password, const char* contact,
        const char* addr, const char* bloodGrp, int health);
    BloodDonor(const BloodDonor& other);
    BloodDonor& operator=(const BloodDonor& other);
    virtual ~BloodDonor();

    const char* getBloodGroup() const;
    const char* getLastDonationDate() const;
    int getTimesDonatedThisYear() const;
    bool getIsEligibleForDonation() const;
    int getHealthScore() const;
    const char* getMedicalConditions() const;

    void setLastDonationDate(const char* date);
    void setMedicalConditions(const char* conditions);
    void updateHealthScore(int score);
    void recordBloodDonation(const char* date);
    bool checkEligibility() const;
    int getDonationLimitRemaining() const;

    virtual float calculateImpactScore() const;
    virtual void displayDonorInfo() const;
    virtual const char* getDonationType() const;

    void display() const;
    virtual void showMenu();

private:
    void copyString(char*& dest, const char* src);
};