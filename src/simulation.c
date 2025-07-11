/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:44:42 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/11 18:45:55 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_table *tab)
{
	int	i;

	tab->start_time = get_time_ms();
	i = 0;
	while (i < tab->nb_p)
	{
		if (pthread_create(&(tab->threads[i]), NULL, (void *)simulation,
				tab->philos + i) != 0)
			return (error(tab, STR_ERR_THREAD, NULL, EXIT_FAILURE));
		i++;
	}
	return (EXIT_SUCCESS);
}

void	*simulation(t_philo *philo)
{
	while (!philo->table->stop)
	{
		if (philo->table->nb_p == 1)
		{
			fork_is_taken(philo->table, philo, philo->left_fork);
			break ;
		}
		else if (philo->p_number % 2 == 1)
		{
			fork_is_taken(philo->table, philo, philo->left_fork);
			fork_is_taken(philo->table, philo, philo->right_fork);
		}
		else
		{
			fork_is_taken(philo->table, philo, philo->right_fork);
			fork_is_taken(philo->table, philo, philo->left_fork);
		}
		eating(philo->table, philo);
		sleeping(philo->table, philo);
		thinking(philo->table, philo);
		while (philo->times_ate > philo->table->min_lunches
			&& !philo->table->stop)
			usleep(5000);
	}
	return (NULL);
}
