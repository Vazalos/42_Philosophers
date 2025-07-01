/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:46:30 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/30 14:08:57 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <stdio.h>

void	ft_error_message(int error)
{
	if (error == 0)
		printf("Argument error. For proper usage provide:\n \
			1 - number_of_philosophers (0 - 200)\n2 - time_to_die (>60ms)\n \
			3 - time_to_eat (>60ms)\n4 - time_to_sleep (>60ms)\n \
			5 - max_number_of_meals (optional)\n");
	else if (error == 1)
		printf("undefined error\n");
}

int ft_parse_args(t_data *table, int argc, char** argv) //EVERYTHING HAS TO BE NON NEGATIVE
{
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_error_message(0), 1);
	table->n_philo = ft_check_atol(argv[1]);
	table->die_time = ft_check_atol(argv[2]);
	table->eat_time	= ft_check_atol(argv[3]);
	table->sleep_time = ft_check_atol(argv[4]);
	if (argv[5])
		table->meal_limit = ft_check_atol(argv[5]);
	if (table->die_time < 60
		|| table->eat_time < 60
		|| table->sleep_time < 60
		|| table->n_philo <= 0 || table->n_philo > 200
		|| (argv[5] && table->meal_limit <= 0))
		return (ft_error_message(0), 1);
	pthread_mutex_init(&table->is_ready, NULL);
	return (0);
}

int	ft_init_data(void)
{
	return (0);
 //CHANGE TIMES to *1000, fix parse
}

int	ft_init_philos(t_data *table)
{
	int	i;

	i = -1;
	table->philo_arr = malloc((table->n_philo + 1) * sizeof(t_philo));
	if (!table->philo_arr)
		return (1);
	while (++i <= table->n_philo)
	{
		table->philo_arr[i].id = i + 1;
		table->philo_arr[i].meals_eaten = 0;
		table->philo_arr[i].time_since_meal = 0;
		table->philo_arr[i].is_dead = 0;
		table->philo_arr[i].is_full = 0;
		table->philo_arr[i].table = table;
		table->philo_arr[i].r_fork = &(table->fork_arr[i].fork);
		if (i == table->n_philo - 1)
			table->philo_arr[i].l_fork = &(table->fork_arr[0].fork);
		else
			table->philo_arr[i].l_fork = &(table->fork_arr[i + 1].fork);
	}
	return (0);
}

int	ft_init_forks(t_data *table)
{
	int	i;

	i = -1;
	table->fork_arr = malloc((table->n_philo + 1) * sizeof(t_fork));
	if (!table->fork_arr)
		return (1);
	while (++i <= table->n_philo)
	{
		pthread_mutex_init(&(table->fork_arr[i].fork), NULL);
		table->fork_arr[i].id = i + 1;
	}
	return (0);
}

int	ft_init_threads(t_data *table)
{
	pthread_t	*thread;
	int			i;

	pthread_mutex_lock(&table->is_ready);
	i = -1;
	thread = malloc((table->n_philo + 1) * sizeof(pthread_t));
	if (!thread)
		return (1);
	thread[table->n_philo] = 0;
	pthread_mutex_unlock(&table->is_ready);
	pthread_mutex_destroy(&table->is_ready); //is this correct positioning?
	while (++i < table->n_philo)
		if (pthread_create(&thread[i], NULL, &ft_routine, &table->philo_arr[i]) != 0)
			return (1);
	i = -1;
	while (++i < table->n_philo)
		if (pthread_join(thread[i], NULL) != 0)
			return (2);
	return (0);
}
