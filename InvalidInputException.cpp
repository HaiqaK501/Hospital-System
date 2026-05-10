#include "InvalidInputException.h"

InvalidInputException::InvalidInputException(const char* field) : HospitalException() {
    for (int i = 0; field[i] != '\0' && i < 49; i++) {
        fieldName[i] = field[i];
    }
    fieldName[49] = '\0';
}

const char* InvalidInputException::what() const {
    static char msg[200];
    const char* prefix = "Invalid ";
    int i = 0;

    for (i = 0; prefix[i] != '\0' && i < 199; i++) {
        msg[i] = prefix[i];
    }

    for (int j = 0; fieldName[j] != '\0' && i < 199; j++, i++) {
        msg[i] = fieldName[j];
    }

    const char* suffix = " provided";
    for (int j = 0; suffix[j] != '\0' && i < 199; j++, i++) {
        msg[i] = suffix[j];
    }

    msg[i] = '\0';
    return msg;
}