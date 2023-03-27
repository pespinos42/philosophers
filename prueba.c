#include <stdio.h>
#include <stdlib.h>

typedef struct s_prueba
{
    int number;
}   t_prueba;

void ft_modify(t_prueba *prueba)
{
    prueba[1].number = 200;
}

int main()
{
    t_prueba *prueba;

    prueba = malloc (2 * sizeof (*prueba));
    if (!prueba)
        return (-1);
    prueba[0].number = 10;
    prueba[1].number = 20;
    ft_modify(prueba);
    printf("PRUEBA.NUMBER = %i\n", prueba[1].number);
}