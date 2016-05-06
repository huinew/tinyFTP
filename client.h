#include<string.h>

#ifndef MAX_CMD_ARGS
#define MAX_CMD_ARGS 1024
#endif

/*Command struct*/
typedef struct _command
{
  char command[5];
  char args[MAX_CMD_ARGS];
}command;

/*Port struct*/
typedef struct _port
{
   int port1;
   int port2;
}port;

static const char *cmdlist_str[] = 
{
  "ABOR", "CWD", "DELE", "LIST", "MDTM", "MKD", "NLST", "PASS", "PASV",
  "PORT", "PWD", "QUIT", "RETR", "RMD", "RNFR", "RNTO", "SITE", "SIZE",
  "STOR", "TYPE", "USER", "NOOP" 
};
