/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:07:08 by arabeman          #+#    #+#             */
/*   Updated: 2024/06/20 09:07:14 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

void	init_priority(t_data *data);

void	init_data(t_data *data, int argc, char *argv[])
{
	data->philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->times_each_philosopher_must_eat = -1;
	if (argc == 6)
		data->times_each_philosopher_must_eat = ft_atoi(argv[5]);
	data->finished_eating = 0;
	data->no_deaths = 1;
	data->whoisdead = 0;
	if (pthread_mutex_init(&data->data_mutex, NULL))
		return ;
	create_philos(data);
	init_priority(data);
}

void	free_data(t_data *data)
{
	int		i;
	void	*arg;

	i = 0;
	while (i < data->philosophers)
	{
		pthread_join(data->philos[i]->thread, &arg);
		free(arg);
		i++;
	}
	while (i--)
	{
		pthread_mutex_destroy(&data->philos[i]->philo_mutex);
		pthread_mutex_destroy(data->philos[i]->rfork);
		free(data->philos[i]->rfork);
		free(data->philos[i]);
	}
	pthread_mutex_destroy(&data->data_mutex);
	free(data->priority);
	free(data->philos);
}
