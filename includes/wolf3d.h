/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 14:56:52 by adippena          #+#    #+#             */
/*   Updated: 2016/07/30 09:25:37 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include "SDL.h"

# define WIN_X	1200
# define WIN_Y	675
# define TEX	1024

typedef struct			s_v2d
{
	float				x;
	float				y;
}						t_v2d;

typedef struct			s_v2dint
{
	int					x;
	int					y;
}						t_v2dint;

typedef struct			s_ent
{
	t_v2d				loc;
	t_v2d				rot;
}						t_ent;

typedef struct			s_keys
{
	int					w_key;
	int					a_key;
	int					s_key;
	int					d_key;
}						t_keys;

typedef struct			s_map
{
	int					**map;
	double				rows;
	double				cols;
	double				start_x;
	double				start_y;
	double				rot;
}						t_map;

typedef struct			s_env
{
	t_ent				player;
	t_ent				ray;
	t_v2d				plane;
	t_v2d				camera;
	double				total_dist;
	int					line_height;
	t_v2dint			step;
	t_v2dint			map;
	t_v2d				wall;
	t_v2d				dist;
	t_v2d				delta_dist;
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*img;
	void				*pixels;
	int					px_pitch;
	int					start;
	int					end;
	size_t				side;
	t_keys				key;
	int					exit;
	t_map				world[5];
	int					cw;
	size_t				run_time;
	size_t				run_cooldown;
	size_t				map_time;
	size_t				map_cooldown;
	double				top_bottom;
	double				rot;
	time_t				time_old;
	uint32_t			***tex;
	unsigned char		tick;
	unsigned int		activated;
	char				*message;
	size_t				message_time;
}						t_env;

void					free_textures(t_env *e);
void					exit_wolf(t_env *e);

/*
** src/dda.c
*/
void					calc_ray_loc_rot(t_env *e, size_t x);
void					calc_init_dist(t_env *e);
void					dda(t_env *e);
void					calc_line(t_env *e);

/*
** src/game_loop.c
*/
void					game_loop(t_env *e);
void					rotate(t_env *e, double rot);
void					set_run(t_env *e);
/*
** src/mouse.c
*/
void					mouse_move(int x);

/*
** src/env_init.c
*/
void					init_env(t_env *e);
void					next_map(t_env *e);

/*
** src/key_events.c
*/
void					key_down(SDL_Keycode key, t_env *e);
void					key_up(SDL_Keycode key, t_env *e);
void					move_player(t_env *e);
void					minimap(t_env *e);

/*
** src/draw.c
*/
void					redraw(t_env *e);
void					draw_frame(t_env *e);

/*
** src/use.c
*/
void					use(t_env *e);

/*
** src/fill_map.c
*/
void					fill_map(t_map *world, char *str);

/*
** src/load_texture.c
*/
uint32_t				**load_texture(char *file);

/*
** src/get_time.c
*/
size_t					ft_get_time(void);

/*
** src/draw_vscan.c
*/
void					draw_vscan_line(t_env *e, size_t x);

/*
** src/draw_floor.c
*/
void					draw_floor(t_env *e, size_t x);

#endif
