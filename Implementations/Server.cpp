/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:17:12 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/16 14:20:05 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
Server::Server(unsigned short int port, std::string pass)
{
    if(port < 0 || port > 6669)
        PORT_EXCEPTION;
    this->port = port;
    this->password = pass;
}

Server::~Server() { }

/////// Setters
void Server::setPort(unsigned short int port) {
    this->port = port;
}

void Server::setPassword(std::string password) {
    this->password = password;
}

/////// Getters
std::string Server::getPassword(void) {
    return this->password;
}

unsigned short int Server::getPort(void) {
    return this->port;
}

// must return to A Simple Stream Server

int Server::initServer() {
    struct addrinfo hints,*res,*p;
    int serverSocket_fd ,status;

    /// setting up the hints to be used in getaddrinfo function to indicate the type of socket we want

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    /// getaddrinfo function to get the address of the server

    if ((status = getaddrinfo(NULL, std::to_string(this->port).c_str(), &hints, &res)) != 0)
        GETADDRINFO_EXCEPTION;

    /// loop through all the results and bind to the first we can



   for (p = res; p; p = p->ai_next) {
       if ((serverSocket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("Error server Side : socket");
            continue;
        }
        if (bind(serverSocket_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(serverSocket_fd);
            perror("Error server Side : bind");
            continue;
        }
        break;
    }
    if (listen(serverSocket_fd, MAX_CLIENTS) == -1) {
        return -1;
    }
    /// set the socket to non blocking

    if(fcntl(serverSocket_fd, F_SETFL, O_NONBLOCK) == -1)
        return -1;
    // disable the Nagle algorithm

    int opt = 1;
    if (setsockopt(serverSocket_fd, IPPROTO_TCP, TCP_NODELAY, (char *)&opt, sizeof(opt)) < 0)
        return -1;

     // add the server socket to the pool of clients
    return serverSocket_fd;
}

// implement the runServer function

void Server::runServer(void) {
    // init the server

    int serverSocket_fd = this->initServer();
    poolFdClients.push_back({serverSocket_fd, POLLIN , 0});
    printf("%d \n",serverSocket_fd);

    printf("Server is running on port %d\n", this->port);
    while(true) {
        // poll the pool of clients
        int pollResult = poll(poolFdClients.data(), poolFdClients.size(), -1);
        if(pollResult == -1) {
            perror("Error server Side : poll");
            return;
        }
         // Iterate over the pollfd vector and handle events on the sockets
        for (auto it = poolFdClients.begin(); it != poolFdClients.end() && pollResult > 0; ) {
            if (it->revents & POLLIN) {
                if (it->fd == serverSocket_fd) {
                    // handle new connection
                    struct sockaddr_in clientAddr;
                    socklen_t clientAddrLen = sizeof(clientAddr);
                    int newClientSocket_fd = accept(serverSocket_fd, (struct sockaddr *)&clientAddr, &clientAddrLen);
                    if (newClientSocket_fd == -1) {
                        perror("Error server Side : accept");
                    }
                    // the first phase of client registation is the accept and store new connection from accept function
                    this->acceptAndStoreNewClient(newClientSocket_fd, clientAddr);
                } else {
                // handle incoming data from a client
                    this->recvMsg(it->fd);
                }
                pollResult--;
            }
            if (it->revents & POLLOUT) {
                // handle outgoing data to a client
                this->sendMsg(it->fd, "Hello from server");
                it->events &= ~POLLOUT;
                pollResult--;
            }
            if(it->revents & POLLERR || it->revents & POLLHUP) {
                // handle disconnection
                printf("Client disconnected");
                close(it->fd);
                it = poolFdClients.erase(it);
                pollResult--;
            } else {
                it++;
            }
        }
        close(serverSocket_fd);
    }
}

// implement the recvMsg function

void Server::recvMsg(int fd) {
    char buffer[MAX_MSG_SIZE];
    int recvResult = recv(fd, buffer, MAX_MSG_SIZE, 0);
    if(recvResult <= 0) {
        if (recvResult==0)
            std::cout << "Connection closed by client" << std::endl;
        else
           std::cout << "recv error on socket " << fd << ": " << strerror(errno) << std::endl;
        close(fd);
    //must remove the clientfd from the pool of clients
    //poolFdClients.erase(std::remove(poolFdClients.begin(), poolFdClients.end(), fd), poolFdClients.end());
    } else {
        std::cout << "Received message from client " << fd << ": " << buffer << std::endl;
        poolFdClients[fd].events |= POLLOUT;
    }
}

// implement the sendMsg function

void Server::sendMsg(int fd, std::string msg) {
    int sendResult = send(fd, msg.c_str(), msg.size(), 0);
    if(sendResult == -1) {
        std::cout << "send error on socket " << fd << ": " << strerror(errno) << std::endl;
        close(fd);
        // must remove the clientfd from the pool of clients
    }
}

void Server::acceptAndStoreNewClient(int newClient_fd, sockaddr_in clientAddr) {
    // handling the new pollfd client
    pollfd newPollfd;
    memset(&newPollfd, 0, sizeof(newPollfd));
    newPollfd.events = POLLIN | POLLOUT;
    newPollfd.fd = newClient_fd;
    this->poolFdClients.push_back(newPollfd);
    //check if the size of the pool of clients is greater than the max number of clients
    if(this->poolFdClients.size() > MAX_CLIENTS) {
        // close the connection
        close(newClient_fd);
        return;
    }
    // handling the new client
    Client newClient(newClient_fd);
    std::string hostname = inet_ntoa(clientAddr.sin_addr);
    newClient.setHostname(hostname);
    newClient.printClientInfo();
    this->connectedClientsToIrcServer.insert(std::pair<int, Client>(newClient_fd, newClient));
}
