#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

static void* receiver(void* arg);

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char packet[4096] = "";
    sockfd=socket ( AF_INET,SOCK_STREAM,0 );
    
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons ( 1237 );
    
    int result = connect ( sockfd, ( struct sockaddr* ) &serv_addr,sizeof ( serv_addr ) );
    
    printf("connect ready! %d %s\n", result, strerror(errno));
    // receiver thread create
    pthread_t tid = 0;
    pthread_create(&tid, NULL, receiver, (void*)&sockfd);
    while(1)
    {
        printf("send ready!\n");
        char buffer[100] = "";
        scanf("%s", &buffer);
        // 숫자 입력
        int value = atoi(buffer);
        memset(buffer, 0, 100);
        buffer[0] = (unsigned char)0xaa;
        unsigned short size = 4;
        memcpy(&buffer[1], &size, 2);
        buffer[3] = 0;
        memcpy(&buffer[4], &value, 4);
        write(sockfd, buffer, 4 + 4);
        printf("Sent!\n");
    }
    return 0;
}


static void* receiver(void* arg)
{
    printf("receiver ready!\n");
    int sockfd = *(int*)arg;
    while(1)
    {
        char packet[4096] = "";
        int num = read(sockfd, packet, sizeof(packet));
        int value = 0;
        memcpy(&value, &packet[4], 4);
        //printf("value: %d\n", value);
        // 패킷 얻어내기
        
    }
}