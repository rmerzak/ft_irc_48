/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ownServer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:42:46 by rmerzak           #+#    #+#             */
/*   Updated: 2023/04/13 23:42:49 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv )
{
  int     sockfd,newsockfd,clilen;
  char    c;
  struct  sockaddr_in cli_addr,serv_addr;
  if (argc!=3) {
    printf ("usage  socket_client server port\n");
    exit(0);
  }
  printf ("client starting\n");
  bzero((char*) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family       = AF_INET;
  serv_addr.sin_addr.s_addr  = inet_addr(argv[1]);
  serv_addr.sin_port         = htons(atoi(argv[2]));

  if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
    printf("socket error\n");
    exit(0);
  }
  if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) {
    printf("socket error\n");
    exit(0);
  }
  while (1) {
    c=getchar();
    write (sockfd,&c,1);
  }
  return 1;
}