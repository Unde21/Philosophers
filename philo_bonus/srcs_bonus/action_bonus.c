/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:33:58 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/21 13:51:42 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eating(t_data *data, t_philo *philo, size_t current)
{
	sem_wait(data->death_lock);
	philo[current].time_last_meal = get_current_time_ms();
	sem_post(data->death_lock);
	safe_print(data, current, MSG_EATING);
	++philo[current].nb_meal;
	waiting(data, data->eat_time, current);
}

void	handle_fork(t_data *data, t_philo *philo, size_t current)
{
	sem_wait(data->eating_limit);
	sem_wait(data->forks);
	safe_print(data, current, MSG_FORK);
	sem_wait(data->forks);
	safe_print(data, current, MSG_FORK);
	eating(data, philo, current);
	sem_post(data->forks);
	sem_post(data->forks);
	sem_post(data->eating_limit);
}
