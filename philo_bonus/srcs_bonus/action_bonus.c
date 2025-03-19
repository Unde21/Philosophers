/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:33:58 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/19 13:50:08 by samaouch         ###   ########lyon.fr   */
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
	++philo[current - 1].nb_meal;
	philo[current - 1].time_last_meal = get_current_time_ms();
	// printf("elapsed before waiting : %zu\n", get_current_time_ms() - philo->time_last_meal[current - 1]);
	// sem_post(data->death_lock);
	waiting(data, data->eat_time);
	// printf("elapsed after waiting : %zu\n", get_current_time_ms() - philo->time_last_meal[current - 1]);
	//TODO faire des thread supervisor pour chaque child 

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
