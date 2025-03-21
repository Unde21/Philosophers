/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:35:23 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/21 13:49:49 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>
# include <pthread.h>

static	void only_one(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	safe_print(data, philo[0].id, MSG_FORK);
	waiting(data, data->death_time, 1);
	printf("%ld 1 died\n", data->death_time);
}

static void	routine_loop(t_data *data, t_philo *philo, size_t current)
{
	while (1)
	{
		handle_fork(data, philo, current);
		safe_print(data, current, MSG_SLEEP);
		waiting(data, data->sleep_time, current);
		safe_print(data, current, MSG_THINK);
	}
}

void	routine(t_data *data, size_t current)
{
	data->philos[current].time_last_meal = data->start_time;
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
	if (pthread_create(&data->philos[current].thread_supervisor, NULL, supervisor, &data->philos[current]) != 0)
	{
		//TODO handle error
		// sem_post(data->sem_end);
		exit(1);
	}
	routine_loop(data, data->philos, current);
	pthread_join(data->philos->thread_supervisor, NULL);
	exit(0) ;
}
