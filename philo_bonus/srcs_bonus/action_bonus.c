/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:33:58 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/18 13:23:53 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// TODO protect with semaphore ?
static void eating(t_data *data, t_philo *philo, size_t current)
{
	safe_print(data, data->pid[current], MSG_EATING);
	++philo[current].nb_meal;
	philo[current].time_last_meal = get_current_time_ms();
	waiting(data, data->eat_time);
}

//library
#include <stdio.h>
//BUG
int	handle_fork(t_data *data, t_philo *philo, size_t current)
{
	if (sem_wait(data->forks) != 0)
		return (-1);
	printf("ALED\n");
	safe_print(data, data->pid[current], MSG_FORK);
	if (sem_wait(data->forks) != 0)
	{
		sem_post(data->forks);
		return (-1);
	}
	safe_print(data, data->pid[current], MSG_FORK);
	eating(data, philo, current);
	sem_post(data->forks);
	sem_post(data->forks);
	return (0);
}
