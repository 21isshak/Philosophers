/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:40:16 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/06 19:35:06 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf ("gettimeofday() error\n");
		return (1);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	time_since_start(t_simulation *sim)
{
	long	time;

	time = current_time_ms() - sim->p->start_time;
	return (time);
}

int	uslep(long milliseconds)
{
	long	start;
	long	target;

	start = current_time_ms();
	target = start + milliseconds;
	while (current_time_ms() < target)
	{
		usleep(0);
	}
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

int	dead_flag_checker(t_philosopher *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}
