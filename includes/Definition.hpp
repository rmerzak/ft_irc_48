/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Definition.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:40:54 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/15 22:44:20 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>


/// VARIABLES
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
#define MAX_CLIENTS 10
#define MAX_MSG_SIZE 512

#define THROW_EXCEPTION( str )       throw std::runtime_error( str )
#define ERRCODE_EXCEPT( code ) THROW_EXCEPTION( std::strerror( code ) )

#define ARGS_EXCEPTION  THROW_EXCEPTION( "Usage: ./ircserv <port> <password>" )
#define PORT_EXCEPTION  THROW_EXCEPTION( "Must respect Port Range for Irc Server! [66660, 66669]" )
#define PASSWORD_EXCEPTION     THROW_EXCEPTION( "password shoud be not be empty" )
#define BIND_EXCEPTION THROW_EXCEPTION("Failed to bind socket to address and port")
#define LISTEN_EXCEPTION THROW_EXCEPTION("Failed to start listening on socket.")
#define GETADDRINFO_EXCEPTION THROW_EXCEPTION("Failed to get address info.")
#define GetAddrInfoException THROW_EXCEPTION("Failed to get address info.")