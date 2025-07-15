/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:54:33 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/15 14:22:27 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *tab)
{
	if (tab->mutex_to_print)
		free(tab->mutex_to_print);
	if (tab->locks)
		free(tab->locks);
	if (tab->threads)
		free(tab->threads);
	if (tab->philos)
		free(tab->philos);
	free(tab);
}

void	destroy_mutex(t_table *tab)
{
	int	i;

	i = 0;
	while (i < tab->nb_p)
	{
		pthread_mutex_destroy(tab->locks + i);
		i++;
	}
	pthread_mutex_destroy(tab->mutex_to_print);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_message(t_table *tab, long time, int p_nb, const char *s)
{
	pthread_mutex_lock(tab->mutex_to_print);
	if (tab->stop)
	{
		pthread_mutex_unlock(tab->mutex_to_print);
		return ;
	}
	printf("%ld %d %s\n", time, p_nb, s);
	pthread_mutex_unlock(tab->mutex_to_print);
}

void	philo_died(t_table *tab, long time, int nb)
{
	print_message(tab, time, nb + 1, "died");
	tab->stop = true;
}

// void	print_message(t_table *tab, long time, int p_nb, const char *s)
// {
// 	pthread_mutex_lock(tab->mutex_to_print);
// 	if (tab->stop)
// 	{
// 		pthread_mutex_unlock(tab->mutex_to_print);
// 		return ;
// 	}
// 	printf("%ld %d %s %d\n", time, p_nb, s, tab->philos[p_nb - 1].times_ate);
// 	pthread_mutex_unlock(tab->mutex_to_print);
// }