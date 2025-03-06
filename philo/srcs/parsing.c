/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:42:45 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/06 01:57:26 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_integer(char *s)
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
	init_struc(data, ac, av);
	return (0);
}

void	init_struc(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1], 0);
	data->death_time = ft_atoi(av[2], 0);
	data->eat_time = ft_atoi(av[3], 0);
	data->sleep_time = ft_atoi(av[4], 0);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5], 0);
	else
		data->nb_eat = -1;
}
