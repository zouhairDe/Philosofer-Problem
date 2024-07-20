/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:52:30 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/20 23:20:02 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_done(t_philo *philo, int code)
{
	int	timestamp;

	timestamp = get_time() - philo->data->start;
	if (code == 1)
		printf("%d %d died\n", timestamp, philo->id);
	else
		pthread_exit(NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac > 6 || ac < 5)
		return (printf("Error:\nIncorrect arguments nnumber\n"));
	if (init(&data, ac, av))
		return (1);
	if (simulator(&data))
		return (1);
	free(data.forks);
	free(data.philos);
	return (0);
}
