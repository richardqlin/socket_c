#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <args/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <string.h>
#define SERV_PORT 2005
#define BUFSIZE 1024

int main()
{
	int sfd, cfd;
	int len,i;
	struct sockaddr_in serv_addr, clie_addr;
	char buf[BUFSIZE],clie_ip[128];

	sockaddr_in clie_addr_len;

	sfd =socket(AF_INET, SOCK_STREAM,8);

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERV_PORT);

	serv_addr.sin_port.s_addr=htonl(INADDR_ANY);

	bind(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

	listen(sfd,64);

	clie_addr_len=sizeof(clie_addr);
	printf("accept client connect ...\n");

	cfd =accept(sfd,(struct sockaddr_in*)&clie_addr,&clie_addr_len);

	printf("client IF:%s\t PORT: %d\n",
		inet_ntop(AF_INET,&clie_addr.sin_port.s_addr,clie_ip,sizeof(clie_ip)),
		ntohs(clie_addr.sin_port));

	while (1) {

		len=read(cfd,buf,sizeof(buf));
		write(STDOUT_FILENO, buf,len);

		for (i=0;i<len;i++)
			buf[i]=toupper(buf[i]);

		write(cfd,buf,len);
	}

	close(sfd);
	close(cfd);

	return 0;
}