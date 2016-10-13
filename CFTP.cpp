#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/un.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAXBUF 512

void criaSock();
void tipoStream();

int main() {
	criaSock();
}

void criaSock() {
	int sock, status, buflen;
  	unsigned sinlen;	
  	char buffer[MAXBUF];
  	struct sockaddr_in sock_in;
  	int yes = 1;

  	sinlen = sizeof(struct sockaddr_in);
  	memset(&sock_in, 0, sinlen);

  	sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  	sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
  	sock_in.sin_port = htons(46160);
  	sock_in.sin_family = AF_INET;

  	status = bind(sock, (struct sockaddr *)&sock_in, sinlen);
  	printf("Bind Status = %d\n", status);

  	status = getsockname(sock, (struct sockaddr *)&sock_in, &sinlen);
  	printf("Sock port %d\n",htons(sock_in.sin_port));

  	buflen = MAXBUF;
  	memset(buffer, 0, buflen);

  	status = recvfrom(sock, buffer, buflen, 0, (struct sockaddr *)&sock_in, &sinlen);
  	
  	int op;

  	cout << buffer;
  	cin >> op;

  	sendto(sock, op, sizeof(op), 0, (struct sockaddr *)&sock_in, sinlen);

  	switch(op) {
  		case 1:
  			recvfrom(sock, buffer, buflen, 0, (struct sockaddr *)&sock_in, &sinlen);
  			cout << buffer;
  			cin >> buffer;
  			sendto(sock, buffer, buflen, 0, (struct sockaddr *)&sock_in, sinlen);
  			int dest,flag = 0,status,cont,fl=0;
  			dest = creat(argv[2],0666);
  			while(fl == 0) {
  				status = recvfrom(sock, buffer, buflen, 0, (struct sockaddr *)&sock_in, &sinlen);
  				recvfrom(sock, cont, sizeof(cont), 0, (struct sockaddr *)&sock_in, &sinlen);
  				if (status > 0) {
  					flag = 1;
  					sendto(sock, flag, sizeof(flag), 0, (struct sockaddr *)&sock_in, sinlen);
  					write(dest,&buffer,cont);
  				}
  				recvfrom(sock, fl, sizeof(fl), 0, (struct sockaddr *)&sock_in, &sinlen);
  			}
  			break;
  		case 2:
  			break;
  		default:
  	}
}

void tipoStream() {

}