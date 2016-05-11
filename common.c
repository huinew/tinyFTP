#include <stdio.h>
#include <syslog.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/socket.h>

int accept_socket(int server_sock, struct sockaddr_in client_addr, int client_addr_len)
{
  if ((connect_fd = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len)) < 0)
  {
    return INIT_SRV_FAILED;
  }
  printf("Communication started with %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
  
  print_welcome_message(connection_fd);
  
  return connect_fd;
}

int create_socket(int port)
{
	int server_fd;
	struct sockaddr_in sock_addr;
	int ruse = 1;

	bzero(&sock_addr,sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port);
	
	if ((server_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("error opening socket \n");
		return INIT_SRV_FAILED;
	}
	
	/* make server address can be reused after program existed */
	if (setsockopt(server_fd, SOL_SOCKET, SOREUSEADDR, &reuse, sizeof(int)) < 0)
		goto errout;
	
	if (bind(server_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0)
		goto errout;	

	if ((type == SOCK_STREAM) || (type == SOCK_SEQPACKET))
	{
		if (listen(server_fd, MAX_QUE_LEN) < 0)
			goto errout;
	}

	return server_fd;
	errout：
		close(server_fd);
		return INIT_SRV_FAILED;
}
