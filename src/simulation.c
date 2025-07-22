/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:44:42 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/22 22:49:02 by danslav1e        ###   ########.fr       */
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
	while (!check_stop(philo->table))
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
		while (check_if_time_to_repeat(philo->table, philo))
			usleep(100);
	}
	return (NULL);
}

// bool	check_if_time_to_repeat(t_table *tab, t_philo *ph)
// {
// 	pthread_mutex_lock(ph->mutex_times_ate);
// 	pthread_mutex_lock(tab->mutex_min_times_ate);
// 	pthread_mutex_lock(tab->mutex_to_stop);
// 	if (ph->times_ate > tab->min_lunches && !tab->stop)
// 	{
// 		pthread_mutex_unlock(ph->mutex_times_ate);
// 		pthread_mutex_unlock(tab->mutex_min_times_ate);
// 		pthread_mutex_unlock(tab->mutex_to_stop);
// 		return (true);
// 	}
// 	pthread_mutex_unlock(ph->mutex_times_ate);
// 	pthread_mutex_unlock(tab->mutex_min_times_ate);
// 	pthread_mutex_unlock(tab->mutex_to_stop);
// 	return (false);
// }

bool	check_if_time_to_repeat(t_table *tab, t_philo *ph)
{
    int times_ate;
    int min_lunches;
    bool stop_flag;

    pthread_mutex_lock(ph->mutex_times_ate);
    times_ate = ph->times_ate;
    pthread_mutex_unlock(ph->mutex_times_ate);

    pthread_mutex_lock(tab->mutex_min_times_ate);
    min_lunches = tab->min_lunches;
    pthread_mutex_unlock(tab->mutex_min_times_ate);

    pthread_mutex_lock(tab->mutex_to_stop);
    stop_flag = tab->stop;
    pthread_mutex_unlock(tab->mutex_to_stop);

    return (times_ate > min_lunches && !stop_flag);
}