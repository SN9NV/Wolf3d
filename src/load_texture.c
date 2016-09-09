/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 13:05:51 by adippena          #+#    #+#             */
/*   Updated: 2016/06/26 14:24:32 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static uint32_t	**malloc_texture(void)
{
	uint32_t	**tex;
	size_t		y;

	if ((tex = (uint32_t **)malloc(sizeof(uint32_t *) * TEX)) == NULL)
	{
		perror("Malloc failed for loading texture");
		return (0);
	}
	y = 0;
	while (y < TEX)
		if ((tex[y++] = (uint32_t *)malloc(sizeof(uint32_t) * TEX)) == NULL)
		{
			perror("Malloc failed for loading texture");
			return (0);
		}
	return (tex);
}

static int		open_texture(char *file)
{
	int		fd;

	file = ft_strjoin("resources/textures/", file);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		perror("Error opening texture file");
		return (0);
	}
	return (fd);
}

uint32_t		**load_texture(char *file)
{
	int				fd;
	t_v2dint		v;
	unsigned char	line[TEX * TEX];
	uint32_t		**tex;

	tex = malloc_texture();
	if ((fd = open_texture(file)) == 0)
		return (NULL);
	v.y = -1;
	while (++v.y < TEX)
	{
		v.x = -1;
		read(fd, &line, (TEX * 4));
		while (++v.x < TEX)
		{
			tex[v.x][v.y] = 0;
			tex[v.x][v.y] |= *(uint32_t *)(line + v.x * 4) & 0xFFFFFF;
			tex[v.x][v.y] |= (0xFF - *(line + v.x * 4 + 3)) << 24;
		}
	}
	close(fd);
	return (tex);
}
