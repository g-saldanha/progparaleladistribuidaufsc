#include <stdio.h>
#include <locale.h>
#include <sys/time.h>

struct timeval t1, t2;

#define MAX 50000

int multiplicar(int x, int res[], int res_size);

// Procedimento que calcula o fatorial
void fatorial(int n)
{
    if ( n == 1 || n == 2){
        // printf("Fatorial calulado de %d = 1\qtd_fat", qtd_fat);
    } else {
        int res[MAX];

        // Initialize result
        res[0] = 1;
        int res_size = 1;

        // Apply simple fatorial formula qtd_fat! = 1 * 2 * 3 * 4...*qtd_fat
        for (int x=2; x<=n; x++)
            res_size = multiplicar(x, res, res_size);

        // printf("Fatorial calulado de %d = ", qtd_fat);
        // for (int i=res_size-1; i>=0; i--)
        //     printf("%d", res[i]) ;
        // printf("\qtd_fat");
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

    // One by one multiplicar qtd_fat with individual digits of res[]
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

int main() {
    gettimeofday(&t1, NULL);
    int fat = 1000;
//    int fat = 100000;
//    int fat = 1000000;
//    int fat = 1000000000;
    printf("Digite o range de fatorial");
    scanf("%d", &fat);

    for (int i = 1; i < fat+1; i++) {
        fatorial(i);
    }

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