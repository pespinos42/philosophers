#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_t hilo_incremento;
pthread_t hilo_decremento;

int variable_compartida = 100;

void    *incremento(void *arg)
{
    int p = 0;
    
    while (p < 10000)
    {
        pthread_mutex_lock(&mutex);
        variable_compartida++;
        pthread_mutex_unlock(&mutex);
        p++;
    }
    return (NULL);
}

void    *decremento(void *arg)
{
    int p = 0;
    
    while (p < 5000)
    {
        pthread_mutex_lock(&mutex);
        variable_compartida--;
        pthread_mutex_unlock(&mutex);
        p++;
    }
    return (NULL);
}

int main()
{
    pthread_create(&hilo_incremento, NULL, incremento, NULL);
    pthread_create(&hilo_decremento, NULL, decremento, NULL);
    pthread_mutex_init(&mutex, NULL);
    pthread_join(hilo_incremento, NULL);
    pthread_join(hilo_decremento, NULL);
    pthread_mutex_destroy(&mutex);
    printf("VALOR FINAL VARIABLE COMPARTIDA -> %i\n", variable_compartida);
    return(0);
}