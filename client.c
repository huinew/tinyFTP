#define SEND_BUF_MAX 1024
char * host_name = "127.0.0.1";
int port = 8000;

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
