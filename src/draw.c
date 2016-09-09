/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:04:00 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 14:29:09 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		redraw(t_env *e)
{
	move_player(e);
	draw_frame(e);
}

void		draw_frame(t_env *e)
{
	size_t		x;

	x = 0;
	SDL_LockTexture(e->img, NULL, &e->pixels, &e->px_pitch);
	while (x < WIN_X)
	{
		calc_ray_loc_rot(e, x);
		e->map.x = (int)e->ray.loc.x;
		e->map.y = (int)e->ray.loc.y;
		e->delta_dist.x = sqrt(1 + (e->ray.rot.y * e->ray.rot.y) /
			(e->ray.rot.x * e->ray.rot.x));
		e->delta_dist.y = sqrt(1 + (e->ray.rot.x * e->ray.rot.x) /
			(e->ray.rot.y * e->ray.rot.y));
		calc_init_dist(e);
		dda(e);
		calc_line(e);
		draw_vscan_line(e, x);
		++x;
	}
	SDL_UnlockTexture(e->img);
	SDL_RenderCopy(e->rend, e->img, NULL, NULL);
	minimap(e);
	SDL_RenderPresent(e->rend);
}
