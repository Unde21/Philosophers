/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:13:25 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/20 10:36:19 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	clear_data(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print_lock);
	sem_close(data->death_lock);
	sem_close(data->sem_end);
	sem_unlink("/sem_end");
	sem_unlink("/death_lock");
	sem_unlink("/forks");
	sem_unlink("/print_lock");
	if (data->pid != NULL)
		free(data->pid);
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
