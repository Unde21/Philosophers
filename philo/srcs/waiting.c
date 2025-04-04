/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:51:41 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/13 23:55:09 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(t_data *data, long time)
{
	long	start;
	long	elapsed;

	elapsed = 0;
	start = get_current_time_ms();
	while (elapsed < time)
	{
		pthread_mutex_lock(&data->m_end);
		if (data->someone_died == true)
		{
			pthread_mutex_unlock(&data->m_end);
			return ;
		}
		pthread_mutex_unlock(&data->m_end);
		usleep(250);
		elapsed = get_current_time_ms() - start;
	}
}

int	wait_start(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->m_start);
		if (data->start == ALL_THREAD_CREATED)
		{
			pthread_mutex_unlock(&data->m_start);
			pthread_mutex_lock(&data->m_start_time);
			if (data->start_time == 0)
				data->start_time = get_current_time_ms();
			pthread_mutex_unlock(&data->m_start_time);
			return (0);
		}
		pthread_mutex_unlock(&data->m_start);
		pthread_mutex_lock(&data->m_start);
		if (data->start == ERR_THREAD)
		{
			pthread_mutex_unlock(&data->m_start);
			return (-1);
		}
		pthread_mutex_unlock(&data->m_start);
		usleep(500);
	}
	return (0);
}
