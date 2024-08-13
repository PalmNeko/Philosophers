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
	t_manager	*manager;
	int				args[5];
	int				result;

	if (argc != 5 && argc != 6)
		return (ph_print_help(), 1);
	if (ph_to_int(argv[1], &args[0]) != 0
		|| ph_to_int(argv[2], &args[1]) != 0
		|| ph_to_int(argv[3], &args[2]) != 0
		|| ph_to_int(argv[4], &args[3]) != 0
		|| (argc == 6 && ph_to_int(argv[5], &args[4]) != 0))
		return (ph_error_print("Error: arg format.\n"), ph_print_help(), 1);
	if (argc != 6)
		args[4] = -1;
	manager = ph_new_manager(args[1], args[2], args[3], args[4]);
	if (manager == NULL)
		return (1);
	result = ph_main(args[0], manager);
	ph_destroy_manager(manager);
	return (result);
}
