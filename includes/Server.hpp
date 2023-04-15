/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:16:44 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/15 23:42:00 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Definition.hpp"
#include "../includes/Client.hpp"

class Server
{
private:
    unsigned short int port;
    std::string password;
    std::vector<pollfd> poolFdClients;
    std::vector<Client> clients;

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
    void acceptAndStoreNewClient();
    void		recvMsg( int fd );
	void		sendMsg( int fd, std::string msg );
};
