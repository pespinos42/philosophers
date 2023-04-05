#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_atoi(char *str)
{
	int result;
	int s;
	int sign;

	result = 0;
	s = 0;
	sign = 1;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
	{
		s++;
		str++;
	}
	if (*str == '-' && s == 0)
	{
		sign = -1;
		str++;
	}
	if (*str == '-' && s == 1)
		sign = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (sign * result);
}

int	*ft_get_args(int argc, char **argv)
{
	int	*args;
	int	n;

	n = 0;
	args = malloc ((argc - 1) * sizeof (*args));
	if (!args)
		return (NULL);
	while (n < (argc - 1))
	{
		args[n] = ft_atoi(argv[n + 1]);
		n++;
	}
	return (args);
}

void	ft_print_number(long int n)
{
	char	number = 0;

	if (n == INT_MIN)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_print_number(-n);
	}
	else
	{
		if (n > 9)
			ft_print_number(n/10);
		number = (n%10) + 48;
		write(1, &number, 1);
	}
}

void	ft_print_data(int n_elem, t_philosopher *philosophers)
{
	int	p = 0;

	while (p < n_elem)
	{
		printf("----------PHILOSOPHER %i----------\n", philosophers[p].index_philosopher);
		printf("TIME TO DIE -> %li\n", philosophers[p].time_to_die);
		printf("TIME TO EAT -> %li\n", philosophers[p].time_to_eat);
		printf("TIME TO SLEEP -> %li\n", philosophers[p].time_to_sleep);
		printf("NUMBER OF TIMES -> %i\n", philosophers[p].number_of_times);
		printf("START EATING -> %li\n", philosophers[p].last_eating);
		//printf("START SLEEPING -> %li\n", philosophers[p].last_sleeping);
		//printf("START THINKING -> %li\n", philosophers[p].last_thinking);
		//ft_print_number(numbers[p]);
		write(1, "\n", 1);
		p++;
	}
}

long int	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*philosopher(void *arg)
{
	t_all	*data;
	int			active;
	int			fork_right;
	int			fork_left;
	long int	time;
	long int	stop_time;

	data = (t_all *) arg;
	active = data->active;
	fork_right = active;
	if (active)
		fork_left = data->total_philosophers - 1;
	else
		fork_left = lock1 - 1;
	data->philosophers[active].start_thread = ft_get_time();
	while (data->all_alive == 1)//FALTA IMPLEMENTAR EL NUMERO DE VECES QUE HA COMIDO
	{
		while (data->forks[fork_right].using == 1 || data->forks[fork_left].using == 1)
			usleep(1000);
		pthread_mutex_lock(&data->forks[fork_right].fork_mutex);
		pthread_mutex_lock(&data->forks[fork_left].fork_mutex);
		if (data->all_alive == 1)
		{
			pthread_mutex_lock(&data->m_message);
			ft_print_message(data, ft_get_time(), active, " has taken a fork");
			ft_print_message(data, ft_get_time(), active, " has taken a fork");
			ft_print_message(data, ft_get_time(), active, " is eating");
			pthread_mutex_unlock(&data->m_message);
		}
		time = ft_get_time();
		stop_time = time + data->philosophers[active].time_to_eat;
		while (ft_get_time() < stop_time && data->all_alive == 1)
			usleep(1000);
		data->philosophers[active].last_eating = ft_get_time();
		pthread_mutex_unlock(&data->forks[fork_left].fork_mutex);
		pthread_mutex_unlock(&data->forks[fork_right].fork_mutex);
		if (data->all_alive == 1)
		{
			pthread_mutex_lock(&data->m_message);
			ft_print_message(data, ft_get_time(), active, " is sleeping");
			pthread_mutex_unlock(&data->m_message);
		}
		time = ft_get_time();
		stop_time = time + data->philosophers[active].time_to_sleep;
		while (ft_get_time() < stop_time && data->all_alive == 1)
			usleep(1000);
		//Ahora calculamos el tiempo de pensar
		time = ft_get_time();
		stop_time = (time - data->philosophers[active].last_eating) / 2;
		if (stop_time > 500)
			stop_time = 500;
		if (stop_time > 0)
		{
			if (data->all_alive == 1)
			{
				pthread_mutex_lock(&data->m_message);
				ft_print_message(data, ft_get_time(), active, " is thinking");
				pthread_mutex_unlock(&data->m_message);
			}
			stop_time += time;
			while (ft_get_time() < stop_time && data->all_alive == 1)
				usleep(1000);
		}		
		//printf("FILOSOFO_ACTIVO -> %i\n", data->philosophers[active].index_philosopher);
		//usleep(200000);		
	}
	while (data->message_end == 0)
		usleep(100);
	return (NULL);
}

