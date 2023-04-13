/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:16:44 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/13 22:43:19 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <poll.h>
#include <vector>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <iostream>
#include "../includes/Definition.hpp"

class Server
{
private:
    unsigned short int port;
    std::string password;
    std::vector<pollfd> poolFdClients;

public:
    Server();
    Server(unsigned short int port, std::string password);
    ~Server();
    unsigned short int getPort(void);
    void setPort(unsigned short int);
    std::string getPassword(void);
    void setPassword(std::string pass);
    int initServer();
    void runServer();
    void		recvMsg( int fd );
	void		sendMsg( int fd, std::string msg );
};
