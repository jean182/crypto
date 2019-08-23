#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

char *encode(char Message[100], int number);
char *decode(char Message[100], int number);
char *ABC = "ABCDEFGHIJKLMN\xa5OPQRSTUVWXYZ";
char *abc = "abcdefghijklm\xa4opqrstuvwxyz";

void main()
{

	int sockfd;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;
	char buffer[1024];

	int n;
	char word[100];
	printf("enter a message: ");
	fflush(stdin);
	fgets(word, 100, stdin);
	printf("enter a number: ");
	scanf("%d", &n);
	while (getchar() != '\n')
		;
	encode(word, n);

	printf("\nThe encoded message is:\n%s\n", decode(word, n));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("[+]Server Socket Created Sucessfully.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to Port number %d.\n", 4455);

	listen(sockfd, 5);
	printf("[+]Listening...\n");

	newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);

	strcpy(buffer, encode(word, n));
	send(newSocket, buffer, strlen(buffer), 0);
	printf("[+]Closing the connection.\n");
}

char *encode(char Message[100], int number)
{
	int i;
	char *p;
	for (i = 0; Message[i]; i++)
	{
		if ((p = strchr(ABC, Message[i])))
		{
			Message[i] = ABC[(p - ABC + number) % 27];
		}
		if ((p = strchr(abc, Message[i])))
		{
			Message[i] = abc[(p - abc + number) % 27];
		}
	}
	return Message;
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
