/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:09:02 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 21:09:02 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <unistd.h>

void	ph_print_help(void)
{
	ph_putstr(2, "usage: philo philo/fork die eat sleep [eat_times]\n");
	return ;
}

int	main(int argc, char *argv[])
{
	t_manager	manager;
	int			result;

	if (argc != 5 && argc != 6)
		return (ph_print_help(), 1);
	if (ph_to_int(argv[1], &manager.philo_cnt) != 0
		|| ph_to_int(argv[2], &manager.time_to_die) != 0
		|| ph_to_int(argv[3], &manager.time_to_eat) != 0
		|| ph_to_int(argv[4], &manager.time_to_sleep) != 0
		|| (argc == 6 && ph_to_int(argv[5], &manager.must_eat_times) != 0))
		return (ph_error_print("Error: arg format.\n"), ph_print_help(), 1);
	if (argc != 6)
		manager.must_eat_times = -1;
	manager.action_queue = ph_new_queue(manager.philo_cnt * 10);
	if (manager.action_queue == NULL)
		return (1);
	result = ph_main(manager.philo_cnt, &manager);
	ph_destroy_queue(manager.action_queue);
	return (result);
}
