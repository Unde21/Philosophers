/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:38:41 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/18 09:18:18 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>

static bool is_integer(char *s)
{
	size_t	i;
	int		check_error;

	check_error = 0;
	i = 0;
	while(s[i])
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

bool	check_value(t_data *data)
{
	if (data->nb_philo == 0)
	{
		ft_putstr_fd(ERR_NB_PHILO, 2);
		return (false);
	}
	if (data->death_time < MIN_TIME)
	{
		ft_putstr_fd(ERR_DEATH, 2);
		return (false);
	}
	else if (data->eat_time < MIN_TIME)
	{
		ft_putstr_fd(ERR_EAT, 2);
		return (false);
	}
	else if (data->sleep_time < MIN_TIME)
	{
		ft_putstr_fd(ERR_SLEEP, 2);
		return (false);
	}
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
			ft_putstr_fd(ERR_ARG, 2);
			return (-1);
		}
		++i;
	}
	(void)data;
	if (init_data(data, ac, av) == false)
		return (-1);
	return (0);
}
