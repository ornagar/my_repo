#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>


int server(int client_socket);
void Client(void);

int main(int argc, char *argv[])
{
    const char* const socket_name = "/tmp/sock";
    int socket_fd;
    struct sockaddr_un name;
    int client_sent_quit_message;
    
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    printf("%d %d\n", PF_LOCAL, AF_LOCAL);
    name.sun_family = AF_LOCAL;
    strcpy(name.sun_path, socket_name);
    bind(socket_fd, (struct sockaddr*)&name, SUN_LEN(&name));
   
    listen(socket_fd, 5);
   
    do {
        struct sockaddr client_name;
        socklen_t client_name_len;
        int client_socket_fd;
        
        client_socket_fd = accept(socket_fd, &client_name, &client_name_len);
        
        client_sent_quit_message = server(client_socket_fd);
       
        close(client_socket_fd);
    } while (!client_sent_quit_message);
    
    
    close(socket_fd);
    unlink(socket_name);
    
    return 0;
}

int server(int client_socket)
{
	int length;
	char* text;

	if (read(client_socket, &length, sizeof(length)) == 0)
		return 0;

	text = (char*) malloc (length);

	read(client_socket, text, length);
	printf ("%s\n", text);
	
	write(client_socket, &length, 4);
  
    write(client_socket, "pong", length);
	if (!strcmp(text, "q"))
	{
		free(text);
		return 1;
	}

	free(text);
}
