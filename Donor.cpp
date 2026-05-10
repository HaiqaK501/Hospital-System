#include "Donor.h"
#include <iostream>

using namespace std;

void Donor::copyString(char*& dest, const char* src)
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

void Donor::setRegistrationDateToToday()
{
    copyString(registrationDate, "01-01-2025");
}

Donor::Donor() : Person()
{
    donorType = new char[1];
    donorType[0] = '\0';
    registrationDate = new char[1];
    registrationDate[0] = '\0';
    contactNumber = new char[1];
    contactNumber[0] = '\0';
    address = new char[1];
    address[0] = '\0';

    totalDonations = 0;
    totalDonationValue = 0.0f;
    isActive = true;
}

Donor::Donor(int id, const char* nameVal, const char* passVal, const char* type,
    const char* contact, const char* addr)
    : Person(id, nameVal, passVal)
{
    copyString(donorType, type);
    copyString(contactNumber, contact);
    copyString(address, addr);

    totalDonations = 0;
    totalDonationValue = 0.0f;
    isActive = true;

    setRegistrationDateToToday();
}

Donor::Donor(const Donor& other) : Person(other)
{
    copyString(donorType, other.donorType);
    copyString(registrationDate, other.registrationDate);
    copyString(contactNumber, other.contactNumber);
    copyString(address, other.address);

    totalDonations = other.totalDonations;
    totalDonationValue = other.totalDonationValue;
    isActive = other.isActive;
}

Donor& Donor::operator=(const Donor& other)
{
    if (this == &other)
        return *this;

    Person::operator=(other);

    copyString(donorType, other.donorType);
    copyString(registrationDate, other.registrationDate);
    copyString(contactNumber, other.contactNumber);
    copyString(address, other.address);

    totalDonations = other.totalDonations;
    totalDonationValue = other.totalDonationValue;
    isActive = other.isActive;

    return *this;
}

Donor::~Donor()
{
    delete[] donorType;
    delete[] registrationDate;
    delete[] contactNumber;
    delete[] address;
}

const char* Donor::getDonorType() const { return donorType; }
const char* Donor::getRegistrationDate() const { return registrationDate; }
int Donor::getTotalDonations() const { return totalDonations; }
float Donor::getTotalDonationValue() const { return totalDonationValue; }
bool Donor::getIsActive() const { return isActive; }
const char* Donor::getContactNumber() const { return contactNumber; }
const char* Donor::getAddress() const { return address; }

void Donor::setContactNumber(const char* contact) { copyString(contactNumber, contact); }
void Donor::setAddress(const char* addr) { copyString(address, addr); }
void Donor::setIsActive(bool active) { isActive = active; }
void Donor::incrementDonations() { totalDonations++; }
void Donor::addToTotalValue(float amount) { totalDonationValue += amount; }

void Donor::display() const
{
    char nameBuffer[100];
    name.display();

    cout << "Donor ID: " << id << " | Name: " << nameBuffer;
    cout << " | Type: " << donorType;
    cout << " | Donations: " << totalDonations;
    cout << " | Active: " << (isActive ? "Yes" : "No") << endl;
}

void Donor::showMenu()
{
    cout << "\n========== DONOR MENU ==========" << endl;
    cout << "1. Make Donation" << endl;
    cout << "2. View My Donation History" << endl;
    cout << "3. View Impact Score" << endl;
    cout << "4. Update Contact Info" << endl;
    cout << "5. Deactivate Donor Account" << endl;
    cout << "6. Change Password" << endl;
    cout << "7. Logout" << endl;
    cout << "================================" << endl;
}

void Donor::displayInfo() const
{
    char nameBuffer[100];
    name.display();

    cout << "ID: " << id << " | Name: " << nameBuffer;
    cout << " | Role: DONOR";
    cout << " | Type: " << donorType;
    cout << " | Donations: " << totalDonations << endl;
}

bool Donor::operator==(const Donor& other) const
{
    return (id == other.id);
}