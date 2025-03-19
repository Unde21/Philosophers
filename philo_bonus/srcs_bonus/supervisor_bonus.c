/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:59:38 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/19 13:50:33 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>

static bool check_death(t_data *data, t_philo *philo, size_t current)
{
	long	current_time;

	current_time = get_current_time_ms();
	sem_wait(data->death_lock);
	if (current_time - philo[current - 1].time_last_meal > data->death_time)
	{
		// printf("elapsed : %zu\n", philo[current - 1].time_last_meal);

		// printf("death : id: : %zu\n", philo[current - 1].id);
		// printf("elapsed in condition : %zu\n", current_time - philo->time_last_meal[current - 1]);
		philo->philos_alive = false;
		sem_wait(data->print_lock);
		printf("%ld %lu died\n", current_time - data->start_time, current);
		sem_post(data->death_lock);
		sem_post(data->print_lock);
		return (true);
	}
	sem_post(data->death_lock);
	return (false);
}

static bool check_philo_ate_enough(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->nb_eat == -1)
		return (false);
	while (i < data->nb_philo)
	{
		if (data->philos[i].nb_meal < (size_t)data->nb_eat + 1)
			return (false);
		++i;
	}
	return (true);
}
//TODO library
#include <stdlib.h>

void	supervisor(t_data *data)
{
	size_t	i;
	
	while (data->philos->philos_alive == true)
	{
		i = 1;
		while (i < data->nb_philo)
		{
			if (check_death(data, data->philos, i) == true)
			{
				sem_post(data->sem_end);
				// kill_all(data, data->nb_philo + 1);
				return ;
			}
			sem_wait(data->death_lock);
			if (check_philo_ate_enough(data) == true)
			{
				data->philos->philos_alive = false;
				sem_post(data->death_lock);
				return ;
			}
			sem_post(data->death_lock);
			++i;
		}
	}
	return ;
}
