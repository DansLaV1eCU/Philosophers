/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llupache <llupache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:04:12 by danslav1e         #+#    #+#             */
/*   Updated: 2025/07/11 19:30:03 by llupache         ###   ########.fr       */
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
