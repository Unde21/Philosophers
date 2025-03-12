/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:23:59 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/12 09:27:22 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

bool	check_death(t_data *data, t_philo *philo)
{
	long	current_time;
	
	pthread_mutex_lock(&data->mutex_death);
	if (data->someone_died == true)
	{
		pthread_mutex_unlock(&data->mutex_death);
		return (true);
	}
	current_time = get_current_time_ms();
	if (current_time - philo->time_last_meal > data->death_time)
	{
		data->someone_died = true;
		pthread_mutex_unlock(&data->mutex_death);
		printf("%ld %lu died\n", get_current_time_ms() - data->start_time, philo->id + 1);
		return (true);
	}
	pthread_mutex_unlock(&data->mutex_death);
	return (false);
}

bool check_philo_ate_enough(t_data *data)
{
	size_t	i;

	i = 0;
    if (data->nb_eat == -1)
        return false;
    while (i < data->nb_philo)
    {
        if (data->philos[i].nb_meal < (size_t)data->nb_eat)
            return false;
		++i;
    }
    return true;
}

void *status_loop(void *ptr)
{
    t_data *data;
    t_philo *philos;
    size_t	i;

	data = (t_data *)ptr;
	philos = data->philos;
	// waiting(data, data->eat_time);
    while (1)
    {
		i = 0;
        while(i < data->nb_philo)
        {
            if (check_death(data, &philos[i]) == true)
                return NULL;
            if (check_philo_ate_enough(data) == true)
            {
                pthread_mutex_lock(&data->mutex_death);
                data->someone_died = true;
                pthread_mutex_unlock(&data->mutex_death);
                return NULL;
            }
			++i;
        }
        usleep(1000);
    }
    return NULL;
}
