#pragma once

#include "HospitalException.h"

class InsufficientFundsException : public HospitalException {
private:
    double requiredAmount;
    double currentBalance;

public:
    InsufficientFundsException(double required = 0.0, double current = 0.0);
    const char* what() const;
};

