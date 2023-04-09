/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:18:55 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/09 23:25:14 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Server.hpp"

int main(int argc,char **av) {
    if (argc != 3)
        ARGS_EXCEPTION;
    Server server(atoi(av[1]), av[2]);
    server.initServer();
    server.runServer();
    return 0;
}