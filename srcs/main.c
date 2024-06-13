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

void	ft_waitstart(t_data *data)
{
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
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	// ft_getstart(data);
	// ft_waitstart(data);
	while (1)
	{
		// thinking(data, philo);
		// eating(data, philo);
		// philo->state = 3;
		// sleeping(data, philo);
		pthread_mutex_lock(&data->data_mutex);
		if (is_priority(data, philo))
		{
			printf("%d is priority\n", philo->number);
			data->finished_eating++;
		}
		pthread_mutex_unlock(&data->data_mutex);
		ft_sleep(200);
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
			if (data.finished_eating == data.philosophers / 2)
			{
				data.finished_eating = 0;
				get_priority(&data);
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
