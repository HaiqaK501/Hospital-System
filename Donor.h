#pragma once

#include "Person.h"

class Donor : public Person
{
protected:
    char* donorType;
    char* registrationDate;
    int totalDonations;
    float totalDonationValue;
    bool isActive;
    char* contactNumber;
    char* address;

public:
    Donor();
    Donor(int id, const char* name, const char* password, const char* type,
        const char* contact, const char* addr);
    Donor(const Donor& other);
    Donor& operator=(const Donor& other);
    virtual ~Donor();

    const char* getDonorType() const;
    const char* getRegistrationDate() const;
    int getTotalDonations() const;
    float getTotalDonationValue() const;
    bool getIsActive() const;
    const char* getContactNumber() const;
    const char* getAddress() const;

    void setContactNumber(const char* contact);
    void setAddress(const char* addr);
    void setIsActive(bool active);
    void incrementDonations();
    void addToTotalValue(float amount);

    virtual float calculateImpactScore() const = 0;
    virtual void displayDonorInfo() const = 0;
    virtual const char* getDonationType() const = 0;

    void display() const;
    virtual void showMenu();
    virtual void displayInfo() const;

    bool operator==(const Donor& other) const;

protected:
    void copyString(char*& dest, const char* src);
    void setRegistrationDateToToday();
};
