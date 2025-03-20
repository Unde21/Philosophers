/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:33:58 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/20 12:57:27 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eating(t_data *data, t_philo *philo, size_t current)
{
	philo[current].time_last_meal = get_current_time_ms();
	safe_print(data, current, MSG_EATING);
	++philo[current].nb_meal;
	waiting(data, data->eat_time, current);
}
#include <stdio.h>
#include <stdlib.h>
int	handle_fork(t_data *data, t_philo *philo, size_t current)
{
	// long current_time = get_current_time_ms();
	// long time_since_last_meal = current_time - philo[current].time_last_meal;
	// long time_until_death = data->death_time - time_since_last_meal;

	
    // if (time_until_death <= 0 || time_until_death < data->eat_time + 100)
    // {
	// 	printf("aled\n");
	// 	printf("%ld %lu died\n", current_time - data->start_time, current + 1);
	// 	sem_post(data->sem_end);
	// 	clear_data(data);
	// 	exit(0);
    // }
	supervisor(data, philo, current);
	sem_wait(data->forks);
	safe_print(data, current, MSG_FORK);
	sem_wait(data->forks);
	safe_print(data, current, MSG_FORK);
	supervisor(data, philo, current);
	eating(data, philo, current);
	sem_post(data->forks);
	sem_post(data->forks);
	return (0);
}
