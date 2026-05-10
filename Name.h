#pragma once

class Name
{
private:
    char* data;
    int length;

public:
    Name();
    Name(const char* raw);
    Name(const Name& other);
    Name& operator=(const Name& other);
    ~Name();

    void set(const char* raw);
    const char* get() const;
    int getLength() const;
    void display() const;

    bool operator==(const Name& other) const;
    bool operator!=(const Name& other) const;

private:
    void trim();
};