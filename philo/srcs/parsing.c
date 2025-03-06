/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:42:45 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/06 04:56:54 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	is_integer(char *s)
{
	size_t	i;
	int		check_error;

	check_error = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		++i;
	}
	ft_atoi(s, &check_error);
	if (check_error != 0)
		return (-1);
	return (0);
}

static int	check_time_value(t_data *data)
{
	if (data->death_time < MIN_TIME)
	{
		ft_putstr_fd("death_time must be greater than 60ms\n", 2);
		return (-1);
	}
	else if (data->eat_time < MIN_TIME)
	{
		ft_putstr_fd("eat_time must be greater than 60ms\n", 2);
		return (-1);
	}
	else if (data->sleep_time < MIN_TIME)
	{
		ft_putstr_fd("sleep_time must be greater than 60ms\n", 2);
		return (-1);
	}
	return (0);
}

static int	init_struc(t_data *data, int ac, char **av)
{
	data->id = 0;
	data->is_alive = true;
	data->nb_philo = (size_t)ft_atoi(av[1], 0);
	data->death_time = (size_t)ft_atoi(av[2], 0);
	data->eat_time = (size_t)ft_atoi(av[3], 0);
	data->sleep_time = (size_t)ft_atoi(av[4], 0);
	if (ac == 6)
		data->nb_eat = (size_t)ft_atoi(av[5], 0);
	else
		data->nb_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (data->forks == NULL)
		return (-1);
	return (0);
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
		if (is_integer(av[i]) != 0)
		{
			ft_putstr_fd("Wrong character(s) for arg[", 2);
			ft_putchar_fd(i + 48, 2);
			write(2, "] !\n", 4);
			return (-1);
		}
		++i;
	}
	if (init_struc(data, ac, av) != 0 || check_time_value(data) != 0)
		return (-1);
	return (0);
}
