char * host_name = "127.0.0.1";
int port = 8000;

int main(int argc , char * argv[])
{
    char buf[8192];
    //char message[256];
    int socket_descriptor;
    struct sockaddr_in server;
    char * str ="A default test string";
    char send_buf[1024] = {0};
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

    sprintf(send_buf, "USER %s\r\n","li_tingting");
    write(socket_descriptor, send_buf, strlen(send_buf));
    //client receive response code and message from server
    //correct message:"331 User name okey, need password"
    read(socket_descriptor, buf, strlen(buf));    

    printf("\nResponse from server:\n\n%s\n",buf);
    close(socket_descriptor);
    return 1;

}
