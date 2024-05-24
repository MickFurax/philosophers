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

void	*ft_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	if (philo)
	{
		printf("%d\n", philo->number);
	}
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philo		*philo;
	int			i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		if (argc == 6)
			data.times_each_philosopher_must_eat = atoi(argv[5]);
		ft_initdata(&data, argv);
		philo = data.first_philo;
		while (i < data.philosophers)
		{
			pthread_create(philo->thread, NULL, ft_routine, (void *)philo);
			philo = philo->right_philo;
			i++;
		}
		ft_freedata(&data);
	}
	else
		write(2, "Error: Invalid input\n", 22);
	return (0);
}

/* void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%d\n", philo->number);
} */

/* int	main(void)
{
	t_philo *philo;
	philo = ft_newphilo(1);
	if (!philo)
		return (1);
	pthread_create(philo->thread, NULL, routine, (void *)philo);
	pthread_join(*(philo->thread), NULL);
	free(philo->thread);
	free(philo);
	return (0);
} */
