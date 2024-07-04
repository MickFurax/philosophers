/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:53:22 by arabeman          #+#    #+#             */
/*   Updated: 2024/06/21 14:53:28 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

int	ft_no_deaths(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->data_mutex);
	i = data->no_deaths;
	pthread_mutex_unlock(&data->data_mutex);
	return (i);
}

void	check_death(t_data *data, t_philo *philo)
{
	if (philo->number == data->philosophers
		&& philo->spagh_eaten == data->times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->no_deaths = 0;
		pthread_mutex_unlock(&data->data_mutex);
		return ;
	}
	if ((get_time() - philo->last_meal) > (size_t)data->time_to_die)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->no_deaths = 0;
		data->whoisdead = philo->number;
		pthread_mutex_unlock(&data->data_mutex);
		philo->state = 0;
	}
}

void	whoisdead(t_data *data)
{
	int	dead_philo;

	pthread_mutex_lock(&data->data_mutex);
	dead_philo = data->whoisdead;
	pthread_mutex_unlock(&data->data_mutex);
	if (dead_philo)
	{
		pthread_mutex_lock(&data->data_mutex);
		printf("\033[38;5;197m%ld %d died\033[0m\n", get_time() - data->start,
			dead_philo);
		pthread_mutex_unlock(&data->data_mutex);
	}
}
