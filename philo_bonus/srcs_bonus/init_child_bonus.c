/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:32:35 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/18 09:38:09 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	child_creation_loop(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->pid = fork();
		if (data->pid < 0)
		{
			ft_putstr_fd(ERR_FORK, 2);
			// KILL all child
			return (-1);
		}
		++i;
	}
}
int	init_child(t_data *data)
{
	size_t	i;

	i = 0;
	if (child_creation_loop(data) != 0)
		return (-1);
}
