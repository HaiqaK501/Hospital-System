#include "Pharmacy.h"
#include "Validator.h"
#include <iostream>
#include <ctime>
#include <cstdio>
#pragma warning(disable : 4996)

using namespace std;

void Pharmacy::copyString(char*& dest, const char* src)
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

void Pharmacy::resizePrescriptionArray(int newSize)
{
    if (newSize <= maxPrescriptions) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < prescriptionCount; i++)
        newArray[i] = prescriptionIds[i];
    for (int i = prescriptionCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] prescriptionIds;
    prescriptionIds = newArray;
    maxPrescriptions = newSize;
}

int Pharmacy::parseDateToInt(const char* date) const
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

Pharmacy::Pharmacy()
{
    medicineName = new char[1];
    medicineName[0] = '\0';
    category = new char[1];
    category[0] = '\0';
    manufacturer = new char[1];
    manufacturer[0] = '\0';
    expiryDate = new char[1];
    expiryDate[0] = '\0';

    medicineId = 0;
    price = 0.0f;
    stockQuantity = 0;
    reorderLevel = 0;
    requiresPrescription = false;
    taxPercentage = 0.0f;

    prescriptionCount = 0;
    maxPrescriptions = 10;
    prescriptionIds = new int[maxPrescriptions];
    for (int i = 0; i < maxPrescriptions; i++)
        prescriptionIds[i] = 0;
}

Pharmacy::Pharmacy(int id, const char* name, const char* cat, const char* manu,
    float pr, int stock, int reorder, const char* expiry,
    bool needRx, float tax)
{
    // Validate and set medicine name
    if (!Validator::validateMedicineName(name))
        copyString(medicineName, "Unknown");
    else
        copyString(medicineName, name);

    copyString(category, cat);
    copyString(manufacturer, manu);

    // Validate and set expiry date
    if (!Validator::validateDate(expiry))
        copyString(expiryDate, "01-01-2030");
    else
        copyString(expiryDate, expiry);

    // Validate and set price
    if (!Validator::validatePositiveFloat(pr))
        price = 100.0f;
    else
        price = pr;

    // Validate and set stock
    if (!Validator::validateMedicineStock(stock))
        stockQuantity = 0;
    else
        stockQuantity = stock;

    reorderLevel = reorder;
    requiresPrescription = needRx;

    // Validate and set tax
    if (!Validator::validatePositiveFloat(tax))
        taxPercentage = 0.0f;
    else
        taxPercentage = tax;

    medicineId = id;
    prescriptionCount = 0;
    maxPrescriptions = 10;
    prescriptionIds = new int[maxPrescriptions];
    for (int i = 0; i < maxPrescriptions; i++)
        prescriptionIds[i] = 0;
}

Pharmacy::Pharmacy(const Pharmacy& other)
{
    copyString(medicineName, other.medicineName);
    copyString(category, other.category);
    copyString(manufacturer, other.manufacturer);
    copyString(expiryDate, other.expiryDate);

    medicineId = other.medicineId;
    price = other.price;
    stockQuantity = other.stockQuantity;
    reorderLevel = other.reorderLevel;
    requiresPrescription = other.requiresPrescription;
    taxPercentage = other.taxPercentage;

    prescriptionCount = other.prescriptionCount;
    maxPrescriptions = other.maxPrescriptions;
    prescriptionIds = new int[maxPrescriptions];
    for (int i = 0; i < maxPrescriptions; i++)
        prescriptionIds[i] = other.prescriptionIds[i];
}

Pharmacy& Pharmacy::operator=(const Pharmacy& other)
{
    if (this == &other)
        return *this;

    copyString(medicineName, other.medicineName);
    copyString(category, other.category);
    copyString(manufacturer, other.manufacturer);
    copyString(expiryDate, other.expiryDate);

    medicineId = other.medicineId;
    price = other.price;
    stockQuantity = other.stockQuantity;
    reorderLevel = other.reorderLevel;
    requiresPrescription = other.requiresPrescription;
    taxPercentage = other.taxPercentage;

    prescriptionCount = other.prescriptionCount;
    if (maxPrescriptions < other.maxPrescriptions)
    {
        delete[] prescriptionIds;
        maxPrescriptions = other.maxPrescriptions;
        prescriptionIds = new int[maxPrescriptions];
    }
    for (int i = 0; i < maxPrescriptions; i++)
        prescriptionIds[i] = other.prescriptionIds[i];

    return *this;
}

