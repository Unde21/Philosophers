/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:27:46 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/07 05:11:57 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

long	get_current_time_ms(void)
{
	struct timeval current;
	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void print(t_data *data, size_t id, char *str)
{
	if (data->someone_died == true)
		return ;
    pthread_mutex_lock(&data->mutex_print);
    printf("[%ld][%lu] %s\n", get_current_time_ms() - data->start_time, id + 1, str);
    pthread_mutex_unlock(&data->mutex_print);
}

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
		printf("[%ld][%lu] died\n", get_current_time_ms() - data->start_time, philo->id + 1);
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
        // usleep(1000);
    }
    return NULL;
}

void	*philos_loop(void *ptr)
{
	t_philo *philo;
	t_data *data;
	
	philo = (t_philo *)ptr;
	data = philo->data;
	if (philo->id % 2 != 0)
		usleep(100);
	while (1)
	{
		if (check_death(data, philo) == true)
			break;
		print(data, philo->id, "is thinking");
		if (philo->id %2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			print(data, philo->id, "has taken the left fork");
			pthread_mutex_lock(philo->right_fork);
			print(data, philo->id, "has taken the right fork");
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			print(data, philo->id, "has taken the right fork");
			pthread_mutex_lock(philo->left_fork);
			print(data, philo->id, "has taken the left fork");
		}
		print(data, philo->id, "is eating");
		pthread_mutex_lock(&data->mutex_death);
		philo->time_last_meal = get_current_time_ms();
		++philo->nb_meal;
		pthread_mutex_unlock(&data->mutex_death);
		usleep(data->eat_time * 1000);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		print(data, philo->id, "is sleeping");
		usleep(data->sleep_time * 1000);
	}
	return (NULL);
}
void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		++i;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_death);
	free(data->forks);
	free(data->philos);
}

int		create_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philos_loop, &data->philos[i]) != 0)
		{
			printf("Error: Failed to create thread\n");
			return (-1);
		}
		++i;
	}
	if (data->philos == NULL)
		printf("philos is NULL\n");
	if (pthread_create(&data->status_thread, NULL, status_loop, data) != 0)
	{
		printf("Error: Failed to create status thread\n");
		return (-1);
	}
	pthread_join(data->status_thread, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		++i;
	}
	free_data(data);
	return (0);
}
