/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:01:45 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 13:31:54 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	key_down(SDL_Keycode key, t_env *e)
{
	if (key == SDLK_w)
		e->key.w_key = 1;
	else if (key == SDLK_a)
		e->key.a_key = 1;
	else if (key == SDLK_s)
		e->key.s_key = 1;
	else if (key == SDLK_d)
		e->key.d_key = 1;
	else if (key == SDLK_LSHIFT)
		set_run(e);
	else if (key == SDLK_f)
		use(e);
	else if (key == SDLK_n)
		next_map(e);
}

void	key_up(SDL_Keycode key, t_env *e)
{
	if (key == SDLK_w)
	{
		e->key.w_key = 0;
		e->run_time = 0;
	}
	else if (key == SDLK_a)
		e->key.a_key = 0;
	else if (key == SDLK_s)
		e->key.s_key = 0;
	else if (key == SDLK_d)
		e->key.d_key = 0;
}

void	update(t_env *e, t_v2d *rot)
{
	if (e->run_time && e->plane.y == 0.69)
	{
		rotate(e, -e->rot);
		e->plane.y = 0.66;
		rotate(e, e->rot);
	}
	else if (!e->run_time && e->plane.y == 0.66)
	{
		rotate(e, -e->rot);
		e->plane.y = 0.69;
		rotate(e, e->rot);
	}
	if (e->run_time)
	{
		rot->x = e->player.rot.x / 8.0F;
		rot->y = e->player.rot.y / 8.0F;
	}
	else
	{
		rot->x = e->player.rot.x / 16.0F;
		rot->y = e->player.rot.y / 16.0F;
	}
}

void	wall_collision(t_env *e)
{
	if (e->key.w_key || e->key.s_key || e->key.a_key || e->key.d_key)
	{
		while (e->world[e->cw].
			map[(int)(e->player.loc.y + 0.2)][(int)e->player.loc.x])
			e->player.loc.y -= 0.001;
		while (e->world[e->cw].
			map[(int)(e->player.loc.y - 0.2)][(int)e->player.loc.x])
			e->player.loc.y += 0.001;
		while (e->world[e->cw].
			map[(int)e->player.loc.y][(int)(e->player.loc.x + 0.2)])
			e->player.loc.x -= 0.001;
		while (e->world[e->cw].
			map[(int)e->player.loc.y][(int)(e->player.loc.x - 0.2)])
			e->player.loc.x += 0.001;
	}
}

void	move_player(t_env *e)
{
	t_v2d	rot;

	update(e, &rot);
	if (e->key.w_key)
	{
		e->player.loc.x += rot.x;
		e->player.loc.y += rot.y;
	}
	else if (e->key.s_key)
	{
		e->player.loc.x -= rot.x;
		e->player.loc.y -= rot.y;
	}
	if (e->key.a_key)
	{
		e->player.loc.x -= rot.y;
		e->player.loc.y += rot.x;
	}
	else if (e->key.d_key)
	{
		e->player.loc.x += rot.y;
		e->player.loc.y -= rot.x;
	}
	wall_collision(e);
}
