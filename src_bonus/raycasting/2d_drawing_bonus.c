/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_drawing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:40:17 by dgerguri          #+#    #+#             */
/*   Updated: 2025/01/13 00:22:19 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_player_nose(t_map_data *d, float x, float y, float angle)
{
	int	nose_x;
	int	nose_y;
	int	i;

	i = 0;
	while (i < 6)
	{
		nose_x = x + SIZE_P / 2 + cos(deg_to_rad(-angle)) * (SIZE_P / 2 + i);
		nose_y = y + SIZE_P / 2 + sin(deg_to_rad(-angle)) * (SIZE_P / 2 + i);
		if (nose_x >= 0 && nose_x < 320 && nose_y >= 0 && nose_y < 192)
			mlx_put_pixel(d->mlx_data->window, nose_x, nose_y, get_rgba(0, 153, 0, 255));
		i++;
	}
}

static void	draw_player_block(t_map_data *d, float x, float y, uint32_t color)
{
	int	block_y;
	int	block_x;

	block_y = 0;
	while (x > SIZE_B * 5 && x < (d->map_w - 6) * SIZE_B + (27 / 2))
		x = x - SIZE_B;
	while (y > SIZE_B * 3 && y < (d->map_h - 4) * SIZE_B + (27 / 2))
		y = y - SIZE_B;
	if (d->map_w > 10 && x > (d->map_w - 6) * SIZE_B + (27 / 2))
		x = x - d->map_w * SIZE_B + 320;
	if (d->map_h > 6 && y > (d->map_h - 4) * SIZE_B + (27 / 2))
		y = y - d->map_h * SIZE_B + 192;
	while (x >= 0 && y >= 0 && block_y < SIZE_P)
	{
		block_x = 0;
		while (block_x < SIZE_P)
		{
			mlx_put_pixel(d->mlx_data->window, x + block_x, y + block_y, color);
			block_x++;
		}
		block_y++;
	}
	draw_player_nose(d, x, y, d->angle);
}

static void	draw_player(t_map_data *data)
{
	int			block_y;
	int			block_x;
	uint32_t	color;

	block_y = 0;
	color = get_rgba(0, 153, 0, 255);
	while ((block_y * SIZE_B) < 10)
	{
		block_x = 0;
		while ((block_x * SIZE_B) < 20)
		{
			draw_player_block(data, data->pos.x, data->pos.y, color);
			block_x++;
		}
		block_y++;
	}
}

void	draw_minimap(t_map_data *data)
{
	if (data->map_w > 10 || data->map_h > 6)
		draw_map_big(data, 0, 0, 0);
	else
		draw_map_small(data, 0, 0);
	draw_player(data);
}
