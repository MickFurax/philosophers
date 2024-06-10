/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:00:23 by arabeman          #+#    #+#             */
/*   Updated: 2024/06/05 09:24:06 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

void	thinking(t_data *data, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (is_priority(data, philo))
		{
			pthread_mutex_unlock(&data->data_mutex);
			break ;
		}
		if (philo->state == -1)
		{
			philo->last_meal = get_time();
			philo->state = 1;
			printf("%ld %d is thinking\n", get_time() - data->start,
				philo->number);
		}
		pthread_mutex_unlock(&data->data_mutex);
	}
}

void	eating(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	printf("%ld %d has taken a fork\n", get_time() - data->start,
		philo->number);
	philo->fork_held++;
	pthread_mutex_lock(philo->lfork);
	printf("%ld %d has taken a fork\n", get_time() - data->start,
		philo->number);
	philo->fork_held++;
	if (philo->fork_held == 2)
	{
		printf("%ld %d is eating\n", get_time() - data->start, philo->number);
		philo->state = 2;
		ft_sleep(data->time_to_eat);
	}
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	sleeping(t_data *data, t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time() - data->start, philo->number);
	ft_sleep(data->time_to_sleep);
	pthread_mutex_lock(&data->data_mutex);
	printf("%ld %d is thinking\n", get_time() - data->start, philo->number);
	pthread_mutex_unlock(&data->data_mutex);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	ft_getstart(data);
	while (1)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->start != 0)
		{
			pthread_mutex_unlock(&data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->data_mutex);
	}
	while (1)
	{
		thinking(data, philo);
		eating(data, philo);
		sleeping(data, philo);
		pthread_mutex_lock(&data->data_mutex);
		get_priority(data);
		pthread_mutex_unlock(&data->data_mutex);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	int		i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		ft_initdata(&data, argv);
		if (argc == 6)
			data.times_each_philosopher_must_eat = atoi(argv[5]);
		while (i < data.philosophers)
		{
			philo = data.philos[i];
			pthread_create(&philo->thread, NULL, ft_routine, (void *)philo);
			i++;
		}
		ft_freedata(&data);
	}
	else
		write(2, "Error: Invalid input\n", 22);
	return (0);
}

// To do: when argv[5] is invalid
