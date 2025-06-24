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

typedef struct s_philo
{
	int id;
	int meals_eaten;
	int is_dead;
}	t_philo;

typedef struct s_data
{
	int n_philo;
	int	die_time;
	int	eat_time;
	int sleep_time;
	int meal_limit;
	t_philo *philo_arr;
}	t_data;

// MAIN.C

// UTILS.C
int	ft_atoi(const char *str);

#endif
