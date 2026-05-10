#pragma once

class Validator
{
public:
    static bool isDigit(char c);
    static bool isLetter(char c);
    static bool isAlphaNumeric(char c);
    static bool isSpecialChar(char c);
    static int stringToInt(const char* str);
    static float stringToFloat(const char* str);
    static void toLowerCase(char* str);
    static bool compareCaseInsensitive(const char* str1, const char* str2);

    static bool validateID(int id);
    static bool validateName(const char* name);
    static bool validateAge(int age);
    static bool validateGender(const char* gender);
    static bool validateContact(const char* contact);
    static bool validateEmail(const char* email);
    static bool validateAddress(const char* address);
    static bool validateBloodGroup(const char* bloodGroup);
    static bool validatePassword(const char* pass);
    static bool validateDate(const char* date);
    static bool validateTimeSlot(const char* slot);
    static bool validatePositiveFloat(float value);
    static bool validateMenuChoice(int choice, int min, int max);
    static bool validatePercentage(float percent);
    static bool validateRating(int rating);

    static bool validateSpecialization(const char* spec);
    static bool validateDoctorFee(float fee);
    static bool validateDoctorExperience(int years);
    static bool validateDoctorEducation(const char* education);

    static bool validateNurseShift(const char* shift);
    static bool validateNurseSalary(float salary);
    static bool validateNurseExperience(int years);
    static bool validateAssignedWard(const char* ward);

    static bool validateVolunteerHours(int hours);
    static bool validateVolunteerSkills(const char* skills);
    static bool validateVolunteerDepartment(const char* dept);

    static bool validateAppointmentStatus(const char* status);
    static bool validateAppointmentConflict(const char* date, const char* timeSlot);

    static bool validateBillAmount(float amount);
    static bool validateBillStatus(const char* status);
    static bool validatePaymentMethod(const char* method);

    static bool validateMedicineName(const char* name);
    static bool validateMedicinePrice(float price);
    static bool validateMedicineStock(int stock);
    static bool validateMedicineExpiry(const char* expiry);

    static bool validateLabTestName(const char* name);
    static bool validateLabTestCost(float cost);
    static bool validateLabResult(const char* result);

    static bool validateAmbulanceType(const char* type);
    static bool validateAmbulanceDriver(const char* driver);
    static bool validateFuelLevel(float fuel);

    // Ward validations
    static bool validateWardName(const char* name);
    static bool validateWardType(const char* type);
    static bool validateBedCount(int beds);
    static bool validateWardRate(float rate);
    static bool validateNurseInCharge(const char* nurse);

    static bool validateVaccineName(const char* name);
    static bool validateVaccineDoses(int doses);
    static bool validateVaccineTemperature(float temp);
    static bool validateVaccineStock(int stock);

    static bool validateCampName(const char* name);
    static bool validateCampLocation(const char* loc);
    static bool validateCampBudget(float budget);

    static bool validateDonorAmount(float amount);
    static bool validateDonorType(const char* type);
    static bool validateDonorHealthScore(int score);
    static bool validateOrganType(const char* organ);

    static bool validateLoginCredentials(const char* username, const char* password);
    static bool validateSearchQuery(const char* query);

private:
    Validator();
};