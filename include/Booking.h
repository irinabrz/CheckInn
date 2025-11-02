#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <string>
#include "Client.h"
#include "Room.h"

class Booking {
private:
    unsigned long long id;
    const Client* client;
    Room* room;
    bool confirmed;

public:
    Booking(unsigned long long id, Client* client, Room* room);
    Booking(const Booking& other);
    ~Booking();
    unsigned long long getId() const;
    void confirm();
    void cancel();

    friend std::ostream& operator<<(std::ostream& os, const Booking& booking);
};

#endif