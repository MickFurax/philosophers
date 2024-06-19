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

void	whoisdead(t_data *data)
{
	int	i;
	int	max;

	i = 1;
	pthread_mutex_lock(&data->data_mutex);
	max = data->philosophers;
	pthread_mutex_unlock(&data->data_mutex);
	while (i <= max)
	{
		pthread_mutex_lock(&data->philos[i - 1]->philo_mutex);
		pthread_mutex_lock(&data->data_mutex);
		if (data->philos[i - 1]->state == 0)
		{
			printf("\033[38;5;197m%ld %d died\033[0m\n", get_time()
				- data->start, data->philos[i - 1]->number);
			pthread_mutex_unlock(&data->philos[i - 1]->philo_mutex);
			pthread_mutex_unlock(&data->data_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->philos[i - 1]->philo_mutex);
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
}

int	ft_no_deaths(t_data *data)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&data->data_mutex);
	i = data->no_deaths;
	pthread_mutex_unlock(&data->data_mutex);
	return (i);
}

void	check_death(t_data *data, t_philo *philo)
{
	if ((get_time() - philo->last_meal) > (size_t)data->time_to_die)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->no_deaths = 0;
		pthread_mutex_unlock(&data->data_mutex);
		philo->state = 0;
	}
}

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
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->data_mutex);
	while (ft_no_deaths(data))
	{
		check_death(data, philo);
		pthread_mutex_lock(&data->data_mutex);
		priority = is_priority(data, philo);
		pthread_mutex_unlock(&data->data_mutex);
		if (priority && ft_no_deaths(data))
		{
			eating(data, philo, time_to_eat);
			check_death(data, philo);
			pthread_mutex_lock(&data->data_mutex);
			data->finished_eating++;
			pthread_mutex_unlock(&data->data_mutex);
			if (ft_no_deaths(data))
			{
				printf("\033[96m%ld %d is sleeping\033[0m\n", get_time()
					- data->start, philo->number);
				ft_sleep(time_to_sleep);
			}
			philo->state = -1;
			priority = 0;
		}
		else if (philo->state == -1 && ft_no_deaths(data))
		{
			printf("\033[1;32m%ld %d is thinking\033[0m\n", get_time()
				- data->start, philo->number);
			philo->state = 1;
		}
	}
	/* if (!philo->state)
	{
		if (ft_no_deaths(data))
		{
			if (data->terminate)
			{
				printf("\033[38;5;197m%ld %d died\033[0m\n", get_time()
					- data->start, philo->number);
			}
			pthread_mutex_lock(&data->data_mutex);
			data->terminate = 0;
			pthread_mutex_unlock(&data->data_mutex);
		}
	} */
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
		while (ft_no_deaths(&data))
		{
			pthread_mutex_lock(&data.data_mutex);
			if (data.finished_eating >= data.philosophers / 2)
			{
				data.finished_eating = 0;
				get_priority(&data);
				// printf("Priority: %d %d\n", data.priority[0],
				// data.priority[1]);
				// printf("\n");
				// printf("\n");
				// printf("\n");
			}
			pthread_mutex_unlock(&data.data_mutex);
		}
		ft_sleep(1);
		whoisdead(&data);
		ft_freedata(&data);
	}
	else
		write(2, "Error: Invalid input\n", 22);
	return (0);
}

// To do: when argv[5] is invalid
