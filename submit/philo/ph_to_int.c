/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:54:58 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 19:54:58 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

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
