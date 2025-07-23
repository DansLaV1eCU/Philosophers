/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:10:42 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/23 17:41:50 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_table *tab)
{
	if (init_table(tab) != 0)
		return (EXIT_FAILURE);
	if (init_forks(tab) != 0)
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
		if (init_philos_2(tab, philos + i, i) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	tab->philos = philos;
	return (EXIT_SUCCESS);
}

int	init_philos_2(t_table *tab, t_philo *ph, int nb)
{
	ph->destr_lta_mutex = 0;
	ph->destr_ta_mutex = 0;
	if (pthread_mutex_init(&ph->mutex_last_time_ate, NULL) != 0)
		return (error(tab, STR_ERR_MUTEX, "mutex_last_time_ate init",
				EXIT_FAILURE));
	ph->destr_lta_mutex = 1;
	if (pthread_mutex_init(&ph->mutex_times_ate, NULL) != 0)
		return (error(tab, STR_ERR_MUTEX, "mutex_times_ate init",
				EXIT_FAILURE));
	ph->destr_ta_mutex = 1;
	ph->p_number = nb + 1;
	ph->times_ate = 0;
	ph->table = tab;
	ph->right_fork = nb;
	ph->left_fork = nb + 1;
	ph->last_time_ate = 0;
	if (nb == 0)
		ph->right_fork = tab->nb_p;
	return (EXIT_SUCCESS);
}
