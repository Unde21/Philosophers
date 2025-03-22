/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:35:23 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/22 11:05:32 by samaouch         ###   ########lyon.fr   */
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
	sem_post(data->sem_end);
}

void	routine(t_data *data, size_t current)
{
	data->philos[current].time_last_meal = data->start_time;
	if (data->nb_philo == 1)
	{
		only_one(data, data->philos);
		clear_data(data);
		exit(0) ;
	}
	//TODO leak : pthread ??
	if (pthread_create(&data->philos->thread_supervisor, NULL, supervisor, &data->philos[current]) != 0)
	{
		//TODO handle error
		// sem_post(data->sem_end);
		clear_data(data);
		exit(1);
	}
	pthread_detach(data->philos->thread_supervisor);
	if (current % 2 == 0)
	{
		safe_print(data, current, MSG_THINK);
		waiting(data, data->eat_time / 2, current);
	}
	routine_loop(data, data->philos, current);
	//  if (data->philos[current].thread_supervisor)
    //     pthread_join(data->philos[current].thread_supervisor, NULL);
	sem_post(data->sem_end);
	clear_data(data);
	exit(0) ;
}
