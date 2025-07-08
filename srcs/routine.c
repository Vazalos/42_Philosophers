/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:42:51 by david-fe          #+#    #+#             */
/*   Updated: 2025/07/04 15:57:07 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (pthread_mutex_lock(&philo->table->is_ready) != 0)
		return (NULL);
	if (pthread_mutex_unlock(&philo->table->is_ready) != 0)
		return (NULL);
	philo->last_meal_time = philo->table->start_time;
	if (philo->table->n_philo == 1)
	{
		ft_print_message(FORK, philo);
		ft_usleep(philo->table->die_time);
		ft_print_message(DIE, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->eat_time);
	while (philo->table->end_simul == 0)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (1);
	ft_print_message(FORK, philo);
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (2);
	ft_print_message(FORK, philo);
	if (philo->meals_eaten < philo->table->meal_limit)
		philo->meals_eaten++;
	philo->last_meal_time = ft_get_time(MILLISECONDS);
	ft_print_message(EAT, philo);
	ft_usleep(philo->table->eat_time);
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (3);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (4);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_message(SLEEP, philo);
	usleep(philo->table->sleep_time);
}

void	ft_think(t_philo *philo)
{
	ft_print_message(THINK, philo);
}

void	ft_print_message(t_event event, t_philo *philo)
{
	if (philo->table->end_simul == 0)
	{
		if (event == FORK)
			printf("%zu %i has taken a fork\n", ft_get_time(MILLISECONDS)
				- philo->table->start_time, philo->id);
		else if (event == EAT)
			printf("%zu %i is eating\n", ft_get_time(MILLISECONDS)
				- philo->table->start_time, philo->id);
		else if (event == SLEEP)
			printf("%zu %i is sleeping\n", ft_get_time(MILLISECONDS)
				- philo->table->start_time, philo->id);
		else if (event == THINK)
			printf("%zu %i is thinking\n", ft_get_time(MILLISECONDS)
				- philo->table->start_time, philo->id);
	}
	else if (event == DIE)
		printf("%zu %i died\n", ft_get_time(MILLISECONDS)
			- philo->table->start_time, philo->id);
}
