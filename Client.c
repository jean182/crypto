#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

char *decode(char Message[100], int number);
char *ABC = "ABCDEFGHIJKLMN\xa5OPQRSTUVWXYZ";
char *abc = "abcdefghijklm\xa4opqrstuvwxyz";

void main()
{

	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	printf("[+]Client Socket Created Sucessfully.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	printf("[+]Connected to Server.\n");

	recv(clientSocket, buffer, 1024, 0);
	printf("[+]Decoded message: %s\n", buffer);
	printf("[+]Closing the connection.\n");
}

char *decode(char Message[100], int number)
{
	char *p;
	int i;
	for (i = 0; Message[i]; i++)
	{
		if ((p = strchr(ABC, Message[i])))
		{
			Message[i] = ABC[(p - ABC - number + 27) % 27];
		}
		if ((p = strchr(abc, Message[i])))
		{
			Message[i] = abc[(p - abc - number + 27) % 27];
		}
	}
	return Message;
}
