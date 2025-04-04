/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:23:00 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/04 11:41:07 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	only_one(t_data *data, t_philo *philo)
{
	safe_print(data, philo->id, MSG_THINK);
	pthread_mutex_lock(&data->m_forks);
	data->forks_status[philo->id] = UNAVAILABLE;
	safe_print(data, philo->id, MSG_FORK);
	waiting(data, data->death_time);
	data->forks_status[philo->id] = AVAILABLE;
	pthread_mutex_unlock(&data->m_forks);
}

static void	routine_loop(t_data *data, t_philo *philo, bool first_think)
{
	while (1)
	{
		pthread_mutex_lock(&data->m_end);
		if (data->someone_died == true)
		{
			pthread_mutex_unlock(&data->m_end);
			break ;
		}
		pthread_mutex_unlock(&data->m_end);
		if (first_think == false)
		{
			safe_print(data, philo->id, MSG_THINK);
			usleep(500);
		}
		first_think = false;
		if (handle_fork(data, philo) != 0)
			break ;
		safe_print(data, philo->id, MSG_SLEEP);
		waiting(data, data->sleep_time);
	}
}

void	*start_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;
	bool	first_think;

	first_think = true;
	philo = (t_philo *)ptr;
	data = philo->data;
	if (wait_start(data) != 0)
		return (NULL);
	if (data->nb_philo == 1)
	{
		only_one(data, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		safe_print(data, philo->id, MSG_THINK);
		waiting(data, data->eat_time / 2);
	}
	routine_loop(data, philo, first_think);
	return (NULL);
}
