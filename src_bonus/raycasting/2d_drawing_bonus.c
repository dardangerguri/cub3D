/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_drawing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:40:17 by dgerguri          #+#    #+#             */
/*   Updated: 2025/01/13 00:37:07 by dardangergu      ###   ########.fr       */
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

static void	adjust_coordinates(t_map_data *d, float *x, float *y)
{
	if (d->map_w > 10)
	{
		while (*x > SIZE_B * 5 && *x < (d->map_w - 6) * SIZE_B)
			*x = *x - SIZE_B;
		if (*x > (d->map_w - 6) * SIZE_B)
			*x = *x - (d->map_w - 10) * SIZE_B;
	}
	if (d->map_h > 6)
	{
		while (*y > SIZE_B * 3 && *y < (d->map_h - 4) * SIZE_B)
			*y = *y - SIZE_B;
		if (*y > (d->map_h - 4) * SIZE_B)
			*y = *y - (d->map_h - 6) * SIZE_B;
	}
	*x = (*x / SIZE_B) * 32;
	*y = (*y / SIZE_B) * 32;
}

static void	draw_player_block(t_map_data *d, float x, float y, uint32_t color)
{
	int	block_y;
	int	block_x;

	block_y = 0;
	adjust_coordinates(d, &x, &y);
	while (block_y < SIZE_P && x >= 0 && y >= 0)
	{
		block_x = 0;
		while (block_x < SIZE_P)
		{
			if (x + block_x < 320 && y + block_y < 192)
				mlx_put_pixel(d->mlx_data->window, x + block_x, y + block_y,
					color);
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
