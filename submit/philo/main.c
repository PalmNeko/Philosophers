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
#include <limits.h>
#include <unistd.h>
#include <string.h>

void	ph_print_help(void);
int		ph_init_config(int argc, char *argv[], t_ph_config *config);
int		ph_to_int(const char *str, int *num);

int	main(int argc, char *argv[])
{
	t_ph_config	config;
	int			result;

	if (argc != 5 && argc != 6)
		return (ph_print_help(), 1);
	if (argc == 2)
		return (ph_print_error("Error: need at least 2 philosophers"), 1);
	if (ph_init_config(argc, argv, &config) != 0)
		return (ph_print_error("Error: arg format.\n"), ph_print_help(), 1);
	result = ph_main(&config);
	return (result);
}

void	ph_print_help(void)
{
	ph_putstr(2, "usage: philo philo/fork die eat sleep [eat_times]\n");
	return ;
}

int		ph_init_config(int argc, char *argv[], t_ph_config *config)
{
	memset(config, 0, sizeof(t_ph_config));
	if (ph_to_int(argv[1], &config->philo_cnt) != 0
		|| ph_to_int(argv[2], &config->time_to_die) != 0
		|| ph_to_int(argv[3], &config->time_to_eat) != 0
		|| ph_to_int(argv[4], &config->time_to_sleep) != 0
		|| (argc == 6 && ph_to_int(argv[5], &config->must_eat_times) != 0))
		return (1);
	if (argc != 6)
		config->must_eat_times = -1;
	config->die_tv = ph_msectotimeval(config->time_to_die);
	return (0);
}

/**
 * @return
 * 0 if success.
 * -1 if overflow.
 * -2 if unexpected token.
 */
int	ph_to_int(const char *str, int *num)
{
	int	tmp;

	if (*str == '\0')
		return (-2);
	*num = 0;
	while ('0' <= *str && *str <= '9')
	{
		if (*num > INT_MAX / 10)
			return (-1);
		*num *= 10;
		tmp = *str - '0';
		if (*num > INT_MAX - tmp)
			return (-1);
		*num += tmp;
		str++;
	}
	if (*str != '\0')
		return (-2);
	return (0);
}
