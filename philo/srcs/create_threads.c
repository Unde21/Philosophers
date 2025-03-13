/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:27:46 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/13 23:55:53 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	proccess_creation_loop(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, start_routine,
				&data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->m_start);
			data->start = ERR_THREAD;
			pthread_mutex_unlock(&data->m_start);
			while (i != 0)
			{
				pthread_join(data->philos[i].thread, NULL);
				--i;
			}
			ft_putstr_fd(ERR_MSG_THREAD, 2);
			return (-1);
		}
		++i;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	size_t	i;

	i = 0;
	if (proccess_creation_loop(data) != 0)
		return (-1);
	pthread_mutex_lock(&data->m_start);
	data->start = ALL_THREAD_CREATED;
	pthread_mutex_unlock(&data->m_start);
	supervisor(data, data->philos);
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		++i;
	}
	free_data(data);
	return (0);
}
