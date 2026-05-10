#include "Validator.h"
#include "Password.h"

Validator::Validator() {}

bool Validator::isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

bool Validator::isLetter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool Validator::isAlphaNumeric(char c)
{
    return isDigit(c) || isLetter(c);
}

bool Validator::isSpecialChar(char c)
{
    const char special[] = "!@#$%^&*()_+-=[]{}|;:',.<>?/";
    for (int i = 0; special[i] != '\0'; i++)
        if (c == special[i]) return true;
    return false;
}

int Validator::stringToInt(const char* str)
{
    if (!str) return 0;
    int result = 0;
    int i = 0;
    int sign = 1;

    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

float Validator::stringToFloat(const char* str)
{
    if (!str) return 0.0f;
    float result = 0.0f;
    int i = 0;
    int sign = 1;

    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    if (str[i] == '.')
    {
        i++;
        float fraction = 0.1f;
        while (str[i] >= '0' && str[i] <= '9')
        {
            result += (str[i] - '0') * fraction;
            fraction *= 0.1f;
            i++;
        }
    }

    return result * sign;
}

void Validator::toLowerCase(char* str)
{
    if (!str) return;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
}

bool Validator::compareCaseInsensitive(const char* str1, const char* str2)
{
    if (!str1 || !str2) return false;

    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        char c1 = str1[i];
        char c2 = str2[i];

        if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;

        if (c1 != c2) return false;
        i++;
    }

    return (str1[i] == '\0' && str2[i] == '\0');
}

bool Validator::validateID(int id)
{
    return id > 0;
}

bool Validator::validateName(const char* name)
{
    if (!name) return false;

    int len = 0;
    while (name[len] != '\0') len++;

    if (len < 2 || len > 50) return false;

    for (int i = 0; i < len; i++)
    {
        if (!isLetter(name[i]) && name[i] != ' ' && name[i] != '.')
            return false;
    }

    return true;
}

bool Validator::validateAge(int age)
{
    return (age >= 0 && age <= 150);
}

bool Validator::validateGender(const char* gender)
{
    if (!gender) return false;

    return (compareCaseInsensitive(gender, "M") ||
        compareCaseInsensitive(gender, "F") ||
        compareCaseInsensitive(gender, "Male") ||
        compareCaseInsensitive(gender, "Female") ||
        compareCaseInsensitive(gender, "Other"));
}

bool Validator::validateContact(const char* contact)
{
    if (!contact) return false;

    int len = 0;
    while (contact[len] != '\0') len++;

    if (len != 11 && len != 13) return false;

    for (int i = 0; i < len; i++)
    {
        if (!isDigit(contact[i])) return false;
    }

    return true;
}

bool Validator::validateEmail(const char* email)
{
    if (!email) return false;

    int len = 0;
    while (email[len] != '\0') len++;

    if (len < 5 || len > 100) return false;

    int atCount = 0;
    int dotCount = 0;
    int atPos = -1;

    for (int i = 0; i < len; i++)
    {
        if (email[i] == '@')
        {
            atCount++;
            atPos = i;
        }
        else if (email[i] == '.')
        {
            dotCount++;
        }
        else if (!isAlphaNumeric(email[i]) && email[i] != '_' && email[i] != '-')
        {
            return false;
        }
    }

    return (atCount == 1 && dotCount >= 1 && atPos > 0 && atPos < len - 1);
}

bool Validator::validateAddress(const char* address)
{
    if (!address) return false;

    int len = 0;
    while (address[len] != '\0') len++;

    return (len >= 5 && len <= 200);
}

bool Validator::validateBloodGroup(const char* bloodGroup)
{
    if (!bloodGroup) return false;

    const char* validGroups[] = { "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-" };

    for (int i = 0; i < 8; i++)
    {
        if (compareCaseInsensitive(bloodGroup, validGroups[i]))
            return true;
    }

    return false;
}

bool Validator::validatePassword(const char* pass)
{
    if (!pass) return false;

    Password temp(pass, 0);
    return temp.isValid();
}

bool Validator::validateDate(const char* date)
{
    if (!date) return false;

    int len = 0;
    while (date[len] != '\0') len++;
    if (len != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5) continue;
        if (!isDigit(date[i])) return false;
    }

    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (isLeap) daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1]) return false;

    return true;
}

