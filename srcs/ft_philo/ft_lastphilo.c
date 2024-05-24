/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastphilo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:00:02 by arabeman          #+#    #+#             */
/*   Updated: 2024/04/18 09:19:41 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosophers.h"

t_philo *ft_lastphilo(t_philo *philo)
{
	t_philo *last;
	if (!philo)
		return (NULL);
	last = philo;
	while (last->right_philo != philo)
		last = last->right_philo;
	return (last);	
}
