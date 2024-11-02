/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:07:50 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/02 16:22:07 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_p(t_simulation *sim)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < sim->n_p)
		{
			pthread_mutex_lock(&sim->p[i].state_lock);
			if (sim->p[i].meals_eaten < sim->meals_required)
			{
				pthread_mutex_unlock(&sim->p[i].state_lock);
				break ;
			}
			pthread_mutex_unlock(&sim->p[i].state_lock);
			i++;
		}
		if (i == sim->n_p)
			break ;
		usleep(1000);
	}
}

void	start_p(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->n_p)
	{
		sim->p[i].id = i + 1;
		sim->p[i].meals_eaten = 0;
		sim->p[i].last_meal_time = sim->start_time;
		sim->p[i].left_fork = &sim->forks[i];
		sim->p[i].right_fork = &sim->forks[(i + 1) % sim->n_p];
		sim->p[i].sim = sim;
		pthread_create(&sim->p[i].thread, NULL, routine, &sim->p[i]);
		i++;
	}
	monitor_p(sim);
	i = 0;
	while (i < sim->n_p)
	{
		pthread_join(sim->p[i].thread, NULL);
		pthread_mutex_destroy(&sim->p[i].state_lock);
		i++;
	}
}

void	init_sim(t_simulation *sim, int argc, char **argv)
{
	int	i;

	sim->n_p = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->meals_required = ft_atoi(argv[5]);
	else
		sim->meals_required = -1;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->n_p);
	sim->p = malloc(sizeof(t_philosopher) * sim->n_p);
	i = 0;
	while (i < sim->n_p)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		pthread_mutex_init(&sim->p[i].state_lock, NULL);
		i++;
	}
	sim->philosopher_dead = false;
	pthread_mutex_init(&sim->print_lock, NULL);
	sim->start_time = current_time_ms();
	sim->all_philos_done = 0;
}

void	one_philo(char **argv)
{	
	long int	a;

	a = argv[2][ft_strlen(argv[2]) - 1] - '0';
	printf("%ld 1 has taken a fork\n", a);
	printf("%ld %d died\n", (long int)ft_atoi(argv[2]), ft_atoi(argv[1]));
}

int	main(int argc, char **argv)
{
	int				i;
	t_simulation	sim;

	if (check_input(argc, argv) != 0)
	{
		print_input();
		return (1);
	}
	if ((argc == 5 || argc == 6) && ft_atoi(argv[1]) == 1)
	{
		one_philo(argv);
		return (2);
	}
	init_sim(&sim, argc, argv);
	start_p(&sim);
	i = -1;
	while (++i < sim.n_p)
		pthread_mutex_destroy(&sim.forks[i]);
	pthread_mutex_destroy(&sim.print_lock);
	free(sim.forks);
	free(sim.p);
	return (0);
}
