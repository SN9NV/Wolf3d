/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 13:38:02 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 13:38:16 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	activate_power(t_env *e)
{
	char	*s;

	s = NULL;
	--e->activated;
	e->world[e->cw].map[e->map.y][e->map.x] = 11;
	if (e->activated > 1)
		ft_sprintf(&s, "%d inactive power supplies", e->activated);
	else if (e->activated == 1)
		ft_sprintf(&s, "Only %d inactive power supply", e->activated);
	else
		ft_sprintf(&s, "The portal is now active");
	ft_printf("    %s\n", s);
	ft_strdel(&s);
}

static void	activate_next_map(t_env *e)
{
	char	*s;

	s = NULL;
	if (e->activated < 1)
	{
		ft_sprintf(&s, "MAP %d COMPLETED!!!", e->cw);
		next_map(e);
	}
	else
		ft_sprintf(&s, "Not all the power sources have been activated!");
	ft_printf("    %s\n", s);
	ft_strdel(&s);
}

void		use(t_env *e)
{
	if (e->world[e->cw].map[e->map.y][e->map.x] == 10)
	{
		activate_power(e);
	}
	else if (e->world[e->cw].map[e->map.y][e->map.x] == 6)
	{
		activate_next_map(e);
	}
	else if (e->world[e->cw].map[e->map.y][e->map.x] == 3)
		e->world[e->cw].map[e->map.y][e->map.x] = 0;
}
