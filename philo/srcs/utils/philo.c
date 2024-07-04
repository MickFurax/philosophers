/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:15:53 by arabeman          #+#    #+#             */
/*   Updated: 2024/06/20 10:15:57 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

t_philo	*newphilo(int number)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->thread = 0;
	philo->number = number;
	philo->state = -1;
	philo->spagh_eaten = 0;
	philo->last_meal = 0;
	philo->rfork = malloc(sizeof(pthread_mutex_t));
	if (!philo->rfork)
		return (NULL);
	if (pthread_mutex_init(philo->rfork, NULL))
		return (NULL);
	philo->lfork = NULL;
	return (philo);
}

void	create_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo *) * data->philosophers);
	if (!data->philos)
		return ;
	while (i < data->philosophers)
	{
		data->philos[i] = newphilo(i + 1);
		if (pthread_mutex_init(&data->philos[i]->philo_mutex, NULL))
			return ;
		i++;
	}
	while (i--)
	{
		if (i == 0)
			data->philos[i]->lfork = data->philos[data->philosophers
				- 1]->rfork;
		else
			data->philos[i]->lfork = data->philos[i - 1]->rfork;
	}
}

void	launch_philos(t_data *data)
{
	int		i;
	t_arg	*arg;
	t_philo	*philo;

	i = 0;
	data->start = get_time();
	while (i < data->philosophers)
	{
		arg = malloc(sizeof(t_arg));
		philo = data->philos[i];
		philo->last_meal = get_time();
		arg->data = data;
		arg->philo = philo;
		pthread_create(&philo->thread, NULL, routine, (void *)arg);
		i++;
	}
}
