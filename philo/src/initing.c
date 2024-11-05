/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:39:26 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/05 18:06:48 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philosopher *philo, char **argv)
{
	philo->n_p = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals_required = ft_atoi(argv[5]);
	else
		philo->meals_required = -1;
}

void	init_philo(t_philosopher *philo, t_simulation *sim,
		pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].eat = 0;
		init_input(&philo[i], argv);
		philo[i].start_time = current_time_ms();
		philo[i].last_meal_time = current_time_ms();
		philo[i].print_lock = &sim->print_lock;
		philo[i].meal_lock = &sim->meal_lock;
		philo[i].dead_lock = &sim->dead_lock;
		philo[i].dead = &sim->philosopher_dead;
		philo[i].left_fork = &forks[i];
		if (i == 0)
			philo[i].right_fork = &forks[philo[i].n_p - 1];
		else
			philo[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_simulation(t_simulation *sim, t_philosopher *philos,
		pthread_mutex_t *forks, char **argv)
{
	sim->philosopher_dead = 0;
	sim->p = philos;
	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->dead_lock, NULL);
	pthread_mutex_init(&sim->meal_lock, NULL);
	init_forks(forks, ft_atoi(argv[1]));
	init_philo(philos, sim, forks, argv);
	start_p(sim, forks);
	destroyer(NULL, sim, forks);
}
