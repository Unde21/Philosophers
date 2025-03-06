/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:43:48 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/06 04:56:08 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //TODO remove library
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_data	data;

	if (check_params(&data, ac, av) != 0)
	{
		if (data.forks != NULL)
			free(data.forks);
		return (1);
	}
	init_threads(&data);
	return (0);
}
