/*
 * Client.c
 *
 *  Created on: Jan 22, 2016
 *      Author: felixamoruwa
 */

/**
 * Parameters: 1) Portname 2) Server
 * i.e. ./client1 -port 18732 -server 127.0.0.1
 * Result: Server should return: 1) "foo.txt" with contents "You lose!"
 */

/* file: client.c class: 18-732, Spring 2016, assignment: Homework 2
*/

/* Obligatory includes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>
#include <stdarg.h>
#include <errno.h>


int main(int argc, char** argv)


	/* Create Foo.txt file */
	printf("\nWriting Foo.txt...");

	char c[1000] = "You lose!";
	FILE *fptr;
	fptr=fopen("foo.txt","w");
	if(fptr==NULL){
		printf("Error!");
		exit(1);
	}
	fprintf(fptr,c);
	fclose(fptr);

	printf("\nFoo.txt with payload has been created.");

	/* Set up some defaults for if you don't enter any parameters */
	PORTNUM = 18732;
	strcpy(SERVER_IP, "127.0.0.1");

	printf("\nUsage: client [-port <port_number>] [-server <server_IP>]\n");

	/* Process command line switches */
	/* Usage: client [-port <port_number>] [-server <server_IP>] */
	for(i = 1; i < argc; i++){
		if(argv[i][0] == '-'){
			if(strcmp(argv[i], "-port") == 0){
				PORTNUM = atoi(argv[++i]);
			}else if(strcmp(argv[i], "-server") == 0){
				strncpy(SERVER_IP, argv[++i],16);
	
            }else{
				printf("Unknown switch \"%s\"\n", argv[i]);
				exit(1);
			}
		}else{
			printf("Unknown switch \"%s\"\n", argv[i]);
			exit(1);
		}
	}

	/* Fill in the server data structure */
	memset(&srv, 0, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORTNUM);
	srv.sin_addr.s_addr = inet_addr(SERVER_IP);

	/* Create the socket */
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		exit(1);
	}

	printf("\nConnecting to %s:%u\n", SERVER_IP, PORTNUM);

	/* Connect to the socket */
	if(connect(sock, (struct sockaddr*) &srv, sizeof(srv)) < 0){
		perror("connect");
		exit(1);
	}

	printf("The request is:\n%s\n", reqstring);

	/* Make the request */
	strncpy(request, reqstring,1000 );
	total = 0;
	s = strlen(request);
	while( total < s){
		nbytes = write(sock, request + total, s);
		total = total + nbytes;
	}





	printf("The response of the server is:\n");
/*
	printf("Add Foo.txt and contents to the request payload");

	FILE *fp;
	char ch;
	fp=fopen("foo.txt","w");
	printf("\nEnter data to be stored in to the file:");
	while((ch=getchar())!=EOF)
		putc(ch,fp);
	fclose(fp);
*/

	/* Get and output the response */
	nbytes = 0;
	while( (nbytes = read(sock, recvline, 1000)) > 0){
		recvline[nbytes] = 0;
		printf("%s\n", recvline);
	}



	return(0);
}

