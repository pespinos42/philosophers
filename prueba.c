#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define N_PHILOSOPHERS 4
#define TIME_TO_EAT 100
#define TIME_TO_SLEEP 200
#define TIME_TO_DIE 400

typedef struct s_philosopher
{
    int             index_philosopher;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             number_of_times;
    long            start_eating;
    long            start_sleeping;
    long            start_thinking;
    int             alive;
    struct timeval  tv;
}   t_philosopher;

typedef struct s_all
{
    t_philosopher   *philosophers;
    pthread_t       *threads;
    pthread_mutex_t *forks;
    int             active_philosopher;
}   t_all;

long int    ft_get_time()
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_usec/1000);
}

void    *filosofo(void *arg)
{
    //En esta función se observa el estado de un filosofo concreto, ciclando entre COMER->DORMIR->[PENSAR]->COMER...
    //No cabe la posibilidad de que se pisen varios filosofos porque los mutex son compartidos
    
    int filosofo_activo = -1;
    int otro_tenedor = -1;
    int n = 0;
    t_all *data = (t_all *) arg;
    
    filosofo_activo = data->active_philosopher;
    
    if (filosofo_activo == 0)
        otro_tenedor = N_PHILOSOPHERS - 1;
    else
        otro_tenedor = filosofo_activo - 1;
    
    //printf("FILOSOFO ACTIVO: %i\n", filosofo_activo);
    //printf("INDICE FILOSOFO: %i\n", data->philosophers[filosofo_activo].index_philosopher);
    
    while (n < 10)
    {
        pthread_mutex_lock(&data->forks[filosofo_activo]);
        pthread_mutex_lock(&data->forks[otro_tenedor]);
        printf("%li FILOSOFO %i COMIENDO\n", ft_get_time(), filosofo_activo);
        usleep(data->philosophers[filosofo_activo].time_to_eat);
        pthread_mutex_unlock(&data->forks[otro_tenedor]);
        pthread_mutex_unlock(&data->forks[filosofo_activo]);
        
        printf("%li FILOSOFO %i DURMIENDO\n", ft_get_time(), filosofo_activo);
        usleep(data->philosophers[filosofo_activo].time_to_sleep * 1000);
        printf("%li FILOSOFO %i PENSANDO\n", ft_get_time(), filosofo_activo);
        n++;
    }
    
    return ("OK");
}


int main()
{
    t_all   data;
    int     n = 0;
    void    *message_return = NULL;
    
    printf("INICIO DEL PROGRAMA %li\n", ft_get_time());
    
    //CREAMOS EL ARRAY DE FILOSOFOS
    data.philosophers = malloc (N_PHILOSOPHERS * sizeof (*data.philosophers));
    if (!data.philosophers)
        return (-1);
        
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
    
    //CREAMOS EL ARRAY DE MUTEX (UNO POR CADA FILOSOFO) Y LOS INICIALIZAMOS
    data.forks = malloc (N_PHILOSOPHERS * sizeof (*data.forks));
    if (!data.forks)
        return (-1);
    while (n < N_PHILOSOPHERS)
    {
        pthread_mutex_init(&data.forks[n], NULL);
        n++;
    }
    n = 0;
        
    //CREAMOS EL ARRAY DE HILOS (UNO POR CADA FILOSOFO)
        //INICIALIZAMOS EL CONTADOR DEL FILOSOFO ACTIVO A -1
        //data.active_philosopher = -1;
    data.threads = malloc (N_PHILOSOPHERS * sizeof (*data.threads));
    if (!data.threads)
        return (-1);
    while (n < N_PHILOSOPHERS)
    {
        data.active_philosopher = n;
        pthread_create(&data.threads[n], NULL, filosofo, &data);
        n++;
        usleep(100000);
    }
    n = 0;
    
    
    
    //INICIAMOS LOS HILOS
    while (n < N_PHILOSOPHERS)
    {
        pthread_join(data.threads[n], &message_return);
        n++;
    }
    n = 0;
    
    //DESTRUIMOS LOS MUTEX
    while (n < N_PHILOSOPHERS)
    {
        pthread_mutex_destroy(&data.forks[n]);
        n++;
    }
    n = 0;
    
    printf("MENSAJE DEVUELTO %s\n", (char *) message_return);
    printf("FINAL DEL PROGRAMA %li\n", ft_get_time());
    
    return (0);
}