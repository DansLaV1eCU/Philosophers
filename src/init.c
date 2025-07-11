/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:10:42 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/11 18:02:44 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_table *tab)
{
	pthread_mutex_t	*print_mutex;

	print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!print_mutex)
		return (error(tab, STR_ERR_MALLOC, "init", EXIT_FAILURE));
	if (pthread_mutex_init(print_mutex, NULL) != 0)
		return (error(tab, STR_ERR_MUTEX, "mutex_to_print init", EXIT_FAILURE));
	tab->mutex_to_print = print_mutex;
	if (init_mutex(tab) != 0)
		return (EXIT_FAILURE);
	if (init_philos(tab) != 0)
		return (EXIT_FAILURE);
	if (init_threads(tab) != 0)
		return (EXIT_FAILURE);
	tab->stop = false;
	tab->min_lunches = -1;
	return (EXIT_SUCCESS);
}

int	init_philos(t_table *tab)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * tab->nb_p);
	if (!philos)
		return (error(tab, STR_ERR_MALLOC, "init_philos", EXIT_FAILURE));
	i = 0;
	while (i < tab->nb_p)
	{
		philos[i].p_number = i + 1;
		philos[i].times_ate = 0;
		philos[i].table = tab;
		philos[i].right_fork = i;
		philos[i].left_fork = i + 1;
		philos[i].last_time_ate = 0;
		if (i == 0)
			philos[i].right_fork = tab->nb_p;
		i++;
	}
	tab->philos = philos;
	return (EXIT_SUCCESS);
}

int	init_mutex(t_table *tab)
{
	pthread_mutex_t	*mutexes;
	int				i;

	mutexes = malloc(sizeof(pthread_mutex_t) * tab->nb_p);
	if (!mutexes)
		return (error(tab, STR_ERR_MALLOC, "init_mutex", EXIT_FAILURE));
	i = 0;
	while (i < tab->nb_p)
	{
		if (pthread_mutex_init(mutexes + i, NULL) != 0)
			return (error(tab, STR_ERR_MUTEX, "locks init", EXIT_FAILURE));
		i++;
	}
	tab->locks = mutexes;
	return (EXIT_SUCCESS);
}

int	init_threads(t_table *tab)
{
	pthread_t	*threads;

	threads = malloc(sizeof(threads) * tab->nb_p);
	if (!threads)
		return (error(tab, STR_ERR_MALLOC, "init_threads", EXIT_FAILURE));
	tab->threads = threads;
	return (EXIT_SUCCESS);
}
