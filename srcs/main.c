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

	//pthread_mutex_init(&table.mutex, NULL); //MUTEX INIT
	//pthread_mutex_destroy(&table.mutex);
	//pthread_mutex_lock(&table->mutex);
	//pthread_mutex_unlock(&table->mutex);

size_t	ft_get_time(t_time_format format)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	if (format == SECONDS)
		return(time.tv_sec + (time.tv_usec / 1000000));
	else if (format == MILLISECONDS)
		return((time.tv_sec * 1000) + (time.tv_usec / 1000));
	else if (format == MICROSECONDS)
		return((time.tv_sec * 1000000) + time.tv_usec);
	else 
		return (0);
}

void*	ft_routine(void* arg)
{
	t_philo	*philo;
	int i;
	philo = (t_philo *)arg;
	i = 0;
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_data table;

	if (ft_parse_args(&table, argc, argv) != 0)
		return(1);
	ft_init_forks(&table);
	ft_init_philos(&table);
	ft_init_threads(&table);
}
