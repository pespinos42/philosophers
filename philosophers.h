#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philosopher
{
	int		index_philosopher;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;
	int		number_of_times;
	long	start_eating;
	long	start_sleeping;
	long	start_thinking;
}	t_philosopher;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				using;
}	t_fork;

typedef struct s_all
{
	int				total_philosophers;
	t_philosopher	*philosophers;
	pthread_t		*threads;
	pthread_t		alive;
	t_fork			*forks;
	int				active;
	pthread_mutex_t	m_a_alive;
	int				all_alive;
	pthread_mutex_t	m_message;
	int				alive;
}	t_all;

int		ft_atoi(char *str);
int		*ft_get_args(int argc, char **argv);
void	ft_print_number(int n);
void	ft_fill_data(t_philosopher *philosophers, int *data, int n_arg);