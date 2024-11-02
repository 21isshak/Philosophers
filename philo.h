/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:08:08 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/02 16:20:16 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct philosopher
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		state_lock;
	struct simulation	*sim;
}	t_philosopher;

typedef struct simulation
{
	int				n_p;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	mut_start_time;
	t_philosopher	*p;
	int				all_philos_done;
	bool			philosopher_dead;
}	t_simulation;

long	current_time_ms(void);
long	time_since_start(t_simulation *sim);
int		ft_atoi(const char *str);
void	*routine(void *arg);
void	print_fork_message(t_philosopher *philo, long time);
void	take_fork(pthread_mutex_t *fork, t_philosopher *philo);
void	print_input(void);
int		check_digit(int argc, char **argv);
int		check_input(int argc, char **argv);
int		is_philosopher_dead(t_philosopher *philo);
size_t	ft_strlen(const char *s);
void	one_philo(char **argv);

#endif
