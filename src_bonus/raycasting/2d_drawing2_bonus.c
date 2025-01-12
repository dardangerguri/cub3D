/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_drawing2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 03:02:47 by jhesso            #+#    #+#             */
/*   Updated: 2025/01/13 00:34:57 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_blocks(t_map_data *d, float x, float y, uint32_t color)
{
	int	block_y;
	int	block_x;

	block_y = 0;
	while (block_y < 32 && color)
	{
		block_x = 0;
		while (block_x < 32)
		{
			mlx_put_pixel(d->mlx_data->window, x + block_x, y + block_y, color);
			block_x++;
		}
		block_y++;
	}
}

static void	get_top_left_y_and_x(t_map_data *data, int *y, int *x, int type)
{
	int	pos_x;
	int	pos_y;

	pos_x = ((int)data->pos.x / SIZE_B) + 1;
	pos_y = ((int)data->pos.y / SIZE_B) + 1;
	if (type == 1)
	{
		if (data->map_h > 6 && pos_y > data->map_h - 6 / 2)
			*y = data->map_h - 6;
		else if (data->map_h > 6 && pos_y > 6 / 2)
			*y = pos_y - 6 / 2;
		else
			*y = 0;
	}
	else if (type == 2)
	{
		if (data->map_w > 10 && pos_x > data->map_w - 10 / 2)
			*x = data->map_w - 10;
		else if (data->map_w > 10 && pos_x > 10 / 2)
			*x = pos_x - 10 / 2;
		else
			*x = 0;
	}
}

void	draw_map_big(t_map_data *data, int row, int column, int x)
{
	int			y;
	uint32_t	color;

	get_top_left_y_and_x(data, &y, 0, 1);
	while (data->map_c[y] && row < 6)
	{
		column = 0;
		get_top_left_y_and_x(data, 0, &x, 2);
		while (column < 10)
		{
			if (x < (int)ft_strlen(data->map_c[y]) && data->map_c[y][x] == '1')
				color = get_rgba(0, 0, 0, 255);
			else if (x < (int)ft_strlen(data->map_c[y]) \
				&& (data->map_c[y][x] == '0' || (data->map_c[y][x] != ' ' \
				&& ft_strrchr("NSWE", data->map_c[y][x]))))
				color = get_rgba(96, 96, 96, 255);
			else
				color = 0x000000;
			draw_blocks(data, column * 32, row * 32, color);
			x++;
			column++;
		}
		y++;
		row++;
	}
}

void	draw_map_small(t_map_data *data, int x, int y)
{
	uint32_t	color;

	while (data->map_c[y] && y < 6)
	{
		x = 0;
		while (data->map_c[y][x] && x < 10)
		{
			if (x < (int)ft_strlen(data->map_c[y]) && data->map_c[y][x] == '1')
				color = get_rgba(0, 0, 0, 255);
			else if (x < (int)ft_strlen(data->map_c[y]) \
				&& (data->map_c[y][x] == '0' || (data->map_c[y][x] != ' ' \
				&& ft_strrchr("NSWE", data->map_c[y][x]))))
				color = get_rgba(96, 96, 96, 255);
			else
				color = 0x000000;
			draw_blocks(data, x * 32, y * 32, color);
			x++;
		}
		y++;
	}
}
