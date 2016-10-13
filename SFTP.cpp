#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

#define MAXBUF 512

void criaSock();
void tipoStream(int op);

int main() {
	criaSock();
}

void criaSock() {
	int sock, status, buflen, sinlen,op;
	struct sockaddr_in sock_in;
	char buffer[MAXBUF];
	int yes = 1;
	buflen = MAXBUF;

	sinlen = sizeof(struct sockaddr_in);
	memset(&sock_in, 0, sinlen);

	sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sock_in.sin_addr.s_addr = htonl(-1);
	sock_in.sin_port = htons(46160);
	sock_in.sin_family = AF_INET;

	status = bind(sock, (struct sockaddr *)&sock_in, sinlen);
	printf("Bind Status = %d\n", status);

	status = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int) );
	printf("Setsockopt Status = %d\n", status);

	strcpy(buffer,"Download --> (1) ou Upload --> (2) ou Sair --> (0)");

	sendto(sock,buffer,buflen,0,(struct sockaddr *)&sock_in, sinlen);

	recvfrom(sock,op,sizeof(op),0,(struct sockaddr *)&sock_in, &sinlen);
	tipoStream(op);
}

void tipoStream(int op) {
	char buffer[MAXBUF];
	int bufflen = MAXBUF,sinlen;
	switch(op) {
		case 1:
			strcpy(buffer,"Digite o nome do arquivo: ");
			sendto(sock,buffer,bufflen,0,(struct sockaddr *)&sock_in, sinlen);
			recvfrom(sock,buffer,bufflen,0,(struct sockaddr *)&sock_in, &sinlen);
			int src,cont,status = 0,flag;
			src = open(argv[1],O_RDONLY);

			if (src == -1) {
         		printf("Impossivel abrir o arquivo %s\n", argv[1]);
         		exit (1); 
       		}

       		while (cont = read(src, &buffer,sizeof(buffer)) > 0) {
       			sendto(sock,buffer,bufflen,0,(struct sockaddr *)&sock_in, sinlen);
       			sendto(sock,cont,sizeof(cont),0,(struct sockaddr *)&sock_in, sinlen);
       			while (status == 0) {
       				status = recvfrom(sock,flag,sizeof(flag),0,(struct sockaddr *)&sock_in, &sinlen);
       				if (flag == 0) {
       					sendto(sock,buffer,bufflen,0,(struct sockaddr *)&sock_in, sinlen);
       					status = 0;
       				}
       				flag = 0;
       				sendto(sock,flag,sizeof(flag),0,(struct sockaddr *)&sock_in, sinlen);	
       			}
       		}
       		flag = 1;
       		sendto(sock,flag,sizeof(flag),0,(struct sockaddr *)&sock_in, sinlen);
			break;
		case 2:
			break;
		default:
			break; 
	}
}