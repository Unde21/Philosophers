/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:56:18 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/14 00:30:59 by samaouch         ###   ########lyon.fr   */
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
	if (data->m_fork_init == true)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->m_forks[i]);
			++i;
		}
	}
	if (data->m_print_init == true)
		pthread_mutex_destroy(&data->m_print);
	if (data->m_end_init == true)
		pthread_mutex_destroy(&data->m_end);
	if (data->m_start_time_init == true)
		pthread_mutex_destroy(&data->m_start_time);
	if (data->m_start_init == true)
		pthread_mutex_destroy(&data->m_start);
	if (data->m_forks != NULL)
		free(data->m_forks);
	if (data->philos != NULL)
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
