#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define N_PHILOSOPHERS 2
#define TIME_TO_EAT 100
#define TIME_TO_SLEEP 200
#define TIME_TO_DIE 400

typedef struct s_philosopher
{
    int     index_philosopher;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    int     number_of_times;
    long    start_eating;
    long    start_sleeping;
    long    start_thinking;
    int     alive;
}   t_philosopher;

typedef struct s_all
{
    t_philosopher   *philosophers;
    pthread_t       *threads;
    pthread_mutex_t *forks;
    int             active_philosopher;
}   t_all;

void    *filosofo(void *arg)
{
    int filosofo_activo = -1;
    //En esta función se observa el estado de un filosofo concreto, ciclando entre COMER->DORMIR->[PENSAR]->COMER...
    //No cabe la posibilidad de que se pisen varios filosofos porque los mutex son compartidos
    t_all *data = (t_all *) arg;
    
    filosofo_activo = data->active_philosopher;
    printf("FILOSOFO ACTIVO: %i\n", data->active_philosopher);
    return (NULL);
}

int main()
{
    t_all   data;
    int     n = 0;
    void    *message_return = NULL;
    
    //CREAMOS EL ARRAY DE FILOSOFOS
    data.philosophers = malloc (N_PHILOSOPHERS * sizeof (*data.philosophers));
    if (!data.philosophers)
        return (-1);
        
    //CREAMOS EL ARRAY DE MUTEX (UNO POR CADA FILOSOFO)
    data.forks = malloc (N_PHILOSOPHERS * sizeof (*data.forks));
    if (!data.forks)
        return (-1);
        
    //CREAMOS EL ARRAY DE HILOS (UNO POR CADA FILOSOFO)
    data.threads = malloc (N_PHILOSOPHERS * sizeof (*data.threads));
    if (!data.threads)
        return (-1);
    while (n < N_PHILOSOPHERS)
    {
        data.active_philosopher = n;
        pthread_create(&data.threads[n], NULL, filosofo, &data);
        n++;
        usleep(100);
    }
    n = 0;
    
    //INICIALIZAMOS EL CONTADOR DEL FILOSOFO ACTIVO A -1
    //data.active_philosopher = -1;
    
    while (n < N_PHILOSOPHERS)
    {
        data.philosophers[n].index_philosopher = n + 1;
        data.philosophers[n].time_to_die = TIME_TO_DIE;
        data.philosophers[n].time_to_eat = TIME_TO_EAT;
        data.philosophers[n].time_to_sleep = TIME_TO_SLEEP;
        data.philosophers[n].number_of_times = -1;
        data.philosophers[n].start_eating = -1;
        data.philosophers[n].start_sleeping = -1;
        data.philosophers[n].start_thinking = -1;
        data.philosophers[n].alive = 1;
        n++;
    }
    n = 0;
    
    while (n < N_PHILOSOPHERS)
    {
        pthread_join(data.threads[n], &message_return);
        n++;
    }
    
    printf("MENSAJE DEVUELTO %s\n", (char *) message_return);
    return (0);
}