/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:03:15 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/30 14:10:15 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_data table;

	if (ft_parse_args(&table, argc, argv) != 0)
		return(ft_error_message(1), 1);	
	if (ft_init_data(&table) != 0)
		return(ft_error_message(2), 2);
	if (ft_destroy_mutexes(&table))
		return(ft_error_message(3), 3);
	return(0);
}

size_t	ft_get_time(t_time_format format)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	if (format == MICROSECONDS)
		return((time.tv_sec * 1000000) + time.tv_usec);
	else if (format == MILLISECONDS)
		return((time.tv_sec * 1000) + (time.tv_usec / 1000));
	else 
		return (0);
}

void	ft_usleep(size_t wait_time)
{
	size_t	start;

	start = ft_get_time(MICROSECONDS);
	while ((ft_get_time(MICROSECONDS) - start) < wait_time)
		usleep(500);
}

int	ft_destroy_mutexes(t_data *table)
{
	int	i;

	i = -1;
	if(pthread_mutex_destroy(&(table->is_ready)) != 0)
		return (2);
	while (++i < table->n_philo)
	{
		if(pthread_mutex_destroy(&(table->fork_arr[i].fork)) != 0)
			return (1);
	}
	return(0);
}

void	ft_error_message(int error)
{
	if (error == 1)
		printf("Argument error. For proper usage provide:\n"
			"	1. number_of_philosophers (0 - 200)\n"
			"	2. time_to_die (>60ms)\n"
			"	3. time_to_eat (>60ms)\n"
			"	4. time_to_sleep (>60ms)\n"
			"	5. max_number_of_meals (optional, >=0)\n");
	else if (error == 2)
		printf("Init error\n");
	else if (error == 3)
		printf("Destroy mutex error\n");
}

