/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 13:23:44 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 13:25:38 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	get_floor_xy(t_env *e, t_v2d *floor_wall)
{
	if (e->side == 0 && e->ray.rot.x > 0)
	{
		floor_wall->x = e->map.x;
		floor_wall->y = e->map.y + e->wall.x;
	}
	else if (e->side == 0 && e->ray.rot.x < 0)
	{
		floor_wall->x = e->map.x + 1.0;
		floor_wall->y = e->map.y + e->wall.x;
	}
	else if (e->side == 1 && e->ray.rot.y > 0)
	{
		floor_wall->x = e->map.x + e->wall.x;
		floor_wall->y = e->map.y;
	}
	else
	{
		floor_wall->x = e->map.x + e->wall.x;
		floor_wall->y = e->map.y + 1.0;
	}
}

void		draw_floor(t_env *e, size_t x)
{
	t_v2d		floor_wall;
	t_v2dint	floor_tex;
	double		d;

	get_floor_xy(e, &floor_wall);
	while (++e->end < WIN_Y)
	{
		d = ((double)WIN_Y / ((double)(e->end << 1) - (double)WIN_Y)) /
			e->total_dist;
		floor_tex.x = (int)((d * floor_wall.x + (1.0 - d) * e->player.loc.x) *
			(double)TEX) % TEX;
		floor_tex.y = (int)((d * floor_wall.y + (1.0 - d) * e->player.loc.y) *
			(double)TEX) % TEX;
		*(int *)(e->pixels + (e->end * e->px_pitch + (x * 4))) =
			e->tex[3][floor_tex.x][floor_tex.y];
		*(int *)(e->pixels + ((WIN_Y - e->end) * e->px_pitch + (x * 4))) =
			e->tex[4][floor_tex.x][floor_tex.y];
	}
}
