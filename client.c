#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main(void) {
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(2,2), &wsadata)!=0) {
		printf("소켓 라이브러리 초기화 실패");
		return 0;
	}
	
	struct sockaddr_in addr;
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sock==INVALID_SOCKET) {
		printf("소켓 생성에 실패하였습니다.");
		return 0;
	}
	
	char ip_addr[16];
	printf("접속할 아이피를 입력하세요: ");
	scanf("%s",ip_addr);
	
	// 주소 구조체 초기화
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip_addr, &(addr.sin_addr));
	addr.sin_port = htons(1234);
	
	if(connect(sock, (struct sockaddr*) &addr, sizeof(addr))==SOCKET_ERROR) {
		printf("연결에 실패하였습니다.");
		return 0;
	}
	
	char buf[500];
	while(1) {
		printf("나> ");
		scanf("%s",buf);
		
		if(strcmp(buf,"EXIT")==0) {
			break;
		}
	
		send(sock, buf, 500, 0);
		recv(sock, buf, 500, 0);
		printf("상대방> %s\n",buf);
	}
	
	closesocket(sock);
	WSACleanup();
	
	return 0;
}
