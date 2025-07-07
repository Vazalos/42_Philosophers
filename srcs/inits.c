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

int ft_parse_args(t_data *table, int argc, char** argv)
{
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_error_message(0), 1);
	table->n_philo = ft_check_atol(argv[1]);
	table->die_time = ft_check_atol(argv[2]) * 1e3;
	table->eat_time	= ft_check_atol(argv[3]) * 1e3; 
	table->sleep_time = ft_check_atol(argv[4]) * 1e3;
	if (argv[5])
		table->meal_limit = ft_check_atol(argv[5]);
	else
		table->meal_limit = -1;
	if (table->die_time < (60 * 1e3)
		|| table->eat_time < (60 * 1e3)
		|| table->sleep_time < (60 * 1e3)
		|| table->n_philo <= 0 || table->n_philo > 200
		|| (argv[5] && table->meal_limit < 0)) // SHOULD THIS BE POSSIBLY 0?
		return (1);
	return (0);
}

int	ft_init_data(t_data *table)
{
	int	i;

	i = -1;
	if (ft_alloc_arr(table) != 0)
		return (1);
	while (++i < table->n_philo)
	{
		if(pthread_mutex_init(&(table->fork_arr[i].fork), NULL) != 0)
			return (2);
		table->fork_arr[i].id = i + 1;
	}
	if (pthread_mutex_init(&table->is_ready, NULL) != 0)
		return (3);
	table->end_simul = 0;
	table->full_philos = 0;
	ft_init_philos(table);
	if (ft_init_threads(table) != 0)
		return (4);
	return(0);
}

int	ft_alloc_arr(t_data *table)
{
	int philo;

	philo = table->n_philo;
	table->philo_arr = malloc(philo * sizeof(t_philo));
	if (!table->philo_arr)
		return (1);
	table->fork_arr = malloc(philo * sizeof(t_fork));
	if (!table->fork_arr)
		return (free(table->philo_arr), 2);
	table->thread_arr = malloc(philo * sizeof(pthread_t));
	if (!table->thread_arr)
		return (free(table->philo_arr), free(table->fork_arr), 3);
	return (0);
}

void	ft_init_philos(t_data *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		table->philo_arr[i].id = i + 1;
		table->philo_arr[i].meals_eaten = 0;	
		table->philo_arr[i].last_meal_time = 0;
		table->philo_arr[i].is_full = 0;
		table->philo_arr[i].table = table;
		table->philo_arr[i].r_fork = &(table->fork_arr[i].fork);
		if (i == table->n_philo - 1)
			table->philo_arr[i].l_fork = &(table->fork_arr[0].fork);
		else
			table->philo_arr[i].l_fork = &(table->fork_arr[i + 1].fork);
	}
}

int	ft_init_threads(t_data *table)
{
	int	i;

	i = -1;
	if (pthread_create(&table->monitor, NULL, &ft_monitor_routine, &table) != 0)
		return (1);
	if (pthread_mutex_lock(&table->is_ready) != 0)
		return (2);
	while (++i < table->n_philo)
	{
		if (pthread_create(&table->thread_arr[i], NULL, &ft_routine, &table->philo_arr[i]) != 0)
			return (3);
		//printf("thread %i is %lu\n", i, (unsigned long)table->thread_arr[i]);
	}
	table->start_time = ft_get_time(MILLISECONDS); // is this where I position this?	
	if (pthread_mutex_unlock(&table->is_ready) != 0)
		return (4);
	i = -1;
	while (++i < table->n_philo)
		if (pthread_join(table->thread_arr[i], NULL) != 0)
			return (5);
	return (0);	
}
