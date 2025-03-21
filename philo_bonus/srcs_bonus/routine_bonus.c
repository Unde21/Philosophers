/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:35:23 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/21 12:07:16 by samaouch         ###   ########lyon.fr   */
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
	sem_post(data->sem_end);
	printf("%ld 1 died\n", data->death_time);
}

static void	routine_loop(t_data *data, t_philo *philo, size_t current)
{
	// long current_time;

	// current_time = 0;
	// if (current % 2 == 0)
	// {
	// 	safe_print(data, current, MSG_THINK);
	// 	waiting(data, data->eat_time / 2, current);
	// }
	while (1)
	{
		//TODO return always 0
		if (handle_fork(data, philo, current) != 0)
		{
			sem_post(data->sem_end);
			return ;
		}
		// printf("current : %zu\n", current + 1);
		safe_print(data, current, MSG_SLEEP);
		waiting(data, data->sleep_time, current);
		// sleep(1);
		// supervisor(data, philo, current);
		safe_print(data, current, MSG_THINK);
	}
}

// static void	*routine_loop(void *ptr)
// {
// 	t_philo	*philo;
// 	t_data *data;
// 	// long	current_time;
	
// 	philo = (t_philo *)ptr;
// 	data = philo->data;
// 	// if (philo->id % 2 == 0)
// 	// {
// 	// 	safe_print(data, philo->id, MSG_THINK);
// 	// 	waiting(data, data->eat_time / 2, philo->id);
// 	// }
// 	while (1)
// 	{
// 		if (handle_fork(data, philo, philo->id) != 0)
// 			exit(0) ;
// 		// printf("current : %zu\n", current + 1);
// 		safe_print(data, philo->id, MSG_SLEEP);
// 		waiting(data, data->sleep_time, philo->id);
// 		// sleep(1);
// 		// supervisor(data, philo, philo->id);
// 		safe_print(data, philo->id, MSG_THINK);
// 	}
// }
void	routine(t_data *data, size_t current)
{
	// if (wait_start(data) != 0)
	// 	return ;
	// data->start_time = get_current_time_ms();
	// data->philos->time_last_meal = data->start_time;
	while (get_current_time_ms() < data->start_time)
		usleep(50);
	// printf("Process %zu, start_time: %ld, current_time: %ld\n",
    //    current, data->start_time, get_current_time_ms());
	// exit(0);
	// usleep(1000);
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
		sem_post(data->sem_end);
		exit(1);
	}
	routine_loop(data, data->philos, current);
	pthread_join(data->philos->thread_supervisor, NULL);
	// sem_post(data->sem_end);
	exit(0) ;
}
