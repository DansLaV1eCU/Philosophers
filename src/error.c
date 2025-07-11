/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:04:12 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/11 18:14:17 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(t_table *tab, char *str, char *detail, int exit_nb)
{
	if (tab)
		free_all(tab);
	if (detail)
		printf(str, STR_PROG_NAME, detail);
	else
		printf(str, STR_PROG_NAME);
	return (exit_nb);
}

void	void_error(t_table *tab, char *str, char *detail)
{
	if (tab)
		free_all(tab);
	error(tab, str, detail, EXIT_FAILURE);
}
