#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philosopher
{
	int		index_philosopher;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		number_of_times;
	long	start_eating;
	long	start_sleeping;
	long	start_thinking;
}	t_philosopher;

typedef struct s_all
{
	t_philosopher	*philosophers;
	pthread_t		*threads;
	int				*forks;
	pthread_mutex_t	*mutex;
}	t_all;

pthread_mutex_t mutex;
pthread_t hilo_incremento;
pthread_t hilo_decremento;

int variable_compartida = 100;

void    *incremento(void *arg)
{
    int p = 0;
    
    while (p < 10000000)
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
    
    while (p < 5000000)
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
    struct timeval tv;

    pthread_create(&hilo_incremento, NULL, incremento, NULL);
    pthread_create(&hilo_decremento, NULL, decremento, NULL);
    pthread_mutex_init(&mutex, NULL);
    gettimeofday(&tv, NULL);
    printf("VALOR INICIAL VARIABLE COMPARTIDA -> %i\nMILISEGUNDOS -> %i\n\n", variable_compartida, tv.tv_usec/1000);
    pthread_join(hilo_incremento, NULL);
    gettimeofday(&tv, NULL);
    printf("VALOR INTERMEDIO VARIABLE COMPARTIDA -> %i\nMILISEGUNDOS -> %i\n\n", variable_compartida, tv.tv_usec/1000);
    pthread_join(hilo_decremento, NULL);
    pthread_mutex_destroy(&mutex);
    gettimeofday(&tv, NULL);
    printf("VALOR FINAL VARIABLE COMPARTIDA -> %i\nMILISEGUNDOS -> %i\n\n", variable_compartida, tv.tv_usec/1000);
    return(0);
}