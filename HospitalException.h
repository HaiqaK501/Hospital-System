#pragma once

class HospitalException {
private:
    char message[200];

public:
    HospitalException(const char* msg = "Hospital system error");
    virtual ~HospitalException();
    virtual const char* what() const;
    HospitalException(const HospitalException& other);
    HospitalException& operator=(const HospitalException& other);
};

