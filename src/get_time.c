/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 13:14:45 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 13:27:56 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

size_t		ft_get_time(void)
{
	struct timeval	t_now;

	gettimeofday(&t_now, NULL);
	return ((size_t)((t_now.tv_sec << 20) + t_now.tv_usec));
}
