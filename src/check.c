/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:56:38 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/11 18:14:06 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_alive(t_table *tab)
{
	int		i;
	long	time;

	i = 0;
	time = get_time_ms() - tab->start_time;
	while (i < tab->nb_p)
	{
		if (time - tab->philos[i].last_time_ate > tab->time_to_die)
		{
			print_message(tab, time, i + 1, "died");
			tab->stop = true;
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
	min = tab->philos[0].times_ate;
	while (i < tab->nb_p)
	{
		if (tab->philos[i].times_ate < min)
			min = tab->philos[i].times_ate;
		i++;
	}
	if (min == tab->times_eat_to_end)
	{
		tab->stop = true;
		return (false);
	}
	tab->min_lunches = min;
	return (true);
}
