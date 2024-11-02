/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:40:16 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/02 16:20:59 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	time_since_start(t_simulation *sim)
{
	return (current_time_ms() - sim->start_time);
}

void	print_fork_message(t_philosopher *philo, long time)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%ld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
}

void	take_fork(pthread_mutex_t *fork, t_philosopher *philo)
{
	long	time;

	pthread_mutex_lock(fork);
	time = time_since_start(philo->sim);
	print_fork_message(philo, time);
}

int	is_philosopher_dead(t_philosopher *philo)
{
	long	current_time;
	long	last_meal;

	current_time = current_time_ms();
	pthread_mutex_lock(&philo->state_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->state_lock);
	if (current_time - last_meal >= philo->sim->time_to_die)
	{
		pthread_mutex_lock(&philo->sim->print_lock);
		printf("%ld %d died\n", time_since_start(philo->sim), philo->id);
		pthread_mutex_unlock(&philo->sim->print_lock);
		philo->sim->philosopher_dead = true;
		return (1);
	}
	return (0);
}
