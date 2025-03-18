/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:11:01 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/18 12:42:12 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>

void	safe_print(t_data *data, size_t id, char *str)
{
	long	current_time;

	sem_wait(data->death_lock);
	if (data->philos->philos_alive == true)
	{
		sem_post(data->death_lock);
		return ;
	}
	current_time = get_current_time_ms() - data->start_time;
	sem_wait(data->print_lock);
	sem_post(data->death_lock);
	printf("%ld %lu %s\n", current_time, id + 1, str);
	sem_post(data->print_lock);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
