#pragma once

#include <iostream>
using namespace std;

class Patient;
class Appointment;

class Bill
{
private:
    int billId;
    int patientId;
    int appointmentId;
    float amount;
    char* status;
    char* date;
    float paidAmount;
    char* paymentMethod;
    float taxAmount;
    float discountAmount;
    char* dueDate;

public:
    Bill();
    Bill(int id, int patientId, int appointmentId, float amount, const char* date);
    Bill(const Bill& other);
    Bill& operator=(const Bill& other);
    ~Bill();

    int getBillId() const;
    int getID() { return billId; };
    int getPatientId() const;
    int getAppointmentId() const;
    float getAmount() const;
    const char* getStatus() const;
    const char* getDate() const;
    float getPaidAmount() const;
    const char* getPaymentMethod() const;
    float getTaxAmount() const;
    float getDiscountAmount() const;
    const char* getDueDate() const;
    float getOutstandingBalance() const;

    void setStatus(const char* newStatus);
    void setPaymentMethod(const char* method);
    void setDiscount(float discount);
    void setDueDate(const char* date);
    void addTax(float tax);

    bool makePayment(float amount, const char* method);
    bool isOverdue(const char* currentDate) const;
    void markAsPaid();
    void markAsCancelled();

    float calculateTotalWithTax() const;
    float calculateTotalAfterDiscount() const;

    bool operator==(const Bill& other) const;
    friend ostream& operator<<(ostream& os, const Bill& bill);

    void display() const;
    void displayFullDetails(const Patient& patient, const Appointment& appointment) const;

private:
    void copyString(char*& dest, const char* src);
};
