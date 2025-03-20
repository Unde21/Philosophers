/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:43:16 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/20 10:23:03 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	waiting(t_data *data, long time, size_t current)
{
	long	start;
	long	elapsed;
	
	elapsed = 0;
	start = get_current_time_ms();
	while (elapsed < time)
	{
		supervisor(data, data->philos, current);
		sem_wait(data->death_lock);
		if (data->philos->philos_alive == false)
		{
			sem_post(data->death_lock);
			return ;
		}
		sem_post(data->death_lock);
		usleep(250);
		elapsed = get_current_time_ms() - start;
	}
}

int	wait_start(t_data *data)
{
	while (1)
	{
		sem_wait(data->start_lock);
		if (data->start == ALL_PROCESS_CREATED)
		{
			sem_post(data->start_lock);
			return (0);
		}
		if (data->start == ERR_PROCESS)
		{
			sem_post(data->start_lock);
			return (-1);
		}
		sem_post(data->start_lock);
		usleep(500);
	}
	return (0);
}
