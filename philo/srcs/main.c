/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 07:56:23 by arabeman          #+#    #+#             */
/*   Updated: 2024/06/20 07:56:32 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	*routine(void *param)
{
	t_arg	*arg;
	t_philo	*philo;
	t_data	*data;
	int		priority;

	priority = 0;
	arg = (t_arg *)param;
	data = arg->data;
	philo = arg->philo;
	while (ft_no_deaths(data))
	{
		check_death(data, philo);
		priority = is_priority(data, philo);
		if (priority && ft_no_deaths(data))
		{
			eating(data, philo);
			sleeping(data, philo);
		}
		if (philo->state == -1 && ft_no_deaths(data))
			thinking(data, philo);
		ft_sleep(0);
	}
	return (arg);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if ((argc == 5 || argc == 6) && input_valid(argc, argv))
	{
		if (argc == 6 && !ft_atoi(argv[5]))
			return (0);
		init_data(&data, argc, argv);
		launch_philos(&data);
		update_priority(&data);
		whoisdead(&data);
		free_data(&data);
	}
	else
		write(2, "Error: Invalid input\n", 22);
	return (0);
}
