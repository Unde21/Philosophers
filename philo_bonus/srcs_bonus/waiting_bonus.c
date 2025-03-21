/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:43:16 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/21 13:57:53 by samaouch         ###   ########lyon.fr   */
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
		(void)current;
		(void)data;
		usleep(100);
		elapsed = get_current_time_ms() - start;
	}
}

// int	wait_start(t_data *data)
// {
	// while (1)
	// {
	// 	sem_wait(data->start_lock);
	// 	if (data->start == ALL_PROCESS_CREATED)
	// 	{
	// 		sem_post(data->start_lock);
	// 		return (0);
	// 	}
	// 	if (data->start == ERR_PROCESS)
	// 	{
	// 		sem_post(data->start_lock);
	// 		return (-1);
	// 	}
	// 	sem_post(data->start_lock);
	// 	usleep(500);
	// }
// 	while (1)
// 	{
// 		if (sem_wait(data->sem_start) == 0)
// 		{
// 			sem_post(data->sem_start);
// 			return (0);
// 		}
// 	}
// 	return (0);
// }
