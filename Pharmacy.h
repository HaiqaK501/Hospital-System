#pragma once

#include <ctime>

class Pharmacy
{
private:
    int medicineId;
    char* medicineName;
    char* category;
    char* manufacturer;
    float price;
    int stockQuantity;
    int reorderLevel;
    char* expiryDate;
    bool requiresPrescription;
    int* prescriptionIds;
    int prescriptionCount;
    int maxPrescriptions;
    float taxPercentage;

public:
    Pharmacy();
    Pharmacy(int id, const char* name, const char* cat, const char* manu, float pr,
        int stock, int reorder, const char* expiry, bool needRx, float tax);
    Pharmacy(const Pharmacy& other);
    Pharmacy& operator=(const Pharmacy& other);
    ~Pharmacy();

    int getMedicineId() const;
    const char* getMedicineName() const;
    const char* getCategory() const;
    const char* getManufacturer() const;
    float getPrice() const;
    int getStockQuantity() const;
    int getReorderLevel() const;
    const char* getExpiryDate() const;
    bool getRequiresPrescription() const;
    float getTaxPercentage() const;
    int getPrescriptionCount() const;

    void setPrice(float pr);
    void setStockQuantity(int qty);
    void setReorderLevel(int level);

    bool addStock(int quantity);
    bool removeStock(int quantity);
    bool isExpired() const;
    bool needsReorder() const;
    float calculatePriceWithTax() const;
    void addPrescription(int prescriptionId);

    void display() const;
    void displayFullDetails() const;
    int getID() { return medicineId; }

private:
    void copyString(char*& dest, const char* src);
    void resizePrescriptionArray(int newSize);
    int parseDateToInt(const char* date) const;
};