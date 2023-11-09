/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:24:44 by jhesso            #+#    #+#             */
/*   Updated: 2023/11/09 15:23:11 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	starting_point(t_map_data *d, int row, int col, bool *p_start, char c) //move somewhere
{
	d->pos.x = col * SIZE_B + ((SIZE_B - SIZE_P) / 2);
	d->pos.y = row * SIZE_B + ((SIZE_B - SIZE_P) / 2);
	*(p_start) = true;
	if (c == 'N')
	{
		d->angle = 90;
		d->dir.x = cos(90 * M_PI / 180);
		d->dir.y = -sin(90 * M_PI / 180);
	}
	else if (c == 'S')
	{
		d->angle = 270;
		d->dir.x = cos(270 * M_PI / 180);
		d->dir.y = -sin(270 * M_PI / 180);
	}
	else if (c == 'W')
	{
		d->angle = 180;
		d->dir.x = cos(180 * M_PI / 180);
		d->dir.y = -sin(180 * M_PI / 180);
	}
	else if (c == 'E')
	{
		d->angle = 0;
		d->dir.x = cos(0 * M_PI / 180);
		d->dir.y = -sin(0 * M_PI / 180);
	}
	printf("pdx: %f   %f   %f\n", d->angle, d->dir.x, d->dir.y);
}

static bool	check_chars(t_map_data *data, int row, int col, bool p_start)
{
	char	c;

	while (data->map[row])
	{
		col = 0;
		while (data->map[row][col])
		{
			c = data->map[row][col];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && \
				c != 'W' && c != ' ')
				return (error_message(X_UNKNOWN_ELEMENT_MAP));
			if ((c == 'N' || c == 'S' || c == 'E' || c == 'W') && !p_start)
				starting_point(data, row, col, &p_start, c);
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				return (error_message(X_MULTIPLE_S_POINTS));
			if (c == '\t' || c == '\v' || c == '\f' || c == '\r')
				return (error_message(X_UNKNOWN_ELEMENT_MAP));
			col++;
		}
		row++;
	}
	if (!p_start)
		return (error_message(X_S_P_MISSING));
	return (true);
}

// static bool	check_first_and_last(char **map)
// {
// 	int		row;
// 	int		col;
// 	char	c;

// 	row = 0;
// 	col = 0;
// 	while (map[row][col])
// 	{
// 		c = map[row][col];
// 		if (c != '1' && c != ' ')
// 			return (false);
// 		col++;
// 	}
// 	while (map[row + 1])
// 		row++;
// 	row--;
// 	col = 0;
// 	while (map[row][col])
// 	{
// 		c = map[row][col];
// 		if (c != '1' && c != ' ')
// 			return (false);
// 		col++;
// 	}
// 	return (true);
// }

static bool	flood_fill(char **map, t_vector pos, bool *stop)
{
	if (map[pos.y][pos.x] == '\0' || (*stop))
		return (false);
	if (map[pos.y][pos.x] == '1')
		return (true);
	if (find_wall(map, pos))
		map[pos.y][pos.x] = '1';
	else
	{
		*(stop) = true;
		return (false);
	}
	flood_fill(map, (t_vector){pos.x + 1, pos.y}, stop);
	flood_fill(map, (t_vector){pos.x - 1, pos.y}, stop);
	flood_fill(map, (t_vector){pos.x, pos.y + 1}, stop);
	flood_fill(map, (t_vector){pos.x, pos.y - 1}, stop);
	return (false);
}

static size_t get_longest_line(char **map)
{
	size_t	i;
	size_t line_l;
	size_t len;

	i = 0;
	len = 0;
	while (map[i])
	{
		line_l = ft_strlen(map[i]);
		if (ft_strlen(map[i]) > len)
			len = line_l;
		i++;
	}
	return (len);
}

static size_t get_map_size(char **map)
{
	size_t	i;

	i = 0;
	while (map[i] && map[i][0] != '\0')
		i++;
	return (i);
}

static bool	check_walls(t_map_data *data, bool stop)
{
	char		**tmp_map;
	t_vector	last_point;
	t_vector	point;

	// if (!check_first_and_last(data->map))
	// 	return (false);
	data->longest_line = get_longest_line(data->map); //change it later and initialize;
	data->map_size = get_map_size(data->map); //change it later and initialize;
	remove_newline(data->map);
	tmp_map = duplicate_map(data->map);
	last_point = get_last_point(tmp_map);
	point = find_empty_space(tmp_map);
	while (true)
	{
		if ((point.y == last_point.y && point.x == last_point.x) || stop)
			break ;
		flood_fill(tmp_map, point, &stop);
		point = find_empty_space(tmp_map);
	}
	if (!map_filled(tmp_map))
		return (false);
	free_array(tmp_map);
	return (true);
}

bool	validate_map(t_map_data *data)
{
	if (!check_chars(data, 0, 0, false))
		return (false);
	if (!check_walls(data, false))
		return (error_message(X_MAP_NOT_CLOSED));
	return (true);
}
