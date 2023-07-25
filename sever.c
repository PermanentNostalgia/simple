#include <stdio.h>
#include <winsock2.h>

int main(void) {
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(2,2), &wsadata)!=0) {
		printf("소켓 라이브러리 초기화 실패");
	}
	
	struct sockaddr_in addr;
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sock==INVALID_SOCKET) {
		printf("소켓 생성에 실패하였습니다.");
		return 0;
	}
	
	// 주소 구조체 초기화
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(1234);
	
	if(bind(sock, (struct sockaddr*) &addr, sizeof(addr))==SOCKET_ERROR) {
		printf("주소 할당 실패.");
		return 0;
	}
	
	if(listen(sock, 1)==SOCKET_ERROR) {
		printf("대기열 생성 실패.");
		return 0;
	}
	
	SOCKET sub_sock;
	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);
	
	sub_sock = accept(sock, (struct sockaddr*) &client_addr, &client_addr_len);
	if(sub_sock==INVALID_SOCKET) {
		printf("듣기 소켓 생성에 실패하였습니다.");
		return 0;
	}
	
	char buf[500];
	while(1) {
		recv(sub_sock, buf, 500, 0);
	
		printf("상대방> %s\n",buf);
		printf("나> ");
		scanf("%s",buf);
		
		if(strcmp(buf,"EXIT")==0) {
			break;
		}
		
		send(sub_sock, buf, 500, 0);
	}
	
	closesocket(sock);
	WSACleanup();
	
	return 0;
}
