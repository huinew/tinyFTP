#include <string.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUF_SIZE 1024
#define MIN_BUF_SIZE 5

#define MAX_CMD_LEN 5

#define LOGIN_SUCCESS 0
#define LOGIN_ERR -1
#define ARG_ERR -2

int get_user_name(char* buf, char* username)
{
  if ((!buf) || (!username))
      return ARG_ERR;

  if (strlen(buf) < MIN_BUF_SIZE)
      return ARG_ERR;

  buf = buf + MIN_BUF_SIZE;
  
  while(buf && *buf != '\0')
  {
      *username = *buf;
      buf++;
      username++;
  }
  return 0;
}

int get_user_pwd(char* buf, char* password)
{
  if ((!buf) || (!password))
    return ARG_ERR;

  buf = buf + MIN_BUF_SIZE;
  
  while(buf && *buf != '\0')
  {
    *password = *buf;
    buf++;
    password++;
  }
  return 0;
}

char* trim_space(char* pwd, int pwd_len)
{
		// remove end of line and whitespace, so do the start
		while (pwd_len && isspace((int)pwd[pwd_len - 1]))
		{
			pwd[pwd_len - 1] = '\0';
			pwd_len--;	
		}		
		while(pwd_len && isspace((int)*pwd))
		{
			pwd++;
			pwd_len--;
		}		
	return pwd;
}

int srv_user_login()
{
  char buf[MAX_BUF_SIZE] = {0};
  char user[MAX_BUF_SIZE] = {0};
  char password[MAX_BUF_SIZE] = {0};

  if (get_user_name(buf, user) < 0)
    return ARG_ERR;

  if (get_user_pwd(buf, password) < 0)
    return ARG_ERR;
    
  return srv_user_check(user, password);
}

int srv_check_user(char*user, char*pass)
{
	char username[MAXSIZE];
	char password[MAXSIZE];
	char buf[MAXSIZE];
	char *usr_str = NULL;								
	FILE* fd = NULL;
	int pwd_len = 0;
	
	fd = fopen("auth", "r");
	if (fd == NULL)
	{
		perror("file not found");
		exit(1);
	}	

	while (fgets(buf, MAXSIZE, fd)) 
	{	
		usr_str = strtok (buf," ");
		strcpy(username, usr_str);

		if (usr_str != NULL) 
		{
			usr_str = strtok (NULL, " ");
			strcpy(password, usr_str);
		}

		pwd_len = strlen(password);
		
		if ((password = trim_space(password)) == NULL)
		{
			fclose(fd);
			return LOGIN_ERR;
		}
		
		if ((strcmp(user,username) == 0) && (strcmp(pass,password) == 0)) 
		{
			return LOGIN_SUCCESS;
			break;
		}		
	}
	fclose(fd);	
	return LOGIN_ERR;
}


//chilid process handles connections to client
int command_process(int sock_control)
{
  int sock_data;
  char cmd[MAX_CMD_LEN] = {0};
  char args[MAX_BUF_LEN] = {0};
  int rc = 0;
  
// Authenticate user
  if (srv_user_login(sock_control) == LOGIN_SUCCESS) 
  {
    send_response(sock_control, 230);
  } 
  else 
  {
    send_response(sock_control, 430);
    exit(0);
  } 
  //wait for command
  while(1)
  {
  	//recv_cmd
  	rc = recv_command(sock_control,cmd, args);
  	//data connection
  	//execute command
  	//close connection
  }
}
