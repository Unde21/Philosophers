/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:23:00 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/12 21:58:00 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
void	eating(t_data *data, t_philo *philo)
{
	safe_print(data, philo->id, "is eating", YELLOW);
	waiting(data, data->eat_time);
	pthread_mutex_lock(&data->mutex_death);
	++philo->nb_meal;
	philo->time_last_meal = get_current_time_ms();
	pthread_mutex_unlock(&data->mutex_death);
	// printf("Philo %zu: updated last_meal to %ld\n", philo->id + 1, philo->time_last_meal);
}
#include <stdio.h>
int	handle_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t *second_fork;
	
	// if (philo->id % 2 == 0)
	// {
	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
		// pthread_mutex_lock(philo->left_fork);
		// safe_print(data, philo->id, "has taken a fork", GREEN);
		// pthread_mutex_lock(philo->right_fork);
		// safe_print(data, philo->id, "has taken a fork", GREEN);	
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	safe_print(data, philo->id, "has taken a fork", GREEN);
	pthread_mutex_lock(second_fork);
	safe_print(data, philo->id, "has taken a fork", GREEN);
	// }
	// else
	// {
	// 	pthread_mutex_lock(philo->right_fork);
	// 	safe_print(data, philo->id, "has taken a fork", GREEN);
	// 	pthread_mutex_lock(philo->left_fork);
	// 	safe_print(data, philo->id, "has taken a fork", GREEN);
	// }
	if (data->someone_died == true)
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (-1);
	}
	// printf("philo : %zu\n", philo->id + 1);

	eating(data, philo);
	// if (data->someone_died == true)
	// {
	// 	pthread_mutex_unlock(philo->left_fork);
	// 	pthread_mutex_unlock(philo->right_fork);
	// 	return (-1);
	// }
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return (0);
}

void	only_one(t_data *data, t_philo *philo)
{
	safe_print(data, philo->id, "is thinking", MAGENTA);
	pthread_mutex_lock(philo->left_fork);
	safe_print(data, philo->id, "has taken a fork", GREEN);
	waiting(data, data->death_time);
	pthread_mutex_unlock(philo->left_fork);
}
// #include <stdio.h>
void	*philos_loop(void *ptr)
{
	t_philo *philo;
	t_data *data;
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
		safe_print(data, philo->id, "is thinking", MAGENTA);
		waiting(data, data->eat_time / 2);
	}
	while (1)
	{
		pthread_mutex_lock(&data->mutex_death);
		if (data->someone_died == true)
		{
			pthread_mutex_unlock(&data->mutex_death);
			break;
		}
		pthread_mutex_unlock(&data->mutex_death);
		if (first_think == false)
			safe_print(data, philo->id, "is thinking", MAGENTA);
		first_think = false;
		if (handle_fork(data, philo) != 0)
			break;
		safe_print(data, philo->id, "is sleeping", BLUE);
		waiting(data, data->sleep_time);
	}
	return (NULL);
}
