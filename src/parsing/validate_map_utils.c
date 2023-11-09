/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:19:59 by jhesso            #+#    #+#             */
/*   Updated: 2023/11/09 14:39:43 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	find_wall(char **map, t_vector pos)
{
	int		row;
	int		col;

	row = pos.y;
	col = pos.x;
	if (map[row][0] == '0')
		return (false);
	if (map[row][col + 1] == '\0' || map[row][col + 1] == ' ')
		return (false);
	if (map[row][col - 1] == '\0' || map[row][col - 1] == ' ')
		return (false);
	if (map[row + 1][col] == '\0' || map[row + 1][col] == ' ')
		return (false);
	if (map[row - 1][col] == '\0' || map[row - 1][col] == ' ')
		return (false);
	return (true);
}

bool	map_filled(char **map)
{
	char	c;
	int		row;
	int		col;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			c = map[row][col];
			if (c != '1' && c != ' ')
				return (false);
			col++;
		}
		row++;
	}
	return (true);
}

void	remove_newline(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	i--;
	if (map[i][0] == '\0')
	{
		free(map[i]);
		map[i] = NULL;
	}
}

t_vector	get_last_point(char **map)
{
	t_vector	ret;
	int			row;
	int			col;

	row = 0;
	col = 0;
	while (map[row])
		row++;
	row--;
	while (map[row][col])
		col++;
	col--;
	ret.y = row;
	ret.x = col;
	return (ret);
}

t_vector	find_empty_space(char **map)
{
	t_vector	vec;

	vec.y = 1;
	while (map[vec.y])
	{
		vec.x = 0;
		while (map[vec.y][vec.x])
		{
			if (map[vec.y][vec.x] == '0' || map[vec.y][vec.x] == 'N' || \
				map[vec.y][vec.x] == 'S' || map[vec.y][vec.x] == 'E' || \
				map[vec.y][vec.x] == 'W')
				break ;
			vec.x++;
		}
		if (map[vec.y][vec.x] == '0' || map[vec.y][vec.x] == 'N' || \
			map[vec.y][vec.x] == 'S' || map[vec.y][vec.x] == 'E' || \
			map[vec.y][vec.x] == 'W')
			break ;
		vec.y++;
	}
	if (!map[vec.y])
		vec.y--;
	if (!map[vec.y][vec.x])
		vec.x--;
	return (vec);
}
