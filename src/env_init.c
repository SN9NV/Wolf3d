/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 16:58:51 by adippena          #+#    #+#             */
/*   Updated: 2016/09/08 15:04:39 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		init_env(t_env *e)
{
	e->player.loc.x = 1.5;
	e->player.loc.y = 1.5;
	e->player.rot.x = -1;
	e->player.rot.y = 0;
	e->plane.x = 0;
	e->plane.y = 0.69;
	e->key.w_key = 0;
	e->key.a_key = 0;
	e->key.s_key = 0;
	e->key.d_key = 0;
	e->rot = 0;
	e->run_time = 0;
	e->run_cooldown = 0;
	e->time_old = ft_get_time();
	rotate(e, 270);
	e->tick = 0;
	e->activated = 4;
	fill_map(&e->world[0], "resources/maps/wolf.map");
	fill_map(&e->world[1], "resources/maps/level01.map");
	fill_map(&e->world[2], "resources/maps/level02.map");
	e->cw = 0;
	e->message = NULL;
	e->message_time = 0;
}

void		next_map(t_env *e)
{
	char	*message;

	++e->cw;
	if (e->cw == 3)
		exit_wolf(e);
	ft_sprintf(&message, "Round %d", e->cw);
	ft_putendl(message);
	e->player.loc.x = 1.5;
	e->player.loc.y = 1.5;
	rotate(e, -e->rot);
	e->rot = 0;
	rotate(e, 270);
	e->activated = 4;
}
