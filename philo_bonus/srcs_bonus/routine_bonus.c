/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:35:23 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/19 13:49:38 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void only_one(t_data *data, t_philo *philo)
{
	safe_print(data, philo[0].id, MSG_THINK);
	//TODO Secure with semaphore FORK ?
	safe_print(data, philo[0].id, MSG_FORK);
	waiting(data, data->death_time);
	//TODO close semaphore ?
}
//TODO libraryyyyyyy
#include <stdio.h>
#include <stdlib.h>
static void	routine_loop(t_data *data, t_philo *philo, size_t current)
{
	while (1)
	{
		// sem_wait(data->death_lock);
		// // if (philo->philos_alive == false)
		// // {
		// // 	sem_post(data->death_lock);
		// // 	exit(0);
		// // }
		// sem_post(data->death_lock);
		if (handle_fork(data, philo, current) != 0)
			exit(0) ;
		safe_print(data, current, MSG_SLEEP);
		waiting(data, data->sleep_time);
	}
}
//Library
#include <stdio.h>
void	routine(t_data *data, size_t current)
{
	// if (wait_start(data) != 0)
	// 	return ;
	if (data->nb_philo == 1)
	{
		only_one(data, data->philos);
		exit(0) ;
	}
	if (current % 2 == 0)
	{
		safe_print(data, current, MSG_THINK);
		waiting(data, data->eat_time / 2);
	}
	routine_loop(data, data->philos, current);
	exit(0) ;
	
}
