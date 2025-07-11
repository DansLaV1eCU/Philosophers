/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:53:50 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/11 18:13:58 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_params(int len, char **s, t_table *tab)
{
	int	value;
	int	count;

	count = 1;
	tab->times_eat_to_end = -1;
	while (count < len)
	{
		value = philo_atoi(s[count]);
		if (count == 1 && value > 0)
			tab->nb_p = value;
		else if (count == 2 && value > 0)
			tab->time_to_die = value;
		else if (count == 3 && value > 0)
			tab->time_to_eat = value;
		else if (count == 4 && value > 0)
			tab->time_to_sleep = value;
		else if (count == 5 && value > 0)
			tab->times_eat_to_end = value;
		else
			return (EXIT_FAILURE);
		count++;
	}
	return (EXIT_SUCCESS);
}

int	philo_atoi(char *str)
{
	int	count;
	int	result;

	count = 0;
	result = 0;
	while (((str[count] >= 9 && str[count] <= 13) || str[count] == 32))
		count++;
	if (str[count] == '+')
		count++;
	while (str[count] >= '0' && str[count] <= '9')
		result = result * 10 + (str[count++] - '0');
	if (str[count] != '\0')
		return (-1);
	return (result);
}
