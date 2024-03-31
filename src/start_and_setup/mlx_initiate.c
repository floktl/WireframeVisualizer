/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initiate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:53:16 by flo               #+#    #+#             */
/*   Updated: 2024/03/25 16:30:41 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//	reading the lines from the manual and assigning them in a list of images
int	create_manual(t_window *window)
{
	char	*manual_line;
	int		fd;
	t_man	*new_node;

	fd = open("manual.txt", O_RDONLY);
	manual_line = get_next_line(fd);
	if (!manual_line)
	{
		close(fd);
		perror("manual damaged");
		return (0);
	}
	while (manual_line)
	{
		new_node = malloc(sizeof(t_man));
		if (!new_node)
			return (EXIT_FAILURE);
		new_node->string = manual_line;
		new_node->next = NULL;
		lstadd_back(&window->manual, new_node);
		manual_line = get_next_line(fd);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

//	function to set up the window and image inside the window
int	initialize_mlx_image(t_window *window)
{
	int32_t	max_size_x;
	int32_t	max_size_y;

	ft_printf("\033[0;35mInitializing Window...\033[0m\n");
	window->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!(window->mlx))
		return (EXIT_FAILURE);
	window->image = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (!(window->image)
		|| mlx_image_to_window(window->mlx, window->image, 0, 0) == ERROR)
		return (EXIT_FAILURE);
	window->man = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (!(window->image)
		|| mlx_image_to_window(window->mlx, window->image, 0, 0) == ERROR
		|| create_manual(window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_get_monitor_size(0, &max_size_x, &max_size_y);
	mlx_set_window_limit(window->mlx, 300, 300, max_size_x, max_size_y);
	ft_printf("\033[0;34m\nProgramm ready, press I for manual!\033[0m\n");
	window->man = mlx_put_string(window->mlx, "Press <I> for manual", 8, 8);
	return (EXIT_SUCCESS);
}
