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

// void	ft_takeforks(t_philo *philo, t_data *data)
// {
// 	char	*forks;
// 	int		index;

// 	forks = data->forks;
// 	index = philo->number - 1;
// 	if (forks[index] - 48 == 1)
// 	{
// 		forks[index] = '0';
// 		printf("%d has taken a fork\n", philo->number);
// 		printf("%s\n", forks);
// 	}
// 	if (forks[index - 1] - 48 == 1)
// 	{
// 		forks[index - 1] = '0';
// 		printf("%d has taken a fork\n", philo->number);
// 	}
// }

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (no_died(data))
	{
		pthread_mutex_lock(&philo->philo_mutex);
		// printf("%s\n", data->forks);
		// if (philo->state == -1)
		// ft_takeforks(philo, data);
		if (philo->number == 6)
		{
			philo->state = 0;
			printf("Someone died\n");
			break ;
		}
		printf("%c\n", data->forks[0]);
		(void)data;
		pthread_mutex_unlock(&philo->philo_mutex);
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
