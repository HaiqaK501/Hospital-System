#include "Volunteer.h"
#include <iostream>

using namespace std;

void Volunteer::copyString(char*& dest, const char* src)
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

void Volunteer::resizeTaskArray(int newSize)
{
    if (newSize <= maxTasks) return;

    int* newArray = new int[newSize];
    for (int i = 0; i < taskCount; i++)
        newArray[i] = assignedTaskIds[i];
    for (int i = taskCount; i < newSize; i++)
        newArray[i] = 0;

    delete[] assignedTaskIds;
    assignedTaskIds = newArray;
    maxTasks = newSize;
}

Volunteer::Volunteer() : Person()
{
    department = new char[1];
    department[0] = '\0';
    shift = new char[1];
    shift[0] = '\0';
    skills = new char[1];
    skills[0] = '\0';
    availability = new char[1];
    availability[0] = '\0';
    emergencyContactName = new char[1];
    emergencyContactName[0] = '\0';
    emergencyContactPhone = new char[1];
    emergencyContactPhone[0] = '\0';
    tShirtSize = new char[1];
    tShirtSize[0] = '\0';

    hoursPerWeek = 0;
    totalHours = 0;
    backgroundCheckCompleted = false;
    trainingCompleted = false;
    rating = 0;

    taskCount = 0;
    maxTasks = 20;
    assignedTaskIds = new int[maxTasks];
    for (int i = 0; i < maxTasks; i++)
        assignedTaskIds[i] = 0;
}

Volunteer::Volunteer(int id, const char* nameVal, const char* passVal, const char* dept,
    const char* shiftTime, int hours, const char* skillset, const char* avail)
    : Person(id, nameVal, passVal)
{
    copyString(department, dept);
    copyString(shift, shiftTime);
    copyString(skills, skillset);
    copyString(availability, avail);
    copyString(emergencyContactName, "");
    copyString(emergencyContactPhone, "");
    copyString(tShirtSize, "M");

    hoursPerWeek = hours;
    totalHours = 0;
    backgroundCheckCompleted = false;
    trainingCompleted = false;
    rating = 0;

    taskCount = 0;
    maxTasks = 20;
    assignedTaskIds = new int[maxTasks];
    for (int i = 0; i < maxTasks; i++)
        assignedTaskIds[i] = 0;
}

Volunteer::Volunteer(const Volunteer& other) : Person(other)
{
    copyString(department, other.department);
    copyString(shift, other.shift);
    copyString(skills, other.skills);
    copyString(availability, other.availability);
    copyString(emergencyContactName, other.emergencyContactName);
    copyString(emergencyContactPhone, other.emergencyContactPhone);
    copyString(tShirtSize, other.tShirtSize);

    hoursPerWeek = other.hoursPerWeek;
    totalHours = other.totalHours;
    backgroundCheckCompleted = other.backgroundCheckCompleted;
    trainingCompleted = other.trainingCompleted;
    rating = other.rating;

    taskCount = other.taskCount;
    maxTasks = other.maxTasks;
    assignedTaskIds = new int[maxTasks];
    for (int i = 0; i < maxTasks; i++)
        assignedTaskIds[i] = other.assignedTaskIds[i];
}

Volunteer& Volunteer::operator=(const Volunteer& other)
{
    if (this == &other)
        return *this;

    Person::operator=(other);

    copyString(department, other.department);
    copyString(shift, other.shift);
    copyString(skills, other.skills);
    copyString(availability, other.availability);
    copyString(emergencyContactName, other.emergencyContactName);
    copyString(emergencyContactPhone, other.emergencyContactPhone);
    copyString(tShirtSize, other.tShirtSize);

    hoursPerWeek = other.hoursPerWeek;
    totalHours = other.totalHours;
    backgroundCheckCompleted = other.backgroundCheckCompleted;
    trainingCompleted = other.trainingCompleted;
    rating = other.rating;

    taskCount = other.taskCount;
    if (maxTasks < other.maxTasks)
    {
        delete[] assignedTaskIds;
        maxTasks = other.maxTasks;
        assignedTaskIds = new int[maxTasks];
    }
    for (int i = 0; i < maxTasks; i++)
        assignedTaskIds[i] = other.assignedTaskIds[i];

    return *this;
}

Volunteer::~Volunteer()
{
    delete[] department;
    delete[] shift;
    delete[] skills;
    delete[] availability;
    delete[] emergencyContactName;
    delete[] emergencyContactPhone;
    delete[] tShirtSize;
    delete[] assignedTaskIds;
}

const char* Volunteer::getDepartment() const { return department; }
const char* Volunteer::getShift() const { return shift; }
const char* Volunteer::getAvailability() const { return availability; }
int Volunteer::getHoursPerWeek() const { return hoursPerWeek; }
int Volunteer::getTotalHours() const { return totalHours; }
const char* Volunteer::getSkills() const { return skills; }
bool Volunteer::getBackgroundCheck() const { return backgroundCheckCompleted; }
bool Volunteer::getTrainingCompleted() const { return trainingCompleted; }
int Volunteer::getRating() const { return rating; }

void Volunteer::setAvailability(const char* avail)
{
    copyString(availability, avail);
}

void Volunteer::completeBackgroundCheck()
{
    backgroundCheckCompleted = true;
}

void Volunteer::completeTraining()
{
    trainingCompleted = true;
}

void Volunteer::addHours(int hours)
{
    if (hours > 0)
    {
        totalHours += hours;
    }
}

bool Volunteer::assignTask(int taskId)
{
    if (taskCount >= maxTasks)
        resizeTaskArray(maxTasks + 10);

    assignedTaskIds[taskCount] = taskId;
    taskCount++;
    return true;
}

bool Volunteer::completeTask(int taskId)
{
    for (int i = 0; i < taskCount; i++)
    {
        if (assignedTaskIds[i] == taskId)
        {
            for (int j = i; j < taskCount - 1; j++)
                assignedTaskIds[j] = assignedTaskIds[j + 1];
            taskCount--;
            return true;
        }
    }
    return false;
}

void Volunteer::updateRating(int newRating)
{
    if (newRating >= 1 && newRating <= 5)
        rating = newRating;
}

bool Volunteer::isEligibleForAward() const
{
    return (totalHours >= 100 && rating >= 4 && backgroundCheckCompleted && trainingCompleted);
}

int Volunteer::getTasksCompleted() const
{
    return taskCount;
}

void Volunteer::display() const
{
    cout << "Volunteer ID: " << id << " | Name: ";
    name.display();
    cout << " | Dept: " << department;
    cout << " | Shift: " << shift;
    cout << " | Hours: " << totalHours;
    cout << " | Rating: " << rating << "/5" << endl;
}

void Volunteer::showMenu()
{
    cout << "\n========== VOLUNTEER MENU ==========" << endl;
    cout << "1. View Assigned Tasks" << endl;
    cout << "2. Mark Task Complete" << endl;
    cout << "3. Log Hours" << endl;
    cout << "4. View My Stats" << endl;
    cout << "5. Update Availability" << endl;
    cout << "6. Check Award Eligibility" << endl;
    cout << "7. Change Password" << endl;
    cout << "8. Logout" << endl;
    cout << "====================================" << endl;
}

void Volunteer::displayInfo() const
{
    cout << "ID: " << id << " | Name: ";
    name.display();
    cout << " | Role: VOLUNTEER";
    cout << " | Department: " << department;
    cout << " | Availability: " << availability;
    cout << " | Total Hours: " << totalHours << endl;
}