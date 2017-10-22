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
    const char* const socket_name = argv[1];
    int socket_fd;
    struct sockaddr_un name;
    int client_sent_quit_message;
    pid_t child_pid = 0;
    
    /* Create the socket. */
    socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
    
    /* Indicate that this is a server. */
    name.sun_family = AF_LOCAL;
    strcpy (name.sun_path, socket_name);
    bind (socket_fd, &name, SUN_LEN (&name));
    /* Listen for connections. */
    listen (socket_fd, 5);
    /* Repeatedly accept connections, spinning off one server() to deal
    with each client. Continue until a client sends a “quit” message.*/
    do {
        struct sockaddr client_name;
        socklen_t client_name_len;
        int client_socket_fd;
        
        /* Accept a connection. */
        client_socket_fd = accept(socket_fd, &client_name, &client_name_len);
        /* Handle the connection. */
        client_sent_quit_message = server(client_socket_fd);
        /* Close our end of the connection. */
        close(client_socket_fd);
    } while (!client_sent_quit_message);
    
    /* Remove the socket file.*/
    close(socket_fd);
    unlink(socket_name);
    
    return 0;
    /*
    child_pid = fork();
    if (!child_pid)
    
    {
        Client();
    }
    
    */
    
    /*return 0;*/
}

int server(int client_socket)
{
    while (1) {
        int length;
        char* text;
        /* First, read the length of the text message from the socket.
        read returns zero, the client closed the connection. */
        if (read (client_socket, &length, sizeof (length)) == 0)
            return 0;
        /* Allocate a buffer to hold the text. */
        text = (char*) malloc (length);
        /* Read the text itself, and print it. */
        read (client_socket, text, length);
        printf ("%s\n", text);
        /* Free the buffer. */
        
         /* If the client sent the message “quit,” we’re all done.*/
        if (!strcmp (text, "q"))
            return 1;
        free(text);
       
    }
}

void Client(void)
{
    int i = 0;
    while (10 > i++)
    {
        printf("ping\n");
        sleep(1);
    }
}