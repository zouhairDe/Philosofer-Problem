/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:24:11 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/28 01:17:45 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_NULL(t_cpu *cpu)
{
	if (cpu->nb_philo <= 0 || cpu->time_to_die <= 0 || cpu->time_to_eat <= 0
		|| cpu->time_to_sleep <= 0 || cpu->must_eat_nb < 0)
		return (-1);
	return (0);
}

int	ft_copy_data(int ac, char **av, t_cpu *cpu)
{
	cpu->nb_philo = ft_atoi(av[1]);
	cpu->time_to_die = ft_atoi(av[2]);
	cpu->time_to_eat = ft_atoi(av[3]);
	cpu->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		cpu->must_eat_nb = ft_atoi(av[5]);
	else
		cpu->must_eat_nb = -1;
	cpu->dead = false;
	pthread_mutex_init(&cpu->lock, NULL);
	pthread_mutex_init(&cpu->dead_lock, NULL);
	pthread_mutex_init(&cpu->print_lock, NULL);
	cpu->start = ft_get_time();
	return (0);
}

int	ft_is_all_ints(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}