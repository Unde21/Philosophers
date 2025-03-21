/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:59:38 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/21 12:08:56 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>

bool	check_death(t_data *data, t_philo *philo, size_t current)
{
	long	current_time;

	current_time = get_current_time_ms();
	sem_wait(data->death_lock);
	if (current_time - philo->time_last_meal > data->death_time)
	{
		philo->philos_alive = false;
		sem_wait(data->print_lock);
		printf("%ld %lu died\n", current_time - data->start_time, current + 1);
		sem_post(data->print_lock);
		return (true);
	}
	sem_post(data->death_lock);
	return (false);
}

static bool	check_philo_ate_enough(t_data *data, t_philo *philo, size_t current)
{
	size_t	i;

	i = 0;
	(void)current;
	if (data->nb_eat == -1)
		return (false);
	if (philo->nb_meal < (size_t)data->nb_eat + 1)
		return (false);
	return (true);
}

// void	supervisor(t_data *data, t_philo *philo, size_t current)
// {
// 	if (check_death(data, philo, current) == true)
// 	{
// 		sem_post(data->sem_end);
// 		clear_data(data);
// 		exit(0);
// 	}
// 	else if (check_philo_ate_enough(data, philo, current) == true)
// 	{
// 		sem_post(data->sem_end);
// 		clear_data(data);
// 		exit(0);
// 	}
// }

void	*supervisor(void *ptr)
{
	t_philo	*philo;
	t_data *data;
	
	philo = (t_philo *)ptr;
	data = philo->data;
	while (1)
	{
		if (check_death(data, philo, philo->id) == true)
		{
			sem_post(data->sem_end);
			// clear_data(data);
			// kill_all(data);

			exit(0);
			break ;
		}
		else if (check_philo_ate_enough(data, philo, philo->id) == true)
		{
			sem_post(data->sem_end);
			// // clear_data(data);
			// exit(0);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
