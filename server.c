#include <syslog.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/socket.h>

#define LOG_ERR -1

//max backlog num for func listen
#define MAX_QUE_LEN 10
#define MAX_BUF_SIZE 1024
//status of init server
enum
{
	INIT_SRV_SUCCESS,
	INIT_SRV_FAILED
}

init_server(int);

int init_server(int port)
{
	int server_fd;
	struct sockaddr_in server_addr;
	int ruse = 1;

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	
	if ((server_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("error opening socket \n");
		return INIT_SRV_FAILED;
	}
	
	/* make server address can be reused after program existed */
	if (setsockopt(server_fd, SOL_SOCKET, SOREUSEADDR, &reuse, sizeof(int)) < 0)
	{
		goto errout;
	}
	
	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		goto errout;	
	}
	
	if ((type == SOCK_STREAM) || (type == SOCK_SEQPACKET))
	{
		if (listen(server_fd, MAX_QUE_LEN) < 0)
		{
			goto errout;
		}
		
	}

	return server_fd;
	errout：
		err = errno;
		close(server_fd);
		errno = err;
		return INIT_SRV_FAILED;
}

void serve(int port)
{
	struct sockaddr_in cli_addr;
	int cli_addr_len = 0;
	int srv_sock = 0;
	int connect_fd = 0;
	int status = 0;
	pid_t pid;
	char rcv_buffer[MAX_BUF_SIZE] = {0};
	
	memset(rcv_buffer, 0, MAX_BUF_SIZE);
	
	srv_sock = init_server(port);
	connect_fd = accept(srv_sock, (struct sockaddr*)&cli_addr, &cli_addr_len);
	
	set_cloexec(sockfd);
	
	for(;;)
	{
		if ((clfd = accept(sockfd, NULL, NULL)) < 0)
		{
			return -1;
		}
		
		if ((pid = fork()) < 0)
		{
			
		}
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
	server(1024);
	return 0;
}
