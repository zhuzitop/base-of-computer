#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char ** argv)
{
	unsigned short port = 1234;
	if(argc > 1)
	{
		port = atoi(argv[1]);
	}
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket");
		exit(-1);
	}
	
	//设置本地地址结构体
	struct sockaddr_in my_addr;
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//
	int err_log = bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr) );
	if(err_log != 0)
	{
		perror("binding");
		close(sockfd);
		exit(-1);
	}
	
	err_log = listen(sockfd, 10);
	if(err_log != 0)
	{
		perror("listen");
		close(sockfd);
		exit(-1);
	}
	printf("listen client @port=%d...\n",port);
	
	while(1)
	{
		struct sockaddr_in client_addr;
		char client_ip[INET_ADDRSTRLEN] = "";
		socklen_t clientaddr_len = sizeof(client_addr);
		
		int connfd;
		connfd = accept(sockfd, (struct sockaddr*)&client_addr, &clientaddr_len );
		if(connfd < 0)
		{
			perror("accept");
			continue;
		}
		
		inet_ntop(AF_INET,&client_addr.sin_addr,client_ip,INET_ADDRSTRLEN);
		printf("--------------------------------------------------------\n");
		printf("client ip=%s,port=%d\n",client_ip,ntohs(client_addr.sin_port));
		
		char recv_buf[512] = "";
		while( recv(connfd, recv_buf, sizeof(recv_buf), 0) > 0 )
		{
			printf("\nrecv data:\n");
			printf("%s\n",recv_buf);
			memset(recv_buf, 0, sizeof(recv_buf));
		}
		close(connfd);
		printf("client closed!\n");
	}
	close(sockfd);
	
	return 0;
}





