/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:35:23 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/20 10:35:59 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

//BUG avec 1 sa fonctionne pas
static	void only_one(t_data *data, t_philo *philo)
{
	safe_print(data, philo[0].id, MSG_THINK);
	safe_print(data, philo[0].id, MSG_FORK);
	waiting(data, data->death_time, 1);
}

static void	routine_loop(t_data *data, t_philo *philo, size_t current)
{
	while (1)
	{
		if (handle_fork(data, philo, current) != 0)
			exit(0) ;
		safe_print(data, current, MSG_SLEEP);
		supervisor(data, philo, current);
		waiting(data, data->sleep_time, current);
	}
}
//Library
#include <stdio.h>
void	routine(t_data *data, size_t current)
{
	if (data->nb_philo == 1)
	{
		only_one(data, data->philos);
		exit(0) ;
	}
	if (current % 2 == 0)
	{
		safe_print(data, current, MSG_THINK);
		waiting(data, data->eat_time / 2, current);
	}
	routine_loop(data, data->philos, current);
	exit(0) ;
	
}
