/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:37:20 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/28 01:33:54 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_cpu
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_nb;
	bool			dead;
	pthread_mutex_t	lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	long			start;
}		t_cpu;

int		ft_is_all_ints(int ac, char **av);
long	ft_get_time(void);
int		ft_atoi(char *str);
void	ft_simple_functions(t_cpu *cpu);
int		ft_copy_data(int ac, char **av, t_cpu *cpu);
int		ft_check_NULL(t_cpu *cpu);



# endif