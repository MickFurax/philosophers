/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:00:23 by arabeman          #+#    #+#             */
/*   Updated: 2024/05/20 11:00:25 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

int	no_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers)
	{
		if (data->philos[i]->state == 0)
			return (0);
		i++;
	}
	return (1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		break;
	}
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
