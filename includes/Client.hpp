/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:16:49 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/15 23:28:54 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Definition.hpp"
class Client
{
private:
std::string nickname;
std::string username;
std::string realname;
std::string hostname;
int clientSocket_fd;

public:
    Client();
    Client(int fd);
    ~Client();
    Client &operator=(const Client &client);
    void setNickname(std::string nickname);
    void setUsername(std::string username);
    void setRealname(std::string realname);
    void setHostname(std::string hostname);
    void setClientSocket_fd(int clientSocket_fd);
    std::string getNickname(void);
    std::string getUsername(void);
    std::string getRealname(void);
    std::string getHostname(void);
    int getClientSocket_fd(void);
};