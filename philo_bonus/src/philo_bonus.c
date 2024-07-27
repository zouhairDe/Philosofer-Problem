/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 01:23:19 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/27 00:54:33 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int ac, char **av)
{
	t_data	data;

	if (ac > 6 || ac < 5)
		return (printf("Error:\nIncorrect arguments number\n"));
	if (init(&data, ac, av))
		return (1);
	if (simulator(&data))
		return (1);
	sem_close(data.forks);
	sem_close(data.write);
	sem_close(data.lock);
	sem_close(data.end);
	return (0);
}
