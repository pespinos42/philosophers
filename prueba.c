#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int variable_compartida = 10;
pthread_mutex_t mutex;

void    *ft_incremento(void *arg)
{
    int n = 0;

    while (n < 10)
    {
        pthread_mutex_lock(&mutex);
        variable_compartida++;
        pthread_mutex_unlock(&mutex);
        usleep(1000000);
        printf("INCREMENTADO\n");
        n++;
    }
    return (NULL);
}

void    *ft_decremento(void *arg)
{
    int n = 0;

    while (n < 5)
    {
        pthread_mutex_lock(&mutex);
        variable_compartida--;
        pthread_mutex_unlock(&mutex);
        usleep(1000000);
        printf("DECREMENTADO\n");
        n++;
    }
    return (NULL);
}

int main()
{
    pthread_t hilo_incremento;
    pthread_t hilo_decremento;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&hilo_incremento, NULL, ft_incremento, NULL);
    pthread_create(&hilo_decremento, NULL, ft_decremento, NULL);
    printf("VALOR VARIABLE INTERMEDIO %i\n", variable_compartida);
    pthread_join(hilo_incremento, NULL);
    pthread_join(hilo_decremento, NULL);

    pthread_mutex_destroy(&mutex);

    printf("VALOR VARIABLE FINAL %i\n", variable_compartida);

    return (0);
}