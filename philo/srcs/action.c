/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:36:40 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/04 12:50:54 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_data *data, t_philo *philo)
{
	safe_print(data, philo->id, MSG_EATING);
	pthread_mutex_lock(&data->m_end);
	++philo->nb_meal;
	philo->time_last_meal = get_current_time_ms();
	pthread_mutex_unlock(&data->m_end);
	waiting(data, data->eat_time);
}

static void	fork_for_odd_nb_philo(t_data *data, t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		if (philo->time_last_meal - data->death_time > data->eat_time)
			waiting(data, data->eat_time);
		philo->first_fork_index = (philo->id + 1) % data->nb_philo;
		philo->second_fork_index = philo->id;
	}
	else
	{
		if (philo->time_last_meal - data->death_time > data->eat_time)
			waiting(data, data->eat_time);
		philo->first_fork_index = philo->id;
		philo->second_fork_index = (philo->id + 1) % data->nb_philo;
	}
}

static void	fork_for_even_nb_philo(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork_index = philo->id;
		philo->second_fork_index = (philo->id + 1) % data->nb_philo;
	}
	else
	{
		philo->first_fork_index = (philo->id + 1) % data->nb_philo;
		philo->second_fork_index = philo->id;
	}
}

int	handle_fork(t_data *data, t_philo *philo)
{
	if (data->nb_philo % 2 == 0)
		fork_for_even_nb_philo(data, philo);
	else
		fork_for_odd_nb_philo(data, philo);
	if (take_right_fork(data, philo) == false)
		return (-1);
	return (0);
}
