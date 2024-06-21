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
