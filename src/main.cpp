#include <iostream>
#include "Room.h"
#include "Client.h"
#include "Booking.h"
#include "Hotel.h"

int main() {
    Hotel hotel;
    Room r1(101);
    Room r2(102);
    hotel.addRoom(r1);
    hotel.addRoom(r2);

    Client c1(1, "Irina", "Popescu");
    Client c2(2, "Ana", "Ionescu");
    hotel.addClient(c1);
    hotel.addClient(c2);


    Booking b1(1,&c1, &r1);
    Booking b2(2,&c2, &r2);

    hotel.addBooking(b1);
    hotel.addBooking(b2);

    std::cout << "Rooms:\n";
    hotel.listRooms();

    std::cout << "\nClients:\n";
    hotel.listClients();

    std::cout << "\nBookings:\n";
    hotel.listBookings();

    return 0;
}