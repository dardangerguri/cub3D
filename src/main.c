/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:00:19 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/21 17:25:39 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_struct(t_map_data *data) // this is just for testing!
{
	printf("------STRUCT-----\n");
	printf("NORTH: %s\n", data->north);
	printf("SOUTH: %s\n", data->south);
	printf("WEST: %s\n", data->west);
	printf("EAST: %s\n", data->east);
	printf("FLOOR: %s\n", data->floor);
	printf("CEILING: %s\n", data->ceiling);
	// print_string_arr(data->map);
}

int	main(int argc, char **argv)
{
	t_map_data	data;

	if (argc == 2)
	{
		if (map_data(&data, argv[1]))
			ft_printf(1, "Everything working fine!\n");
		else
		{
			ft_printf(2, "Not Working!\n");
			exit(1);
		}
	}
	else
		ft_printf(2, "ERROR"); //should decide about the error!
	return (0);
}
