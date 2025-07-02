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
	int		*ret_val;

	ret_val = malloc(sizeof(int));
	philo = (t_philo *)arg;
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (*ret_val = 1, ret_val);
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (*ret_val = 1, ret_val);

	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (*ret_val = 2, ret_val);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (*ret_val = 2, ret_val);
	return (*ret_val = 0, ret_val);
}

int	main(int argc, char **argv)
{
	t_data table;

	if (ft_parse_args(&table, argc, argv) != 0)
		return(ft_error_message(1), 1);	
	if (ft_init_data(&table) != 0)
		return(ft_error_message(2), 2);
}

void	ft_error_message(int error)
{
	if (error == 0)
		printf("Argument error. For proper usage provide:\n \
			1 - number_of_philosophers (0 - 200)\n2 - time_to_die (>60ms)\n \
			3 - time_to_eat (>60ms)\n4 - time_to_sleep (>60ms)\n \
			5 - max_number_of_meals (optional)\n");
	else if (error == 1)
		printf("Init error\n");
	else if (error == 2)
		printf("undef\n");
}