Pharmacy::~Pharmacy()
{
    delete[] medicineName;
    delete[] category;
    delete[] manufacturer;
    delete[] expiryDate;
    delete[] prescriptionIds;
}

int Pharmacy::getMedicineId() const { return medicineId; }
const char* Pharmacy::getMedicineName() const { return medicineName; }
const char* Pharmacy::getCategory() const { return category; }
const char* Pharmacy::getManufacturer() const { return manufacturer; }
float Pharmacy::getPrice() const { return price; }
int Pharmacy::getStockQuantity() const { return stockQuantity; }
int Pharmacy::getReorderLevel() const { return reorderLevel; }
const char* Pharmacy::getExpiryDate() const { return expiryDate; }
bool Pharmacy::getRequiresPrescription() const { return requiresPrescription; }
float Pharmacy::getTaxPercentage() const { return taxPercentage; }
int Pharmacy::getPrescriptionCount() const { return prescriptionCount; }

void Pharmacy::setPrice(float pr) { price = pr; }
void Pharmacy::setStockQuantity(int qty) { stockQuantity = qty; }
void Pharmacy::setReorderLevel(int level) { reorderLevel = level; }

bool Pharmacy::addStock(int quantity)
{
    if (quantity <= 0) return false;
    stockQuantity += quantity;
    return true;
}

bool Pharmacy::removeStock(int quantity)
{
    if (quantity <= 0 || quantity > stockQuantity) return false;
    stockQuantity -= quantity;
    return true;
}

bool Pharmacy::isExpired() const
{
    if (!expiryDate || expiryDate[0] == '\0') return false;

    // Get current date
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char currentDate[11];
    sprintf(currentDate, "%02d-%02d-%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);

    int expiryDateInt = parseDateToInt(expiryDate);
    int currentDateInt = parseDateToInt(currentDate);

    return expiryDateInt < currentDateInt;
}

bool Pharmacy::needsReorder() const
{
    return stockQuantity <= reorderLevel;
}

float Pharmacy::calculatePriceWithTax() const
{
    return price + (price * taxPercentage / 100);
}

void Pharmacy::addPrescription(int prescriptionId)
{
    if (prescriptionCount >= maxPrescriptions)
        resizePrescriptionArray(maxPrescriptions + 5);

    prescriptionIds[prescriptionCount] = prescriptionId;
    prescriptionCount++;
}

void Pharmacy::display() const
{
    cout << "ID: " << medicineId << " | " << medicineName << " | Stock: " << stockQuantity;
    if (needsReorder()) cout << " | REORDER NEEDED";
    if (isExpired()) cout << " | EXPIRED";
    cout << endl;
}

void Pharmacy::displayFullDetails() const
{
    cout << "\n========== MEDICINE DETAILS ==========" << endl;
    cout << "ID: " << medicineId << endl;
    cout << "Name: " << medicineName << endl;
    cout << "Category: " << category << endl;
    cout << "Manufacturer: " << manufacturer << endl;
    cout << "Price: Rs. " << price << endl;
    cout << "Price with Tax: Rs. " << calculatePriceWithTax() << endl;
    cout << "Stock: " << stockQuantity << endl;
    cout << "Reorder Level: " << reorderLevel << endl;
    cout << "Expiry Date: " << expiryDate << endl;
    if (isExpired()) cout << "STATUS: EXPIRED - DO NOT USE" << endl;
    cout << "Requires Prescription: " << (requiresPrescription ? "Yes" : "No") << endl;
    cout << "Tax Percentage: " << taxPercentage << "%" << endl;
    cout << "Prescriptions Filled: " << prescriptionCount << endl;
    cout << "======================================" << endl;
}