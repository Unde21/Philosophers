/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:32:54 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/21 13:50:23 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define USG "Use: ./philo nb_philo, time_to_die, time_to_eat, \
time_to_sleep, [nb_must_eat]\n"
# define ERR_MALLOC "malloc failed\n"
# define ERR_ARG "invalid parameters\n"
# define ERR_NB_PHILO "invalid numbers of Philosophers\n"
# define ERR_NB_EAT "invalid number eat\n"
# define TOO_MANY_PHILO "Too many philosophers\n"
# define ERR_EAT "eat_time must be greater than 60ms\n"
# define ERR_SLEEP "sleep_time must be greater than 60ms\n"
# define ERR_DEATH "death_time must be greater than 60ms\n"
# define ERR_SEM "sem_open failed\n"
# define ERR_FORK "fork failed\n"
# define MIN_TIME 60
# define ALL_PROCESS_CREATED 1
# define ERR_PROCESS 2

# define MSG_FORK "has taken a fork"
# define MSG_EATING "is eating"
# define MSG_THINK "is thinking"
# define MSG_SLEEP "is sleeping"

# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <semaphore.h>


typedef struct s_philo
{
	size_t	id;
	size_t	nb_meal;
	long	time_last_meal;
	bool	philos_alive;
	struct s_data *data;
	pthread_t thread_routine;
	pthread_t thread_supervisor;
}	t_philo;


typedef struct s_data
{
	size_t	nb_philo;
	pid_t	*pid;
	long	death_time;
	long	eat_time;
	long	sleep_time;
	long	start_time;
	int		nb_eat;
	int		start;
	sem_t	*death_lock;
	sem_t	*forks;
	sem_t	*print_lock;
	// sem_t	*start_lock;
	// sem_t	*sem_end;
	// sem_t	*sem_start;
	sem_t	*eating_limit;
	t_philo	*philos;
} t_data;


void	clear_data(t_data *data);
int	check_params(t_data *data, int ac, char **av);
void	ft_putstr_fd(char *s, int fd);
int	ft_atoi(const char *nptr, int *check_error);
size_t	ft_strlen(char *s);
bool	init_data(t_data *data, int ac, char **av);
int	init_child(t_data *data);
bool	init_semaphores(t_data *data);
long	get_current_time_ms(void);
bool	check_value(t_data *data);
void	routine(t_data *data, size_t current);
void	waiting(t_data *data, long time, size_t current);
int	wait_start(t_data *data);
void	handle_fork(t_data *data, t_philo *philo, size_t current);
void	safe_print(t_data *data, size_t id, char *str);
void	kill_all (t_data *data);
void *supervisor(void *ptr);
#endif
