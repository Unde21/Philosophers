/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:56:18 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/13 20:35:44 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->m_forks[i]);
		++i;
	}
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_end);
	pthread_mutex_destroy(&data->m_start_time);
	pthread_mutex_destroy(&data->m_start);
	free(data->m_forks);
	free(data->philos);
}

long	get_current_time_ms(void)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL) == 1)
		return (-1);
	else
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
