/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:39:55 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/04 08:37:14 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	try_take_fork(t_data *data, t_philo *philo,
		pthread_mutex_t *fork_mutex, int fork_index)
{
	pthread_mutex_lock(fork_mutex);
	if (data->forks_status[fork_index] == AVAILABLE)
	{
		data->forks_status[fork_index] = UNAVAILABLE;
		safe_print(data, philo->id, MSG_FORK);
		pthread_mutex_unlock(fork_mutex);
		return (true);
	}
	pthread_mutex_unlock(fork_mutex);
	return (false);
}

static void	release_fork(t_data *data, t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	data->forks_status[philo->first_fork_index] = AVAILABLE;
	pthread_mutex_unlock(fork);
}

bool	take_right_fork(t_data *data, t_philo *philo,
		pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	if (try_take_fork(data, philo, first_fork,
			philo->first_fork_index) == false)
	{
		pthread_mutex_lock(first_fork);
		data->forks_status[philo->first_fork_index] = AVAILABLE;
		pthread_mutex_unlock(first_fork);
		return (false);
	}
	pthread_mutex_lock(&data->m_end);
	if (data->someone_died == true)
	{
		pthread_mutex_unlock(&data->m_end);
		release_fork(data, philo, first_fork);
		return (true);
	}
	pthread_mutex_unlock(&data->m_end);
	eating(data, philo);
	pthread_mutex_lock(first_fork);
	data->forks_status[philo->first_fork_index] = AVAILABLE;
	pthread_mutex_unlock(first_fork);
	pthread_mutex_lock(second_fork);
	data->forks_status[philo->second_fork_index] = AVAILABLE;
	pthread_mutex_unlock(second_fork);
	return (true);
}

void	fork_for_odd_nb_philo(t_data *data, t_philo *philo,
		pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->id % 2 != 0)
	{
		if (philo->time_last_meal - data->death_time > data->eat_time)
			waiting(data, data->eat_time);
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
		philo->first_fork_index = (philo->id + 1) % data->nb_philo;
		philo->second_fork_index = philo->id;
	}
	else
	{
		if (philo->time_last_meal - data->death_time > data->eat_time)
			waiting(data, data->eat_time);
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
		philo->first_fork_index = philo->id;
		philo->second_fork_index = (philo->id + 1) % data->nb_philo;
	}
}

void	fork_for_even_nb_philo(t_data *data, t_philo *philo,
		pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
		philo->first_fork_index = philo->id;
		philo->second_fork_index = (philo->id + 1) % data->nb_philo;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
		philo->first_fork_index = (philo->id + 1) % data->nb_philo;
		philo->second_fork_index = philo->id;
	}
}
