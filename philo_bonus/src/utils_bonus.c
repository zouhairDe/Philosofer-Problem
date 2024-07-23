/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 01:42:14 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/23 01:42:37 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_round(double nb)
{
	nb = nb + 0.5;
	return ((long)nb);
}

double	get_time(void)
{
	struct timeval	counter;

	gettimeofday(&counter, NULL);
	return (counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0);
}

int	is_number(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (-2);
	if (i > 11)
		return (-2);
	return (0);
}

int	ft_atoi(char *str)
{
	long	number;
	int		sign;

	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-2);
		str++;
	}
	number = 0;
	while (*str)
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	if (number > 2147483647)
		return (-2);
	return (number * sign);
}
