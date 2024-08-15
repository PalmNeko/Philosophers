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

t_philosopher	*ph_generate_philosophers(t_manager *manager);
int				ph_start(t_manager *manager, t_philosopher *philos);

int	ph_main(t_manager *manager)
{
	t_philosopher	*philos;
	int				error;

	philos = ph_generate_philosophers(manager);
	if (philos == NULL)
		return (ENOMEM);
	manager->philos = philos;
	gettimeofday(&manager->start, NULL);
	manager->in_process = true;
	pthread_mutex_init(&manager->lock, NULL);
	error = ph_start(manager, philos);
	ph_destroy_philosophers(philos, manager->philo_cnt);
	return (error);
}

int	ph_start(t_manager *manager, t_philosopher *philos)
{
	pthread_t		*threads;
	pthread_t		print_thread;
	int				index;
	int				error;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * manager->philo_cnt);
	if (threads == NULL)
		return (ENOMEM);
	error = ph_create_philo_threads(threads, philos, manager->philo_cnt);
	if (error != 0)
		return (free(threads), error);
	pthread_create(&print_thread, NULL,
		(void *(*)(void *))ph_routine_print, manager);
	index = 0;
	while (index < manager->philo_cnt)
		pthread_join(threads[index++], NULL);
	pthread_mutex_lock(&manager->lock);
	manager->in_process = false;
	pthread_mutex_unlock(&manager->lock);
	pthread_join(print_thread, NULL);
	free(threads);
	return (0);
}

t_philosopher	*ph_generate_philosophers(t_manager *manager)
{
	t_philosopher	*philos;
	int				index;
	int				size;

	size = sizeof(t_philosopher) * manager->philo_cnt;
	philos = (t_philosopher *)malloc(size);
	if (philos == NULL)
		return (NULL);
	memset(philos, 0, size);
	index = 0;
	while (index < manager->philo_cnt)
	{
		philos[index] = (t_philosopher){
			.manager = manager,
			.no = index + 1,
		};
		pthread_mutex_init(&philos[index].fork, NULL);
		index++;
	}
	return (philos);
}
