/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:52:30 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/30 02:13:47 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac > 6 || ac < 5)
		return (printf("Error:\nIncorrect arguments nnumber\n"));
	if (init(&data, ac, av))
		return (1);
	if (simulator(&data))
		return (1);
	pthread_mutex_destroy(&data.lock);
	pthread_mutex_destroy(&data.read);
	pthread_mutex_destroy(&data.end);
	i = -1;
	while (++i < data.number)
		pthread_mutex_destroy(&data.forks[i]);
	free(data.forks);
	free(data.philos);
	return (0);
}
