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
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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
	printf("Bind the port:%d\n",port);
	int err_log = bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr) );
	if(err_log != 0)
	{
		perror("binding");
		close(sockfd);
		exit(-1);
	}
	printf("receive data...\n");
	while(1)
	{
		struct sockaddr_in client_addr;
		char client_ip[INET_ADDRSTRLEN] = "";
		socklen_t clientaddr_len = sizeof(client_addr);
		
		int recv_len;
		char recv_buf[16] = "";
		
		{
			recv_len = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&client_addr, &clientaddr_len);
			inet_ntop(AF_INET,&client_addr.sin_addr,client_ip,INET_ADDRSTRLEN);
			printf("client ip=%s,port=%d\n",client_ip,ntohs(client_addr.sin_port));
			printf("recv data(%d):%s\n",recv_len,recv_buf);
			memset(recv_buf, 0, sizeof(recv_buf));
		}
	}
	close(sockfd);
	
	return 0;
}





