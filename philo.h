/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:09:42 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/23 15:45:51 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			time_since_meal;
	int				is_dead;
	int				is_full;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	t_data			*table;
}	t_philo;

typedef struct s_data
{
	long		n_philo;
	long		die_time;
	long		eat_time;
	long		sleep_time;
	long		meal_limit;
	t_philo		*philo_arr;
	pthread_t	*thread_arr;
}	t_data;

// MAIN.C

// UTILS.C
long	ft_check_atol(const char *str);

#endif
