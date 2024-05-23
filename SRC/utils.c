/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:40:56 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/28 00:44:14 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_larger_than(char *str, char *max)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(max);
	while (*str == '0')
		str++;
	while (*(str + i) >= '0' && *(str + i) <= '9')
		i++;
	if (i > len)
		return (1);
	else if (i < len)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if (*str > *max)
			return (1);
		else if (*str++ < *max++)
			return (0);
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int		nbr;
	char	sign;

	nbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		if (ft_larger_than(str++, "2147483648"))
			return (-1);
	}
	else if (*str == '+')
		if (ft_larger_than(str++, "2147483647"))
			return (-1);
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0') * sign;
		str++;
	}
	return (nbr);
}