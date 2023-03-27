#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

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
	int		instruction;
	int		alive;
}	t_philosopher;

typedef struct s_all
{
	t_philosopher	*philosophers;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
}	t_all;

int		ft_atoi(char *str);
int		*ft_get_args(int argc, char **argv);
void	ft_print_number(int n);
void	ft_fill_data(t_philosopher *philosophers, int *data, int n_arg);