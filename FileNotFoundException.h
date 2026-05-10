#pragma once



#include "HospitalException.h"

class FileNotFoundException : public HospitalException {
private:
    char filename[100];

public:
    FileNotFoundException(const char* file = "unknown");
    const char* what() const;
};
