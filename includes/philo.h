/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:20:22 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/11 23:47:49 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/******************************************************************************
 *                                     Macros                                  *
 ******************************************************************************/

# define STR_PROG_NAME "philo:"
# define STR_USAGE \
	"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n\
Each number is a positive integer\n"
# define STR_ERR_THREAD "%s error: Could not create thread.\n"
# define STR_ERR_MALLOC "%s error: Could not allocate memory.\n"
# define STR_ERR_MUTEX "%s error: Could not create mutex.\n"

/******************************************************************************
*                                 Structures									*
 ******************************************************************************/

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct					s_table
{
	int					nb_p;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					times_eat_to_end;
	long				start_time;
	bool				stop;
	int					min_lunches;
	pthread_mutex_t		*mutex_to_print;
	pthread_t			*threads;
	pthread_mutex_t		*locks;
	t_philo				*philos;
};

struct					s_philo
{
	int					p_number;
	int					times_ate;
	long				last_time_ate;
	int					left_fork;
	int					right_fork;
	t_table				*table;
};

/******************************************************************************
 *                           Function Prototypes                               *
 ******************************************************************************/

// check.c
bool					check_alive(t_table *tab);
bool					check_times_ate(t_table *tab);

// init.c
int						init(t_table *tab);
int						init_philos(t_table *tab);
int						init_mutex(t_table *tab);
int						init_threads(t_table *tab);

// params.c
int						check_params(int len, char **s, t_table *tab);
int						philo_atoi(char *str);

// routine.c
void					eating(t_table *tab, t_philo *philo);
void					sleeping(t_table *tab, t_philo *philo);
void					thinking(t_table *tab, t_philo *philo);
void					fork_is_taken(t_table *tab, t_philo *philo, int fork);

// simulation.c
int						start_simulation(t_table *tab);
void					*simulation(t_philo *philo);

// utils.c
void					free_all(t_table *tab);
long					get_time_ms(void);
void					print_message(t_table *tab, long time, int p_nb,
							const char *s);
void					destroy_mutex(t_table *tab);
void					philo_died(t_table *tab, long time, int nb);

// error.c
int						error(t_table *tab, char *str, char *detail,
							int exit_nb);

#endif
