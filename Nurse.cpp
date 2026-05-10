#include "Nurse.h"
#include "Doctor.h"
#include "Patient.h"
#include "Admin.h"
#include <iostream>

using namespace std;

void Nurse::copyString(char*& dest, const char* src)
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

void Nurse::resizeDoctorArray(int newSize)
{
    if (newSize <= maxDoctors) return;

    int* newArray = new int[newSize];

    for (int i = 0; i < assignedDoctorCount; i++)
    {
        newArray[i] = assignedDoctorIds[i];
    }

    for (int i = assignedDoctorCount; i < newSize; i++)
    {
        newArray[i] = 0;
    }

    delete[] assignedDoctorIds;
    assignedDoctorIds = newArray;
    maxDoctors = newSize;
}

void Nurse::resizePatientArray(int newSize)
{
    if (newSize <= maxPatients) return;

    int* newArray = new int[newSize];

    for (int i = 0; i < assignedPatientCount; i++)
    {
        newArray[i] = assignedPatientIds[i];
    }

    for (int i = assignedPatientCount; i < newSize; i++)
    {
        newArray[i] = 0;
    }

    delete[] assignedPatientIds;
    assignedPatientIds = newArray;
    maxPatients = newSize;
}

void Nurse::resizeCertificationArray(int newSize)
{
    if (newSize <= maxCertifications) return;

    char** newArray = new char* [newSize];

    for (int i = 0; i < certificationCount; i++)
    {
        newArray[i] = new char[50];
        copyString(newArray[i], certifications[i]);
    }

    for (int i = certificationCount; i < newSize; i++)
    {
        newArray[i] = nullptr;
    }

    for (int i = 0; i < certificationCount; i++)
    {
        delete[] certifications[i];
    }
    delete[] certifications;

    certifications = newArray;
    maxCertifications = newSize;
}

Nurse::Nurse() : Person()
{
    specialization = new char[1];
    specialization[0] = '\0';
    shift = new char[1];
    shift[0] = '\0';
    assignedWard = new char[1];
    assignedWard[0] = '\0';
    emergencyContact = new char[1];
    emergencyContact[0] = '\0';
    bloodGroup = new char[1];
    bloodGroup[0] = '\0';

    salary = 0.0f;
    experienceYears = 0;
    overtimeHours = 0;
    sickLeavesTaken = 0;
    annualLeavesTaken = 0;
    performanceRating = 0;
    isHeadNurse = false;

    assignedDoctorCount = 0;
    maxDoctors = 5;
    assignedDoctorIds = new int[maxDoctors];
    for (int i = 0; i < maxDoctors; i++)
        assignedDoctorIds[i] = 0;

    assignedPatientCount = 0;
    maxPatients = 10;
    assignedPatientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++)
        assignedPatientIds[i] = 0;

    certificationCount = 0;
    maxCertifications = 5;
    certifications = new char* [maxCertifications];
    for (int i = 0; i < maxCertifications; i++)
        certifications[i] = nullptr;
}

Nurse::Nurse(int id, const char* nameVal, const char* passVal, const char* spec,
    const char* shiftTime, const char* ward, float sal, int experience)
    : Person(id, nameVal, passVal)
{
    copyString(specialization, spec);
    copyString(shift, shiftTime);
    copyString(assignedWard, ward);
    copyString(emergencyContact, "");
    copyString(bloodGroup, "");

    salary = sal;
    experienceYears = experience;
    overtimeHours = 0;
    sickLeavesTaken = 0;
    annualLeavesTaken = 0;
    performanceRating = 0;
    isHeadNurse = false;

    assignedDoctorCount = 0;
    maxDoctors = 5;
    assignedDoctorIds = new int[maxDoctors];
    for (int i = 0; i < maxDoctors; i++)
        assignedDoctorIds[i] = 0;

    assignedPatientCount = 0;
    maxPatients = 10;
    assignedPatientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++)
        assignedPatientIds[i] = 0;

    certificationCount = 0;
    maxCertifications = 5;
    certifications = new char* [maxCertifications];
    for (int i = 0; i < maxCertifications; i++)
        certifications[i] = nullptr;
}

