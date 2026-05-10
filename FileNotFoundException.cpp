#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(const char* file) : HospitalException() {
    for (int i = 0; file[i] != '\0' && i < 99; i++) {
        filename[i] = file[i];
    }
    filename[99] = '\0';
}

const char* FileNotFoundException::what() const {
    static char fullMsg[250];
    const char* prefix = "Cannot open file: ";
    int i = 0;

    for (i = 0; prefix[i] != '\0' && i < 249; i++) {
        fullMsg[i] = prefix[i];
    }

    for (int j = 0; filename[j] != '\0' && i < 249; j++, i++) {
        fullMsg[i] = filename[j];
    }
    fullMsg[i] = '\0';

    return fullMsg;
}