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

	arg = (t_arg *)param;
	// t_data *data = arg->data;
	philo = arg->philo;
	while (1)
	{
		printf("%d\n", philo->number);
		break;
	}
	return (arg);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		init_data(&data, argc, argv);
		launch_philos(&data);
		//
		free_data(&data);
	}
	else
		write(2, "Error: Invalid input\n", 22);
	return (0);
}
