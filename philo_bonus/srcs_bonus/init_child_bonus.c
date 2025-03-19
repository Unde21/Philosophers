/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:32:35 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/19 11:45:50 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <sys/wait.h>

//TODO lib
#include <stdio.h>
#include <stdlib.h>
void	kill_all (t_data *data, size_t i)
{
	while (i > 0)
	{
		if (data->pid[i] > 0)
			kill(data->pid[i], SIGKILL);
		--i;
	}
}

static int	child_creation_loop(t_data *data)
{
	size_t	i;

	i = 0;
	while (i <= data->nb_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			data->start = ERR_PROCESS;
			ft_putstr_fd(ERR_FORK, 2);
			kill_all(data, i);
			return (-1);
		}
		if (data->pid[i] == 0)
		{
			if (i == 0)
				supervisor(data);
			else
				routine(data, i);
			exit(0);
		}
		++i;
	}
	data->start = ALL_PROCESS_CREATED;
	return (0);
}

int	init_child(t_data *data)
{
	size_t	i;
	int	status;
	i = 0;
	if (child_creation_loop(data) != 0)
		return (-1);
	
	sem_wait(data->sem_end);
	kill_all(data, data->nb_philo);
	kill(data->pid[0], SIGKILL);
	while(waitpid(-1, &status, 0) > 0);
	// while (i <= data->nb_philo)
	// {
	// 	waitpid(data->pid[i], NULL, 0);
	// 	++i;
	// }
	clear_data(data);
	return (0);
}
