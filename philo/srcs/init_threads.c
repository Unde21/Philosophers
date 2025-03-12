/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:27:46 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/12 21:26:15 by samaouch         ###   ########lyon.fr   */
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
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void safe_print(t_data *data, size_t id, char *str, char *color_code)
{
    pthread_mutex_lock(&data->mutex_death);
	if (data->someone_died == true)
	{
		pthread_mutex_unlock(&data->mutex_death);
		return ;
	}
    pthread_mutex_lock(&data->mutex_print);
    pthread_mutex_unlock(&data->mutex_death);
	if (ft_strcmp(color_code, BLUE) == 0)
   	 printf("\033[34m%ld %lu %s\033[0m\n", get_current_time_ms() - data->start_time, id + 1, str);
	else if (ft_strcmp(color_code, RED) == 0)
   		printf("\033[31m%ld %lu %s\033[0m\n", get_current_time_ms() - data->start_time, id + 1, str);
	else if (ft_strcmp(color_code, GREEN) == 0)
   		printf("\033[32m%ld %lu %s\033[0m\n", get_current_time_ms() - data->start_time, id + 1, str);
	else if (ft_strcmp(color_code, YELLOW) == 0)
   		printf("\033[33m%ld %lu %s\033[0m\n", get_current_time_ms() - data->start_time, id + 1, str);
	else if (ft_strcmp(color_code, MAGENTA) == 0)
   		printf("\033[35m%ld %lu %s\033[0m\n", get_current_time_ms() - data->start_time, id + 1, str);
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
	// pthread_mutex_destroy(data->philos->right_fork);
	// pthread_mutex_destroy(data->philos->left_fork);
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
			pthread_mutex_lock(&data->m_start);
			data->start = 2;
			pthread_mutex_unlock(&data->m_start);
			printf("Error: Failed to create thread\n");
			return (-1);
		}
		++i;
	}
	pthread_mutex_lock(&data->m_start);
	data->start = 1;
	pthread_mutex_unlock(&data->m_start);
	// if (data->philos == NULL)
	// 	printf("philos is NULL\n");
	// if (pthread_create(&data->status_thread, NULL, status_loop, data) != 0) //TODO Virer le thread...
	// {
	// 	printf("Error: Failed to create status thread\n");
	// 	return (-1);
	// }
	status_loop(data, data->philos);
	// pthread_join(data->status_thread, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		++i;
	}
	free_data(data);
	return (0);
}
