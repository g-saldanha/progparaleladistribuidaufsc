// Compilar: gcc -o reproduz_texto reproduz_texto.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <sys/time.h>
#include <pthread.h>
#include <malloc.h>

char *texto;
char *chute;

struct timeval t1, t2;

typedef struct objeto_t{
    int comeco;
    int final;
} objeto;


int cria_palavra_secreta(char *palavra, int tam){
  srand((unsigned)time(NULL));
  for (int i = 0; i < tam-1; i++)
    // sorteia algum caracter visivel, valores ASCII entre 32 e 126
    palavra[i] = 32 + rand() % 94;    
  palavra[tam-1] = '\0';  
}

void *calculaThreadCaculaTexto(void *arg);

int main(int argc, char **argv){
    unsigned long i,tam;
    short j;

    int  quantidade_de_threads;

    if(argc != 2){
        printf("Favor informar o tamanho da palavra. Por exemplo:\n");
        printf("./reproduz texto 100\n");
        return 0;
    }

    printf("Digite as threads: ");
    scanf("%d", &quantidade_de_threads);

    pthread_t threads_a_processar[quantidade_de_threads];

    sscanf(argv[1],"%lu",&tam);
    texto = malloc(sizeof(char)*tam);
    chute = malloc(sizeof(char)*tam);
    gettimeofday(&t1, NULL);
    cria_palavra_secreta(texto,tam);

    int contador = 0;
    int divisao_de_numeros_nas_threads = tam / quantidade_de_threads;

    // Procedimento que descobre o texto
    chute[tam-1] = '\0';
    for (int j = 0; j < quantidade_de_threads; j++) {
        objeto *pObjeto;
        pObjeto = malloc(sizeof(objeto));
        pObjeto->comeco = contador;
        pObjeto->final = contador + divisao_de_numeros_nas_threads;
        contador = contador + divisao_de_numeros_nas_threads;
        pthread_create(&threads_a_processar[j], NULL, calculaThreadCaculaTexto, (void *) pObjeto);
    }

    for (int i = 0; i < quantidade_de_threads; ++i) {
        pthread_join(threads_a_processar[i], NULL);
    }


    printf("Palavra secreta:    %s\n\n",texto);
    printf("Palavra descoberta: %s\n",chute);

    gettimeofday(&t2, NULL);

    double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec)/1000000.0);
    printf("tempo total = %f\n", t_total);

    return 0;
}

void *calculaThreadCaculaTexto(void *arg){
    objeto *numeros;
    numeros = (objeto *) arg;
    unsigned long i;
    short j;
    for (i = numeros->comeco; i <= numeros->final; i++)
        for (j = 0; j < 255; j++){
            chute[i]=j;
            if(chute[i] == texto[i]){
                j=0;
                break;
            }
        }
}
