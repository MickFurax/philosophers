/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:05:45 by arabeman          #+#    #+#             */
/*   Updated: 2024/06/24 08:10:05 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

/*
** state
** -1: fork
** 0: dead
** 1: thinking
** 2: eating
** 3: sleeping
*/
void	eating(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = philo->rfork;
	second_fork = philo->lfork;
	if (philo->number % 2)
	{
		first_fork = philo->lfork;
		second_fork = philo->rfork;
	}
	philo->last_meal = get_time();
	pthread_mutex_lock(first_fork);
	ft_print(data, philo, -1);
	pthread_mutex_lock(second_fork);
	ft_print(data, philo, -1);
	ft_print(data, philo, 2);
	philo->state = 2;
	ft_sleep(data->time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_lock(&data->data_mutex);
	data->finished_eating++;
	pthread_mutex_unlock(&data->data_mutex);
	philo->spagh_eaten++;
	check_death(data, philo);
}

void	sleeping(t_data *data, t_philo *philo)
{
	if (ft_no_deaths(data))
	{
		ft_print(data, philo, 3);
		philo->state = 3;
		ft_sleep(data->time_to_sleep);
		philo->state = -1;
		if (data->time_to_sleep <= 1)
		{
			while (is_priority(data, philo) && ft_no_deaths(data))
				ft_sleep(0);
		}
		check_death(data, philo);
	}
}

void	thinking(t_data *data, t_philo *philo)
{
	if (ft_no_deaths(data))
	{
		ft_print(data, philo, 1);
		philo->state = 1;
		check_death(data, philo);
	}
}
