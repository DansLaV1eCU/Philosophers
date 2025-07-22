/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:10:42 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/22 23:03:21 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_table *tab, t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_last_time_ate);
	philo->last_time_ate = get_time_ms() + tab->time_to_eat;
	pthread_mutex_unlock(philo->mutex_last_time_ate);
	if (check_stop(tab))
	{
		pthread_mutex_unlock(tab->locks + philo->left_fork - 1);
		pthread_mutex_unlock(tab->locks + philo->right_fork - 1);
		return ;
	}
	pthread_mutex_lock(philo->mutex_times_ate);
	philo->times_ate++;
	pthread_mutex_unlock(philo->mutex_times_ate);
	print_message(tab, philo->p_number, "is eating");
	sleep_time(tab->time_to_eat);
	pthread_mutex_unlock(tab->locks + philo->left_fork - 1);
	pthread_mutex_unlock(tab->locks + philo->right_fork - 1);
}

void	sleeping(t_table *tab, t_philo *philo)
{
	if (check_stop(tab))
		return ;
	print_message(tab, philo->p_number, "is sleeping");
	sleep_time(tab->time_to_sleep);
}

void	thinking(t_table *tab, t_philo *philo)
{
	print_message(tab, philo->p_number, "is thinking");
}

void	fork_is_taken(t_table *tab, t_philo *philo, int fork)
{
	pthread_mutex_lock(tab->locks + fork - 1);
	if (check_stop(tab))
	{
		pthread_mutex_unlock(tab->locks + fork - 1);
		return ;
	}
	print_message(tab, philo->p_number, "has taken a fork");
}

bool check_stop(t_table *tab)
{
	bool stop;

	pthread_mutex_lock(tab->mutex_to_stop);
	stop = tab->stop;
	pthread_mutex_unlock(tab->mutex_to_stop);	
	return (stop);
}

void sleep_time(long time)
{
	long start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
		usleep(100);
}