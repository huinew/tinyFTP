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

#define MAX_CMD_NUM 7

//支持的FTP客户端命令
enum
{
	CMD_GET = 1，
	CMD_PUT，
	CMD_MGET，
	CMD_MPUT，
	CMD_LS，
	CMD_CD
}


//用户命令信息
typedef struct _command_info
{
	int cmd_id;		//id that represent command
	int path_num;
	char **path;
}command_info;

typedef struct _command_list
{
	char* key;
	int id;
}command_list;

static command_list cmd_list[MAX_CMD_NUM] = 
{
	{"get", CMD_GET},
	{"put", CMD_PUT},
	{"mget", CMD_MGET},
	{"mput", CMD_MPUT},
	{"ls", CMD_LS},
	{"cd", CMD_CD},
	{"", -1}
};
