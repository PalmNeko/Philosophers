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
int				ph_philo_start(t_manager *manager, t_philosopher *philos);
int				ph_init_manager(t_manager *manager, t_ph_config *config);
void			ph_finalize_manager(t_manager *manager);

int	ph_main(t_ph_config *config)
{
	t_manager		manager;
	int				error;

	if (ph_init_manager(&manager, config) != 0)
		return (1);
	error = ph_start(&manager, manager.philos);
	ph_finalize_manager(&manager);
	return (error);
}

int	ph_init_manager(t_manager *manager, t_ph_config *config)
{
	t_philosopher	*philos;

	memset(manager, 0, sizeof(t_manager));
	manager->action_queue = ph_new_queue(config->philo_cnt * 2);
	if (manager->action_queue == NULL)
		return (ENOMEM);
	pthread_mutex_init(&manager->lock, NULL);
	gettimeofday(&manager->start, NULL);
	manager->config = config;
	manager->in_process = true;
	gettimeofday(&manager->now, NULL);
	philos = ph_generate_philosophers(manager);
	if (philos == NULL)
		return (ph_finalize_manager(manager), ENOMEM);
	manager->philos = philos;
	return (0);
}

void	ph_finalize_manager(t_manager *manager)
{
	pthread_mutex_destroy(&manager->lock);
	ph_destroy_philosophers(manager->philos, manager->config->philo_cnt);
	ph_destroy_queue(manager->action_queue);
}

int	ph_start(t_manager *manager, t_philosopher *philos)
{
	pthread_t		print_thread;
	pthread_t		update_thread;
	int				error;

	pthread_create(&print_thread, NULL,
		(void *(*)(void *))ph_routine_print, manager);
	pthread_create(&update_thread, NULL,
		(void *(*)(void *))ph_routine_update_manager, manager);
	error = ph_philo_start(manager, philos);
	if (error != 0)
		return (error);
	pthread_mutex_lock(&manager->lock);
	manager->in_process = false;
	pthread_mutex_unlock(&manager->lock);
	pthread_join(print_thread, NULL);
	pthread_join(update_thread, NULL);
	return (0);
}

int	ph_philo_start(t_manager *manager, t_philosopher *philos)
{
	pthread_t		*threads;
	int				index;
	int				error;

	threads = (pthread_t *)malloc(sizeof(pthread_t)
			* manager->config->philo_cnt);
	if (threads == NULL)
		return (ENOMEM);
	error = ph_create_philo_threads(
			threads, philos, manager->config->philo_cnt);
	if (error != 0)
		return (free(threads), error);
	index = 0;
	while (index < manager->config->philo_cnt)
		pthread_join(threads[index++], NULL);
	free(threads);
	return (0);
}
