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
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len=0;
	int idx=0,read_len=0;

	sock = socket(PF_INET, SOCK_STREAM, 0);

	if(sock == -1){
		printf("socket error\n");
	}

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("192.168.2.1"); //htonl : host to network order long
	serv_addr.sin_port=htons(7989); //htons: host to network order short

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		printf("CONNECT_ERROR\n");
	
	str_len = read(sock, message, sizeof(message) -1);
	if(str_len == -1)
		printf("READ_ERROR\n");
	message[str_len]=0;

	printf("Message from server: %s\n",message);
	
	close(sock);

	return 0;
}

