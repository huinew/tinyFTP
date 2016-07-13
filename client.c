#define SEND_BUF_MAX 1024
char * host_name = "127.0.0.1";
int port = 8000;


struct command_info* input_command(char* usr_cmd)
{
	struct command_list* cmd_info = NULL;
	char* savestate;
	char* token;
	int i, j;
	cmd_list = (struct command_info*)malloc(sizeof(command_info));
	if (!cmd_list)
	{
		printf("Failed to allocate space for cmd list.\n");
		return -1;
	}
	
	cmd->id = -1;
	for(i = 0; ; i++, s = NULL)
	{
		token = strtok_r(usr_cmd, " \t\n", &savestate);
		if(token == NULL)
			break;
		if(cmd->id == -1)
		{
			for(j = 0; j < MAX_CMD_NUM; j++)
			{	
				if(!strcmp(token, cmd_list[j].key))
				{
					cmd_info->id = cmd_list[j].id;
					break;
				}
			}// ommitting braces for the "for loop" here is \
			 disastrous because the else below gets \
			 associated with the "if inside the for loop". \
		}
		else
			append_path(cmd, token);
	}
}


int main(int argc , char * argv[])
{
    char buf[8192];
    char *user_name = "li_tingting";
    char *password = "12345";
    //char message[256];
    int socket_descriptor;
    struct sockaddr_in server;
    char * str ="A default test string";
    char send_buf[SEND_BUF_MAX] = {0};
    if(argc < 2)
    {
            printf("we will send a default test string.\n");

    }
    else
    {
            str = argv[1];
            if(argc == 3)
            {
                    host_name = argv[2];
            }
    }

    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    inet_pton(AF_INET,host_name,&server.sin_addr);
    server.sin_port = htons(port);
    if ((socket_descriptor =  socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
            perror("error opening socket \n");
            exit(1);
    }
    if(connect(socket_descriptor,(struct sockaddr * )&server,sizeof(server)) == -1)
    {
            perror("error connecting to socket \n");
            exit(1);
    }
    
    //read welcome message from server
    read(socket_descriptor,buf,sizeof(buf));
    printf("welcome message from server:%s.\n",buf);

    printf("sending message %s to server ..\n",str);
    if( write(socket_descriptor,str,strlen(str)+1) == -1 )
    {
            perror("error in send \n");
            exit(1);
    }

    printf("..sent message ...wait for message..\n");
    if( read(socket_descriptor, buf, sizeof(buf)) == -1 )
    {
            perror("error in receiving response from server \n");
            exit(1);
    }

    sprintf(send_buf, "USER %s\r\n", username);
    write(socket_descriptor, send_buf, strlen(send_buf));
    //client receive response code and message from server
    //correct message:"331 User name okey, need password"
    read(socket_descriptor, buf, strlen(buf)); 
    printf("\nResponse from server:\n\n%s\n",buf);
    
    sprintf(send_buf, "PASS %s\r\n", password);
    write (control_sock, send_buf, strlen(send_buf));
    
    read(socket_descriptor, buf, strlen(buf)); 
    printf("\nResponse from server:\n\n%s\n",buf);
    
    //passive mode
    sprintf(send_buf, "PASV\r\n");
    
    write(control_sock, send_buf, strlen(send_buf));
    //It shold be 227 Entering passive mode<h1,h2,h3,h4,p1,p2>
    read(socket_descriptor, buf, strlen(buf));
    close(socket_descriptor);
    return 1;

}