//Rellenamos el array de filosofos con los datos introducidos
void	ft_fill_data(t_philosopher *philosophers, int *data, int n_arg)
{
	int	p;

	p = 0;
	printf("----------DATOS INTRODUCIDOS----------\n");
	printf("ARG[0] -> %i\n", data[0]);
	printf("ARG[1] -> %i\n", data[1]);
	printf("ARG[2] -> %i\n", data[2]);
	printf("ARG[3] -> %i\n", data[3]);
	printf("ARG[4] -> %i\n", data[4]);
	while (p < data[0])
	{
		philosophers[p].index_philosopher = p + 1;
		philosophers[p].time_to_die = data[1];
		philosophers[p].time_to_eat = data[2];
		philosophers[p].time_to_sleep = data[3];
		if (n_arg == 5)
			philosophers[p].number_of_times = data[4];
		else
			philosophers[p].number_of_times = -1;
		p++;
	}
}

//Creamos el array de filosofos segun el numero introducido en args[0]
t_philosopher	*ft_create_philosophers(int n_philosophers)
{
	t_philosopher	*philosophers;
	int				n;

	n = 0;
	philosophers = malloc (n_philosophers * sizeof(*philosophers));
	if (!philosophers)
		return (NULL);
	while (n < n_philosophers)
	{
		philosophers[n].index_philosopher = -1;
		philosophers[n].time_to_die = -1;
		philosophers[n].time_to_eat = -1;
		philosophers[n].time_to_sleep = -1;
		philosophers[n].number_of_times = -1;
		philosophers[n].last_eating = -1;
		//philosophers[n].last_sleeping = -1;
		//philosophers[n].last_thinking = -1;
		philosophers[n].start_thread = -1;
		n++;
	}
	return (philosophers);
}

//REVISAR EL PLANTEAMIENTO DE LOS HILOS
//HACERLO UNO POR CADA ACCIÓN (COMER, DORMIR, PENSAR) EN LUGAR DE POR CADA FILOSOFO
pthread_t	*ft_create_threads(int n_philosophers)
{
	pthread_t	*threads;

	threads = malloc (n_philosophers * sizeof (*threads));
	if (!threads)
		return (NULL);
	return (threads);
}

void	ft_initialize_threads(t_all *data)
{
	int	n;

	n = 0;
	while (n < data->total_philosophers)
	{
		data->active = n;
		pthread_create(&data->threads[n], NULL, philosopher, data);
		usleep(10000);
		n++;
	}
	n = 0;
	while (n < data->total_philosophers)
	{
		pthread_join(data->threads[n], NULL);
		n++;
	}
}

void	ft_destroy_mutex(int n_philosophers, pthread_mutex_t *forks)
{
	int	n;

	n = 0;
	while (n < n_philosophers)
	{
		pthread_mutex_destroy(&forks[n]);
		n++;
	}
}

pthread_mutex_t	*ft_create_mutex(int n_philosophers)
{
	pthread_mutex_t	*forks;
	int				n;

	n = 0;
	forks = malloc (n_philosophers * sizeof (*forks));
	if (!forks)
		return (NULL);
	while (n < n_philosophers)
	{
		pthread_mutex_init(&forks[n], NULL);
		n++;
	}
	return (forks);
}

