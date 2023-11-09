/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:40:17 by dgerguri          #+#    #+#             */
/*   Updated: 2023/11/09 16:33:21 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_blocks(t_map_data *data, int x, int y, uint32_t color)
{
	int	block_y;
	int	block_x;

	block_y = 0;
	while (block_y < SIZE_B - 1)
	{
		block_x = 0;
		while (block_x < SIZE_B - 1)
		{
			mlx_put_pixel(data->mlx_data->window, x + block_x, y + block_y, color);
			block_x++;
		}
		block_y++;
	}
}

static void	get_top_left_y_and_x(t_map_data *data, int *y, int *x, int type)
{
	if (type == 1)
	{
		*y = 0;
		if (data->map_size - 33 / 2 > 0)
		{
			if (g->components.rows - g->components.player_pos.y > 32 / 2)
				*y = g->components.player_pos.y - 33 / 2;
			else
				*y = g->components.rows - 33;
		}
	}
	else if (type == 2)
	{
		if (g->components.player_pos.x - 60 / 2 > 0)
		{
			if (g->components.columns - g->components.player_pos.x > 60 / 2)
				*x = g->components.player_pos.x - 60 / 2;
			else
			{
				*x = g->components.columns - 60;
				if (*x < 0)
					*x = 0;
			}
		}
	}
}

void draw_map_long(t_map_data *data, int row, int column, int x)
{
	int y;
	uint32_t color;

	get_top_left_y_and_x(data, &y, 0, 1);
	while (y < data->map_size)
	{
		// column = 0;
		x = 0;
		get_top_left_y_and_x(data, 0, &x, 2);
		while ((size_t)x < data->longest_line)
		{
				if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
					color = 0x808080;
				else if (x < (int)ft_strlen(data->map[y]) \
					&& (data->map[y][x] == '0' || (data->map[y][x] != ' ' \
					&& ft_strrchr("NSWE", data->map[y][x]))))
					color = 0x0000FF;
				else
					color = 0x000000;
				draw_blocks(data, x * SIZE_B, y * SIZE_B, color);
			x++;
		}
		row++;
		y++;
	}
	return (1);
}


void	draw_map(t_map_data *data)
{
	int x;
	int y;
	uint32_t color;

	y = 0;
	if (data->longest_line > 10 || data->map_size > 5)
		draw_map_long(data);
		// printf("helo");
	else
	{
		while (data->map[y] && (y * SIZE_B) < HEIGHT_W)
		{
			x = 0;
			while (data->map[y][x] && (x * SIZE_B) < WIDTH_W)
			{
				if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
					color = 0x808080;
				else if (x < (int)ft_strlen(data->map[y]) \
					&& (data->map[y][x] == '0' || (data->map[y][x] != ' ' \
					&& ft_strrchr("NSWE", data->map[y][x]))))
					color = 0x0000FF;
				else
					color = 0x000000;
				draw_blocks(data, x * SIZE_B, y * SIZE_B, color);
				x++;
			}
			y++;
		}
	}
}

static void	draw_player_block(t_map_data *data, float x, float y, uint32_t color)
{
	int	block_y;
	int	block_x;

	block_y = 0;
	while (data->pos.x >= 0 && data->pos.y >= 0 && block_y < SIZE_P)
	{
		block_x = 0;
		while (block_x < SIZE_P)
		{
			mlx_put_pixel(data->mlx_data->window, x + block_x, y + block_y, color);
			block_x++;
		}
		block_y++;
	}
}

void	draw_player(t_map_data *data)
{
	int	block_y;
	int	block_x;

	block_y = 0;
	while ((block_y * SIZE_B) < HEIGHT_W)
	{
		block_x = 0;
		while ((block_x * SIZE_B) < WIDTH_W)
		{
			draw_player_block(data, (data->pos.x ), (data->pos.y), 0xDFFF00);
			block_x++;
		}
		block_y++;
	}
}

void	draw_nose(t_map_data *data)
{
	t_float_v	angle;
	t_float_v	pos;
	float		i;

	angle.x = data->dir.x;
	angle.y = data->dir.y;
	pos.x = data->pos.x + SIZE_P / 2;
	pos.y = data->pos.y + SIZE_P / 2;
	i = 0;
	while (i < 20 && pos.y > -1 && pos.x > -1)
	{
		mlx_put_pixel(data->mlx_data->window, pos.x, pos.y, 0xF000FF);
		pos.y += angle.y;
		pos.x += angle.x;
		i++;
	}
}
