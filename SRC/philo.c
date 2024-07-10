/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:52:30 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/10 23:38:50 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac > 6 || ac < 5)
		return (printf("Error:\nIncorrect arguments nnumber\n"));
	if (init(&data, ac, av))
		return (0);
	if (simulator(&data))
		return (1);
	return (0);
}
