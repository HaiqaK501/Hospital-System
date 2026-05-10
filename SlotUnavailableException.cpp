#include "SlotUnavailableException.h"

SlotUnavailableException::SlotUnavailableException(const char* slot, const char* d)
    : HospitalException("Time slot is already booked")
{
    for (int i = 0; slot[i] != '\0' && i < 9; i++) {
        timeSlot[i] = slot[i];
    }
    timeSlot[9] = '\0';

    for (int i = 0; d[i] != '\0' && i < 11; i++) {
        date[i] = d[i];
    }
    date[11] = '\0';
}

const char* SlotUnavailableException::what() const
{
    static char msg[200];
    const char* prefix = "Time slot ";
    int i = 0;

    for (i = 0; prefix[i] != '\0' && i < 199; i++) {
        msg[i] = prefix[i];
    }

    for (int j = 0; timeSlot[j] != '\0' && i < 199; j++, i++) {
        msg[i] = timeSlot[j];
    }

    const char* suffix = " on ";
    for (int j = 0; suffix[j] != '\0' && i < 199; j++, i++) {
        msg[i] = suffix[j];
    }

    for (int j = 0; date[j] != '\0' && i < 199; j++, i++) {
        msg[i] = date[j];
    }

    const char* suffix2 = " is already booked";
    for (int j = 0; suffix2[j] != '\0' && i < 199; j++, i++) {
        msg[i] = suffix2[j];
    }

    msg[i] = '\0';
    return msg;
}