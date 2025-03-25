/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:33:58 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/25 10:01:07 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eating(t_data *data, t_philo *philo, size_t current)
{
	sem_wait(data->print_lock);
	philo[current].time_last_meal = get_current_time_ms();
	sem_post(data->print_lock);
	safe_print(data, current, MSG_EATING);
	sem_wait(data->print_lock);
	++philo[current].nb_meal;
	sem_post(data->print_lock);
	waiting(data->eat_time);
}

void	handle_fork(t_data *data, t_philo *philo, size_t current)
{
	if (data->nb_philo % 2 != 0 && philo->time_last_meal > data->death_time / 2)
		waiting(data->eat_time);
	sem_wait(data->forks);
	safe_print(data, current, MSG_FORK);
	sem_wait(data->forks);
	safe_print(data, current, MSG_FORK);
	eating(data, philo, current);
	sem_post(data->forks);
	sem_post(data->forks);
}
