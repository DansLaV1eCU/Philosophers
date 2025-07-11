/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:10:42 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/11 18:41:56 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*tab;
	int		i;

	tab = malloc(sizeof(t_table));
	if (!tab)
		return (error(tab, STR_ERR_MALLOC, "table malloc", EXIT_FAILURE));
	memset(tab, 0, sizeof(t_table));
	if ((argc != 5 && argc != 6) || check_params(argc, argv, tab) != 0)
		return (error(tab, STR_USAGE, NULL, EXIT_FAILURE));
	if (init(tab) != 0)
		return (EXIT_FAILURE);
	if (start_simulation(tab) != 0)
		return (EXIT_FAILURE);
	i = 0;
	while (check_alive(tab) && check_times_ate(tab))
		usleep(5000);
	while (i < tab->nb_p)
		pthread_join(tab->threads[i++], NULL);
	destroy_mutex(tab);
	free_all(tab);
	return (EXIT_SUCCESS);
}
