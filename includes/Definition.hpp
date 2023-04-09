/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Definition.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:40:54 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/09 23:25:09 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>


/// VARIABLES

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