/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:43:24 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/06 01:51:02 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USG "Use: ./philo nb_philo [time_to:] death eat sleep [nb_must_eat]\n"

# include <unistd.h>

typedef struct s_data
{
	int	nb_philo;
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	nb_eat;
}		t_data;

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

size_t	ft_strlen(const char *s);
int	ft_atoi(const char *nptr, int *check_error);
int	check_params(t_data *data, int ac, char **av);
void	init_struc(t_data *data, int ac, char **av);

#endif
