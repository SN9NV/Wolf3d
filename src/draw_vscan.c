/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vscan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 13:20:44 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 14:46:56 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	get_tex_x(t_env *e)
{
	int		tex_x;

	if (e->side)
		e->wall.x = e->ray.loc.x + e->total_dist * e->ray.rot.x;
	else
		e->wall.x = e->ray.loc.y + e->total_dist * e->ray.rot.y;
	e->wall.x -= (int)e->wall.x;
	tex_x = (int)(e->wall.x * (double)(TEX));
	if ((e->side && e->ray.rot.y < 0) || (!e->side && e->ray.rot.x > 0))
		tex_x = TEX - tex_x - 1;
	return (tex_x);
}

static int	get_tex_no(t_env *e)
{
	int		tex_no;

	tex_no = e->world[e->cw].map[e->map.y][e->map.x] - 1;
	if (tex_no == 10)
		tex_no += (e->tick % 3);
	return (tex_no);
}

void		draw_vscan_line(t_env *e, size_t x)
{
	int			tex_x;
	int			tex_no;
	int			d;
	int			tex_y;
	size_t		px;

	tex_no = get_tex_no(e);
	tex_x = get_tex_x(e);
	while (e->start <= e->end)
	{
		d = (e->start << 8) - (WIN_Y << 7) + (e->line_height << 7);
		tex_y = ((d * TEX) / e->line_height) >> 8;
		px = e->start * e->px_pitch + (x * 4);
		*(int *)(e->pixels + px) = e->tex[tex_no][tex_x][tex_y];
		++e->start;
	}
	draw_floor(e, x);
}
