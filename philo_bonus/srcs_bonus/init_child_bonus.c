/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:32:35 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/21 12:06:04 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

void	kill_all (t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->pid[i] > 0)
			kill(data->pid[i], SIGKILL);
		++i;
	}
}

static int	child_creation_loop(t_data *data)
{
	size_t	i;

	i = 0;
	data->start_time = get_current_time_ms() + 250;
	while (i < data->nb_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			data->start = ERR_PROCESS;
			ft_putstr_fd(ERR_FORK, 2);
			data->nb_philo = i;
			kill_all(data);
			return (-1);
		}
		if (data->pid[i] == 0)
		{
			// sem_post(data->start_lock);
			// sem_wait(data->sem_start);
			routine(data, i);
			exit(0);
		}
		++i;
	}
	// sem_post(data->start_lock);
	// i = 0;
	// while (i < data->nb_philo)
	// {
	// 	sem_wait(data->start_lock);
	// 	usleep(250);
	// 	++i;
	// }
	i = 0;
	// data->start_time = get_current_time_ms();
	// while (i < data->nb_philo)
	// {
	// 	sem_post(data->sem_start);
	// 	++i;
	// }
	// data->start = ALL_PROCESS_CREATED;
	return (0);
}

int	init_child(t_data *data)
{
	size_t	i;
	// int	status;
	i = 0;
	if (child_creation_loop(data) != 0)
		return (-1);
	sem_wait(data->sem_end);
	// while(waitpid(-1, &status, 0) > 0);
	kill_all(data);
	kill(data->pid[0], SIGKILL);
	clear_data(data);
	return (0);
}
