/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:18:55 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/13 21:47:44 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Server.hpp"

int main(int argc,char **av) {
    try {
        if (argc != 3)
            ARGS_EXCEPTION;
        Server server(atoi(av[1]), av[2]);
        server.initServer();
        server.runServer();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}