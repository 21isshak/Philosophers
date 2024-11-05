/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:40:16 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/05 18:35:39 by iskaraag         ###   ########.fr       */
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
