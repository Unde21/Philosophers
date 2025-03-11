/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:27:46 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/11 03:39:11 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

/*TODO ne pas protect les forks avec un mutex directement, passer par une variable 0/1 (sujet)
faire une fonction waiting qui fonctionne mieux : il y a un pb avec le data->eat_time
Faire un define de tout les print 
wait que tout les threads soit  creer au debut de philos_loop quit properly if one of them failed
-g3 -fsanitize=thread -pg

*/
int	 wait_start(t_data *data);
void	waiting(t_data *data, long time);

long	get_current_time_ms(void)
{
	struct timeval current;
	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void safe_print(t_data *data, size_t id, char *str)
{
	if (data->someone_died == true)
		return ;
    pthread_mutex_lock(&data->mutex_print);
    printf("%ld %lu %s\n", get_current_time_ms() - data->start_time, id + 1, str);
    pthread_mutex_unlock(&data->mutex_print);
}

bool	check_death(t_data *data, t_philo *philo)
{
	long	current_time;
	
	pthread_mutex_lock(&data->mutex_death);
	if (data->someone_died == true)
	{
		pthread_mutex_unlock(&data->mutex_death);
		return (true);
	}
	current_time = get_current_time_ms();
	if (current_time - philo->time_last_meal > data->death_time)
	{
		data->someone_died = true;
		pthread_mutex_unlock(&data->mutex_death);
		printf("%ld %lu died\n", get_current_time_ms() - data->start_time, philo->id + 1);
		return (true);
	}
	pthread_mutex_unlock(&data->mutex_death);
	return (false);
}

bool check_philo_ate_enough(t_data *data)
{
	size_t	i;

	i = 0;
    if (data->nb_eat == -1)
        return false;
    while (i < data->nb_philo)
    {
        if (data->philos[i].nb_meal < (size_t)data->nb_eat)
            return false;
		++i;
    }
    return true;
}

void *status_loop(void *ptr)
{
    t_data *data;
    t_philo *philos;
    size_t	i;

	data = (t_data *)ptr;
	philos = data->philos;
	// waiting(data, data->eat_time);
    while (1)
    {
		i = 0;
        while(i < data->nb_philo)
        {
            if (check_death(data, &philos[i]) == true)
                return NULL;
            if (check_philo_ate_enough(data) == true)
            {
                pthread_mutex_lock(&data->mutex_death);
                data->someone_died = true;
                pthread_mutex_unlock(&data->mutex_death);
                return NULL;
            }
			++i;
        }
        // usleep(1000);
    }
    return NULL;
}

void	waiting(t_data *data, long time)
{
	long	start;

	start = get_current_time_ms();
	while (get_current_time_ms() - start < time)
	{
		pthread_mutex_lock(&data->mutex_death);
		if (data->someone_died == true)
		{
			pthread_mutex_unlock(&data->mutex_death);
			return ;
		}
		pthread_mutex_unlock(&data->mutex_death);
		usleep(1000);
	}
}
int	 wait_start(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->m_start);
		if (data->start == 1)
		{
			pthread_mutex_unlock(&data->m_start);
			pthread_mutex_lock(&data->m_start_time);
			if (data->start_time == 0)
				data->start_time = get_current_time_ms();
			pthread_mutex_unlock(&data->m_start_time);
			return (0);
		}
		pthread_mutex_unlock(&data->m_start);
		pthread_mutex_lock(&data->m_start);
		if (data->start == 2)
		{
			pthread_mutex_unlock(&data->m_start);
			return (-1);
		}
		pthread_mutex_unlock(&data->m_start);
		usleep(100);
	}
	return (0);
}
void	*philos_loop(void *ptr)
{
	t_philo *philo;
	t_data *data;
	
	philo = (t_philo *)ptr;
	data = philo->data;
	if (wait_start(data) != 0)
		return (NULL);
	if (philo->id % 2 != 0)
		usleep(data->eat_time / 2);
	while (data->someone_died == false)
	{
		// ++data->race;
		if (data->nb_philo == 1)
		{
			safe_print(data, philo->id, "is thinking");
			pthread_mutex_lock(philo->left_fork);
			safe_print(data, philo->id, "has taken a fork");
			waiting(data, data->death_time);
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		if (check_death(data, philo) == true)
			break;
		safe_print(data, philo->id, "is thinking");
		// if (data->nb_philo % 2 == 1)
		// 	waiting(data, data->eat_time / 10);
		// if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			safe_print(data, philo->id, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			safe_print(data, philo->id, "has taken a fork");
		}
		// else
		// {
		// 	pthread_mutex_lock(philo->right_fork);
		// 	safe_print(data, philo->id, "has taken a fork");
		// 	pthread_mutex_lock(philo->left_fork);
		// 	safe_print(data, philo->id, "has taken a fork");
		// }
		safe_print(data, philo->id, "is eating");
		pthread_mutex_lock(&data->mutex_death);
		philo->time_last_meal = get_current_time_ms();
		++philo->nb_meal;
		pthread_mutex_unlock(&data->mutex_death);
		waiting(data, data->eat_time);
		// usleep(data->eat_time);
		// if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		// else
		// {
		// 	pthread_mutex_unlock(philo->left_fork);
		// 	pthread_mutex_unlock(philo->right_fork);
		// }
		safe_print(data, philo->id, "is sleeping");
		waiting(data, data->sleep_time);
	}
	return (NULL);
}
void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		++i;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->m_start_time);
	pthread_mutex_destroy(&data->m_start);
	free(data->forks);
	free(data->philos);
}

int		create_threads(t_data *data)
{
	size_t	i;

	i = 0;

	// data->race = 0;
	
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philos_loop, &data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->m_start);
			data->start = 2;
			pthread_mutex_unlock(&data->m_start);
			printf("Error: Failed to create thread\n");
			return (-1);
		}
		++i;
	}
	// pthread_mutex_lock(&data->m_start);
	data->start = 1;
	// pthread_mutex_unlock(&data->m_start);
	if (data->philos == NULL)
		printf("philos is NULL\n");
	if (pthread_create(&data->status_thread, NULL, status_loop, data) != 0) //TODO Virer le thread...
	{
		printf("Error: Failed to create status thread\n");
		return (-1);
	}
	pthread_join(data->status_thread, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		++i;
	}
	free_data(data);
	return (0);
}
