/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iskaraag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:08:14 by iskaraag          #+#    #+#             */
/*   Updated: 2024/10/13 16:08:15 by iskaraag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long int	val;

	sign = 1;
	val = 0;
	while (*str == 32 || (8 < *str && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		val = val * 10 + *str - '0';
		str++;
		if (val == 214748364 && sign == -1 && *str == '8')
			return (-2147483648);
	}
	return (val * sign);
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

int	check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (check_digit(argc, argv) != 0)
		return (1);
	return (0);
}
