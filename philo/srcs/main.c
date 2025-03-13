/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:43:48 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/13 20:12:18 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_data	data;

	if (check_params(&data, ac, av) != 0)
		return (1);
	if (create_threads(&data) != 0)
	{
		free(data.m_forks);
		free(data.philos);
		return (1);
	}
	return (0);
}
