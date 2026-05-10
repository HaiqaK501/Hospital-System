#pragma once

#include "Donor.h"

class Patient;

class CashDonor : public Donor
{
private:
    float totalCashDonated;
    float thisYearDonation;
    int* sponsoredPatientIds;
    int sponsoredPatientCount;
    int maxSponsoredPatients;
    char* donationPurpose;
    bool isAnonymous;
    char* taxId;

public:
    CashDonor();
    CashDonor(int id, const char* name, const char* password, const char* contact,
        const char* addr, bool anonymous);
    CashDonor(const CashDonor& other);
    CashDonor& operator=(const CashDonor& other);
    virtual ~CashDonor();

    float getTotalCashDonated() const;
    float getThisYearDonation() const;
    int getSponsoredPatientCount() const;
    const char* getDonationPurpose() const;
    bool getIsAnonymous() const;
    const char* getTaxId() const;

    void setDonationPurpose(const char* purpose);
    void setTaxId(const char* id);
    void makeDonation(float amount, const char* purpose);
    bool sponsorPatient(int patientId);
    bool removeSponsoredPatient(int patientId);
    const int* getSponsoredPatientIds() const;
    float calculateTaxBenefit() const;

    virtual float calculateImpactScore() const;
    virtual void displayDonorInfo() const;
    virtual const char* getDonationType() const;

    void display() const;
    virtual void showMenu();

private:
    void copyString(char*& dest, const char* src);
    void resizeSponsoredArray(int newSize);
};
