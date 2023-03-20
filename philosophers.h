#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_all
{
	int		index_philosopher;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		number_of_times;
	long	start_eating;
	long	start_sleeping;
	long	start_thinking;
}	t_all;

int	ft_atoi(char *str);
int	*ft_get_args(int argc, char **argv);
void	ft_print_number(int n);