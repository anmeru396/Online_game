#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define PORT "9000"
#define SERVER_NAME "192.168.0.100"

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
	if(bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) return -5;


	//応答待ち
	puts("接続中です。");
	listen(sockfd, 3);
	puts("通過儀礼");
	client_socket = accept(sockfd, NULL, NULL);
	

	//つながったとき
	puts("合流しました。");	
	


	char *name = "名前を入力してください";
	send(client_socket, name, strlen(name), 0);
	char names[11];
	int n = recv(client_socket, names, 10, 0);
	names[n] = '\0';
	
	printf("%s\n",names);

	close(sockfd);



}
