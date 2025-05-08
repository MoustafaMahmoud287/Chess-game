#ifndef CONNECTION_H
#define CONNECTION_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <thread>
#include <atomic>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

class Connection {
public:
    Connection();
    ~Connection();

    bool startServer(unsigned short port = 0); // port=0 means random port
    bool startClient(const std::string& serverIp, unsigned short port);

    void sendMessage(const std::string& message);
    void receiveLoop(); // Call this in a separate thread

    unsigned short getPort() const { return port_; }

private:
    SOCKET socket_;
    SOCKET clientSocket_;
    std::atomic<bool> running_;
    bool isServer_;
    unsigned short port_;

    void cleanup();
};
#endif
