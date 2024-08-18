/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_destroy_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:16:43 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 18:16:43 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <stdlib.h>

void	ph_destroy_philosophers(t_philosopher *philos, int cnt)
{
	int	index;

	index = 0;
	while (index < cnt)
	{
		pthread_mutex_destroy(&philos[index].fork);
		pthread_mutex_destroy(&philos[index].lock);
		index++;
	}
	free(philos);
	return ;
}
