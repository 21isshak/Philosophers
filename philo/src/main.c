/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <iskaraag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:07:50 by iskaraag          #+#    #+#             */
/*   Updated: 2024/11/05 18:28:30 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printer(char *str, t_philosopher *philo, int id)
{
	long	time;

	pthread_mutex_lock(philo->print_lock);
	time = current_time_ms() - philo->start_time;
	if (!dead_flag_checker(philo))
		printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->print_lock);
}

void	print_input(void)
{
	printf("\033[1m\033[31mWRONG INPUT\033[0m\n");
	printf("\033[1m\033[31mWARNING:\033[0m time_to_eat +");
	printf(" time_to_sleep < time_to_die\n");
	printf("\033[1m\033[32mUsage:\033[0m ./philo <number_of_p> <time_to_die>");
	printf(" <time_to_eat> <time_to_sleep>");
	printf(" <[number_of_times_each_philosopher_must_eat]>\n");
	printf("\033[1m\033[34mExample1:\033[0m ./philo 4 800 200 200\n");
	printf("\033[1m\033[34mExample2:\033[0m ./philo 4 800 200 200 4\n");
}

void	one_philo(char **argv)
{
	long int	a;

	a = argv[2][ft_strlen(argv[2]) - 1] - '0';
	printf("%ld 1 \033[0;33mhas taken a fork\033[0m\n", a);
	uslep(ft_atoi(argv[2]));
	printf("%ld", ft_atoi(argv[2]));
	printf("%ld \033[0;31mdied\033[0m\n", ft_atoi(argv[1]));
}

/*
void	one_philo(char **argv)
{
	long int	a;

	a = argv[2][ft_strlen(argv[2]) - 1] - '0';
	printf("%ld 1 \033[0;33mhas taken a fork\033[0m\n", a);
	uslep(ft_atoi(argv[2]));
	printf("%ld", ft_atoi(argv[2]));
	printf("%ld \033[0;31mdied\033[0m\n", ft_atoi(argv[1]));
}
*/

int	check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (1);
	if (check_digit(argc, argv) != 0)
		return (1);
	if (ft_atoi(argv[1]) > 200)
		return (1);
	while (i < argc)
	{
		if (ft_atoi(argv[i]) > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;
	int				num_philos;

	if (check_input(argc, argv) != 0)
		return (print_input(), 1);
	if ((argc == 5 || argc == 6) && ft_atoi(argv[1]) == 1)
		return (one_philo(argv), 2);
	num_philos = ft_atoi(argv[1]);
	philos = (t_philosopher *)malloc(num_philos * sizeof(t_philosopher));
	if (!philos)
		return (3);
	forks = (pthread_mutex_t *)malloc(num_philos * sizeof(pthread_mutex_t));
	if (!forks)
	{
		free(philos);
		return (4);
	}
	init_simulation(&sim, philos, forks, argv);
	free(philos);
	free(forks);
	return (0);
}
