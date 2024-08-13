/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_create_philo_threads.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:17:57 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 18:17:57 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	ph_create_philo_threads(pthread_t *threads, t_philosopher *philos, int cnt)
{
	int	index;
	int	error;

	index = 0;
	while (index < cnt)
	{
		error = 0;
		error = pthread_create(&threads[index],
				NULL,
				(void *(*)(void *))ph_philo_routine,
				&philos[index]);
		if (error != 0)
		{
			index -= 1;
			while (index > 0)
				pthread_detach(threads[index--]);
			return (error);
		}
		index++;
	}
	return (0);
}