Nurse::Nurse(const Nurse& other) : Person(other)
{
    copyString(specialization, other.specialization);
    copyString(shift, other.shift);
    copyString(assignedWard, other.assignedWard);
    copyString(emergencyContact, other.emergencyContact);
    copyString(bloodGroup, other.bloodGroup);

    salary = other.salary;
    experienceYears = other.experienceYears;
    overtimeHours = other.overtimeHours;
    sickLeavesTaken = other.sickLeavesTaken;
    annualLeavesTaken = other.annualLeavesTaken;
    performanceRating = other.performanceRating;
    isHeadNurse = other.isHeadNurse;

    assignedDoctorCount = other.assignedDoctorCount;
    maxDoctors = other.maxDoctors;
    assignedDoctorIds = new int[maxDoctors];
    for (int i = 0; i < maxDoctors; i++)
        assignedDoctorIds[i] = other.assignedDoctorIds[i];

    assignedPatientCount = other.assignedPatientCount;
    maxPatients = other.maxPatients;
    assignedPatientIds = new int[maxPatients];
    for (int i = 0; i < maxPatients; i++)
        assignedPatientIds[i] = other.assignedPatientIds[i];

    certificationCount = other.certificationCount;
    maxCertifications = other.maxCertifications;
    certifications = new char* [maxCertifications];
    for (int i = 0; i < maxCertifications; i++)
    {
        if (other.certifications[i])
        {
            certifications[i] = new char[50];
            copyString(certifications[i], other.certifications[i]);
        }
        else
        {
            certifications[i] = nullptr;
        }
    }
}

Nurse& Nurse::operator=(const Nurse& other)
{
    if (this == &other)
        return *this;

    Person::operator=(other);

    copyString(specialization, other.specialization);
    copyString(shift, other.shift);
    copyString(assignedWard, other.assignedWard);
    copyString(emergencyContact, other.emergencyContact);
    copyString(bloodGroup, other.bloodGroup);

    salary = other.salary;
    experienceYears = other.experienceYears;
    overtimeHours = other.overtimeHours;
    sickLeavesTaken = other.sickLeavesTaken;
    annualLeavesTaken = other.annualLeavesTaken;
    performanceRating = other.performanceRating;
    isHeadNurse = other.isHeadNurse;

    assignedDoctorCount = other.assignedDoctorCount;
    if (maxDoctors < other.maxDoctors)
    {
        delete[] assignedDoctorIds;
        maxDoctors = other.maxDoctors;
        assignedDoctorIds = new int[maxDoctors];
    }
    for (int i = 0; i < maxDoctors; i++)
        assignedDoctorIds[i] = other.assignedDoctorIds[i];

    assignedPatientCount = other.assignedPatientCount;
    if (maxPatients < other.maxPatients)
    {
        delete[] assignedPatientIds;
        maxPatients = other.maxPatients;
        assignedPatientIds = new int[maxPatients];
    }
    for (int i = 0; i < maxPatients; i++)
        assignedPatientIds[i] = other.assignedPatientIds[i];

    for (int i = 0; i < certificationCount; i++)
    {
        delete[] certifications[i];
    }

    if (maxCertifications < other.maxCertifications)
    {
        delete[] certifications;
        maxCertifications = other.maxCertifications;
        certifications = new char* [maxCertifications];
    }

    certificationCount = other.certificationCount;
    for (int i = 0; i < maxCertifications; i++)
    {
        if (i < other.certificationCount && other.certifications[i])
        {
            certifications[i] = new char[50];
            copyString(certifications[i], other.certifications[i]);
        }
        else
        {
            certifications[i] = nullptr;
        }
    }

    return *this;
}

Nurse::~Nurse()
{
    delete[] specialization;
    delete[] shift;
    delete[] assignedWard;
    delete[] emergencyContact;
    delete[] bloodGroup;
    delete[] assignedDoctorIds;
    delete[] assignedPatientIds;

    for (int i = 0; i < certificationCount; i++)
    {
        delete[] certifications[i];
    }
    delete[] certifications;
}

const char* Nurse::getSpecialization() const { return specialization; }
const char* Nurse::getShift() const { return shift; }
const char* Nurse::getAssignedWard() const { return assignedWard; }
float Nurse::getSalary() const { return salary; }
int Nurse::getExperience() const { return experienceYears; }
float Nurse::getOvertimeHours() const { return overtimeHours; }
int Nurse::getSickLeavesTaken() const { return sickLeavesTaken; }
int Nurse::getAnnualLeavesTaken() const { return annualLeavesTaken; }
int Nurse::getPerformanceRating() const { return performanceRating; }
bool Nurse::getIsHeadNurse() const { return isHeadNurse; }
const char* Nurse::getEmergencyContact() const { return emergencyContact; }
const char* Nurse::getBloodGroup() const { return bloodGroup; }

