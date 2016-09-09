/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 12:52:51 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 14:53:37 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	open_map_fill(t_map *world, char *file)
{
	int				fd;
	t_split_string	split;
	char			*line;

	fd = open(file, O_RDONLY);
	ft_gnl(fd, &line);
	if (fd < 0)
	{
		printf("File not found\n");
		exit(0);
	}
	if (!ft_strncmp(line, "MAP: ", 5))
	{
		ft_printf("Bad map file. No map size defined. ");
		exit(0);
	}
	split = ft_nstrsplit(line, ' ');
	if (split.words != 6)
	{
		ft_printf("Bad map file. Map definition error. Exiting\n");
		exit(0);
	}
	world->rows = ft_atoi(split.strings[1]);
	world->cols = ft_atoi(split.strings[2]);
	return (fd);
}

void		fill_map(t_map *world, char *file)
{
	int				fd;
	char			*line;
	t_v2dint		v;

	fd = open_map_fill(world, file);
	world->map = (int **)malloc(sizeof(int *) * world->rows);
	v.y = 0;
	while (v.y < world->rows)
	{
		world->map[v.y] = (int *)malloc(sizeof(int) * world->cols);
		ft_gnl(fd, &line);
		v.x = 0;
		while (v.x <= world->cols)
		{
			if (ft_isdigit(line[(v.x - 1) * 2]))
				world->map[v.y][v.x - 1] = line[(v.x - 1) * 2] - '0';
			else if (line[(v.x - 1) * 2] == 'A')
				world->map[v.y][v.x - 1] = 10;
			else
				world->map[v.y][v.x] = 0;
			v.x++;
		}
		v.y++;
	}
}