bool Validator::validateTimeSlot(const char* slot)
{
    if (!slot) return false;

    int len = 0;
    while (slot[len] != '\0') len++;
    if (len != 5) return false;
    if (slot[2] != ':') return false;

    for (int i = 0; i < 5; i++)
    {
        if (i == 2) continue;
        if (!isDigit(slot[i])) return false;
    }

    int hour = (slot[0] - '0') * 10 + (slot[1] - '0');
    int minute = (slot[3] - '0') * 10 + (slot[4] - '0');

    if (minute != 0 && minute != 30) return false;
    if (hour < 0 || hour > 23) return false;

    return true;
}

bool Validator::validatePositiveFloat(float value)
{
    return value > 0;
}

bool Validator::validateMenuChoice(int choice, int min, int max)
{
    return (choice >= min && choice <= max);
}

bool Validator::validatePercentage(float percent)
{
    return (percent >= 0 && percent <= 100);
}

bool Validator::validateRating(int rating)
{
    return (rating >= 1 && rating <= 5);
}

bool Validator::validateSpecialization(const char* spec)
{
    if (!spec) return false;

    int len = 0;
    while (spec[len] != '\0') len++;

    return (len >= 3 && len <= 50);
}

bool Validator::validateDoctorFee(float fee)
{
    return fee >= 500.0f && fee <= 10000.0f;
}

bool Validator::validateDoctorExperience(int years)
{
    return years >= 0 && years <= 60;
}

bool Validator::validateDoctorEducation(const char* education)
{
    if (!education) return false;

    int len = 0;
    while (education[len] != '\0') len++;

    return len >= 2 && len <= 100;
}

bool Validator::validateNurseShift(const char* shift)
{
    if (!shift) return false;

    return (compareCaseInsensitive(shift, "Morning") ||
        compareCaseInsensitive(shift, "Evening") ||
        compareCaseInsensitive(shift, "Night"));
}

bool Validator::validateNurseSalary(float salary)
{
    return salary >= 25000.0f && salary <= 200000.0f;
}

bool Validator::validateNurseExperience(int years)
{
    return years >= 0 && years <= 50;
}

bool Validator::validateAssignedWard(const char* ward)
{
    if (!ward) return false;

    int len = 0;
    while (ward[len] != '\0') len++;

    return len >= 1 && len <= 30;
}

bool Validator::validateVolunteerHours(int hours)
{
    return hours >= 0 && hours <= 40;
}

bool Validator::validateVolunteerSkills(const char* skills)
{
    if (!skills) return false;

    int len = 0;
    while (skills[len] != '\0') len++;

    return len >= 2 && len <= 200;
}

bool Validator::validateVolunteerDepartment(const char* dept)
{
    if (!dept) return false;

    int len = 0;
    while (dept[len] != '\0') len++;

    return len >= 2 && len <= 50;
}

bool Validator::validateAppointmentStatus(const char* status)
{
    if (!status) return false;

    return (compareCaseInsensitive(status, "pending") ||
        compareCaseInsensitive(status, "confirmed") ||
        compareCaseInsensitive(status, "completed") ||
        compareCaseInsensitive(status, "cancelled") ||
        compareCaseInsensitive(status, "no-show"));
}

bool Validator::validateAppointmentConflict(const char* date, const char* timeSlot)
{
    return validateDate(date) && validateTimeSlot(timeSlot);
}

bool Validator::validateBillAmount(float amount)
{
    return amount > 0 && amount <= 1000000.0f;
}

bool Validator::validateBillStatus(const char* status)
{
    if (!status) return false;

    return (compareCaseInsensitive(status, "paid") ||
        compareCaseInsensitive(status, "unpaid") ||
        compareCaseInsensitive(status, "partial") ||
        compareCaseInsensitive(status, "cancelled"));
}

bool Validator::validatePaymentMethod(const char* method)
{
    if (!method) return false;

    return (compareCaseInsensitive(method, "cash") ||
        compareCaseInsensitive(method, "card") ||
        compareCaseInsensitive(method, "insurance") ||
        compareCaseInsensitive(method, "online"));
}

bool Validator::validateMedicineName(const char* name)
{
    if (!name) return false;

    int len = 0;
    while (name[len] != '\0') len++;

    return len >= 2 && len <= 100;
}

bool Validator::validateMedicinePrice(float price)
{
    return price > 0 && price <= 100000.0f;
}

