#pragma once

#include "Name.h"
#include "Password.h"

class Person
{
protected:
    int id;
    Name name;
    Password password;

public:
    Person();
    Person(int id, const char* name, const char* password);
    Person(const Person& other);
    Person& operator=(const Person& other);
    virtual ~Person();

    int getID() const;
    const Name& getName() const;
    const Password& getPassword() const;

    void setID(int id);
    void setName(const char* name);
    void setPassword(const char* password);

    bool checkPassword(const char* input) const;
    void changePassword(const char* oldPass, const char* newPass);
    void incrementPasswordDays();
    bool isPasswordAtRisk() const;

    void display() const;

    virtual void showMenu() = 0;
    virtual void displayInfo() const = 0;
};