/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:59:58 by arabeman          #+#    #+#             */
/*   Updated: 2024/05/20 11:00:01 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* first_fork is the fork to the right of the first philosopher
last_fork is the fork to the left of the first philosopher
last_fork is the fork to the right of the first philosopher if there is only one philosopher
nb: same for the last_philosopher */
typedef struct s_data
{
	int				philosophers;
	t_philosopher	*first_philo;
	t_philosopher	*last_philo;
	int				forks_number;
	int				*first_fork;
	int				*last_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_philosopher_must_eat;
}					t_data;

/* state
0: dead
1: thinking
2: eating */
typedef struct s_philospher
{
	pthread_t		thread;
	int				number;
	int				state;
	int				fork_held;
	int				*right_fork;
	int				*left_fork;
	t_philosopher	*right_philo;
	t_philosopher	*left_philo;
	int				spagh_eaten;
}					t_philosopher;

#endif
