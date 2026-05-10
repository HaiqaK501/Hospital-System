#include "Name.h"
#include <iostream>

using namespace std;

Name::Name()
{
    length = 0;
    data = new char[1];
    data[0] = '\0';
}

Name::Name(const char* raw)
{
    length = 0;
    data = nullptr;
    set(raw);
}

Name::Name(const Name& other)
{
    length = other.length;
    data = new char[length + 1];

    for (int i = 0; i < length; i++)
        data[i] = other.data[i];

    data[length] = '\0';
}

Name& Name::operator=(const Name& other)
{
    if (this == &other)
        return *this;

    delete[] data;

    length = other.length;
    data = new char[length + 1];

    for (int i = 0; i < length; i++)
        data[i] = other.data[i];

    data[length] = '\0';

    return *this;
}

Name::~Name()
{
    delete[] data;
}

void Name::set(const char* raw)
{
    if (data)
        delete[] data;

    if (!raw)
    {
        length = 0;
        data = new char[1];
        data[0] = '\0';
        return;
    }

    length = 0;
    while (raw[length] != '\0')
        length++;

    data = new char[length + 1];

    for (int i = 0; i < length; i++)
        data[i] = raw[i];

    data[length] = '\0';

    trim();
}

const char* Name::get() const
{
    return data;
}

int Name::getLength() const
{
    return length;
}

void Name::display() const
{
    cout << data;
}

bool Name::operator==(const Name& other) const
{
    if (length != other.length)
        return false;

    for (int i = 0; i < length; i++)
        if (data[i] != other.data[i])
            return false;

    return true;
}

bool Name::operator!=(const Name& other) const
{
    return !(*this == other);
}

void Name::trim()
{
    if (length == 0)
        return;

    int start = 0;
    while (start < length && data[start] == ' ')
        start++;

    int end = length - 1;
    while (end >= start && data[end] == ' ')
        end--;

    if (start > end)
    {
        delete[] data;
        length = 0;
        data = new char[1];
        data[0] = '\0';
        return;
    }

    int newLen = end - start + 1;

    for (int i = 0; i < newLen; i++)
        data[i] = data[start + i];

    data[newLen] = '\0';
    length = newLen;
}