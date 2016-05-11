#include <syslog.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "common.h"

#define LOG_ERR -1

//max backlog num for func listen
#define MAX_QUE_LEN 10
#define MAX_BUF_SIZE 1024
//status of init server
enum
{
	INIT_SRV_SUCCESS,
	INIT_SRV_FAILED,
	FORK_PID_ERR
}

void serve(int port)
{
	struct sockaddr_in client_addr;
	int client_addr_len = 0;
	int server_sock = 0;
	int connect_fd = 0;
	int status = 0;
	pid_t pid;
	char rcv_buffer[MAX_BUF_SIZE] = {0};
	
	memset(rcv_buffer, 0, MAX_BUF_SIZE);
	
	server_sock = create_server(port);
	
	while(1)
	{
		if ((connect_fd = accept_socket(server_sock) < 0)
		{
			return INIT_SRV_FAILED;
		}
	
		if ((pid = fork()) < 0)
		{
			printf("Cannot create child process.");
			return FORK_PID_ERR;
		}
		else if ( pid == 0 )
		{
			command_process(connect_fd, rcv_buffer);
			memset(rcv_buffer, 0, sizeof(rcv_buffer));
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
