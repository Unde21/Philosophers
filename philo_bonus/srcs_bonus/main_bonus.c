/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:33:27 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/24 09:13:24 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (check_params(&data, ac, av) != 0)
		return (1);
	if (init_child(&data) != 0)
	{
		clear_semaphores(&data);
		clear_data(&data);
		return (1);
	}
	return (0);
}
