/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:09:42 by david-fe          #+#    #+#             */
/*   Updated: 2025/06/23 15:45:51 by david-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef enum e_time_format
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}	t_time_format;

typedef enum e_event
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_event;

typedef struct	s_data t_data;
typedef			pthread_mutex_t mutex;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	size_t		last_meal_time;
	int			is_full;
	mutex		*l_fork;
	mutex		*r_fork;
	t_data		*table;
}	t_philo;

typedef struct s_fork
{
	int			id;
	mutex		fork;
}	t_fork;

typedef struct s_data
{
	int			n_philo;
	size_t		die_time;
	size_t		eat_time;
	size_t		sleep_time;
	int			meal_limit;
	int			full_philos;
	size_t		start_time;
	t_philo		*philo_arr;
	pthread_t	*thread_arr;
	t_fork		*fork_arr;
	mutex		is_ready;
	int			end_simul;
	pthread_t	monitor;
}	t_data;

// MAIN.C
int		main(int argc, char **argv);
size_t	ft_get_time(t_time_format format);
void	ft_usleep(size_t wait_time);
void	ft_error_message(int error);
int		ft_free_allocs(t_data *table);

// INITS.C
int		ft_parse_args(t_data *table, int argc, char** argv);
int		ft_init_data(t_data *table);
int		ft_alloc_arr(t_data *table);
void	ft_init_philos(t_data *table);
int		ft_init_threads(t_data *table);

// ROUTINE.C
void*	ft_routine(void* arg);
void	ft_print_message(t_event event, t_philo* philo);
int		ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);

// UTILS.C
long	ft_check_atol(const char *str);

// MONITOR.C
void	ft_monitor_routine(t_data *table);
int		ft_monitor_end_check(t_philo *philo, t_data *table);

#endif
