/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:43:24 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/13 20:35:03 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USG "Use: ./philo nb_philo [time_to:] die eat sleep [nb_must_eat]\n"
# define ERR_ARG "Invalid params\n"
# define ERR_NB_PHILO "Invalid numbers of Philosophers\n"
# define ERR_EAT "eat_time must be greater than 60ms\n"
# define ERR_SLEEP "sleep_time must be greater than 60ms\n"
# define ERR_DEATH "death_time must be greater than 60ms\n"
# define MIN_TIME 60

# define BLUE "\033[34m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"

# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	size_t	id;
	size_t	nb_meal;
	long	time_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct	s_data *data;
	pthread_t	thread;
}	t_philo;

typedef struct s_data
{
	size_t	nb_philo;
	long	death_time;
	long	eat_time;
	long	sleep_time;
	long	start_time;
	int		nb_eat;
	int		start;

	bool	someone_died;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_end;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t m_start_time;
	pthread_mutex_t m_start;
	t_philo		*philos;
}	t_data;

int		check_params(t_data *data, int ac, char **av);
int		create_threads(t_data *data);
void	ft_putstr_fd(char *s, int fd);
bool	init_data(t_data *data, int ac, char **av);
int		ft_atoi(const char *nptr, int *check_error);
void safe_print(t_data *data, size_t id, char *str);
bool	check_value(t_data *data);
void	*philos_loop(void *ptr);
void	free_data(t_data *data);
void *status_loop(t_data *data, t_philo *philo);
int	 wait_start(t_data *data);
void	waiting(t_data *data, long time);
size_t	ft_strlen(const char *s);
long	get_current_time_ms(void);

#endif