void Nurse::setSpecialization(const char* spec) { copyString(specialization, spec); }
void Nurse::setShift(const char* shiftTime) { copyString(shift, shiftTime); }
void Nurse::setAssignedWard(const char* ward) { copyString(assignedWard, ward); }
void Nurse::setSalary(float sal) { salary = sal; }
void Nurse::setExperience(int years) { experienceYears = years; }
void Nurse::setOvertimeHours(float hours) { overtimeHours = hours; }
void Nurse::setPerformanceRating(int rating) { performanceRating = rating; }
void Nurse::setIsHeadNurse(bool head) { isHeadNurse = head; }
void Nurse::setEmergencyContact(const char* contact) { copyString(emergencyContact, contact); }
void Nurse::setBloodGroup(const char* bg) { copyString(bloodGroup, bg); }

bool Nurse::assignToDoctor(int doctorId)
{
    if (assignedDoctorCount >= maxDoctors)
    {
        resizeDoctorArray(maxDoctors + 5);
    }

    for (int i = 0; i < assignedDoctorCount; i++)
    {
        if (assignedDoctorIds[i] == doctorId)
            return false;
    }

    assignedDoctorIds[assignedDoctorCount] = doctorId;
    assignedDoctorCount++;
    return true;
}

bool Nurse::removeFromDoctor(int doctorId)
{
    for (int i = 0; i < assignedDoctorCount; i++)
    {
        if (assignedDoctorIds[i] == doctorId)
        {
            for (int j = i; j < assignedDoctorCount - 1; j++)
            {
                assignedDoctorIds[j] = assignedDoctorIds[j + 1];
            }
            assignedDoctorCount--;
            return true;
        }
    }
    return false;
}

const int* Nurse::getAssignedDoctorIds() const { return assignedDoctorIds; }
int Nurse::getAssignedDoctorCount() const { return assignedDoctorCount; }

bool Nurse::assignToPatient(int patientId)
{
    if (assignedPatientCount >= maxPatients)
    {
        resizePatientArray(maxPatients + 10);
    }

    for (int i = 0; i < assignedPatientCount; i++)
    {
        if (assignedPatientIds[i] == patientId)
            return false;
    }

    assignedPatientIds[assignedPatientCount] = patientId;
    assignedPatientCount++;
    return true;
}

bool Nurse::removeFromPatient(int patientId)
{
    for (int i = 0; i < assignedPatientCount; i++)
    {
        if (assignedPatientIds[i] == patientId)
        {
            for (int j = i; j < assignedPatientCount - 1; j++)
            {
                assignedPatientIds[j] = assignedPatientIds[j + 1];
            }
            assignedPatientCount--;
            return true;
        }
    }
    return false;
}

const int* Nurse::getAssignedPatientIds() const { return assignedPatientIds; }
int Nurse::getAssignedPatientCount() const { return assignedPatientCount; }

bool Nurse::addCertification(const char* certification)
{
    if (certificationCount >= maxCertifications)
    {
        resizeCertificationArray(maxCertifications + 5);
    }

    if (hasCertification(certification))
        return false;

    certifications[certificationCount] = new char[50];
    copyString(certifications[certificationCount], certification);
    certificationCount++;
    return true;
}

bool Nurse::removeCertification(const char* certification)
{
    for (int i = 0; i < certificationCount; i++)
    {
        bool match = true;
        int j = 0;
        while (certifications[i][j] != '\0' && certification[j] != '\0')
        {
            if (certifications[i][j] != certification[j])
            {
                match = false;
                break;
            }
            j++;
        }
        if (match && certifications[i][j] == '\0' && certification[j] == '\0')
        {
            delete[] certifications[i];
            for (int k = i; k < certificationCount - 1; k++)
            {
                certifications[k] = certifications[k + 1];
            }
            certificationCount--;
            return true;
        }
    }
    return false;
}

const char** Nurse::getCertifications() const { return const_cast<const char**>(certifications); }
int Nurse::getCertificationCount() const { return certificationCount; }

bool Nurse::hasCertification(const char* certification) const
{
    for (int i = 0; i < certificationCount; i++)
    {
        int j = 0;
        bool match = true;
        while (certifications[i][j] != '\0' && certification[j] != '\0')
        {
            if (certifications[i][j] != certification[j])
            {
                match = false;
                break;
            }
            j++;
        }
        if (match && certifications[i][j] == '\0' && certification[j] == '\0')
            return true;
    }
    return false;
}

