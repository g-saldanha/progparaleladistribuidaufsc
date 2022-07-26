//
// Created by gbl on 24/07/22.
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <locale.h>
#include <sys/time.h>
#include <string.h>

struct timeval t1, t2;

int main() {
    int servers[10] = {9578, 9126, 9528, 9259, 9081, 9283, 9737, 9738, 9053, 9391};

    int qtd_fat = 1000;
    // int qtd_fat = 2500;
    // int qtd_fat = 5000;
//    int qtd_fat = 100000;
//    int qtd_fat = 1000000;
//    int qtd_fat = 1000000000;

    int qtd_servidores = 2;
    int sockfd[qtd_servidores];

//    printf("Digit a quantidade de servidores que quer usar para fatorar de 1 até 1000, 1000000 ou 1000000000  (máx 32):");
//    scanf("%d", &qtd_servidores);
    gettimeofday(&t1, NULL);

    for (int i = 0; i < qtd_servidores; i++) {
        int porta = servers[i];
        int len;
        struct sockaddr_in address;
        int result;
        char str[1024];
        sprintf(str, "%d-%d-%d", i+1, qtd_servidores, qtd_fat);

        sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
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
        char str[1024];
        read(sockfd[i], &str, 1024);
        char *ptr;
        double ret;
        ret = strtod(str, &ptr);
        printf("Servidor %d executou em: %f s\n", sockfd[i], ret);
    }

    gettimeofday(&t2, NULL);
    double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    int min = t_total / 60;
    int h, m, s;

    h = (t_total / 3600);

    m = (t_total - (3600 * h)) / 60;

    s = (t_total - (3600 * h) - (m * 60));

    printf("H:M:S - %d:%d:%d\n", h, m, s);

    printf("Tempo em segundos: %f ms\n", t_total);
    printf("Tempo em minutos: %d min\n\n", min);
}