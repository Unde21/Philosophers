/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:23:00 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/12 15:43:55 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_data *data, t_philo *philo)
{
	safe_print(data, philo->id, "is eating");
	pthread_mutex_lock(&data->mutex_death);
	philo->time_last_meal = get_current_time_ms();
	++philo->nb_meal;
	pthread_mutex_unlock(&data->mutex_death);
	waiting(data, data->eat_time);
}

int	handle_fork(t_data *data, t_philo *philo)
{
	if (data->nb_philo % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		safe_print(data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print(data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		safe_print(data, philo->id, "has taken a fork");
	}
	if (check_death(data, philo) == true)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	eating(data, philo);
	if (check_death(data, philo) == true)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	only_one(t_data *data, t_philo *philo)
{
	safe_print(data, philo->id, "is thinking");
	pthread_mutex_lock(philo->left_fork);
	safe_print(data, philo->id, "has taken a fork");
	waiting(data, data->death_time);
	pthread_mutex_unlock(philo->left_fork);
}
void	*philos_loop(void *ptr)
{
	t_philo *philo;
	t_data *data;
	
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
		usleep(data->eat_time / 2);
	while (1)
	{
		if (check_death(data, philo) == true)
			break;
		safe_print(data, philo->id, "is thinking");
		if (handle_fork(data, philo) != 0)
			break;
		safe_print(data, philo->id, "is sleeping");
		waiting(data, data->sleep_time);
		// if (check_death(data, philo) == true)
		// 	break;
	}
	return (NULL);
}


