#include "HospitalException.h"

HospitalException::HospitalException(const char* msg) {
    for (int i = 0; msg[i] != '\0' && i < 199; i++) {
        message[i] = msg[i];
    }
    message[199] = '\0';
}

HospitalException::~HospitalException() {}

const char* HospitalException::what() const {
    return message;
}

HospitalException::HospitalException(const HospitalException& other) {
    for (int i = 0; other.message[i] != '\0' && i < 199; i++) {
        message[i] = other.message[i];
    }
    message[199] = '\0';
}

HospitalException& HospitalException::operator=(const HospitalException& other) {
    if (this != &other) {
        for (int i = 0; other.message[i] != '\0' && i < 199; i++) {
            message[i] = other.message[i];
        }
        message[199] = '\0';
    }
    return *this;
}