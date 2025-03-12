/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:23:00 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/12 09:24:54 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(t_data *data, long time)
{
	long	start;

	start = get_current_time_ms();
	while (get_current_time_ms() - start < time)
	{
		pthread_mutex_lock(&data->mutex_death);
		if (data->someone_died == true)
		{
			pthread_mutex_unlock(&data->mutex_death);
			return ;
		}
		pthread_mutex_unlock(&data->mutex_death);
		usleep(1000);
	}
}
int	 wait_start(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->m_start);
		if (data->start == 1)
		{
			pthread_mutex_unlock(&data->m_start);
			pthread_mutex_lock(&data->m_start_time);
			if (data->start_time == 0)
				data->start_time = get_current_time_ms();
			pthread_mutex_unlock(&data->m_start_time);
			return (0);
		}
		pthread_mutex_unlock(&data->m_start);
		pthread_mutex_lock(&data->m_start);
		if (data->start == 2)
		{
			pthread_mutex_unlock(&data->m_start);
			return (-1);
		}
		pthread_mutex_unlock(&data->m_start);
		usleep(100);
	}
	return (0);
}

void	*philos_loop(void *ptr)
{
	t_philo *philo;
	t_data *data;
	
	philo = (t_philo *)ptr;
	data = philo->data;
	if (wait_start(data) != 0)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(data->eat_time / 2);
	while (data->someone_died == false)
	{
		// ++data->race;
		if (data->nb_philo == 1)
		{
			safe_print(data, philo->id, "is thinking");
			pthread_mutex_lock(philo->left_fork);
			safe_print(data, philo->id, "has taken a fork");
			waiting(data, data->death_time);
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		if (check_death(data, philo) == true)
			break;
		safe_print(data, philo->id, "is thinking");
		// if (data->nb_philo % 2 == 1)
		// 	waiting(data, data->eat_time / 10);
		// if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			safe_print(data, philo->id, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			safe_print(data, philo->id, "has taken a fork");
		}
		// else
		// {
		// 	pthread_mutex_lock(philo->right_fork);
		// 	safe_print(data, philo->id, "has taken a fork");
		// 	pthread_mutex_lock(philo->left_fork);
		// 	safe_print(data, philo->id, "has taken a fork");
		// }
		safe_print(data, philo->id, "is eating");
		pthread_mutex_lock(&data->mutex_death);
		philo->time_last_meal = get_current_time_ms();
		++philo->nb_meal;
		pthread_mutex_unlock(&data->mutex_death);
		waiting(data, data->eat_time);
		// usleep(data->eat_time);
		// if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		// else
		// {
		// 	pthread_mutex_unlock(philo->left_fork);
		// 	pthread_mutex_unlock(philo->right_fork);
		// }
		safe_print(data, philo->id, "is sleeping");
		waiting(data, data->sleep_time);
	}
	return (NULL);
}
