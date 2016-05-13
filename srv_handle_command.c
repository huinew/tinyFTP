#include <string.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUF_SIZE 1024
#define MIN_BUF_SIZE 5

#define MAX_CMD_LEN 5

#define LOGIN_SUCCESS 0
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

int srv_user_login()
{
  char buf[MAX_BUF_SIZE] = {0};
  char user[MAX_BUF_SIZE] = {0};
  char password[MAX_BUF_SIZE] = {0};

  if (get_user_name(buf, user) < 0)
    return ARG_ERR;

  if (get_user_pwd(buf, password) < 0)
    return ARG_ERR;
    
  return LOGIN_SUCCESS;
}

int command_process(int sock_control)
{
  int sock_data;
  char cmd[MAX_CMD_LEN] = {0};

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
}
