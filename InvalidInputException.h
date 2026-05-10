#pragma once



#include "HospitalException.h"

class InvalidInputException : public HospitalException {
private:
    char fieldName[50];

public:
    InvalidInputException(const char* field = "input");
    const char* what() const;
};

