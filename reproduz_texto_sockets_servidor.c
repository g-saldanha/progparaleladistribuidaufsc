#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <sys/time.h>

char *texto;
char *chute;

struct timeval t1, t2;


int cria_palavra_secreta(char *palavra, int tam) {
    srand((unsigned) time(NULL));
    for (int i = 0; i < tam - 1; i++)
        // sorteia algum caracter visivel, valores ASCII entre 32 e 126
        palavra[i] = 32 + rand() % 94;
    palavra[tam - 1] = '\0';
}

int gera_porta_aleatoria() {
    int lower = 9000, upper = 9999;
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int main() {
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    char str_in[1024];
    char str_out[1024];

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
//  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    int porta = gera_porta_aleatoria();
    server_address.sin_port = htons(porta);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
    listen(server_sockfd, 5);
    printf("Porta %d\n", porta);
    while (1) {
        printf("server waiting\n");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
        read(client_sockfd, &str_in, 1024);
        int tam = atoi(str_in);
        texto = malloc(sizeof(char) * tam);
        chute = malloc(sizeof(char) * tam);
        int i, j;
        gettimeofday(&t1, NULL);
        cria_palavra_secreta(texto, tam);

        // Procedimento que descobre o texto
        chute[tam - 1] = '\0';
        for (i = 0; i < tam; i++)
            for (j = 0; j < 255; j++) {
                chute[i] = j;
                if (chute[i] == texto[i]) {
                    j = 0;
                    break;
                }
            }

        printf("Palavra secreta:    %s\n\n", texto);
        printf("Palavra descoberta: %s\n", chute);

        gettimeofday(&t2, NULL);

        double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
        printf("tempo total = %f\n", t_total);
        printf("tamanho da palavra - %s\n", str_in);

        snprintf(str_out, 1024, "%f", t_total);
        write(client_sockfd, &str_out, 1024);
        close(client_sockfd);
    }
}