t_fork	*ft_create_forks(int n_philosophers)
{
	t_fork	*forks;
	int		n;

	n = 0;
	forks = malloc (n_philosophers * sizeof (*forks));
	if (!forks)
		return (NULL);
	while (n < n_philosophers)
	{
		forks[n].using = 0;
		pthread_mutex_init(&forks[n].fork_mutex, NULL);
		n++;
	}
	return (forks);
}

void	ft_print_message(t_all *data, long int time, int philosopher, char *message)
{
	printf("DENTRO DE LA IMPRESION DEL MENSAJE\n");
	pthread_mutex_lock(&data->m_message);
	ft_print_number(time);
	write(1, " ", 1);
	ft_print_number(philosopher);
	write(1, " ", 1);
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	data->message_end = 1;
}

void	*ft_all_alive(void *arg)
{
	t_all		*data;
	int			n;
	long int	time;
	long int	time_start;

	data = (t_all *) arg;
	n = 0;
	time = 0;
	printf("COMIENZO DE FT_ALL_ALIVE -> %li\n", ft_get_time());
	printf("DENTRO DE FT_ALL_ALIVE\n");
	printf("TOTAL FILOSOFOS -> %i\n", data->total_philosophers);
	while (data->all_alive == 1)
	{
		//printf("DENTRO DEL PRIMER WHILE\n");
		while (n < data->total_philosophers && data->all_alive == 1)
		{
			//printf("DENTRO DEL SEGUNDO WHILE\n");
			while (data->philosophers[n].start_thread == -1)
			{
				//printf("ESPERANDO FILOSOFO %i\n", n+1);
				usleep(10000);
			}
			if (data->philosophers[n].last_eating == -1)
				time_start = data->philosophers[n].start_thread;
			else
				time_start = data->philosophers[n].last_eating;
			time = ft_get_time();
			if ((time - time_start) >= data->philosophers[n].time_to_die)
			{
				pthread_mutex_lock(&data->m_a_alive);
				data->all_alive = 0;
				pthread_mutex_unlock(&data->m_a_alive);
				ft_print_message(data, time, data->philosophers[n].index_philosopher, "died");
			}
			n++;
		}
		n = 0;
		usleep(1000);
	}
}

void	ft_fill_t_all(t_all *data, int *args, int n_arg)
{
	data->total_philosophers = args[0];
	data->philosophers = ft_create_philosophers(args[0]);
	ft_fill_data(data->philosophers, args, n_arg);
	data->forks	= ft_create_forks(args[0]);
	data->m_a_alive = *(ft_create_mutex(1));
	data->all_alive = 1;
	data->message_end = 0;
	data->threads = ft_create_threads(args[0]);
	data->t_alive = *(ft_create_threads(1));
	pthread_create(&data->t_alive, NULL, ft_all_alive, data);
	data->m_message = *(ft_create_mutex(1));
	pthread_detach(data->t_alive);
	ft_initialize_threads(data);
}

//args[0] -> numero de filosofos
//args[1] -> tiempo que tardan en morir si no comen 	(en milisegundos)
//args[2] -> tiempo que tardan en comer			(en milisegundos)
//args[3] -> tiempo que tardan en dormir		(en milisegundos)
//args[4] -> veces que tienen que comer todos antes de terminar el programa. 
//	     Si no se especifica el programa se ejecutara hasta que un filosofo muera
int main(int argc, char **argv)
{
	int		*args;
	t_all	all_phi;

	if (argc == 5 || argc == 6)
	{
		args = ft_get_args(argc, argv);

		ft_fill_t_all(&all_phi, args, argc - 1);
	}
	printf("FINAL DEL PROGRAMA -> %li\n", ft_get_time());
	return (0);
}
