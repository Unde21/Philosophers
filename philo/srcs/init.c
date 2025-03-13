/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:19:19 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/14 00:32:04 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static bool	init_mutex(t_data *data)
{
	data->m_start_init = true;
	data->m_start_time_init = true;
	data->m_print_init = true;
	data->m_end_init = true;
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
	{
		data->m_print_init = false;
		return (false);
	}
	if (pthread_mutex_init(&data->m_end, NULL) != 0)
	{
		data->m_end_init = false;
		return (false);
	}
	if (pthread_mutex_init(&data->m_start, NULL) != 0)
	{
		data->m_start_init = false;
		return (false);
	}
	if (pthread_mutex_init(&data->m_start_time, NULL) != 0)
	{
		data->m_start_time_init = false;
		return (false);
	}
	return (true);
}

static bool	init_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL) != 0)
		{
			ft_putstr_fd(ERR_INIT_MUTEX, 2);
			while (i != 0)
			{
				pthread_mutex_destroy(&data->m_forks[i]);
				--i;
			}
			return (false);
		}
		++i;
	}
	data->m_fork_init = true;
	return (true);
}

static void	init_struct_philos(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].nb_meal = 0;
		data->philos[i].time_last_meal = data->start_time;
		data->philos[i].left_fork = &data->m_forks[i];
		data->philos[i].right_fork = &data->m_forks[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		++i;
	}
}

static bool	init_threads(t_data *data)
{
	data->m_fork_init = false;
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (data->m_forks == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		return (false);
	}
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (data->philos == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		free(data->m_forks);
		return (false);
	}
	if (init_forks(data) == false)
	{
		free_data(data);
		return (false);
	}
	init_struct_philos(data);
	return (true);
}

bool	init_data(t_data *data, int ac, char **av)
{
	data->start = 0;
	data->nb_philo = ft_atoi(av[1], 0);
	if (data->nb_philo > 2000)
	{
		ft_putstr_fd(TOO_MANY_PHILO, 2);
		return (false);
	}
	data->death_time = ft_atoi(av[2], 0);
	data->eat_time = ft_atoi(av[3], 0);
	data->sleep_time = ft_atoi(av[4], 0);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5], 0);
	else
		data->nb_eat = -1;
	data->start_time = get_current_time_ms();
	if (data->start_time == -1)
		return (false);
	data->someone_died = false;
	if (check_value(data) == false)
		return (false);
	if (init_mutex(data) == false)
		return (false);
	if (init_threads(data) == false)
		return (false);
	return (true);
}