void Nurse::takeSickLeave(int days)
{
    sickLeavesTaken += days;
}

void Nurse::takeAnnualLeave(int days)
{
    annualLeavesTaken += days;
}

int Nurse::getRemainingLeaves() const
{
    const int MAX_ANNUAL_LEAVES = 20;
    const int MAX_SICK_LEAVES = 10;
    return (MAX_ANNUAL_LEAVES - annualLeavesTaken) + (MAX_SICK_LEAVES - sickLeavesTaken);
}

float Nurse::calculateBonus() const
{
    float bonus = salary * 0.05f;

    if (experienceYears > 5)
        bonus += salary * 0.05f;
    else if (experienceYears > 3)
        bonus += salary * 0.03f;
    else if (experienceYears > 1)
        bonus += salary * 0.01f;

    if (assignedDoctorCount > 3)
        bonus += salary * 0.03f;

    if (certificationCount > 2)
        bonus += salary * 0.02f;

    if (isHeadNurse)
        bonus += salary * 0.10f;

    if (performanceRating >= 4)
        bonus += salary * 0.05f;
    else if (performanceRating >= 3)
        bonus += salary * 0.02f;

    return bonus;
}

bool Nurse::isEligibleForPromotion() const
{
    return (experienceYears >= 3 &&
        certificationCount >= 2 &&
        performanceRating >= 3 &&
        assignedDoctorCount >= 2);
}

float Nurse::calculateOvertimePay() const
{
    float hourlyRate = salary / (20 * 8);
    return overtimeHours * hourlyRate * 1.5f;
}

void Nurse::addOvertime(float hours)
{
    overtimeHours += hours;
}

void Nurse::conductTraining(const char* trainingName)
{
    addCertification(trainingName);
}

void Nurse::receivePerformanceReview(int rating)
{
    if (rating >= 1 && rating <= 5)
        performanceRating = rating;
}

bool Nurse::requestShiftChange(const char* newShift)
{
    if (experienceYears > 2)
    {
        setShift(newShift);
        return true;
    }
    return false;
}

float Nurse::getAnnualSalaryWithBonus() const
{
    return (salary * 12) + calculateBonus() + calculateOvertimePay();
}

int Nurse::getTotalPatientsAssigned() const
{
    return assignedPatientCount;
}

float Nurse::getPatientPerDoctorRatio() const
{
    if (assignedDoctorCount == 0) return 0;
    return (float)assignedPatientCount / assignedDoctorCount;
}

bool Nurse::operator==(const Nurse& other) const
{
    return (id == other.id);
}

bool Nurse::operator<(const Nurse& other) const
{
    return (experienceYears < other.experienceYears);
}

bool Nurse::operator>(const Nurse& other) const
{
    return (experienceYears > other.experienceYears);
}

Nurse& Nurse::operator+=(float overtimeAmount)
{
    addOvertime(overtimeAmount);
    return *this;
}

Nurse& Nurse::operator-=(int leaveDays)
{
    takeAnnualLeave(leaveDays);
    return *this;
}

void Nurse::display() const
{
   
   

    cout << "Nurse ID: " << id << endl;
    name.display();
    cout << " | Specialization: " << specialization;
    cout << " | Shift: " << shift;
    cout << " | Ward: " << assignedWard;
    cout << " | Experience: " << experienceYears << " years";
    if (isHeadNurse)
        cout << " | HEAD NURSE";
    cout << endl;
}

void Nurse::displayInfoToBuffer(char* buffer, int bufferSize) const
{
    if (!buffer || bufferSize <= 0) return;

    int idx = 0;

    const char* text1 = "Nurse: ";
    for (int i = 0; text1[i] != '\0' && idx < bufferSize - 1; i++)
        buffer[idx++] = text1[i];

    name.display();
    while (buffer[idx] != '\0') idx++;

    const char* text2 = " (ID: ";
    for (int i = 0; text2[i] != '\0' && idx < bufferSize - 1; i++)
        buffer[idx++] = text2[i];

    if (id == 0)
    {
        buffer[idx++] = '0';
    }
    else
    {
        int digits[10];
        int digitCount = 0;
        int temp = id;
        while (temp > 0)
        {
            digits[digitCount++] = temp % 10;
            temp /= 10;
        }
        for (int i = digitCount - 1; i >= 0 && idx < bufferSize - 1; i--)
            buffer[idx++] = '0' + digits[i];
    }

    buffer[idx++] = ')';
    buffer[idx] = '\0';
}

