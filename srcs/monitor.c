/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:54:15 by david-fe          #+#    #+#             */
/*   Updated: 2025/07/07 13:02:54 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_monitor_end_check(t_philo *philo, t_data *table)
{
	if (ft_get_time(MILLISECONDS) - philo->last_meal_time > table->die_time)
	{
		table->end_simul = 1;
		return(1);
	}
	else if (philo->meals_eaten == table->meal_limit && philo->is_full == 0)
	{
		philo->is_full = 1;
		table->full_philos++;
	}
	if (table->full_philos == table->meal_limit)
	{
		table->end_simul = 2;
		return (2);
	}
	return(0);
}

void	*ft_monitor_routine(void *arg)
{
	t_data	*table;
	int		i;
	int		result;

	table = (t_data *)arg;
	i = -1;
	while(1)
	{
		result = ft_monitor_end_check(&table->philo_arr[++i], table);
		printf("%i", result);
		if (result != 0)
			break;
		if (i == table->n_philo)
			i = -1;
	}
	if (result == 1)
		ft_print_message(DIE, &table->philo_arr[i]);
	return(NULL);
}
