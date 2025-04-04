/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:39:55 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/04 12:24:46 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	get_fork(t_data *data, t_philo *philo, size_t fork_index)
{
	while (1)
	{
		pthread_mutex_lock(&data->m_forks);
		if (data->forks_status[fork_index] == AVAILABLE)
		{
			safe_print(data, philo->id, MSG_FORK);
			data->forks_status[fork_index] = UNAVAILABLE;
			pthread_mutex_unlock(&data->m_forks);
			break ;
		}
		pthread_mutex_lock(&data->m_end);
		if (data->someone_died == true)
		{
			pthread_mutex_unlock(&data->m_end);
			pthread_mutex_unlock(&data->m_forks);
			return (false);
		}
		pthread_mutex_unlock(&data->m_end);
		pthread_mutex_unlock(&data->m_forks);
		usleep(100);
	}
	return (true);
}

bool	take_right_fork(t_data *data, t_philo *philo)
{
	if (get_fork(data, philo, philo->first_fork_index) == false)
		return (false);
	if (get_fork(data, philo, philo->second_fork_index) == false)
		return (false);
	eating(data, philo);
	pthread_mutex_lock(&data->m_forks);
	data->forks_status[philo->first_fork_index] = AVAILABLE;
	data->forks_status[philo->second_fork_index] = AVAILABLE;
	pthread_mutex_unlock(&data->m_forks);
	return (true);
}
