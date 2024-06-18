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

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		priority;
	int		time_to_eat;
	int		time_to_sleep;

	philo = (t_philo *)arg;
	data = philo->data;
	priority = 0;
	pthread_mutex_lock(&data->data_mutex);
	time_to_eat = data->time_to_eat;
	time_to_sleep = data->time_to_sleep;
	pthread_mutex_unlock(&data->data_mutex);
	while (1)
	{
		pthread_mutex_lock(&data->data_mutex);
		priority = is_priority(data, philo);
		pthread_mutex_unlock(&data->data_mutex);
		if (priority)
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
				printf("\033[1;93m%ld %d is eating\033[0m\n", get_time()
					- data->start, philo->number);
				philo->state = 2;
				ft_sleep(time_to_eat);
				pthread_mutex_lock(&data->data_mutex);
				data->finished_eating++;
				pthread_mutex_lock(&philo->philo_mutex);
				philo->last_meal = get_time();
				pthread_mutex_unlock(&philo->philo_mutex);
				pthread_mutex_unlock(&data->data_mutex);
			}
			pthread_mutex_unlock(philo->lfork);
			philo->fork_held--;
			pthread_mutex_unlock(philo->rfork);
			philo->fork_held--;
			priority = 0;
			printf("\033[96m%ld %d is sleeping\033[0m\n", get_time() - data->start,
				philo->number);
			ft_sleep(time_to_sleep);
			philo->state = -1;
		}
		else if (philo->state == -1)
		{
			printf("\033[1;32m%ld %d is thinking\033[0m\n", get_time()
				- data->start, philo->number);
			philo->state = 1;
		}
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
		data.start = get_time();
		while (i < data.philosophers)
		{
			philo = data.philos[i];
			pthread_create(&philo->thread, NULL, ft_routine, (void *)philo);
			i++;
		}
		while (1)
		{
			pthread_mutex_lock(&data.data_mutex);
			if (data.finished_eating >= data.philosophers / 2)
			{
				data.finished_eating = 0;
				get_priority(&data);
				printf("Priority: %d %d\n", data.priority[0], data.priority[1]);
				printf("\n");
			}
			pthread_mutex_unlock(&data.data_mutex);
		}
		ft_freedata(&data);
	}
	else
		write(2, "Error: Invalid input\n", 22);
	return (0);
}

// To do: when argv[5] is invalid
