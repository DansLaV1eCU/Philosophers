/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:10:42 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/11 23:44:48 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_table *tab, t_philo *philo)
{
	long	start_time;

	start_time = get_time_ms() - tab->start_time;
	if (tab->stop)
		return ;
	philo->last_time_ate = get_time_ms();
	print_message(tab, start_time, philo->p_number, "is eating");
	if (tab->stop)
		return ;
	usleep(tab->time_to_eat * 1000);
	philo->times_ate++;
	philo->last_time_ate = get_time_ms();
	pthread_mutex_unlock(tab->locks + philo->left_fork - 1);
	pthread_mutex_unlock(tab->locks + philo->right_fork - 1);
}

void	sleeping(t_table *tab, t_philo *philo)
{
	long	start_time;

	start_time = get_time_ms() - tab->start_time;
	if (tab->stop)
		return ;
	print_message(tab, start_time, philo->p_number, "is sleeping");
	if (tab->stop)
		return ;
	usleep(tab->time_to_sleep * 1000);
}

void	thinking(t_table *tab, t_philo *philo)
{
	long	start_time;

	start_time = get_time_ms() - tab->start_time;
	if (!tab->stop)
		print_message(tab, start_time, philo->p_number, "is thinking");
}

void	fork_is_taken(t_table *tab, t_philo *philo, int fork)
{
	long	start_time;

	pthread_mutex_lock(tab->locks + fork - 1);
	start_time = get_time_ms() - philo->table->start_time;
	if (tab->stop)
	{
		pthread_mutex_unlock(tab->locks + fork - 1);
		return ;
	}
	print_message(tab, start_time, philo->p_number, "has taken a fork");
}
