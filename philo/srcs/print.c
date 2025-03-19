/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:28:22 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/19 13:33:52 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	safe_print(t_data *data, size_t id, char *str)
{
	long	current_time;

	pthread_mutex_lock(&data->m_end);
	if (data->someone_died == true)
	{
		pthread_mutex_unlock(&data->m_end);
		return ;
	}
	current_time = get_current_time_ms() - data->start_time;
	pthread_mutex_lock(&data->m_print);
	pthread_mutex_unlock(&data->m_end);
	printf("%ld %lu %s\n", current_time, id + 1, str);
	pthread_mutex_unlock(&data->m_print);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
