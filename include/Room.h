#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>

class Room {
private:
    int number;
    bool available;

public:
    Room(int number, bool available=true);
    Room(const Room& other);
    ~Room();

    int getNumber() const;
    bool isAvailable() const;
    void setAvailable(bool status);

    friend std::ostream& operator<<(std::ostream& os, const Room& room);
};

#endif