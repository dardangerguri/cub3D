/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:03:51 by dgerguri          #+#    #+#             */
/*   Updated: 2023/11/11 02:43:11 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_mlx_data(t_mlx_data *data)
{
	if (data->window)
		mlx_delete_image(data->mlx, data->window);
	if (data->north)
		mlx_delete_texture(data->north);
	if (data->south)
		mlx_delete_texture(data->south);
	if (data->west)
		mlx_delete_texture(data->west);
	if (data->east)
		mlx_delete_texture(data->east);
	if (data->mlx)
		mlx_terminate(data->mlx);
}

void	cleanup(t_map_data *data)
{
	if (data->file_splitted)
		free_array(data->file_splitted);
	if (data->north)
		free(data->north);
	if (data->south)
		free(data->south);
	if (data->west)
		free(data->west);
	if (data->east)
		free(data->east);
	if (data->floor)
		free(data->floor);
	if (data->ceiling)
		free(data->ceiling);
	if (data->map)
		free_array(data->map);
	if (data->mlx_data)
	{
		cleanup_mlx_data(data->mlx_data);
		free(data->mlx_data);
	}
}
