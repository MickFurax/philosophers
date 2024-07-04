/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:40:40 by arabeman          #+#    #+#             */
/*   Updated: 2024/06/24 08:40:42 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= 7 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

/*
** state
** -1: fork
** 0: dead
** 1: thinking
** 2: eating
** 3: sleeping
*/
void	ft_print(t_data *data, t_philo *philo, int state)
{
	pthread_mutex_lock(&data->data_mutex);
	if (state == -1)
		printf("%ld %d has taken a fork\n", get_time() - data->start,
			philo->number);
	if (state == 1)
		printf("\033[1;32m%ld %d is thinking\033[0m\n", get_time()
			- data->start, philo->number);
	if (state == 2)
		printf("\033[1;93m%ld %d is eating\033[0m\n", get_time() - data->start,
			philo->number);
	if (state == 3)
		printf("\033[96m%ld %d is sleeping\033[0m\n", get_time() - data->start,
			philo->number);
	pthread_mutex_unlock(&data->data_mutex);
}

static int	ft_isdigit(int c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	return (0);
}

static int	ft_isint(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}

int	input_valid(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (!ft_isint(argv[i]))
			return (0);
		i++;
	}
	if (argc == 6)
	{
		if (!ft_isint(argv[i]))
			return (0);
	}
	return (1);
}
