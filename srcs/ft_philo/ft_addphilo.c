/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addphilo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:33:44 by arabeman          #+#    #+#             */
/*   Updated: 2024/04/05 13:33:45 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../philosophers.h"

void	ft_addphilo(t_philo **philos, t_philo *newphilo)
{
	t_philo	*last;
	t_fork			*fork;

	if (!newphilo)
		return ;
	fork = ft_newfork(newphilo);
	if (!fork)
		return ;
	newphilo->right_fork = fork;
	if (*philos)
	{
		last = ft_lastphilo(*philos);
		last->right_philo = newphilo;
		newphilo->left_philo = last;
		newphilo->right_philo = *philos;
		(*philos)->left_philo = newphilo;
		newphilo->left_fork = last->right_fork;
	}
	else
	{
		(*philos) = newphilo;
		newphilo->right_philo = newphilo;
		newphilo->left_philo = newphilo;
		newphilo->left_fork = fork;
	}
}
