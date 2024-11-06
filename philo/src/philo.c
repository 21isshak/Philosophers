/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:08:00 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/06 19:35:45 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_think(t_philosopher *philo)
{
	printer("is thinking", philo, philo->id);
}

void	philosopher_sleep(t_philosopher *philo)
{
	printer("is sleeping", philo, philo->id);
	uslep(philo->time_to_sleep);
}

void	take_fork(t_philosopher *philo, int lock_order_flag)
{
	if (lock_order_flag == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printer("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printer("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->left_fork);
	}
}

void	philosopher_eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
		take_fork(philo, 0);
	else
		take_fork(philo, 1);
	pthread_mutex_lock(philo->meal_lock);
	philo->eat = 1;
	pthread_mutex_unlock(philo->meal_lock);
	printer("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	uslep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eat = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
//comment previous functions and uncomment next functions for colored output
/*
void	philosopher_think(t_philosopher *philo)
{
	printer("\033[1mis thinking\033[0m", philo, philo->id);
}

void	philosopher_sleep(t_philosopher *philo)
{
	printer("\033[0;32mis sleeping\033[0m", philo, philo->id);
	uslep(philo->time_to_sleep);
}

void	philosopher_eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printer("\033[0;33mhas taken a fork\033[0m", philo, philo->id);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printer("\033[0;33mhas taken a fork\033[0m", philo, philo->id);
		pthread_mutex_lock(philo->left_fork);
	}
	philo->eat = 1;
	printer("\033[0;34mis eating\033[0m", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	uslep(philo->time_to_eat);
	philo->eat = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
*/

void	*routine(void *p)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p;
	if (philo->id % 2 == 0)
		uslep(10);
	while (!dead_flag_checker(philo))
	{
		philosopher_eat(philo);
		philosopher_sleep(philo);
		philosopher_think(philo);
	}
	return (p);
}
