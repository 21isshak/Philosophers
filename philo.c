/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:08:00 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/02 16:21:35 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%ld %d is thinking\n", time_since_start(philo->sim), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
}

void	philosopher_take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 1)
	{
		take_fork(philo->left_fork, philo);
		take_fork(philo->right_fork, philo);
	}
	else
	{
		take_fork(philo->right_fork, philo);
		take_fork(philo->left_fork, philo);
	}
}

void	philosopher_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%ld %d is eating\n", time_since_start(philo->sim), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
	pthread_mutex_lock(&philo->state_lock);
	philo->last_meal_time = current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->state_lock);
	usleep(philo->sim->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philosopher_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%ld %d is sleeping\n", time_since_start(philo->sim), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
	usleep(philo->sim->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!philo->sim->philosopher_dead)
	{
		if (is_philosopher_dead(philo))
			break ;
		if (philo->sim->meals_required != -1
			&& philo->meals_eaten >= philo->sim->meals_required)
			break ;
		philosopher_think(philo);
		philosopher_take_forks(philo);
		philosopher_eat(philo);
		if (is_philosopher_dead(philo))
			break ;
		philosopher_sleep(philo);
	}
	return (NULL);
}
