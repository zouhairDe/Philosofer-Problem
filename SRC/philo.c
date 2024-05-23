/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:34:08 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/28 01:34:07 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_data(void)
{
	t_cpu	cpu;

	cpu.nb_philo = 0;
	cpu.time_to_die = 0;
	cpu.time_to_eat = 0;
	cpu.time_to_sleep = 0;
	cpu.must_eat_nb = 0;
	cpu.dead = false;
	cpu.start = 0;
}

int	ft_parse_args(int ac, char **av, t_cpu *cpu)
{
	if (ft_is_all_ints(ac, av) == -1)
		return (-1);
	if (ft_copy_data(ac, av, cpu) == -1)
		return (-1);
	if (ft_check_NULL(cpu) == -1)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_cpu cpu;
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments\nUsage: ./philo n\
umber_of_philosophers time_to_die time_to_eat time_to_slee\
p [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	ft_init_data();
	if (ft_parse_args(ac, av, &cpu) == -1)
	{
		write(2, "An error occured while parsing arguments\n", 40);
		return (1);
	}
	ft_simple_functions(&cpu);
	return (0);
}
