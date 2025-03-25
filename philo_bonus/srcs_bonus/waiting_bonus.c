/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:43:16 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/25 10:01:58 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	waiting(long time)
{
	long	start;
	long	elapsed;

	elapsed = 0;
	start = get_current_time_ms();
	while (elapsed < time)
	{
		usleep(100);
		elapsed = get_current_time_ms() - start;
	}
}
