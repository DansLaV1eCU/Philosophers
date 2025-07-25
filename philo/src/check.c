/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:56:38 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/23 20:24:00 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_alive(t_table *tab)
{
	int	i;

	i = 0;
	while (i < tab->nb_p)
	{
		if (check_dead_mutex(tab, &(tab->philos[i])))
		{
			pthread_mutex_lock(&tab->mutex_to_print);
			printf("%ld %d %s\n", get_time_ms() - tab->start_time, i + 1,
				"died");
			pthread_mutex_lock(&tab->mutex_to_stop);
			tab->stop = true;
			pthread_mutex_unlock(&tab->mutex_to_stop);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_times_ate(t_table *tab)
{
	int	i;
	int	min;

	i = 0;
	min = INT_MAX;
	while (i < tab->nb_p)
	{
		pthread_mutex_lock(&tab->philos[i].mutex_times_ate);
		if (tab->philos[i].times_ate < min)
			min = tab->philos[i].times_ate;
		pthread_mutex_unlock(&tab->philos[i++].mutex_times_ate);
	}
	if (min == tab->times_eat_to_end)
	{
		pthread_mutex_lock(&tab->mutex_to_print);
		pthread_mutex_lock(&tab->mutex_to_stop);
		tab->stop = true;
		pthread_mutex_unlock(&tab->mutex_to_stop);
		return (false);
	}
	pthread_mutex_lock(&tab->mutex_min_times_ate);
	tab->min_lunches = min;
	pthread_mutex_unlock(&tab->mutex_min_times_ate);
	return (true);
}

bool	check_dead_mutex(t_table *tab, t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex_last_time_ate);
	if (get_time_ms() - tab->start_time - ph->last_time_ate > tab->time_to_die)
	{
		pthread_mutex_unlock(&ph->mutex_last_time_ate);
		return (true);
	}
	pthread_mutex_unlock(&ph->mutex_last_time_ate);
	return (false);
}

bool	check_stop(t_table *tab)
{
	bool	stop;

	pthread_mutex_lock(&tab->mutex_to_stop);
	stop = tab->stop;
	pthread_mutex_unlock(&tab->mutex_to_stop);
	return (stop);
}
