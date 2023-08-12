#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

//int socket(int domain, int type, int protocol);
// domain: PF_INET, type: SOCK_STREAM, Protocol: 0
//

int main()
{
	int sock, client_sock;
	struct sockaddr_in serv_addr, client_addr;
	int client_addr_size;
	char message[30]= "Hello, I'm Pluto";
	int str_len=0;
	int idx=0,read_len=0;

	sock = socket(PF_INET, SOCK_STREAM, 0);

	if(sock == -1){
		printf("socket error\n");
	}

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //htonl : host to network order long
	serv_addr.sin_port=htons(7989); //htons: host to network order short

	if(bind(sock,(struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
		printf("ERROR\n");

	if(listen(sock,5)==-1)
	       printf("CAN'T SET WAITTING MODE\n");

	
	memset(&client_addr,0,sizeof(client_addr));
	client_sock = accept(sock, (struct sockaddr*) &client_addr, &client_addr_size);

	if(client_sock == -1)
		printf("ACCEPT_ERROR\n");
	write(client_sock, message, sizeof(message));
	close(client_sock);
	close(sock);

	return 0;
}

