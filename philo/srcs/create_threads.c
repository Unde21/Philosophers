/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:27:46 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/13 20:38:32 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

/*TODO ne pas protect les forks avec un mutex directement,
	passer par une variable 0/1 (sujet)
faire une fonction waiting qui fonctionne mieux : il y a un pb avec le data->eat_time
Faire un define de tout les print
wait que tout les threads soit  creer au debut de philos_loop quit properly if one of them failed
-g3 -fsanitize=thread -pg

*/

// BUG valgrind --tool=helgrind pour 40 + philo


int	create_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philos_loop,
				&data->philos[i]) != 0)
		{
			// si un qui pete il faut pthread_join le nb de mutex creer
			pthread_mutex_lock(&data->m_start);
			data->start = 2;
			pthread_mutex_unlock(&data->m_start);
			while (i != 0)
			{
				pthread_join(data->philos[i].thread, NULL);
				--i;
			}
			ft_putstr_fd("Error: Failed to create thread\n", 2);
			return (-1);
		}
		++i;
	}
	pthread_mutex_lock(&data->m_start);
	data->start = 1;
	pthread_mutex_unlock(&data->m_start);
	status_loop(data, data->philos);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		++i;
	}
	free_data(data);
	return (0);
}
