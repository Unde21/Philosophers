/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:43:48 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/06 01:57:20 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	t_data	data;
	
	if (check_params(&data, ac, av) != 0)
		return (1);
	printf("nb_philo: %d\ndeath_time: %d\neat_time: %d\nsleep_time: %d\nnb_eat: %d\n", data.nb_philo, data.death_time, data.eat_time, data.sleep_time, data.nb_eat);
	return (0);
}
