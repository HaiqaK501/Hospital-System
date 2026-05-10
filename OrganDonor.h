#pragma once

#include "Donor.h"

class OrganDonor : public Donor
{
private:
    char** organsToDonate;
    int organCount;
    int maxOrgans;
    char* medicalConsentForm;
    char* organDonationCardNumber;
    bool isFamilyConsented;
    char* preferredHospital;
    bool isEmergencyOnly;

public:
    OrganDonor();
    OrganDonor(int id, const char* name, const char* password, const char* contact,
        const char* addr, const char* hospital, bool emergencyOnly);
    OrganDonor(const OrganDonor& other);
    OrganDonor& operator=(const OrganDonor& other);
    virtual ~OrganDonor();

    const char** getOrgansToDonate() const;
    int getOrganCount() const;
    const char* getMedicalConsentForm() const;
    const char* getOrganDonationCardNumber() const;
    bool getIsFamilyConsented() const;
    const char* getPreferredHospital() const;
    bool getIsEmergencyOnly() const;

    void addOrgan(const char* organ);
    bool removeOrgan(const char* organ);
    bool hasOrgan(const char* organ) const;
    void setFamilyConsent(bool consented);
    void setPreferredHospital(const char* hospital);
    void generateDonationCard();
    int getPotentialLivesToSave() const;

    virtual float calculateImpactScore() const;
    virtual void displayDonorInfo() const;
    virtual const char* getDonationType() const;

    void display() const;
    virtual void showMenu();

private:
    void copyString(char*& dest, const char* src);
    void resizeOrgansArray(int newSize);
    int getLivesPerOrgan(const char* organ) const;
};
