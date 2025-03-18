/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:32:54 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/18 09:38:41 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define USG "Use: ./philo nb_philo, time_to_die, time_to_eat, \
time_to_sleep, [nb_must_eat]\n"
# define ERR_MALLOC "Malloc failed\n"
# define ERR_ARG "Invalid parameters\n"
# define ERR_NB_PHILO "Invalid numbers of Philosophers\n"
# define TOO_MANY_PHILO "Too many philosophers\n"
# define ERR_EAT "eat_time must be greater than 60ms\n"
# define ERR_SLEEP "sleep_time must be greater than 60ms\n"
# define ERR_DEATH "death_time must be greater than 60ms\n"
# define ERR_FORK "Fork failed\n"
# define MIN_TIME 60


# define MSG_FORK "has taken a fork"
# define MSG_EATING "is eating"
# define MSG_THINK "is thinking"
# define MSG_SLEEP "is sleeping"

# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>


typedef struct s_philo
{
	size_t	id;
	size_t	nb_meal;
	long	time_last_meal;
	struct s_data *data;
}	t_philo;


typedef struct s_data
{
	size_t	nb_philo;
	pid_t	pid;
	long	death_time;
	long	eat_time;
	long	sleep_time;
	long	start_time;
	int		nb_eat;
	int		start;
	bool	someone_died;
	t_philo	*philos;
} t_data;


int	check_params(t_data *data, int ac, char **av);
void	ft_putstr_fd(char *s, int fd);
int	ft_atoi(const char *nptr, int *check_error);
size_t	ft_strlen(char *s);
bool	init_data(t_data *data, int ac, char **av);

#endif
