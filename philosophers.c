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

void	ft_print_data(int *numbers, t_all *philosophers)
{
	int	p = 0;

	while (p < numbers[0])
	{
		printf("----------PHILOSOPHER %i----------\n", philosophers[p].index_philosopher);
		printf("TIME TO DIE -> %li\n", philosophers[p].time_to_die);
		printf("TIME TO EAT -> %li\n", philosophers[p].time_to_eat);
		printf("TIME TO SLEEP -> %li\n", philosophers[p].time_to_sleep);
		printf("NUMBER OF TIMES -> %i\n", philosophers[p].number_of_times);
		printf("START EATING -> %li\n", philosophers[p].start_eating);
		printf("START SLEEPING -> %li\n", philosophers[p].start_sleeping);
		printf("START THINKING -> %li\n", philosophers[p].start_thinking);
		//ft_print_number(numbers[p]);
		write(1, "\n", 1);
		p++;
	}
}

//Rellenamos el array de filosofos con los datos introducidos
void	ft_fill_data(t_all *philosophers, int *data)
{
	int	p;

	p = 0;
	while (p < data[0])
	{
		philosophers[p].index_philosopher = p;
		philosophers[p].time_to_die = data[1];
		philosophers[p].time_to_eat = data[2];
		philosophers[p].time_to_sleep = data[3];
		if (data[4])
			philosophers[p].number_of_times = data[4];
		p++;
	}
}

//Creamos el array de filosofos segun el numero introducido en args[0]
t_all	*ft_create_philosophers(int n_philosophers)
{
	t_all	*philosophers;

	philosophers = malloc (n_philosophers * sizeof(*philosophers));
	if (!philosophers)
		return (NULL);
	return (philosophers);
}


//args[0] -> numero de filosofos
//args[1] -> tiempo que tardan en morir si no comen 	(en milisegundos)
//args[2] -> tiempo que tardan en comer			(en milisegundos)
//args[3] -> tiempo que tardan en dormir		(en milisegundos)
//args[4] -> veces que tienen que comer todos antes de terminar el programa. 
//	     Si no se especifica el programa se ejecutara hasta que un filosofo muera
int main(int argc, char **argv)
{
	int	*args;
	t_all	*philosophers;

	if (argc == 5 || argc == 6)
	{
		args = ft_get_args(argc, argv);

		//CREAMOS EL ARRAY DE FILOSOFOS SEGUN EL Nº INTRODUCIDO POR PARAMETRO
		philosophers = ft_create_philosophers(args[0]);
		ft_fill_data(philosophers, args);


		ft_print_data(args, philosophers);
	}		
	return (0);
}
