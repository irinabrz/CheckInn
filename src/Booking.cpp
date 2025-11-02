#include "Booking.h"

Booking::Booking(unsigned long long id, Client* client, Room* room)
    : id(id), client(client), room(room), confirmed(false) {}

Booking::Booking(const Booking& other)
    : id(other.id), client(other.client), room(other.room), confirmed(other.confirmed) {}

Booking::~Booking() {}

unsigned long long Booking::getId() const { return id; }

void Booking::confirm() { confirmed = true; }
void Booking::cancel() { confirmed = false; }

std::ostream& operator<<(std::ostream& os, const Booking& booking) {
    os << "Booking[" << booking.id << "] "
       << *(booking.client) << " in " << *(booking.room)
       << " Status: " << (booking.confirmed ? "Confirmed" : "Pending");
    return os;
}

