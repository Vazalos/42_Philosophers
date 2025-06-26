/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:03:15 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/23 15:08:27 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>

int ft_parse_args(t_data *table, int argc, char** argv) //EVERYTHING HAS TO BE NON NEGATIVE
{
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (printf("n_philo, t_to_die, t_to_eat, t_to_sleep, n_meals"), 1);	
	table->n_philo = ft_check_atol(argv[1]);
	table->die_time = ft_check_atol(argv[2]) * 1000;
	table->eat_time	= ft_check_atol(argv[3]) * 1000;
	table->sleep_time = ft_check_atol(argv[4]) * 1000;
	printf("n_philo %lu, die_t %lums, eat_t %lums, sleep_t %lums\n", table->n_philo, table->die_time/1000, table->eat_time/1000, table->sleep_time/1000);
	if (argv[5])
	{
		table->meal_limit = ft_check_atol(argv[5]);
		printf("meal limit %lu\n", table->meal_limit);
	}
	if (table->die_time < 60000
		|| table->eat_time < 60000
		|| table->sleep_time < 60000
		|| table->n_philo < 0 || table->n_philo > 200
		|| (argv[5] && table->meal_limit < 0))
		return (printf("wrong parameters"), 1);
	return (0);
}

int	ft_init_philos(t_data *table)
{
	int	i;

	i = 1;
	table->philo_arr = malloc((table->n_philo + 1) * sizeof(t_philo));
	if (!table->philo_arr)
		return (1);
	while (i <= table->n_philo)
	{
		table->philo_arr[i].id = i;
		table->philo_arr[i].meals_eaten = 0;
		table->philo_arr[i].time_since_meal = 0;
		table->philo_arr[i].is_dead = 0;
		table->philo_arr[i].is_full = 0;
		table->philo_arr[i].table = table;
		//printf("philo n%i, ate %i times, is dead? %i\n", table->philo_arr[i].id,
		//		table->philo_arr[i].meals_eaten, table->philo_arr[i].is_dead);
		i++;
	}
	return (0);
}

void*	ft_routine(void* arg)
{
	t_data	*table;
	int i;

	table = (t_data *)arg;
	i = 0;
	//pthread_mutex_lock(&table->mutex);
	//pthread_mutex_unlock(&table->mutex);
	return(NULL);
}

int	ft_init_threads(t_data *table)
{
	pthread_t	*thread;
	int			i;

	i = 0;
	thread = malloc((table->n_philo + 1) * sizeof(pthread_t));
	if (!thread)
		return (1);
	thread[table->n_philo] = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&thread[i], NULL, &ft_routine, table) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (2);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data table;

	if (ft_parse_args(&table, argc, argv) != 0)
		return(1);
	//pthread_mutex_init(&table.mutex, NULL); //MUTEX INIT
	ft_init_philos(&table);
	ft_init_threads(&table);
	//pthread_mutex_destroy(&table.mutex);
}
