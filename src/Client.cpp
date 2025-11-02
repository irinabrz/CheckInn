#include "Client.h"

Client::Client(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}

Client::Client(const Client& other)
    : id(other.id), name(other.name), email(other.email) {}

Client::~Client() {}

int Client::getId() const { return id; }
std::string Client::getName() const { return name; }

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "Client[" << client.id << "] " << client.name << " <" << client.email << ">";
    return os;
}