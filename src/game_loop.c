/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 09:02:12 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 15:17:49 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		rotate(t_env *e, double rot)
{
	double	temp;

	if (e->rot != -rot && e->rot != rot)
		e->rot += rot;
	rot *= 3.14159265359F / 180.0;
	temp = e->player.rot.x;
	e->player.rot.x = e->player.rot.x * cos(rot) - e->player.rot.y * sin(rot);
	e->player.rot.y = temp * sin(rot) + e->player.rot.y * cos(rot);
	temp = e->plane.x;
	e->plane.x = e->plane.x * cos(rot) - e->plane.y * sin(rot);
	e->plane.y = temp * sin(rot) + e->plane.y * cos(rot);
}

void		set_run(t_env *e)
{
	size_t	now;

	now = ft_get_time();
	if (e->run_cooldown < now)
	{
		e->run_time = now + 5000000;
		e->run_cooldown = now + 7000000;
	}
}

void		calc_tick(t_env *e)
{
	size_t	now;

	now = ft_get_time();
	if (e->run_time < now)
		e->run_time = 0;
	if (now > (size_t)(e->time_old + 62500))
	{
		++e->tick;
		e->time_old = now;
	}
	if (e->message && e->message_time < now)
		ft_strdel(&e->message);
}

int			event_poll(t_env *e)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit_wolf(e);
		else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return (1);
			else
				key_down(event.key.keysym.sym, e);
		else if (event.type == SDL_KEYUP && event.key.repeat == 0)
			key_up(event.key.keysym.sym, e);
		else if (event.type == SDL_MOUSEMOTION && event.motion.x != WIN_X >> 1)
		{
			rotate(e, -(event.motion.xrel >> 3));
			if (event.motion.x < 10 || event.motion.y < 10 ||
				event.motion.x > WIN_X - 10 || event.motion.y > WIN_Y - 10)
				SDL_WarpMouseInWindow(e->win, WIN_X >> 1, WIN_Y >> 1);
		}
	}
	return (0);
}

void		game_loop(t_env *e)
{
	SDL_ShowCursor(SDL_FALSE);
	SDL_WarpMouseInWindow(e->win, WIN_X / 2, WIN_Y / 2);
	while (42)
	{
		if (event_poll(e))
			break ;
		redraw(e);
		SDL_Delay(16);
		calc_tick(e);
	}
	SDL_ShowCursor(SDL_TRUE);
}
