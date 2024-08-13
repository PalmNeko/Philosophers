/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:09:23 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 21:09:23 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

t_philosopher	*ph_generate_philosophers(int philo_cnt, t_manager *common);
int				ph_start(t_philosopher *philos, int philo_cnt);

int	ph_main(int philo_cnt, t_manager *manager)
{
	t_philosopher	*philos;
	pthread_t		print_thread;
	int				error;

	philos = ph_generate_philosophers(philo_cnt, manager);
	if (philos == NULL)
		return (ENOMEM);
	gettimeofday(&manager->start, NULL);
	pthread_create(&print_thread,
				NULL,
				(void *(*)(void *))ph_routine_print,
				manager);
	pthread_detach(print_thread);
	error = ph_start(philos, philo_cnt);
	ph_destroy_philosophers(philos, philo_cnt);
	return (error);
}

int	ph_start(t_philosopher *philos, int philo_cnt)
{
	pthread_t		*threads;
	int				index;
	int				error;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * philo_cnt);
	if (threads == NULL)
		return (ENOMEM);
	error = 0;
	error = ph_create_philo_threads(threads, philos, philo_cnt);
	if (error != 0)
		return (free(threads), error);
	index = 0;
	while (index < philo_cnt)
	{
		if (error == 0)
			error = pthread_join(threads[index], NULL);
		else
			error = pthread_detach(threads[index]);
		index++;
	}
	free(threads);
	return (error);
}

t_philosopher	*ph_generate_philosophers(int philo_cnt, t_manager *common)
{
	t_philosopher	*philos;
	int				index;

	philos = (t_philosopher *)malloc(sizeof(t_philosopher) * philo_cnt);
	if (philos == NULL)
		return (NULL);
	memset(philos, 0, sizeof(t_philosopher *) * philo_cnt);
	index = 0;
	while (index < philo_cnt)
	{
		philos[index] = (t_philosopher){
			.common = common,
			.no = index + 1,
		};
		pthread_mutex_init(&philos[index].fork, NULL);
		index++;
	}
	return (philos);
}
