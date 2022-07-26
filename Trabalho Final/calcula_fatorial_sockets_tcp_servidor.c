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
#include <string.h>


struct timeval t1, t2;


#define MAX 50000

int multiplicar(int x, int res[], int res_size);

// Procedimento que calcula o fatorial
void calcula_fatorial(int n)
{
    if ( n == 1 || n == 2){
        // printf("Fatorial calulado de %d = 1\n", n);
    } else {
        int res[MAX];

        // Initialize result
        res[0] = 1;
        int res_size = 1;

        // Apply simple fatorial formula n! = 1 * 2 * 3 * 4...*n
        for (int x=2; x<=n; x++)
            res_size = multiplicar(x, res, res_size);

        // printf("Fatorial calulado de %d = ", n);
        // for (int i=res_size-1; i>=0; i--)
        //     printf("%d", res[i]) ;
        // printf("\n");
    }
}

// This function multiplies x with the number
// represented by res[].
// res_size is size of res[] or number of digits in the
// number represented by res[]. This function uses simple
// school mathematics for multiplication.
// This function may value of res_size and returns the
// new value of res_size
int multiplicar(int x, int res[], int res_size)
{
    int carry = 0;  // Initialize carry

    // One by one multiplicar n with individual digits of res[]
    for (int i=0; i<res_size; i++)
    {
        int prod = res[i] * x + carry;

        // Store last digit of 'prod' in res[]
        res[i] = prod % 10;

        // Put rest in carry
        carry  = prod/10;
    }

    // Put carry in res and increase result size
    while (carry)
    {
        res[res_size] = carry%10;
        carry = carry/10;
        res_size++;
    }
    return res_size;
}


// unsigned long int calcula_fatorial(int n) {
//     unsigned long int fat;
//     for (fat = 1; n > 1; n = n - 1)
//         fat = fat * n;
//     return fat;
// }

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
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    int porta = gera_porta_aleatoria();
    server_address.sin_port = htons(porta);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
    listen(server_sockfd, 5);
    printf("Porta %d\n", porta);
    while (1) {
        printf("Servidor Aguardando\n");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
        read(client_sockfd, &str_in, 1024);
        gettimeofday(&t1, NULL);

        int valor_para_pular, qtd_servidores, qtd_fat;
        valor_para_pular = atoi(strtok(str_in, "-"));
        qtd_servidores = atoi(strtok(NULL, "-"));
        qtd_fat = atoi(strtok(NULL, "-"));

        printf("Veio do servidor: %s\n", str_in);
        // Procedimento que calcula os factorials
        for (int i = valor_para_pular; i < qtd_fat + 1; i = i + qtd_servidores) {
            calcula_fatorial(i);
        }

        gettimeofday(&t2, NULL);

        double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
        printf("tempo total = %f\n", t_total);

        snprintf(str_out, 1024, "%f", t_total);
        write(client_sockfd, &str_out, 1024);
//        close(client_sockfd);
    }
}