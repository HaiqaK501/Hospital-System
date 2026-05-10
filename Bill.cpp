#include "Bill.h"
#include "Patient.h"
#include "Appointment.h"
#include <iostream>

using namespace std;

void Bill::copyString(char*& dest, const char* src)
{
    if (dest) delete[] dest;
    if (!src)
    {
        dest = new char[1];
        dest[0] = '\0';
        return;
    }
    int len = 0;
    while (src[len] != '\0') len++;
    dest = new char[len + 1];
    for (int i = 0; i < len; i++) dest[i] = src[i];
    dest[len] = '\0';
}

Bill::Bill()
{
    status = new char[1]; status[0] = '\0';
    date = new char[1]; date[0] = '\0';
    paymentMethod = new char[1]; paymentMethod[0] = '\0';
    dueDate = new char[1]; dueDate[0] = '\0';

    billId = 0;
    patientId = 0;
    appointmentId = 0;
    amount = 0.0f;
    paidAmount = 0.0f;
    taxAmount = 0.0f;
    discountAmount = 0.0f;
}

Bill::Bill(int id, int pId, int appId, float amt, const char* dt)
{
    copyString(status, "unpaid");
    copyString(date, dt);
    copyString(paymentMethod, "none");
    copyString(dueDate, dt);

    billId = id;
    patientId = pId;
    appointmentId = appId;
    amount = amt;
    paidAmount = 0.0f;
    taxAmount = amt * 0.05f;
    discountAmount = 0.0f;
}

Bill::Bill(const Bill& other)
{
    copyString(status, other.status);
    copyString(date, other.date);
    copyString(paymentMethod, other.paymentMethod);
    copyString(dueDate, other.dueDate);

    billId = other.billId;
    patientId = other.patientId;
    appointmentId = other.appointmentId;
    amount = other.amount;
    paidAmount = other.paidAmount;
    taxAmount = other.taxAmount;
    discountAmount = other.discountAmount;
}

Bill& Bill::operator=(const Bill& other)
{
    if (this == &other) return *this;

    copyString(status, other.status);
    copyString(date, other.date);
    copyString(paymentMethod, other.paymentMethod);
    copyString(dueDate, other.dueDate);

    billId = other.billId;
    patientId = other.patientId;
    appointmentId = other.appointmentId;
    amount = other.amount;
    paidAmount = other.paidAmount;
    taxAmount = other.taxAmount;
    discountAmount = other.discountAmount;

    return *this;
}

Bill::~Bill()
{
    delete[] status;
    delete[] date;
    delete[] paymentMethod;
    delete[] dueDate;
}

int Bill::getBillId() const { return billId; }
int Bill::getPatientId() const { return patientId; }
int Bill::getAppointmentId() const { return appointmentId; }
float Bill::getAmount() const { return amount; }
const char* Bill::getStatus() const { return status; }
const char* Bill::getDate() const { return date; }
float Bill::getPaidAmount() const { return paidAmount; }
const char* Bill::getPaymentMethod() const { return paymentMethod; }
float Bill::getTaxAmount() const { return taxAmount; }
float Bill::getDiscountAmount() const { return discountAmount; }
const char* Bill::getDueDate() const { return dueDate; }
float Bill::getOutstandingBalance() const { return amount - paidAmount; }

void Bill::setStatus(const char* newStatus) { copyString(status, newStatus); }
void Bill::setPaymentMethod(const char* method) { copyString(paymentMethod, method); }
void Bill::setDiscount(float discount) { discountAmount = discount; }
void Bill::setDueDate(const char* dt) { copyString(dueDate, dt); }
void Bill::addTax(float tax) { taxAmount = tax; }

bool Bill::makePayment(float amt, const char* method)
{
    if (amt <= 0) return false;

    float outstanding = getOutstandingBalance();
    if (amt > outstanding) return false;

    paidAmount += amt;
    setPaymentMethod(method);

    if (paidAmount >= amount)
    {
        copyString(status, "paid");
    }
    else
    {
        copyString(status, "partial");
    }

    return true;
}

bool Bill::isOverdue(const char* currentDate) const
{
    // Check if already paid
    for (int i = 0; status[i] != '\0'; i++)
    {
        char c = status[i];
        if (c >= 'A' && c <= 'Z') c = c + 32;
        if (c == 'p' && status[i + 1] == 'a' && status[i + 2] == 'i' && status[i + 3] == 'd')
            return false;
    }

    if (!currentDate) return false;
    if (!dueDate || dueDate[0] == '\0') return false;

    int dueDay = (dueDate[0] - '0') * 10 + (dueDate[1] - '0');
    int dueMonth = (dueDate[3] - '0') * 10 + (dueDate[4] - '0');
    int dueYear = (dueDate[6] - '0') * 1000 + (dueDate[7] - '0') * 100 +
        (dueDate[8] - '0') * 10 + (dueDate[9] - '0');

    int currDay = (currentDate[0] - '0') * 10 + (currentDate[1] - '0');
    int currMonth = (currentDate[3] - '0') * 10 + (currentDate[4] - '0');
    int currYear = (currentDate[6] - '0') * 1000 + (currentDate[7] - '0') * 100 +
        (currentDate[8] - '0') * 10 + (currentDate[9] - '0');

    if (currYear > dueYear) return true;
    if (currYear < dueYear) return false;
    if (currMonth > dueMonth) return true;
    if (currMonth < dueMonth) return false;
    return currDay > dueDay;
}

void Bill::markAsPaid()
{
    copyString(status, "paid");
    paidAmount = amount;
}

void Bill::markAsCancelled()
{
    copyString(status, "cancelled");
}

float Bill::calculateTotalWithTax() const
{
    return amount + taxAmount;
}

float Bill::calculateTotalAfterDiscount() const
{
    return calculateTotalWithTax() - discountAmount;
}

bool Bill::operator==(const Bill& other) const
{
    return (billId == other.billId);
}

ostream& operator<<(ostream& os, const Bill& bill)
{
    os << "Bill ID: " << bill.billId;
    os << " | Amount: Rs. " << bill.amount;
    os << " | Status: " << bill.status;
    os << " | Due: " << bill.dueDate;
    return os;
}

void Bill::display() const
{
    cout << "Bill ID: " << billId;
    cout << " | Patient ID: " << patientId;
    cout << " | Amount: Rs. " << amount;
    cout << " | Paid: Rs. " << paidAmount;
    cout << " | Status: " << status;
    cout << " | Date: " << date << endl;
}

void Bill::displayFullDetails(const Patient& patient, const Appointment& appointment) const
{
    const char* patientName = patient.getName().get();

    cout << "\n========== BILL DETAILS ==========" << endl;
    cout << "Bill ID: " << billId << endl;
    cout << "Patient: " << patientName << " (ID: " << patientId << ")" << endl;
    cout << "Appointment ID: " << appointmentId << endl;
    cout << "Date: " << date << endl;
    cout << "Due Date: " << dueDate << endl;
    cout << "Amount: Rs. " << amount << endl;
    cout << "Tax: Rs. " << taxAmount << endl;
    cout << "Discount: Rs. " << discountAmount << endl;
    cout << "Total: Rs. " << calculateTotalAfterDiscount() << endl;
    cout << "Paid Amount: Rs. " << paidAmount << endl;
    cout << "Outstanding: Rs. " << getOutstandingBalance() << endl;
    cout << "Status: " << status << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    if (isOverdue(date)) cout << "OVERDUE" << endl;
    cout << "==================================" << endl;
}