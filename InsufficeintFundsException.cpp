#include "InsufficeintFundsException.h"


InsufficientFundsException::InsufficientFundsException(double required, double current)
    : HospitalException("Insufficient funds"), requiredAmount(required), currentBalance(current) {
}

const char* InsufficientFundsException::what() const {
    static char msg[250];
    const char* prefix = "Insufficient funds! Required: PKR ";
    int i = 0;

    for (i = 0; prefix[i] != '\0' && i < 249; i++) {
        msg[i] = prefix[i];
    }

    int reqInt = static_cast<int>(requiredAmount);
    int reqDecimal = static_cast<int>((requiredAmount - reqInt) * 100);

    if (reqInt == 0) {
        msg[i++] = '0';
    }
    else {
        int reqCopy = reqInt;
        int numDigits = 0;
        int temp = reqInt;
        while (temp > 0) {
            numDigits++;
            temp /= 10;
        }

        int startPos = i + numDigits - 1;
        reqCopy = reqInt;
        for (int j = 0; j < numDigits; j++) {
            msg[startPos - j] = '0' + (reqCopy % 10);
            reqCopy /= 10;
        }
        i += numDigits;
    }

    msg[i++] = '.';

    if (reqDecimal < 10) {
        msg[i++] = '0';
        msg[i++] = '0' + reqDecimal;
    }
    else {
        msg[i++] = '0' + (reqDecimal / 10);
        msg[i++] = '0' + (reqDecimal % 10);
    }

    const char* suffix = ". Balance: PKR ";
    for (int j = 0; suffix[j] != '\0' && i < 249; j++, i++) {
        msg[i] = suffix[j];
    }

    int currInt = static_cast<int>(currentBalance);
    int currDecimal = static_cast<int>((currentBalance - currInt) * 100);

    if (currInt == 0) {
        msg[i++] = '0';
    }
    else {
        int currCopy = currInt;
        int numDigits = 0;
        int temp = currInt;
        while (temp > 0) {
            numDigits++;
            temp /= 10;
        }

        int startPos = i + numDigits - 1;
        currCopy = currInt;
        for (int j = 0; j < numDigits; j++) {
            msg[startPos - j] = '0' + (currCopy % 10);
            currCopy /= 10;
        }
        i += numDigits;
    }

    msg[i++] = '.';

    if (currDecimal < 10) {
        msg[i++] = '0';
        msg[i++] = '0' + currDecimal;
    }
    else {
        msg[i++] = '0' + (currDecimal / 10);
        msg[i++] = '0' + (currDecimal % 10);
    }

    msg[i] = '\0';
    return msg;
}