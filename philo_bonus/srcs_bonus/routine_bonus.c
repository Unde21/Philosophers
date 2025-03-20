/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:35:23 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/20 12:37:28 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>

static	void only_one(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	safe_print(data, philo[0].id, MSG_FORK);
	waiting(data, data->death_time, 1);
	sem_post(data->sem_end);
	printf("%ld 1 died\n", data->death_time);
}

static void	routine_loop(t_data *data, t_philo *philo, size_t current)
{
	long current_time;

	current_time = 0;
	while (1)
	{
		if (handle_fork(data, philo, current) != 0)
			exit(0) ;
		// printf("current : %zu\n", current + 1);
		safe_print(data, current, MSG_SLEEP);
		waiting(data, data->sleep_time, current);
		// sleep(1);
		supervisor(data, philo, current);
		safe_print(data, current, MSG_THINK);
	}
}

void	routine(t_data *data, size_t current)
{
	if (data->nb_philo == 1)
	{
		only_one(data, data->philos);
		exit(0) ;
	}
	if (current % 2 == 0)
	{
		safe_print(data, current, MSG_THINK);
		waiting(data, data->eat_time / 2, current);
	}
	routine_loop(data, data->philos, current);
	exit(0) ;
	
}
