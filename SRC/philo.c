/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:34:08 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/09 07:40:42 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_data(t_cpu *cpu, t_philo **philo)
{
	int	i;

	cpu->start = 0;
	(*philo) = (t_philo *)malloc(sizeof(t_philo) * cpu->nb_philo);
	if (!(*philo))
		return ;
	i = 0;
	while (i < cpu->nb_philo)
	{
		(*philo)[i].cpu = cpu;
		(*philo)[i].id = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_eat = 0;
		(*philo)[i].thread = 0;
		(*philo)[i].dead = false;
		(*philo)[i].thinking = false;
		i++;
	}
}

int	ft_parse_args(int ac, char **av, t_cpu *cpu)
{
	if (ft_is_all_ints(ac, av) == -1)
		return (-1);
	if (ft_copy_data(ac, av, cpu) == -1)
		return (-1);
	if (ft_check_null(cpu) == -1)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_cpu	cpu;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments\nUsage: ./philo n\
umber_of_philosophers time_to_die time_to_eat time_to_slee\
p [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (ft_parse_args(ac, av, &cpu) == -1)
	{
		write(2, "An error occured while parsing arguments\n", 40);
		return (1);
	}
	ft_init_data(&cpu, &philo);
	simulator(&cpu, philo);
	return (0);
}
