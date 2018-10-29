#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLEN 80
//#define SERV_PORT 8000

int main(int argc, char ** argv)
{
	unsigned short port = 1234;
	char *server_ip = "127.0.0.1";
	
	//更改服务器IP、port
	if(argc > 1)
	{
		server_ip = argv[1];
	}
	if(argc > 2)
	{
		port = atoi(argv[2]);
	}

	//创建套接字
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(-1);
	}
	
	//设置服务器地址结构体
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_pton(AF_INET,server_ip,&servaddr.sin_addr); 
	
	//
	/*int err_log = connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr) );
	if(err_log != 0)
	{
		perror("connect");
		close(sock);
		exit(-1);
	}*/
	char send_buf[] = "hello world";
	puts(send_buf);
	printf("send data to %s:%d\n", server_ip,port);
	
	//循环发
	while(1)
	{
		//printf("send:");
		//fgets(send_buf,sizeof(send_buf),stdin);
		send_buf[strlen(send_buf)-1]='\0';
		sendto(sock, send_buf, strlen(send_buf),0,(struct sockaddr*)&servaddr, sizeof(servaddr) );
		sleep(10);
	}
	
	
	close(sock);
	
	return 0;
}


