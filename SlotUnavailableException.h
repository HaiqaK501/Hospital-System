#pragma once

#include "HospitalException.h"

class SlotUnavailableException : public HospitalException {
private:
    char timeSlot[10];
    char date[12];

public:
    SlotUnavailableException(const char* slot = "", const char* d = "");
    const char* what() const;
};