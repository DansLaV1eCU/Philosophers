/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:11:01 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/23 17:41:34 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *tab)
{
	tab->general_mutexes_to_destroy = 0;
	if (pthread_mutex_init(&tab->mutex_to_print, NULL) != 0)
		return (error(tab, STR_ERR_MUTEX, "mutex_to_print init", EXIT_FAILURE));
	tab->general_mutexes_to_destroy++;
	if (pthread_mutex_init(&tab->mutex_to_stop, NULL) != 0)
		return (error(tab, STR_ERR_MUTEX, "mutex_to_stop init", EXIT_FAILURE));
	tab->general_mutexes_to_destroy++;
	if (pthread_mutex_init(&tab->mutex_min_times_ate, NULL) != 0)
		return (error(tab, STR_ERR_MUTEX, "mutex_min_times_ate init",
				EXIT_FAILURE));
	tab->general_mutexes_to_destroy++;
	return (EXIT_SUCCESS);
}

int	init_forks(t_table *tab)
{
	pthread_mutex_t	*mutexes;
	int				i;

	mutexes = malloc(sizeof(pthread_mutex_t) * tab->nb_p);
	if (!mutexes)
		return (error(tab, STR_ERR_MALLOC, "init_mutex", EXIT_FAILURE));
	i = 0;
	tab->locks_to_destroy = 0;
	while (i < tab->nb_p)
	{
		if (pthread_mutex_init(mutexes + i, NULL) != 0)
			return (error(tab, STR_ERR_MUTEX, "locks init", EXIT_FAILURE));
		tab->locks_to_destroy++;
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
