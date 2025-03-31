/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:36:40 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/31 10:47:47 by samaouch         ###   ########lyon.fr   */
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

int	handle_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	bool			res;

	res = false;
	first_fork = NULL;
	second_fork = NULL;
	if (data->nb_philo % 2 == 0)
		fork_for_even_nb_philo(data, philo, &first_fork, &second_fork);
	else
		fork_for_odd_nb_philo(data, philo, &first_fork, &second_fork);
	while (res == false)
	{
		res = take_right_fork(data, philo, first_fork, second_fork);
		if (res == false)
			usleep(500);
	}
	return (0);
}
