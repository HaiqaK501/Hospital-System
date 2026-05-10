#include "Person.h"
#include <iostream>

using namespace std;

Person::Person()
{
    id = 0;
}

Person::Person(int idVal, const char* nameVal, const char* passVal)
{
    id = idVal;
    name.set(nameVal);
    password.setPassword(passVal);
}

Person::Person(const Person& other)
{
    id = other.id;
    name = other.name;
    password = other.password;
}

Person& Person::operator=(const Person& other)
{
    if (this == &other)
        return *this;

    id = other.id;
    name = other.name;
    password = other.password;

    return *this;
}

Person::~Person()
{
}

int Person::getID() const
{
    return id;
}

const Name& Person::getName() const
{
    return name;
}

const Password& Person::getPassword() const
{
    return password;
}

void Person::setID(int idVal)
{
    id = idVal;
}

void Person::setName(const char* nameVal)
{
    name.set(nameVal);
}

void Person::setPassword(const char* passVal)
{
    password.setPassword(passVal);
}

bool Person::checkPassword(const char* input) const
{
    if (!input) return false;
    return password.matches(input);
}

void Person::changePassword(const char* oldPass, const char* newPass)
{
    if (!oldPass || !newPass) return;

    if (password.matches(oldPass))
    {
        password.setPassword(newPass);
    }
}

void Person::incrementPasswordDays()
{
    password.incrementDays();
}

bool Person::isPasswordAtRisk() const
{
    return password.isAtRisk();
}

void Person::display() const
{
    cout << "ID: " << id << " | Name: ";
    name.display();
    cout << endl;
}