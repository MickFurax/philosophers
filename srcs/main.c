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
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

void *routine(void *arg)
{
	__uint64_t number = (__uint64_t)arg;
	printf("%ld\n", number);
}

int	main(void)
{
	pthread_t philo;
	pthread_create(&philo, NULL, routine, (void *)1);
	pthread_join(philo, NULL);
	return (0);
}
