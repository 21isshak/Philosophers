/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:08:14 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/05 18:35:01 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	uslep(long milliseconds)
{
	long	start;

	start = current_time_ms();
	while ((current_time_ms() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	destroyer(const char *str, t_simulation *sim, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		printf("%s\n", str);
		return ;
	}
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->meal_lock);
	pthread_mutex_destroy(&sim->dead_lock);
	while (i < sim->p[0].n_p)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

long	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}

int	check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
