#include <syslog.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#define LOG_ERR -1

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255
#endif

extern init_server(int, const struct sockaddr* ,socklen_t, int);

void serve(int sockfd)
{
	int clfd, status;
	pid_t pid;
	
	set_cloexec(sockfd);
	
	for(;;)
	{
		if ((clfd = accept(sockfd, NULL, NULL)) < 0)
		{
			syslog(LOG_ERR, "ruptime: accept log err: %s.", strerror(errno));
			return -1;
		}
		
		if ((pid = fork()) < 0)
		{}
		else if ( pid == 0 )
		{
			if ((dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO)
			|| (dup2(clfd, STDERR_FILENO) != STDERR_FILENO))
			{
				syslog(LOG_ERR, "ruptimed: unexpected error");
			}
			close(clfd);
			execl ("/usr/bin/uptime", "uptime", (char *)0);
			syslog(LOG_ERR, "ruptime: accept log err: %s.", strerror(errno));
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
	char *host = NULL;
	
	if (argc != 1)
	{
		printf("usage: ruptime.\n");
	}
	if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
	{
		n = HOST_NAME_MAX;
	}
	if ((host = malloc(host_name_len) == NULL))
	{
		printf("malloc error.\n");
		return -1;
	}
	if (gethostname(host, host_name_len) < 0)
	{
		printf("get host name error.\n");
		return -1;
	}
	daemonize("ruptimed");
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ad_next = NULL;
	if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0)
	{
		syslog(LOG_ERR, "ruptime: accept log err: %s.", get_addr_info_err(err));
		return -1;
	}
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
