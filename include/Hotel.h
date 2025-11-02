#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include "Room.h"
#include "Client.h"
#include "Booking.h"

class Hotel {
    std::vector<Room> rooms;
    std::vector<Client> clients;
    std::vector<Booking> bookings;
public:
    ~Hotel();
    void addRoom(const Room& room);
    void addClient(const Client& client);
    void addBooking(const Booking& booking);
    std::vector<Room> getAvailableRooms() const;
    void listRooms() const;///ceva
    void listClients() const;
    void listBookings() const;
    void confirmBooking(unsigned long long bookingId);
    void cancelBooking(unsigned long long bookingId);
};
#endif // HOTEL_H