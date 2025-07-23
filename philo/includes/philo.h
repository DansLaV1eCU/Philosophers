/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:20:22 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/23 20:23:22 by danslav1e        ###   ########.fr       */
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
# include <limits.h>

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
	int					locks_to_destroy;
	int					general_mutexes_to_destroy;
	pthread_mutex_t		mutex_to_print;
	pthread_mutex_t		mutex_to_stop;
	pthread_mutex_t		mutex_min_times_ate;
	pthread_mutex_t		*locks;
	pthread_t			*threads;
	t_philo				*philos;
};

struct					s_philo
{
	int					p_number;
	int					times_ate;
	long				last_time_ate;
	int					left_fork;
	int					right_fork;
	int					destr_lta_mutex;
	int					destr_ta_mutex;
	pthread_mutex_t		mutex_last_time_ate;
	pthread_mutex_t		mutex_times_ate;
	t_table				*table;
};

/******************************************************************************
 *                           Function Prototypes                               *
 ******************************************************************************/

// check.c
bool					check_alive(t_table *tab);
bool					check_times_ate(t_table *tab);
bool					check_dead_mutex(t_table *tab, t_philo *ph);
bool					check_stop(t_table *tab);

// init.c
int						init(t_table *tab);
int						init_philos(t_table *tab);
int						init_philos_2(t_table *tab, t_philo *ph, int nb);

// init_2.c
int						init_table(t_table *tab);
int						init_forks(t_table *tab);
int						init_threads(t_table *tab);

// params.c
int						check_params(int len, char **s, t_table *tab);
int						philo_atoi(char *str);

// routine.c
void					eating(t_table *tab, t_philo *philo);
void					sleeping(t_table *tab, t_philo *philo);
void					thinking(t_table *tab, t_philo *philo);
int						fork_is_taken(t_table *tab, t_philo *philo, int fork);
void					sleep_time(long time);

// simulation.c
int						start_simulation(t_table *tab);
void					*simulation(t_philo *philo);
bool					check_fork(t_philo *ph);
bool					check_if_time_to_repeat(t_table *tab, t_philo *ph);

// utils.c
long					get_time_ms(void);
void					print_message(t_table *tab, int p_nb, const char *s);

// exit.c
int						error(t_table *tab, char *str, char *detail,
							int exit_nb);
int						free_all(t_table *tab, int rt);
void					free_table(t_table *tab);
void					free_philos(t_table *tab);

#endif
