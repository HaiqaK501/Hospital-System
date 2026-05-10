#include "Password.h"

static bool isDigitChar(char c)
{
    return (c >= '0' && c <= '9');
}

static bool isUpperChar(char c)
{
    return (c >= 'A' && c <= 'Z');
}

static bool isSpecialChar(char c)
{
    const char special[] = "!@#$%^&*()_+-=[]{}|;:',.<>?/";
    for (int i = 0; special[i] != '\0'; i++)
        if (c == special[i])
            return true;
    return false;
}

static int getRandomInt(int max)
{
    static unsigned int next = 1;
    next = next * 1103515245 + 12345;
    return (next / 65536) % (max + 1);
}

int Password::findlen() const
{
    int i = 0;
    while (data[i] != '\0')
        i++;
    return i;
}

bool Password::hasNumeric() const
{
    for (int i = 0; i < length; i++)
        if (isDigitChar(data[i]))
            return true;
    return false;
}

bool Password::hasUpper() const
{
    for (int i = 0; i < length; i++)
        if (isUpperChar(data[i]))
            return true;
    return false;
}

bool Password::hasSpecial() const
{
    for (int i = 0; i < length; i++)
        if (isSpecialChar(data[i]))
            return true;
    return false;
}

bool Password::hasMinLength() const
{
    return findlen() >= 15;
}

Password::Password()
{
    length = 0;
    days_kept = 0;
    data = new char[1];
    data[0] = '\0';
}

Password::Password(const char* raw, int len)
{
    length = len;
    days_kept = 0;
    data = new char[length + 1];
    for (int i = 0; i < length; i++)
        data[i] = raw[i];
    data[length] = '\0';
}

Password::Password(const Password& other)
{
    length = other.length;
    days_kept = other.days_kept;
    data = new char[length + 1];
    for (int i = 0; i < length; i++)
        data[i] = other.data[i];
    data[length] = '\0';
}

Password& Password::operator=(const Password& other)
{
    if (this == &other)
        return *this;

    delete[] data;
    length = other.length;
    days_kept = other.days_kept;
    data = new char[length + 1];
    for (int i = 0; i < length; i++)
        data[i] = other.data[i];
    data[length] = '\0';
    return *this;
}

Password::~Password()
{
    delete[] data;
}

bool Password::isValid() const
{
    return (hasMinLength() && hasNumeric() && hasUpper() && hasSpecial());
}

Password Password::generateStrong(bool userPermission)
{
    if (!userPermission)
    {
        return Password();
    }

    char generated[20];
    int idx = 0;

    const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char digits[] = "0123456789";
    const char special[] = "!@#$%^&*()_+-=[]{}|;:',.<>?/";

    generated[idx++] = upper[getRandomInt(25)];
    generated[idx++] = digits[getRandomInt(9)];
    generated[idx++] = special[getRandomInt(28)];

    const char all[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:',.<>?/";
    int allLen = 0;
    while (all[allLen] != '\0')
        allLen++;

    while (idx < 15)
    {
        generated[idx++] = all[getRandomInt(allLen - 1)];
    }
    generated[idx] = '\0';

    for (int i = 14; i > 0; i--)
    {
        int j = getRandomInt(i);
        char tmp = generated[i];
        generated[i] = generated[j];
        generated[j] = tmp;
    }

    return Password(generated, 15);
}

bool Password::isAtRisk() const
{
    return days_kept >= 90;
}

bool Password::matches(const char* input) const
{
    if (!input)
        return false;

    int i = 0;
    while (input[i] != '\0' && data[i] != '\0')
    {
        if (input[i] != data[i])
            return false;
        i++;
    }
    return (input[i] == '\0' && data[i] == '\0');
}

void Password::setPassword(const char* newData)
{
    delete[] data;

    if (!newData)
    {
        length = 0;
        data = new char[1];
        data[0] = '\0';
        days_kept = 0;
        return;
    }

    length = 0;
    while (newData[length] != '\0')
        length++;

    data = new char[length + 1];
    for (int i = 0; i < length; i++)
        data[i] = newData[i];
    data[length] = '\0';
    days_kept = 0;
}

const char* Password::get() const
{
    return data;
}

void Password::incrementDays()
{
    days_kept++;
}