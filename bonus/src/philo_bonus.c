/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:47:45 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/19 14:33:38 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void kill_all(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->number)
        kill(data->philos[i].pid, SIGKILL);
}

void f()
{
	system ("leaks philo");
}

int	main(int ac, char **av)
{
	t_data	data;
    // atexit(f);
	if (ac > 6 || ac < 5)
		return (printf("Error:\nIncorrect arguments nnumber\n"));
	if (init(&data, ac, av))
		return (1);
	if (simulator(&data))
		return (1);
	free(data.philos);
	return (0);
}
