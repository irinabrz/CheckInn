#include "Hotel.h"
#include <iostream>

Hotel::~Hotel() {}

void Hotel::addRoom(const Room& room) {
    rooms.push_back(room);  // obiect direct
}

void Hotel::addClient(const Client& client) {
    clients.push_back(client); // obiect direct
}

void Hotel::addBooking(const Booking& booking) {
    bookings.push_back(booking); // obiect direct
}

std::vector<Room> Hotel::getAvailableRooms() const {
    std::vector<Room> available;
    for (const auto& room : rooms) {
        if (room.isAvailable()) available.push_back(room);
    }
    return available;
}

void Hotel::listRooms() const {
    for (const auto& room : rooms) std::cout << room << std::endl;
}

void Hotel::listClients() const {
    for (const auto& client : clients) std::cout << client << std::endl;
}

void Hotel::listBookings() const {
    for (const auto& booking : bookings) std::cout << booking << std::endl;
}

void Hotel::confirmBooking(unsigned long long bookingId) {
    for (auto& booking : bookings)
        if (booking.getId() == bookingId)
            booking.confirm();
}

void Hotel::cancelBooking(unsigned long long bookingId) {
    for (auto& booking : bookings)
        if (booking.getId() == bookingId)
            booking.cancel();
}
