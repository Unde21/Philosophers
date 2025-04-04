/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:43:24 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/04 12:51:03 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USG \
	"Use: ./philo nb_philo, time_to_die, time_to_eat, \
time_to_sleep, [nb_must_eat]\n"
# define ERR_MALLOC "malloc failed\n"
# define ERR_ARG "invalid parameters\n"
# define ERR_NB_PHILO "invalid numbers of Philosophers\n"
# define ERR_NB_EAT "invalid number eat\n"
# define TOO_MANY_PHILO "Too many philosophers\n"
# define ERR_EAT "eat_time must be greater than 60ms\n"
# define ERR_SLEEP "sleep_time must be greater than 60ms\n"
# define ERR_DEATH "death_time must be greater than 60ms\n"
# define MIN_TIME 60
# define ERR_INIT_MUTEX "Failed to init mutex\n"
# define ERR_MSG_THREAD "Failed to create thread\n"
# define ERR_THREAD 2
# define ALL_THREAD_CREATED 1
# define MSG_FORK "has taken a fork"
# define MSG_EATING "is eating"
# define MSG_THINK "is thinking"
# define MSG_SLEEP "is sleeping"
# define AVAILABLE 1 
# define UNAVAILABLE 0

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	size_t			id;
	size_t			nb_meal;
	int				first_fork_index;
	int				second_fork_index;
	long			time_last_meal;
	struct s_data	*data;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	size_t			nb_philo;
	long			death_time;
	long			eat_time;
	long			sleep_time;
	long			start_time;
	int				nb_eat;
	int				start;
	int				*forks_status;
	bool			someone_died;
	bool			m_fork_init;
	bool			m_start_init;
	bool			m_print_init;
	bool			m_start_time_init;
	bool			m_end_init;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_end;
	pthread_mutex_t	m_forks;
	pthread_mutex_t	m_start_time;
	pthread_mutex_t	m_start;
	t_philo			*philos;
}					t_data;

void	waiting(t_data *data, long time);
void	safe_print(t_data *data, size_t id, char *str);
void	ft_putstr_fd(char *s, int fd);
void	free_data(t_data *data);
void	*supervisor(t_data *data, t_philo *philo);
void	*start_routine(void *ptr);

size_t	ft_strlen(const char *s);

long	get_current_time_ms(void);

int		wait_start(t_data *data);
int		handle_fork(t_data *data, t_philo *philo);
int		ft_atoi(const char *nptr, int *check_error);
int		create_threads(t_data *data);
int		check_params(t_data *data, int ac, char **av);

bool	init_data(t_data *data, int ac, char **av);
bool	check_value(t_data *data);
bool	take_right_fork(t_data *data, t_philo *philo);
void	eating(t_data *data, t_philo *philo);

#endif
