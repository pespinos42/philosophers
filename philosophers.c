#include "philosophers.h"

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

void	ft_print_number(int n)
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
		printf("START EATING -> %li\n", philosophers[p].start_eating);
		printf("START SLEEPING -> %li\n", philosophers[p].start_sleeping);
		printf("START THINKING -> %li\n", philosophers[p].start_thinking);
		printf("INSTRUCTION -> %i\n", philosophers[p].instruction);
		//ft_print_number(numbers[p]);
		write(1, "\n", 1);
		p++;
	}
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
		philosophers[n].start_eating = -1;
		philosophers[n].start_sleeping = -1;
		philosophers[n].start_thinking = -1;
		philosophers[n].instruction = -1;
		philosophers[n].alive = 1;
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

pthread_mutex_t	*ft_create_forks(int n_philosophers)
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

void	ft_fill_t_all(t_all *data, int *args, int n_arg)
{
	data->philosophers = ft_create_philosophers(args[0]);
	ft_fill_data(data->philosophers, args, n_arg);
	data->threads = ft_create_threads(3);
	data->forks	= ft_create_forks(args[0]);
}

int	ft_all_alive(int n_philosophers, t_philosophers *philosobers)
{
	int n = 0;
	int	alive = 1;

	while (n < n_philosophers && alive == 1)
	{
		if (philosobers[n].alive == 0)
			alive = 0;
		n++;
	}
	return (alive);
}

void	ft_philosophers_odd(t_all *all_phi)
{
	
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

		//CREAMOS EL ARRAY DE FILOSOFOS SEGUN EL Nº INTRODUCIDO POR PARAMETRO
		ft_fill_t_all(&all_phi, args, argc - 1);
		//COMPROBAMOS SI EL NUMERO DE FILOSOFOS ES PAR
		if (args[0] % 2 == 0)
			ft_philosophers_odd();
		else
			ft_philosophers_even();
		ft_print_data(args[0], all_phi.philosophers);
	}		
	return (0);
}
