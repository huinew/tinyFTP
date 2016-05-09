#include <syslog.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#define LOG_ERR -1

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255
#endif

init_server(const struct sockaddr* , int);

int init_server(const struct sockaddr* ,int port)
{
	int server_fd;
	struct sockaddr_in srv_addr;
	int ruse = 1;

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if ((server_fd =  socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
			perror("error opening socket \n");
			return -1;
	}
	
	if (setsockopt(server_fd, SOL_SOCKET, SOREUSEADDR, &reuse, sizeof(int)) < 0)
	{}
	return server_fd;
}
void serve(int sockfd)
{
	int clfd, status;
	pid_t pid;
	
	set_cloexec(sockfd);
	
	for(;;)
	{
		if ((clfd = accept(sockfd, NULL, NULL)) < 0)
		{
			return -1;
		}
		
		if ((pid = fork()) < 0)
		{}
		else if ( pid == 0 )
		{
			
		}
		else
		{
			close(clfd) ;
			waitpid (pid, &status, 0);
		}
	}
}

int main(int argc, char* argv[])
{
	struct addrinfo *ailist = NULL;
	struct addrinfo *aip = NULL;
	struct addrinfo hint;
	int sockfd = 0;
	int err = 0; 
	int host_name_len = 0;

	for (aip = ailist; aip != NULL; aip = aip->ai_next)
	{
		if ((sockfd = init_server(SOCK_STREAM, aip->ai_addr,
		aip->ai_addrlen, QLEN)) >= 0)
		{
			serve(sockfd);
			return -1;
		}
	}
	return -1;
}
