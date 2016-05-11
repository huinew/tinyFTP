#define SUCCESS 1
int command_process(int sock_control)
{
  int sock_data;
  char cmd[5];
  char arg[MAXSIZE];

// Authenticate user
if (srv_user_login(sock_control) == SUCCESS) 
{
  send_response(sock_control, 230);
} 
else 
{
  send_response(sock_control, 430);
  exit(0);
} 
