/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:10:42 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/23 19:42:51 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*tab;

	tab = malloc(sizeof(t_table));
	if (!tab)
		return (error(tab, STR_ERR_MALLOC, "table malloc", EXIT_FAILURE));
	memset(tab, 0, sizeof(t_table));
	if ((argc != 5 && argc != 6) || check_params(argc, argv, tab) != 0)
		return (error(tab, STR_USAGE, NULL, EXIT_FAILURE));
	if (init(tab) != 0)
		return (free_all(tab, EXIT_FAILURE));
	if (start_simulation(tab) != 0)
		return (free_all(tab, EXIT_FAILURE));
	while (check_alive(tab) && check_times_ate(tab) && !check_stop(tab))
	{
		usleep(100);
	}
	usleep(100);
	pthread_mutex_unlock(&tab->mutex_to_print);
	return (free_all(tab, EXIT_SUCCESS));
}