void Nurse::displayFullDetails() const
{
   
   

    cout << "\n========== NURSE FULL DETAILS ==========" << endl;
    cout << "ID: " << id << endl;
    name.display();
    cout << "Specialization: " << specialization << endl;
    cout << "Shift: " << shift << endl;
    cout << "Assigned Ward: " << assignedWard << endl;
    cout << "Salary: Rs. " << salary << endl;
    cout << "Experience: " << experienceYears << " years" << endl;
    cout << "Overtime Hours: " << overtimeHours << endl;
    cout << "Blood Group: " << bloodGroup << endl;
    cout << "Emergency Contact: " << emergencyContact << endl;
    cout << "Performance Rating: " << performanceRating << "/5" << endl;
    cout << "Head Nurse: " << (isHeadNurse ? "Yes" : "No") << endl;

    cout << "\nCertifications: ";
    if (certificationCount == 0)
        cout << "None";
    else
    {
        for (int i = 0; i < certificationCount; i++)
        {
            cout << certifications[i];
            if (i < certificationCount - 1) cout << ", ";
        }
    }
    cout << endl;

    cout << "\nAssigned Doctors: ";
    if (assignedDoctorCount == 0)
        cout << "None";
    else
    {
        for (int i = 0; i < assignedDoctorCount; i++)
        {
            cout << assignedDoctorIds[i];
            if (i < assignedDoctorCount - 1) cout << ", ";
        }
    }
    cout << endl;

    cout << "\nAssigned Patients: " << assignedPatientCount << endl;
    cout << "Patient/Doctor Ratio: " << getPatientPerDoctorRatio() << endl;

    cout << "\nLeave Summary:" << endl;
    cout << "  Sick Leaves Taken: " << sickLeavesTaken << "/10" << endl;
    cout << "  Annual Leaves Taken: " << annualLeavesTaken << "/20" << endl;
    cout << "  Remaining Leaves: " << getRemainingLeaves() << endl;

    cout << "\nFinancial Info:" << endl;
    cout << "  Monthly Salary: Rs. " << salary << endl;
    cout << "  Annual Salary: Rs. " << salary * 12 << endl;
    cout << "  Bonus: Rs. " << calculateBonus() << endl;
    cout << "  Overtime Pay: Rs. " << calculateOvertimePay() << endl;
    cout << "  Total Annual Compensation: Rs. " << getAnnualSalaryWithBonus() << endl;

    cout << "\nPromotion Eligibility: " << (isEligibleForPromotion() ? "ELIGIBLE" : "Not Eligible") << endl;
    cout << "=========================================" << endl;
}

bool Nurse::workWithDoctor(const Doctor& doctor)
{
    return assignToDoctor(doctor.getID());
}

bool Nurse::careForPatient(const Patient& patient)
{
    return assignToPatient(patient.getID());
}

bool Nurse::reportToAdmin(const Admin& admin)
{
    return (admin.getID() > 0);
}

void Nurse::showMenu()
{
    cout << "\n========== NURSE MENU ==========" << endl;
    cout << "1. View My Schedule" << endl;
    cout << "2. View Assigned Patients" << endl;
    cout << "3. View Assigned Doctors" << endl;
    cout << "4. Update Patient Vitals" << endl;
    cout << "5. Request Leave" << endl;
    cout << "6. View My Financial Summary" << endl;
    cout << "7. View Certifications" << endl;
    cout << "8. Add Overtime Hours" << endl;
    cout << "9. Request Shift Change" << endl;
    cout << "10. Check Promotion Status" << endl;
    cout << "11. View Full Details" << endl;
    cout << "12. Change Password" << endl;
    cout << "13. Logout" << endl;
    cout << "================================" << endl;
}

void Nurse::displayInfo() const
{
    char nameBuffer[100];
    name.display();

    cout << "ID: " << id << " | Name: " << nameBuffer;
    cout << " | Role: NURSE";
    cout << " | Specialization: " << specialization;
    cout << " | Shift: " << shift;
    cout << " | Ward: " << assignedWard;
    cout << " | Experience: " << experienceYears << " years";
    if (isHeadNurse)
        cout << " | HEAD NURSE";
    cout << endl;
}