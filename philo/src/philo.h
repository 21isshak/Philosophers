/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:08:08 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/06 19:35:35 by iskaraag         ###   ########.fr       */
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
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	int					eat;
	long				last_meal_time;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	long				start_time;
	int					n_p;
	int					meals_required;
	int					*dead;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*print_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
}	t_philosopher;

typedef struct simulation
{
	int				philosopher_dead;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philosopher	*p;
}	t_simulation;

//main.c
void	printer(char *str, t_philosopher *philo, int id);
void	print_input(void);
void	one_philo(char **argv);
int		check_input(int argc, char **argv);

//initing.c
void	init_input(t_philosopher *philo, char **argv);
void	init_philo(t_philosopher *philo, t_simulation *sim,
			pthread_mutex_t *forks, char **argv);
void	init_forks(pthread_mutex_t *forks, int num_of_philos);
void	init_simulation(t_simulation *sim, t_philosopher *philos,
			pthread_mutex_t *forks, char **argv);

//starting.c
int		all_philos_ate(t_philosopher *philos);
void	*monitor_p(void *p);
int		start_p(t_simulation *sim, pthread_mutex_t *forks);

//philo.c
void	philosopher_think(t_philosopher *philo);
void	philosopher_sleep(t_philosopher *philo);
void	take_fork(t_philosopher *philo, int lock_order_flag);
void	philosopher_eat(t_philosopher *philo);
void	*routine(void *p);

//philo_utils.c
long	current_time_ms(void);
long	time_since_start(t_simulation *sim);
int		uslep(long milliseconds);
void	destroyer(const char *str, t_simulation *sim, pthread_mutex_t *forks);
int		dead_flag_checker(t_philosopher *philo);

//utils.c
size_t	ft_strlen(const char *s);
long	ft_atoi(char *str);
int		check_digit(int argc, char **argv);
int		dead_checker(t_philosopher *philo, long time_to_die);
int		check_dead(t_philosopher *philos);

#endif
