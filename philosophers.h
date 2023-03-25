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
}	t_philosopher;

typedef struct s_all
{
	t_philosopher	*philosophers;
	pthread_t		*threads;
	int				*forks;
	pthread_mutex_t	*mutex_forks;
}

int		ft_atoi(char *str);
int		*ft_get_args(int argc, char **argv);
void	ft_print_number(int n);
void	ft_print_data(int *numbers, t_all *philosophers);
void	ft_fill_data(t_all *philosophers, int *data);
t_all	*ft_create_philosophers(int n_philosophers);
