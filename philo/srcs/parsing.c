/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:42:45 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/07 04:46:54 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static bool	is_integer(char *s)
{
	size_t	i;
	int		check_error;

	check_error = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		++i;
	}
	ft_atoi(s, &check_error);
	if (check_error != 0)
		return (false);
	return (true);
}

static bool	check_value(t_data *data)
{
	if (data->nb_philo == 0)
	{
		ft_putstr_fd("Invalid numbers of Philosophers\n", 2);
		return (false);
	}
	if (data->death_time < MIN_TIME)
	{
		ft_putstr_fd("death_time must be greater than 60ms\n", 2);
		return (false);
	}
	else if (data->eat_time < MIN_TIME)
	{
		ft_putstr_fd("eat_time must be greater than 60ms\n", 2);
		return (false);
	}
	else if (data->sleep_time < MIN_TIME)
	{
		ft_putstr_fd("sleep_time must be greater than 60ms\n", 2);
		return (false);
	}
	return (true);
}

bool	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0 
		|| pthread_mutex_init(&data->mutex_death, NULL) != 0)
        return false;
	return (true);
}

bool	init_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
		++i;
	}
	return (true);
}

void 	init_struct_philos(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].nb_meal = 0;
		data->philos[i].time_last_meal = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		++i;
	}
}
bool	init_threads(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (data->forks == NULL)
		return (false);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (data->philos == NULL)
	{
		free(data->forks);
		return (false);
	}
	if (init_forks(data) == false)
	{
		free(data->forks);
		free(data->philos);
		return (false);
	}
	init_struct_philos(data);
	return (true);
}

static	bool init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1], 0);
	data->death_time = ft_atoi(av[2], 0);
	data->eat_time = ft_atoi(av[3], 0);
	data->sleep_time = ft_atoi(av[4], 0);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5], 0);
	else
		data->nb_eat = -1;
	data->start_time = get_current_time_ms();
	data->someone_died = false;
	if (check_value(data) == false)
		return (false);
	if (init_mutex(data) == false)
		return (false);
	if (init_threads(data) == false)
		return (false);
	return (true);
}

int	check_params(t_data *data, int ac, char **av)
{
	size_t	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd(USG, 2);
		return (-1);
	}
	while ((int)i < ac)
	{
		if (is_integer(av[i]) == false)
		{
			ft_putstr_fd("Invalid arg[", 2);
			ft_putchar_fd(i + 48, 2);
			write(2, "] !\n", 4);
			return (-1);
		}
		++i;
	}
	if (init_data(data, ac, av) == false)
		return (-1);
	return (0);
}
