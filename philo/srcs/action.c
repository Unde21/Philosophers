/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:36:40 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/14 00:03:28 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_data *data, t_philo *philo)
{
	safe_print(data, philo->id, MSG_EATING);
	pthread_mutex_lock(&data->m_end);
	++philo->nb_meal;
	philo->time_last_meal = get_current_time_ms();
	pthread_mutex_unlock(&data->m_end);
	waiting(data, data->eat_time);
}

static int	take_right_fork(t_data *data, t_philo *philo,
	pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	safe_print(data, philo->id, MSG_FORK);
	pthread_mutex_lock(second_fork);
	safe_print(data, philo->id, MSG_FORK);
	pthread_mutex_lock(&data->m_end);
	if (data->someone_died == true)
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(&data->m_end);
		return (-1);
	}
	pthread_mutex_unlock(&data->m_end);
	eating(data, philo);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return (0);
}

int	handle_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
		{
			first_fork = philo->left_fork;
			second_fork = philo->right_fork;
		}
		else
		{
			first_fork = philo->right_fork;
			second_fork = philo->left_fork;
		}
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	if (take_right_fork(data, philo, first_fork, second_fork) != 0)
		return (-1);
	return (0);
}
