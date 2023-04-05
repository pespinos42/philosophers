#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philosopher
{
	int			index_philosopher;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_think;
	int			number_of_times;
	long int	last_eating;
	//long int	last_sleeping;
	//long int	last_thinking;
	long int	start_thread;
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
	pthread_t		t_alive;
	t_fork			*forks;
	int				active;
	pthread_mutex_t	m_a_alive;
	int				all_alive;
	pthread_mutex_t	m_message;
	int				message_end;
}	t_all;

int				ft_strlen(char *str);
int				ft_atoi(char *str);
int				*ft_get_args(int argc, char **argv);
void			ft_print_number(long int n);
void			ft_print_data(int n_elem, t_philosopher *philosophers);
long int		ft_get_time(void);
void			*philosopher(void *arg);
void			ft_fill_data(t_philosopher *philosophers, int *data, int n_arg);
t_philosopher	*ft_create_philosophers(int n_philosophers);
pthread_t		*ft_create_threads(int n_philosophers);
void			ft_initialize_threads(t_all *data);
void			ft_destroy_mutex(int n_philosophers, pthread_mutex_t *forks);
pthread_mutex_t	*ft_create_mutex(int n_philosophers);
t_fork			*ft_create_forks(int n_philosophers);
void			ft_print_message(t_all *data, long int time, int philosopher, char *message);
void			*ft_all_alive(void *arg);
void			ft_fill_t_all(t_all *data, int *args, int n_arg);
