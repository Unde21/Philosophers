/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:27:46 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/06 04:57:41 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void	*philo_routine(void *ptr)
{
	t_data	*data;
	size_t	id;

	data = (t_data *)ptr;
	id = data->id;
	while (data->is_alive == true 
		|| (data->nb_eat <= data->meal_count 
		&& data->nb_eat != -1 && data->is_alive == true))
	{
		printf("Philo %lu is thinking\n", id);
		usleep(data->sleep_time);
		//TODO start get_time
		pthread_mutex_lock(&data->forks[id]);
		printf("Philo %lu take the left fork\n", id);
		pthread_mutex_lock(&data->forks[(id + 1) % data->nb_philo]);
		printf("Philo %lu take the right fork\n", id);
		//TODO compare current time avec start_time si la dif est > a death_time = data->is_alive = false .. print dead and quit
		printf("Philo %lu is eating\n", id);
		usleep(data->eat_time);
		++data->meal_count;
		pthread_mutex_unlock(&data->forks[id]);
		pthread_mutex_unlock(&data->forks[(id + 1) % data->nb_philo]);
	}
	return (NULL);
}

void	destroy_mutex(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		++i;
	}
}

void	init_threads(t_data *data)
{
	pthread_t	*philo;
	t_data		*philos;
	size_t		i;

	philo = malloc(sizeof(pthread_t) * data->nb_philo);
	if (philo == NULL)
		return ;
	philos = malloc(sizeof(t_data) * data->nb_philo);
	if (philos == NULL)
	{
		free(philo);
		return ;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i] = *data;
		philos[i].id = i;
		philos[i].meal_count = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		++i;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo[i], NULL, philo_routine, &philos[i]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			while (i > 0)
				pthread_join(philo[--i], NULL);
			free(philos);
			free(philo);
			return ;
		}
		++i;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i], NULL);
		++i;
	}
	destroy_mutex(data);
	free(philos);
	free(philo);
	free(data->forks);
}
