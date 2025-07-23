/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:04:12 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/23 19:31:42 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(t_table *tab, char *str, char *detail, int exit_nb)
{
	if (tab)
	{
		pthread_mutex_lock(&tab->mutex_to_stop);
		tab->stop = true;
		pthread_mutex_unlock(&tab->mutex_to_stop);
	}
	if (detail)
		printf(str, STR_PROG_NAME, detail);
	else
		printf(str, STR_PROG_NAME);
	return (exit_nb);
}

int	free_all(t_table *tab, int rt)
{
	int	i;

	i = 0;
	while (i < tab->nb_p)
		pthread_join(tab->threads[i++], NULL);
	free_table(tab);
	if (tab->philos)
		free_philos(tab);
	if (tab->threads)
		free(tab->threads);
	free(tab);
	return (rt);
}

void	free_table(t_table *tab)
{
	int	i;

	if (tab->general_mutexes_to_destroy > 0)
		pthread_mutex_destroy(&tab->mutex_to_print);
	if (tab->general_mutexes_to_destroy > 1)
		pthread_mutex_destroy(&tab->mutex_to_stop);
	if (tab->general_mutexes_to_destroy > 2)
		pthread_mutex_destroy(&tab->mutex_min_times_ate);
	i = 0;
	while (tab->locks && i < tab->locks_to_destroy)
	{
		pthread_mutex_destroy(tab->locks + i);
		i++;
	}
	if (tab->locks)
		free(tab->locks);
}

void	free_philos(t_table *tab)
{
	int	i;

	i = 0;
	while (i < tab->nb_p)
	{
		if (tab->philos[i].destr_lta_mutex == 1)
			pthread_mutex_destroy(&tab->philos[i].mutex_last_time_ate);
		if (tab->philos[i].destr_ta_mutex == 1)
			pthread_mutex_destroy(&tab->philos[i].mutex_times_ate);
		else
		{
			free(tab->philos);
			return ;
		}
		i++;
	}
	free(tab->philos);
}
