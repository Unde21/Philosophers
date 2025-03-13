/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:43:24 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/13 17:25:53 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USG "Use: ./philo nb_philo [time_to:] die eat sleep [nb_must_eat]\n"
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
	pthread_mutex_t	aled;
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
	// int		race;

	bool	someone_died;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	*forks;
	pthread_mutex_t m_start_time;
	pthread_mutex_t m_start; //TODO faire sa partout
	t_philo		*philos;
	// pthread_t	status_thread;
}	t_data;


void	*philos_loop(void *ptr);
bool check_philo_ate_enough(t_data *data);
void *status_loop(t_data *data, t_philo *philo);

void safe_print(t_data *data, size_t id, char *str, char *color_code);
bool	check_death(t_data *data, t_philo *philo);
void	waiting(t_data *data, long time);
int	 wait_start(t_data *data);

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr, int *check_error);

int		check_params(t_data *data, int ac, char **av);
int		create_threads(t_data *data);

long	get_current_time_ms(void);

#endif
