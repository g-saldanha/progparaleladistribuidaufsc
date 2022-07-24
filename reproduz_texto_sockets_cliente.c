#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval t1, t2;

int main() {
    int qtd_servidores;
    printf("Digite a quantidade de servidores que quer usar(máx 32):");
    scanf("%d", &qtd_servidores);
    int tam = 1000000 / qtd_servidores;
    int servers[32] = {9956, 9408, 9157, 9702, 9225, 9327, 9106, 9682, 9478, 9417, 9753, 9151, 9253, 9331, 9746, 9659,
                       9334, 9286, 9311, 9945, 9840, 9966, 9190, 9137, 9143, 9576, 9968, 9342, 9740, 43139, 9222, 9962};
    int sockfd[qtd_servidores];
    gettimeofday(&t1, NULL);
    for (int i = 0; i < qtd_servidores; ++i) {
        int porta = servers[i];

        int len;
        struct sockaddr_in address;
        int result;
        char str[1024];
        sprintf(str, "%d", tam);

        sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        //address.sin_addr.s_addr = inet_addr("192.168.0.15");
        uint16_t i1 = htons(porta);
        address.sin_port = i1;

        len = sizeof(address);
        result = connect(sockfd[i], (struct sockaddr *) &address, len);
        if (result == -1) {
            perror("oops: client1");
            exit(1);
        }
        write(sockfd[i], &str, 1024);
    }
    for (int i = 0; i < qtd_servidores; ++i) {
        //sleep(30);
        char str[1024];
        read(sockfd[i], &str, 1024);
        char *ptr;
        double ret;
        ret = strtod(str, &ptr);
        printf("Servidor %d executou em: %f s\n", sockfd[i], ret);
//        printf("mensagem do servidor: %s\n", str);
//        close(sockfd);
    }
    gettimeofday(&t2, NULL);

    double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);

    printf("tempo total = %f\n", t_total);
    exit(0);

}

