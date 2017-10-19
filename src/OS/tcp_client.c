#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

void write_text(int socket_fd, const char* text)
{
    int length = strlen(text) + 1;
    write(socket_fd, &length, sizeof(length));
  
    write(socket_fd, text, length);
    
    
}

int main(int argc, char **argv)
{
    const char* const socket_name = "/tmp/sock";
    char* message = "ping";
    int socket_fd;
    struct sockaddr_un name;
    int length;
    char *text;
    
    if (argc > 1)
    {
		message = malloc(strlen(argv[1]) + 1);
		strcpy(message, argv[1]);
	}
    
    while (1)
    {
		socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

		name.sun_family = AF_LOCAL;
		strcpy(name.sun_path, socket_name);

		connect(socket_fd, (struct sockaddr*)&name, SUN_LEN(&name));

		write_text(socket_fd, message);
		if (argc > 1)
		{
			free(message);
		}
		
		sleep(1);
		
        length = 0;
        
		if (read(socket_fd, &length, sizeof(length)) == 0)
			return 0;

		text = (char*) calloc (1, length);

		read(socket_fd, text, length);
		printf ("%s\n", text);

}

    close(socket_fd);
    
    return 0;
}
