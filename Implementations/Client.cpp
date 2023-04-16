/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:18:35 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/15 22:40:09 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"


Client::Client(int fd)
{
    this->clientSocket_fd = fd;
    this->nickname = "default";
    this->username = "default";
    this->realname = "default";
    this->hostname = "default";
}
Client::~Client()
{
}
Client::Client(){}
void Client::setClientSocket_fd(int clientFd) {
    this->clientSocket_fd = clientFd;
}
void Client::setHostname(std::string hostname) {
    this->hostname = hostname;
}
void Client::setNickname(std::string nickname) {
    this->nickname = nickname;
}
void Client::setRealname(std::string realname) {
    this->realname = realname;
}
void Client::setUsername(std::string username) {
    this->username = username;
}

int Client::getClientSocket_fd(void) {
    return this->clientSocket_fd;
}
std::string Client::getHostname(void) {
    return this->hostname;
}
std::string Client::getNickname(void) {
    return this->nickname;
}
std::string Client::getRealname(void) {
    return this->realname;
}
std::string Client::getUsername(void) {
    return this->username;
}
void Client::printClientInfo(void) {
    std::cout << "nickname: " << this->nickname << "username: " << this->username << "realname: " << this->realname << "hostname: " << this->hostname;
    std::cout << " clientSocket_fd: " << this->clientSocket_fd << std::endl;
}