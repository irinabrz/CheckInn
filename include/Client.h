#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>

class Client {
private:
    int id;
    std::string name;
    std::string email;

public:
    Client(int id, const std::string& name, const std::string& email);
    Client(const Client& other);
    ~Client();

    int getId() const;
    std::string getName() const;

    friend std::ostream& operator<<(std::ostream& os, const Client& client);
};

#endif