//
// Created by gbl on 25/07/22.
//

#include <stdio.h>
#include <locale.h>
#include <sys/time.h>
#include <mpi.h>

struct timeval t1, t2, t3, t4;


#define MAX 50000

//Fatoriais pra testar
//int qtd_fat = 1000;
// int qtd_fat = 2500;
int qtd_fat = 5000;

int multiplicar(int x, int res[], int res_size);

// Procedimento que calcula o fatorial
int calcula_fatorial(int n) {
    if (n == 1 || n == 2) {
        // printf("Fatorial calulado de %d = 1\qtd_fat", qtd_fat);
    } else {
        int res[MAX];

        // Initialize result
        res[0] = 1;
        int res_size = 1;

        // Apply simple fatorial formula qtd_fat! = 1 * 2 * 3 * 4...*qtd_fat
        for (int x = 2; x <= n; x++)
            res_size = multiplicar(x, res, res_size);

//         printf("Fatorial calulado de %d = ", n);
//         for (int i=res_size-1; i>=0; i--)
//             printf("%d", res[i]) ;
//         printf("\n");
    }
    return n;
}

// This function multiplies x with the number
// represented by res[].
// res_size is size of res[] or number of digits in the
// number represented by res[]. This function uses simple
// school mathematics for multiplication.
// This function may value of res_size and returns the
// new value of res_size
int multiplicar(int x, int res[], int res_size) {
    int carry = 0;  // Initialize carry

    // One by one multiplicar qtd_fat with individual digits of res[]
    for (int i = 0; i < res_size; i++) {
        int prod = res[i] * x + carry;

        // Store last digit of 'prod' in res[]
        res[i] = prod % 10;

        // Put rest in carry
        carry = prod / 10;
    }

    // Put carry in res and increase result size
    while (carry) {
        res[res_size] = carry % 10;
        carry = carry / 10;
        res_size++;
    }
    return res_size;
}


int main(int argc, char *argv[]) {
    // Numero de processos total no programa
    int world_size;
    // Identiicador do processo em execucao
    int rank;

    // Inicializa o ambiente de execução de MPI
    MPI_Init(&argc, &argv);

    MPI_Status status;


    // Obtém o rank do processo requisitante associado ao
    // comunicador. Cada processo será associado a um único
    // rank inteiro entre 0 e o (número de processos – 1)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // O número de processos em um grupo associado a um comunicador
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    gettimeofday(&t1, NULL);
    // Processo Mestre
    if (rank == 0) {
//        Aguarda os processos que calculam o fatorial
        for (int i = 1; i < world_size; i++) {
            double tmp;
            MPI_Recv(&tmp, 1, MPI_DOUBLE,
                     MPI_ANY_SOURCE, 0,
                     MPI_COMM_WORLD,
                     &status);
            int sender = status.MPI_SOURCE;
//            printf("Processo executou %d em %f ms\n", i, tmp);
        }
    }
    // Processos Escravos
    else {
        gettimeofday(&t3, NULL);
        // Executa o cálculo do fatorial e envia ao Processo Mestre
        for (int i = rank; i <= qtd_fat; i = i + world_size) {
            calcula_fatorial(i);
        }
        gettimeofday(&t4, NULL);
        double t_total = (t4.tv_sec - t3.tv_sec) + ((t4.tv_usec - t3.tv_usec) / 1000000.0);
        printf("Tempo em milisegundos do processo %d: %f ms\n", rank, t_total);
        MPI_Send(&t_total, 1 , MPI_DOUBLE , 0, 0, MPI_COMM_WORLD);
    }
    // Termina a execução do ambiente MPI
    MPI_Finalize();
    if(rank == 0){
        gettimeofday(&t2, NULL);
        double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
        int min = t_total / 60;
        int h, m, s;

        h = (t_total / 3600);

        m = (t_total - (3600 * h)) / 60;

        s = (t_total - (3600 * h) - (m * 60));

        printf("H:M:S - %d:%d:%d\n", h, m, s);

        printf("Tempo em milisegundos: %f ms\n", t_total);
        printf("Tempo em minutos: %d min\n\n", min);
    }


}
