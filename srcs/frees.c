/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:43:24 by david-fe          #+#    #+#             */
/*   Updated: 2025/07/02 11:58:38 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_free_malloc_err(t_data *table, t_philo *philo, t_fork *fork)
{
	int	i;

	i = -1;
	while (philo && ++i < table->n_philo)
		free(philo[i]);
	free(philo);
	i = -1;
	while (fork && ++i < table->n_philo)
		free(fork[i]);
	free(fork);
}
