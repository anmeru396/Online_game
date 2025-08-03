#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define PORT "9000"
#define SERVER_NAME "duce.mydns.jp"

void chat(){

}


int main(){
	int sockfd, client_socket;
	struct addrinfo hints, *res, their_addr;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;//初期設定
	hints.ai_socktype =SOCK_STREAM;//初期設定

	//hintとresにサーバーの情報を色々格納
	if(getaddrinfo(SERVER_NAME, PORT, &hints,&res)!=0)return -1;

	//ソケットを開通
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	
	//ソケットとアドレスの紐づけ
	//bind(sockfd, res->ai_addr, res->ai_addrlen);


	//応答待ち
	puts("接続中です。");
	if(connect(sockfd, res->ai_addr, res->ai_addrlen) < 0){ 
		perror("CONNECT failed");
		return -5;
	}

	char message[100];
	int n = recv(sockfd, message, sizeof(message) -1 , 0 );
	message[n] = '\0';
	printf("%s\n",message);
	
	char name[11];
	scanf("%10s",name);
	send(sockfd, name, strlen(name), 0);	
	

	close(sockfd);



}
