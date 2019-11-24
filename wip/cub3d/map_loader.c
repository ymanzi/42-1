/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:23:28 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 14:23:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ARG_CMP(arg, max) (ft_strncmp(key, arg, max) == 0)

static char
	*i_map_loader_interpret_key(t_engine *eng, t_map *map, char *line,
								char **split)
{
	char	*key;
	char	*path;
	char	*r;

	key = split[0];
	path = ft_strchr(line, ' ') + 1;
	r = NULL;
	if (split[1] == NULL)
		r = (ft_strjoin("No argument found for config key: ", key));
	else if (ft_strncmp(key, P_RESOLUTION, 2) == 0)
		r = (map_loader_set_resolution(key, split + 1, eng));
	else if (ARG_CMP(P_SPRITE, 2))
		r = (map_loader_set_sprite_texture(eng, map, path));
	else if (ARG_CMP(P_FLOOR_COLOR, 2))
		r = (map_loader_set_color(key, split[1], &map->floor_color));
	else if (ARG_CMP(P_ROOF_COLOR, 2))
		r = (map_loader_set_color(key, split[1], &map->roof_color));
	else
		r = (map_loader_set_wall_texture(eng, map, key, path));
	return (r);
}

static char
	*i_map_loader_parse_line(t_engine *eng, t_map *map, char *line, int *fully)
{
	char	**split;
	char	*key;
	char	*error;

	CHECK_PTR_DEF(split = ft_split(line, ' '), EMALLOC("line parser"));
	error = NULL;
	key = split[0];
	if (*fully == 2 && key != NULL)
		return (E("More content after map data") + (int)ft_split_free(&split));
	if (key == NULL)
	{
		*fully = *fully == 1 ? 2 : *fully;
		return (0 + ft_split_free(&split));
	}
	if (map->objs || (!map->objs && ft_isinstr(split[0][0], "012") != -1))
	{
		error = map_loader_parse_grid(eng, map, split);
		*fully = 1;
	}
	else
		error = i_map_loader_interpret_key(eng, map, line, split);
	ft_split_free(&split);
	return (error);
}

t_map
	*map_create(char *file)
{
	t_map	*map;

	CHECK_MALLOC(map, sizeof(t_map));
	map->file = file;
	map->objs = NULL;
	map->roof_color = -1;
	map->floor_color = -1;
	map->wall_texs[NORTH] = NULL;
	map->wall_texs[SOUTH] = NULL;
	map->wall_texs[WEST] = NULL;
	map->wall_texs[EAST] = NULL;
	map->sprite = NULL;
	map->size.w = 0;
	map->size.h = 0;
	map->sprts = NULL;
	map->spr_ordr = NULL;
	map->spr_dist = NULL;
	map->sprite_count = 0;
	return (map);
}

t_map
	*map_load(t_engine *eng, char *path)
{
	int		fd;
	int		returned;
	int		fully;
	char	*line;
	char	*error;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (engine_error_raison(ft_strjoin("Failed to read file: ", path)));
	CHECK_PTR(eng->map = map_create(path));
	eng->map->objs = NULL;
	fully = 0;
	while (1)
	{
		returned = get_next_line(fd, &line);
		error = i_map_loader_parse_line(eng, eng->map, line, &fully);
		free(line);
		if (error != NULL)
			engine_error(error);
		if (!returned)
			break ;
	}
	return (map_finalize(eng->map));
}
