/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:43:24 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/06 04:57:03 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USG "Use: ./philo nb_philo [time_to:] death eat sleep [nb_must_eat]\n"
# define MIN_TIME 60

# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_data
{
	size_t			id;
	size_t			nb_philo;
	size_t			death_time;
	size_t			eat_time;
	size_t			sleep_time;
	int				meal_count;
	int				nb_eat;
	// bool			is_meal_limit;
	bool			is_alive;
	pthread_mutex_t	*forks;
}		t_data;

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr, int *check_error);

int		check_params(t_data *data, int ac, char **av);
void	init_threads(t_data *data);

#endif
