/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:16:04 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/19 12:18:53 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h> 
#include <stdlib.h>

//TODO remonter d erreur et free tout sa en cas d erreur 
static bool	init_struct_philos(t_data *data)
{
	size_t	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (data->philos == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		return (false);
	}
	data->philos->id = malloc(sizeof(size_t) * data->nb_philo);
	if (data->philos->id == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		return (false);
	}
	data->philos->nb_meal = malloc(sizeof(size_t) * data->nb_philo);
	if (data->philos->nb_meal == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		return (false);
	}
	data->philos->time_last_meal = malloc(sizeof(long) * data->nb_philo);
	if (data->philos->time_last_meal == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		return (false);
	}
	while (i < data->nb_philo)
	{
		data->philos->id[i] = i;
		data->philos->nb_meal[i] = 0;
		data->philos->time_last_meal[i] = data->start_time;
		data->philos[i].data = data;
		++i;
	}
	data->philos->philos_alive = true;
	return (true);
}

bool	init_semaphores(t_data *data)
{
	//TODO quitter proprement le programme pour retirer sa 
	sem_close(data->forks);
	sem_close(data->print_lock);
	sem_close(data->death_lock);
	sem_close(data->sem_end);
	sem_unlink("/sem_end");
	sem_unlink("/death_lock");
	sem_unlink("/forks");
	sem_unlink("/print_lock");
	//TODO define le path des semaphores O_EXCL ???? 
	data->sem_end = sem_open("/sem_end", O_CREAT | O_EXCL, 0644, 0);
	if (data->sem_end == SEM_FAILED)
	{
		ft_putstr_fd(ERR_SEM, 2);
		return (false);
	}
	data->death_lock = sem_open("/death_lock", O_CREAT, 0644, 1);
	if (data->death_lock == SEM_FAILED)
	{
		ft_putstr_fd(ERR_SEM, 2);
		sem_close(data->death_lock);
		sem_unlink("/sem_end");
		return (false);
	}
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
	{
		ft_putstr_fd(ERR_SEM, 2);
		sem_close(data->death_lock);
		sem_unlink("/death_lock");
		return (false);
	}
	data->print_lock = sem_open("/print_lock", O_CREAT, 0644, 1);
	if (data->print_lock == SEM_FAILED)
	{
		ft_putstr_fd(ERR_SEM, 2);
		sem_close(data->death_lock);
		sem_close(data->forks);
		sem_unlink("/forks");
		sem_unlink("/death_lock");
		return (false);
	}
	init_struct_philos(data);
	return (true);
}

bool	init_data(t_data *data, int ac, char **av)
{
	data->start = 0;
	data->nb_philo = ft_atoi(av[1], 0);
	data->pid = malloc(sizeof(pid_t) * (data->nb_philo + 1));
	if (data->pid == NULL)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		return (false);
	}
	if (data->nb_philo > 2000)
	{
		ft_putstr_fd(TOO_MANY_PHILO, 2);
		return (false);
	}
	data->death_time = ft_atoi(av[2], 0);
	data->eat_time = ft_atoi(av[3], 0);
	data->sleep_time = ft_atoi(av[4], 0);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5], 0);
	else
		data->nb_eat = -1;
	data->start_time = get_current_time_ms();
	if (data->start_time == -1 || check_value(data) == false)
		return (false);
	return (true);
}
