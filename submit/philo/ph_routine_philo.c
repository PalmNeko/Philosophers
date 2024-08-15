/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:18:58 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 17:18:58 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	*ph_routine_philo(t_philosopher *philo)
{
	int	cnt;

	cnt = 0;
	while (cnt < 10)
	{
		ph_think(philo);
		ph_eat(philo);
		ph_sleep(philo);
		cnt++;
	}
	return (NULL);
}
