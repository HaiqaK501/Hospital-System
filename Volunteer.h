#pragma once

#include "Person.h"

class Volunteer : public Person
{
private:
    char* department;
    char* shift;
    int hoursPerWeek;
    int totalHours;
    char* skills;
    char* availability;
    bool backgroundCheckCompleted;
    bool trainingCompleted;
    int* assignedTaskIds;
    int taskCount;
    int maxTasks;
    char* emergencyContactName;
    char* emergencyContactPhone;
    int rating;
    char* tShirtSize;

public:
    Volunteer();
    Volunteer(int id, const char* name, const char* password, const char* dept, const char* shiftTime,
        int hours, const char* skillset, const char* avail);
    Volunteer(const Volunteer& other);
    Volunteer& operator=(const Volunteer& other);
    virtual ~Volunteer();

    const char* getDepartment() const;
    const char* getShift() const;
    int getHoursPerWeek() const;
    int getTotalHours() const;
    const char* getSkills() const;
    bool getBackgroundCheck() const;
    bool getTrainingCompleted() const;
    int getRating() const;

    void completeBackgroundCheck();
    void completeTraining();
    void addHours(int hours);
    bool assignTask(int taskId);
    bool completeTask(int taskId);
    void updateRating(int newRating);
    bool isEligibleForAward() const;
    int getTasksCompleted() const;

    virtual void display() const;
    virtual void showMenu();
    virtual void displayInfo() const;

    const char* getAvailability() const;
    void setAvailability(const char* avail);

private:
    void copyString(char*& dest, const char* src);
    void resizeTaskArray(int newSize);
};