/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:50:36 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/18 08:51:12 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>

static int	is_overflow(unsigned long n, const char *str, size_t i, int s);
static int	loop_atoi(const char *str, size_t i, int *check_error, int s);

int	ft_atoi(const char *nptr, int *check_error)
{
	unsigned long	n;
	int				s;
	size_t			i;

	i = 0;
	n = 0;
	s = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		++i;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s = -s;
		++i;
	}
	n = loop_atoi(nptr, i, check_error, s);
	return (n * s);
}

static int	loop_atoi(const char *str, size_t i, int *check_error, int s)
{
	unsigned long	n;

	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (is_overflow(n, str, i, s) == -1)
		{
			++*(check_error);
			return (-1);
		}
		else if (is_overflow(n, str, i, s) == 0)
		{
			++*(check_error);
			return (0);
		}
		n = n * 10 + (str[i] - '0');
		++i;
	}
	return (n);
}

static int	is_overflow(unsigned long n, const char *str, size_t i, int s)
{
	if (s < 0)
	{
		if (n > (unsigned)INT_MIN / 10)
			return (0);
		else if ((long)n * 10 > INT_MIN - (str[i] - '0'))
			return (0);
	}
	else if (s > 0)
	{
		if (n > INT_MAX / 10)
			return (-1);
		else if ((long)n * 10 > INT_MAX - (str[i] - '0'))
			return (0);
	}
	return (1);
}