bool Validator::validateMedicineStock(int stock)
{
    return stock >= 0 && stock <= 10000;
}

bool Validator::validateMedicineExpiry(const char* expiry)
{
    return validateDate(expiry);
}

bool Validator::validateLabTestName(const char* name)
{
    if (!name) return false;

    int len = 0;
    while (name[len] != '\0') len++;

    return len >= 2 && len <= 100;
}

bool Validator::validateLabTestCost(float cost)
{
    return cost > 0 && cost <= 100000.0f;
}

bool Validator::validateLabResult(const char* result)
{
    if (!result) return false;

    int len = 0;
    while (result[len] != '\0') len++;

    return len >= 1 && len <= 500;
}

bool Validator::validateAmbulanceType(const char* type)
{
    if (!type) return false;

    return (compareCaseInsensitive(type, "BLS") ||
        compareCaseInsensitive(type, "ALS") ||
        compareCaseInsensitive(type, "ICU"));
}

bool Validator::validateAmbulanceDriver(const char* driver)
{
    return validateName(driver);
}

bool Validator::validateFuelLevel(float fuel)
{
    return fuel >= 0 && fuel <= 100;
}


bool Validator::validateWardName(const char* name)
{
    if (!name) return false;
    int len = 0;
    while (name[len] != '\0') len++;
    return (len >= 2 && len <= 50);
}

bool Validator::validateWardType(const char* type)
{
    if (!type) return false;
    return (compareCaseInsensitive(type, "General") ||
        compareCaseInsensitive(type, "ICU") ||
        compareCaseInsensitive(type, "Emergency") ||
        compareCaseInsensitive(type, "Pediatric") ||
        compareCaseInsensitive(type, "Isolation") ||
        compareCaseInsensitive(type, "Private") ||
        compareCaseInsensitive(type, "VIP"));
}

bool Validator::validateBedCount(int beds)
{
    return (beds >= 1 && beds <= 200);
}

bool Validator::validateWardRate(float rate)
{
    return (rate >= 1000.0f && rate <= 50000.0f);
}

bool Validator::validateNurseInCharge(const char* nurse)
{
    return validateName(nurse);
}

bool Validator::validateVaccineName(const char* name)
{
    if (!name) return false;

    int len = 0;
    while (name[len] != '\0') len++;

    return len >= 2 && len <= 100;
}

bool Validator::validateVaccineDoses(int doses)
{
    return doses >= 1 && doses <= 6;
}

bool Validator::validateVaccineTemperature(float temp)
{
    return temp >= -80 && temp <= 25;
}

bool Validator::validateVaccineStock(int stock)
{
    return stock >= 0 && stock <= 100000;
}

bool Validator::validateCampName(const char* name)
{
    if (!name) return false;

    int len = 0;
    while (name[len] != '\0') len++;

    return len >= 3 && len <= 100;
}

bool Validator::validateCampLocation(const char* loc)
{
    if (!loc) return false;

    int len = 0;
    while (loc[len] != '\0') len++;

    return len >= 3 && len <= 200;
}

bool Validator::validateCampBudget(float budget)
{
    return budget >= 10000.0f && budget <= 10000000.0f;
}

bool Validator::validateDonorAmount(float amount)
{
    return amount >= 100.0f;
}

bool Validator::validateDonorType(const char* type)
{
    if (!type) return false;

    return (compareCaseInsensitive(type, "Blood Donor") ||
        compareCaseInsensitive(type, "Cash Donor") ||
        compareCaseInsensitive(type, "Organ Donor"));
}

bool Validator::validateDonorHealthScore(int score)
{
    return score >= 0 && score <= 100;
}

bool Validator::validateOrganType(const char* organ)
{
    if (!organ) return false;

    const char* validOrgans[] = { "Heart", "Liver", "Kidney", "Lungs", "Pancreas",
                                   "Eyes", "Cornea", "Skin", "Bone", "Tendons" };

    for (int i = 0; i < 10; i++)
    {
        if (compareCaseInsensitive(organ, validOrgans[i]))
            return true;
    }

    return false;
}

bool Validator::validateLoginCredentials(const char* username, const char* password)
{
    return (username && username[0] != '\0' && password && password[0] != '\0');
}

bool Validator::validateSearchQuery(const char* query)
{
    if (!query) return false;

    int len = 0;
    while (query[len] != '\0') len++;

    return len >= 1 && len <= 100;
}