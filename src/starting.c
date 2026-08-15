/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:40:49 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/06 16:55:30 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philos_ate(t_philosopher *philos)
{
	int	i;
	int	eat_done;

	i = 0;
	eat_done = 0;
	if (philos[0].meals_required == -1)
		return (0);
	while (i < philos[0].n_p)
	{
		pthread_mutex_lock(philos[0].meal_lock);
		if (philos[i].meals_eaten >= philos[i].meals_required)
			eat_done++;
		pthread_mutex_unlock(philos[0].meal_lock);
		i++;
	}
	if (eat_done == philos[0].n_p)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor_p(void *p)
{
	t_philosopher	*philos;

	philos = (t_philosopher *)p;
	while (1)
		if (check_dead(philos) == 1 || all_philos_ate(philos) == 1)
			break ;
	return (p);
}

int	start_p(t_simulation *sim, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	watch;

	i = 0;
	if (pthread_create(&watch, NULL, &monitor_p, sim->p) != 0)
		destroyer("thread creation didn't succes", sim, forks);
	while (i < sim->p[0].n_p)
	{
		if (pthread_create(&sim->p[i].thread, NULL, &routine, &sim->p[i]) != 0)
			destroyer("thread creation didn't succes", sim, forks);
		i++;
	}
	i = 0;
	if (pthread_join(watch, NULL) != 0)
		destroyer("thread join didn't succes", sim, forks);
	while (i < sim->p[0].n_p)
	{
		if (pthread_join(sim->p[i].thread, NULL) != 0)
			destroyer("thread join didn't succes", sim, forks);
		i++;
	}
	return (0);
}
