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

int ft_parse_args(t_data *table, int argc, char** argv) //EVERYTHING HAS TO BE NON NEGATIVE
{
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (printf("n_philo, t_to_die, t_to_eat, t_to_sleep, n_meals"), 1);
	table->n_philo = ft_atoi(argv[1]);
	table->die_time = ft_atoi(argv[2]);
	table->eat_time	= ft_atoi(argv[3]);
	table->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		table->meal_limit = ft_atoi(argv[5]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data *table;

	if (ft_parse_args(table, argc, argv) != 0)
		return(1);
}
