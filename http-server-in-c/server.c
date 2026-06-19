#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netdb.h>
#include<string.h>

int main()
{
	printf("to see the site go to: http://localhost:8080/\n");


	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socker error");
		exit(-1);
	 
	}

	struct addrinfo hint, *res;
        memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, "8080", &hint, &res);

	int bind_result = bind(sockfd, res->ai_addr, res->ai_addrlen);
	if (bind_result < 0)
	{
		perror("Bind error");
		exit(-1);
	}

	// listen for incoming connections.
	int listen_result = listen(sockfd,20);
	if (listen_result < 0)
	{
		perror("listen error");
		exit(-1);
	}


	// accept
 	struct sockaddr_storage their_addr;
 	socklen_t addr_size;
	int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
	
	int max_len = 1000;
	char received_request[max_len];
	memset(received_request, 0, max_len);
	int num_bytes = recv(new_fd, received_request, max_len, 0);
	//printf("num_bytes =  %d\n", num_bytes);
        
	
	if (strncmp(received_request, "GET", 3) == 0)
	{
     		printf("Received HTTP GET request\n");
		//3 used before only checking the first 3 bytes here..
                
		// now respond to the http request
		char *status_line = "HTTP/1.1 200 OK\r\n";
		int sent_bytes = send(new_fd, status_line, strlen(status_line),0);
		
		char *headers = "Content-Type: text/html\r\n\r\n";
		sent_bytes = send(new_fd, headers, strlen(headers),0);

		//char *body = "<h1>Hello Kailas</h1>\r\n";
		//sent_bytes = send(new_fd, body, strlen(body),0);
		//printf("sent_bytes = %d\n", sent_bytes);	

		//open the index.html and serve it to users
		FILE *index_file = fopen("index.html","r");
		char c;
		while ( (c = getc(index_file)) != EOF ) 
		{
			sent_bytes = send(new_fd, &c, 1, 0);
		}
	
	} else {
		printf("Received non GET request. Ignoring ...\n");
	        close(new_fd); 
		close(sockfd);
		exit(-1);
		
	}
	close(sockfd);
	close(new_fd);
	return(0);


}

