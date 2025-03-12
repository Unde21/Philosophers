/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:27:46 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/12 09:24:59 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

/*TODO ne pas protect les forks avec un mutex directement, passer par une variable 0/1 (sujet)
faire une fonction waiting qui fonctionne mieux : il y a un pb avec le data->eat_time
Faire un define de tout les print 
wait que tout les threads soit  creer au debut de philos_loop quit properly if one of them failed
-g3 -fsanitize=thread -pg

*/

long	get_current_time_ms(void)
{
	struct timeval current;
	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void safe_print(t_data *data, size_t id, char *str)
{
	if (data->someone_died == true)
		return ;
    pthread_mutex_lock(&data->mutex_print);
    printf("%ld %lu %s\n", get_current_time_ms() - data->start_time, id + 1, str);
    pthread_mutex_unlock(&data->mutex_print);
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
	pthread_mutex_destroy(&data->m_start_time);
	pthread_mutex_destroy(&data->m_start);
	free(data->forks);
	free(data->philos);
}

int		create_threads(t_data *data)
{
	size_t	i;

	i = 0;

	// data->race = 0;
	
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philos_loop, &data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->m_start);
			data->start = 2;
			pthread_mutex_unlock(&data->m_start);
			printf("Error: Failed to create thread\n");
			return (-1);
		}
		++i;
	}
	// pthread_mutex_lock(&data->m_start);
	data->start = 1;
	// pthread_mutex_unlock(&data->m_start);
	if (data->philos == NULL)
		printf("philos is NULL\n");
	if (pthread_create(&data->status_thread, NULL, status_loop, data) != 0) //TODO Virer le thread...
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
