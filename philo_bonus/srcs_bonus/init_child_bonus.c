/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:32:35 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/22 11:11:54 by samaouch         ###   ########lyon.fr   */
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
	data->start_time = get_current_time_ms() ;
	while (i < data->nb_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			data->start = ERR_PROCESS;
			ft_putstr_fd(ERR_FORK, 2);
			data->nb_philo = i;
			// kill_all(data);
			sem_post(data->sem_end);
			return (-1);
		}
		if (data->pid[i] == 0)
			routine(data, i);
		++i;
	}
	return (0);
}

	
int	init_child(t_data *data)
{
	size_t	i;
	// int	status;
	i = 0;
	// sem_post(data->sem_end);
	// sem_wait(data->sem_end);
	// if (child_creation_loop(data) != 0)
	// 	return (-1);
	child_creation_loop(data);
	// while(waitpid(-1, &status, 0) > 0)
	// {
	// 	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	// 		break ;
	// }
	waitpid(-1, NULL, 0);

	sem_wait(data->sem_end);
	
	// waitpid(-1, NULL, 0);
	kill_all(data);
	kill(data->pid[0], SIGKILL);
	clear_data(data);
	return (0);
}
