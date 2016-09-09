/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 16:58:29 by adippena          #+#    #+#             */
/*   Updated: 2016/07/30 10:14:04 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	load_textures(t_env *e)
{
	int		err;

	err = 0;
	e->tex = (uint32_t ***)malloc(sizeof(uint32_t **) * 15);
	err |= !(e->tex[0] = load_texture("brick_wall1024.data"));
	err |= !(e->tex[1] = load_texture("mossy_wall1024.data"));
	err |= !(e->tex[2] = load_texture("mossy_cracked_wall1024.data"));
	err |= !(e->tex[3] = load_texture("floor1024.data"));
	err |= !(e->tex[4] = load_texture("roof1024.data"));
	err |= !(e->tex[5] = load_texture("chizzeled1024.data"));
	err |= !(e->tex[9] = load_texture("wall_control_01.data"));
	err |= !(e->tex[10] = load_texture("wall_control_02.data"));
	err |= !(e->tex[11] = load_texture("wall_control_03.data"));
	err |= !(e->tex[12] = load_texture("wall_control_04.data"));
	return (err);
}

static void	free_texture(uint32_t **tex)
{
	size_t	y;

	y = 0;
	while (y < TEX)
		free(tex[y++]);
	free(tex);
}

void		free_textures(t_env *e)
{
	free_texture(e->tex[0]);
	free_texture(e->tex[1]);
	free_texture(e->tex[2]);
	free_texture(e->tex[3]);
	free_texture(e->tex[4]);
	free_texture(e->tex[5]);
	free_texture(e->tex[9]);
	free_texture(e->tex[10]);
	free_texture(e->tex[11]);
	free_texture(e->tex[12]);
	free(e->tex);
}

void		exit_wolf(t_env *e)
{
	ft_putstr("SHUTTING DOWN!!!\n");
	SDL_DestroyRenderer(e->rend);
	SDL_DestroyWindow(e->win);
	free_textures(e);
	SDL_Quit();
	exit(0);
}

int			main(void)
{
	t_env	e;

	init_env(&e);
	e.win = SDL_CreateWindow("Wolf3D", 8, 8,
		WIN_X, WIN_Y, SDL_WINDOW_INPUT_GRABBED);
	e.rend = SDL_CreateRenderer(e.win, -1, SDL_RENDERER_ACCELERATED);
	e.img = SDL_CreateTexture(e.rend, SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_X, WIN_Y);
	SDL_SetRenderDrawBlendMode(e.rend, SDL_BLENDMODE_BLEND);
	if (load_textures(&e))
		return (0);
	printf("Activate all of the power supplies\n"
			"Press F to activate / break wall\n"
			"Find your way to the portal\n\n");
	game_loop(&e);
	exit_wolf(&e);
	return (0);
}
