/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:33:58 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/19 12:22:31 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// TODO protect with semaphore ?
#include <stdio.h>
static void eating(t_data *data, t_philo *philo, size_t current)
{
	// printf("id: : %zu\n", philo[current - 1].id);
	safe_print(data, current, MSG_EATING);
	// sem_wait(data->death_lock);
	++philo->nb_meal[current - 1];
	philo->time_last_meal[current - 1] = get_current_time_ms();
	// printf("elapsed before waiting : %zu\n", get_current_time_ms() - philo->time_last_meal[current - 1]);
	// sem_post(data->death_lock);
	waiting(data, data->eat_time);
	// printf("elapsed after waiting : %zu\n", get_current_time_ms() - philo->time_last_meal[current - 1]);

}

//library
#include <stdio.h>
//BUG
int	handle_fork(t_data *data, t_philo *philo, size_t current)
{
	sem_wait(data->forks);
	safe_print(data, current, MSG_FORK);
	sem_wait(data->forks);
	safe_print(data, current, MSG_FORK);
	eating(data, philo, current);
	sem_post(data->forks);
	sem_post(data->forks);
	return (0);
}
