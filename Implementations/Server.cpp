/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:17:12 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/08 14:43:23 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
Server::Server(unsigned short int port, std::string pass)
{
    if(port < 66660 || port > 66669)
        PORT_EXCEPTION;
    this->port = port;
    this->password=pass;
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

int Server::initServer() {
    int serverSocket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->getPort());
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serverSocket_fd, (sockaddr *)&addr, sizeof(addr)) < 0)
        BIND_EXCEPTION;
    if (listen(serverSocket_fd, MAX_CLIENTS) < 0)
        LISTEN_EXCEPTION;
    return serverSocket_fd;
}

