/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:59:38 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/26 15:20:49 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>

bool	check_death(t_data *data, t_philo *philo, size_t current)
{
	long	current_time;

	sem_wait(data->print_lock);
	current_time = get_current_time_ms();
	if (current_time - philo->time_last_meal > data->death_time)
	{
		printf("%ld %lu died\n", current_time - data->start_time, current + 1);
		return (true);
	}
	sem_post(data->print_lock);
	return (false);
}

static bool	check_philo_ate_enough(t_data *data, t_philo *philo)
{
	size_t	i;

	i = 0;
	if (data->nb_eat == -1)
	{
		return (false);
	}
	sem_wait(data->print_lock);
	if (philo->nb_meal < (size_t)data->nb_eat)
	{
		sem_post(data->print_lock);
		return (false);
	}
	sem_post(data->print_lock);
	return (true);
}

static void	make_sem_end_max(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		sem_post(data->sem_end);
		++i;
	}
}

void	*supervisor(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	while (1)
	{
		if (check_death(data, philo, philo->id) == true)
		{
			make_sem_end_max(data);
			clear_data(data);
			exit(0);
		}
		else if (check_philo_ate_enough(data, philo) == true)
		{
			sem_post(data->sem_end);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
