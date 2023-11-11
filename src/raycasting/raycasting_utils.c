/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:22:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/11/11 04:07:52 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_pixel_color(mlx_texture_t *img, uint32_t x, uint32_t y)
{
	uint32_t	*color;

	color = (uint32_t *)(img->pixels + (x + y * img->width) * sizeof(uint32_t));
	return (*color);
}

unsigned int	get_pixel(t_mlx_data *mlx, int x, int y, int dir)
{
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = NULL;
	color = 0;
	if (dir == NORTH)
		texture = mlx->north;
	else if (dir == EAST)
		texture = mlx->east;
	else if (dir == SOUTH)
		texture = mlx->south;
	else if (dir == WEST)
		texture = mlx->west;
	if ((uint32_t)x >= texture->width || x < 0 || \
		(uint32_t)y >= texture->height || y < 0)
		return (get_rgba(255, 0, 0, 255));
	if (texture)
		color = get_pixel_color(texture, x, y);
	return (color);
}

float	fix_angle(float angle)
{
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	return (angle);
}

float	deg_to_rad(float degrees)
{
	float	radians;

	radians = degrees * (PI / 180);
	return (radians);
}

float	get_dist(t_float_v *player, t_float_v *wall_hit)
{
	float	a;
	float	b;
	float	c;

	a = player->x - wall_hit->x;
	b = player->y - wall_hit->y;
	c = sqrt((a * a) + (b * b));
	return (c);
}
