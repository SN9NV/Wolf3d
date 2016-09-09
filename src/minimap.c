/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 13:32:06 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 13:49:33 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static size_t	max_direction(t_env *e)
{
	if (e->world[e->cw].rows > e->world[e->cw].cols)
		return (e->world[e->cw].rows);
	else
		return (e->world[e->cw].cols);
}

static uint32_t	colour(t_env *e, size_t row, size_t col)
{
	uint32_t	colour;

	if (e->world[e->cw].map[row][col] == 0)
		if (row == (size_t)e->player.loc.y &&
			col == (size_t)e->player.loc.x)
			colour = 0xFFFF7A00;
		else
			colour = 0x00000000;
	else if (e->world[e->cw].map[row][col] == 1)
		colour = 0xFF747474;
	else if (e->world[e->cw].map[row][col] == 2)
		colour = 0xFF5E7537;
	else if (e->world[e->cw].map[row][col] == 3)
		colour = 0xFF747474;
	else if (e->world[e->cw].map[row][col] == 10)
		colour = 0xFF3F8E32;
	else if (e->world[e->cw].map[row][col] > 10)
		colour = 0xFF009898;
	else
		colour = 0x00000000;
	return (colour);
}

static void		minimap_assign_colours(t_env *e, void *px, int pitch)
{
	size_t	row;
	size_t	col;

	row = e->world[e->cw].rows;
	while (--row + 1)
	{
		col = e->world[e->cw].cols;
		while (--col + 1)
			*(int *)(px + (row * pitch + col * 4)) = colour(e, row, col);
	}
}

void			minimap(t_env *e)
{
	SDL_Texture		*tex;
	void			*px;
	size_t			row;
	int				pitch;
	SDL_Rect		rect;

	row = max_direction(e);
	rect = (SDL_Rect){row + 8, row + 8,
	e->world[e->cw].cols * 8, e->world[e->cw].rows * 8};
	tex = SDL_CreateTexture(e->rend, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, e->world[e->cw].cols,
		e->world[e->cw].rows);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	SDL_LockTexture(tex, NULL, &px, &pitch);
	minimap_assign_colours(e, px, pitch);
	SDL_UnlockTexture(tex);
	SDL_RenderCopyEx(e->rend, tex, NULL, &rect, e->rot + 90, NULL,
		SDL_FLIP_VERTICAL);
	SDL_DestroyTexture(tex);
}
