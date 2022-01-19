# Network

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
