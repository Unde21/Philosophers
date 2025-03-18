/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:43:16 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/18 11:10:33 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	waiting(t_data *data, long time)
{
	long	start;
	long	elapsed;
	
	elapsed = 0;
	start = get_current_time_ms();
	while (elapsed < time)
	{
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
