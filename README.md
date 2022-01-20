# Network

## 라이브러리  
TCP/IP 프로토콜을 활용한 네트워크 프로그래밍 
```
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")
```
## Winsock API
1. 주소 변경
문자열 -> 숫자  
`int inet_addr(char*);`  
숫자 -> 문자열  
`char* inet_ntoa(IN_ADDR.int);`  

(오류 뜰 시 #define _WINSOCK_DEPRECATED_NO_WARNINGS)  

2. 바이트 정렬  
big endian(빅엔디안 방식) //네트워크 함수(NetworkByteOrder)  
little endian(리틀엔디안 방식) // 일반 함수(HostByteOrder)  

코드에서 -> 소켓 API 함수에 주소를 전달  
HostByteOrder -> NetworkByteOrder  
`htons(short byte)`
`htonl(long byte)`  
소켓 API에서 주소 획득 -> 코드에서 출력  
NetworkByteOrder -> HostByteOrder  
`ntohs(short byte)`
`ntohl(long byte)`  
## 서버소켓
0. 초기화  
1. 리슨 소켓 생성 socket()  
2. bind  
3. listen  
4. accept  
5. send()/receive()  
6. closesocket()  

## 클라이언트 소켓
0. 초기화  
1. 리슨 소켓 생성 socket()  
2. connect()  

동시성을 부여하고 싶을 때 쓰레드를 만든다.  
콘솔앱에서는 while로 처리하는 것을  
winapi 사용할 때는 쓰레드로 처리해야함  


