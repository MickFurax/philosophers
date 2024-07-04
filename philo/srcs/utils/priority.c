/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:17:28 by arabeman          #+#    #+#             */
/*   Updated: 2024/06/25 08:17:30 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

void	init_priority(t_data *data)
{
	int	i;
	int	start;

	i = 0;
	start = 1;
	data->priority = malloc(sizeof(int) * (data->philosophers / 2));
	if (!data->priority)
		return ;
	while (i < data->philosophers / 2)
	{
		data->priority[i] = start;
		start += 2;
		i++;
	}
}

void	get_priority(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers / 2)
	{
		data->priority[i] = data->priority[i] + 1;
		if (data->priority[i] > data->philosophers)
			data->priority[i] = 1;
		i++;
	}
}

int	is_priority(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->data_mutex);
	while (i < data->philosophers / 2)
	{
		if (data->priority[i] == philo->number)
		{
			pthread_mutex_unlock(&data->data_mutex);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}

void	update_priority(t_data *data)
{
	while (ft_no_deaths(data))
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->finished_eating >= data->philosophers / 2)
		{
			data->finished_eating = 0;
			get_priority(data);
		}
		pthread_mutex_unlock(&data->data_mutex);
		ft_sleep(0);
	}
}
