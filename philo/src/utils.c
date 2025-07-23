/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:54:33 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/23 20:15:50 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_message(t_table *tab, int p_nb, const char *s)
{
	pthread_mutex_lock(&tab->mutex_to_print);
	if (!check_stop(tab))
		printf("%ld %d %s\n", get_time_ms() - tab->start_time, p_nb, s);
	pthread_mutex_unlock(&tab->mutex_to_print);
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