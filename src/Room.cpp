#include "Room.h"

Room::Room(int number, bool available) : number(number), available(available) {}
Room::Room(const Room& other) : number(other.number), available(other.available) {}
Room::~Room() {}

int Room::getNumber() const { return number; }
bool Room::isAvailable() const { return available; }
void Room::setAvailable(bool status) { available = status; }

std::ostream& operator<<(std::ostream& os, const Room& room) {
    os << "Room[" << room.number << "] " << (room.available ? "Available" : "Booked");
    return os;
}
