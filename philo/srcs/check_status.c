/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:23:59 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/12 15:46:56 by samaouch         ###   ########lyon.fr   */
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
        // pthread_mutex_lock(&data->mutex_death);
		data->someone_died = true;
		pthread_mutex_unlock(&data->mutex_death);
		pthread_mutex_lock(&data->mutex_print);
		printf("%ld %lu died\n", get_current_time_ms() - data->start_time, philo->id + 1);
		pthread_mutex_unlock(&data->mutex_print);
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
        return (false);
    while (i < data->nb_philo)
    {
        if (data->philos[i].nb_meal < (size_t)data->nb_eat)
            return (false);
		++i;
    }
    return (true);
}

void *status_loop(t_data *data, t_philo *philo)
{

    size_t	i;

    while (1)
    {
		i = 0;
        while(i < data->nb_philo)
        {
            if (check_death(data, &philo[i]) == true)
                return NULL;
            pthread_mutex_lock(&data->mutex_death);
            if (check_philo_ate_enough(data) == true)
            {
                data->someone_died = true;
                pthread_mutex_unlock(&data->mutex_death);
                return NULL;
            }
            pthread_mutex_unlock(&data->mutex_death);
			++i;
        }
        usleep(1000);
    }
    return NULL;
}
