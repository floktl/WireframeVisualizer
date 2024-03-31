/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:54:00 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/25 10:50:37 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//---------------------- functions to hadle error cases ------------------------
//

//--------------------------- program error-cases ------------------------------

//	function to check if the defines are out of the allowed border
int	check_defines(void)
{
	if (ZOOM_DEFAULT != 1.0 || MARGIN != 15)
		return (ft_printf("Dont change default settings!!\n"), EXIT_FAILURE);
	if (WIDTH < 100 || WIDTH > 2500 || HEIGHT < 100 || HEIGHT > 2500)
		return (ft_printf("Change WIDTH & HEIGHT 100 to 2500\n"), EXIT_FAILURE);
	if (ZOOM_M < 0.5 || ZOOM_M > 0.99 || ZOOM_P < 1.01 || ZOOM_P > 1.50)
		return (ft_printf("zoom 0,5-0.99(M) 1.01-1.5(P)\n"), EXIT_FAILURE);
	if (SHIFT_DEFAULT < 1 || SHIFT_DEFAULT > 30)
		return (ft_printf("SHIFT_DEFAULT between 1 and 30\n"), EXIT_FAILURE);
	if (MAX_MAP_SIZE < 1 || MAX_MAP_SIZE > 50
		|| MIN_MAP_SIZE < 11 || MIN_MAP_SIZE > 30)
		return (ft_printf("mapsizee 1-10(MAX) 11-30(MIN)\n"), EXIT_FAILURE);
	if (ZOOM_DEFAULT != 1.0 || MARGIN != 15 || ROTATION_SPEED != 1.0
		|| HEIGHT_DEFAULT != 1.0 || Z != 0 || COLOR != 1 || ON != 1 || OFF != -1
		|| ROTATION_FACTOR != 0.3 || CHANGE != 1 || NO_CHANGE != 0
		|| ERROR != -1)
		return (ft_printf("dont change the default macros!\n"), EXIT_FAILURE);
	if (check_more_defines() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (NO_CHANGE);
}

//	thank you normintte for having thousand functions, i hate you sometimes...
int	check_more_defines(void)
{
	if (RED != 0xEE000000 || GREEN != 0x00EE0000 || BLUE != 0x0000EE00
		|| WHITE != 0xFFFFFF00 || BLACK != 0x00000000 || YELLOW != 0xEEEE0000
		|| CYAN != 0x00EEEE00 || MAGENTA != 0xEE00EE00 || ORANGE != 0xEE770000
		|| PURPLE != 0xEE008800 || GRAY != 0x88888800 || PINK != 0xEE99CC00
		|| BROWN != 0x8B451300)
		return (ft_printf("dont change the default colors!\n"), EXIT_FAILURE);
	if (PI != 3.14159265358979323846 || EPSILON != 0.00000001)
		return (ft_printf("dont touch the holy math!\n"), EXIT_FAILURE);
	if (BRIGHTNESS_DEFAULT < 0x00 || BRIGHTNESS_DEFAULT > 0xEE)
		return (ft_printf("it's a brightmess don't blend me!\n"), EXIT_FAILURE);
	if (DEGREE_DEFAULT_X < 0 || DEGREE_DEFAULT_X > 359.9
		|| DEGREE_DEFAULT_Y < 0 || DEGREE_DEFAULT_Y > 359.9
		|| DEGREE_DEFAULT_Z < 0 || DEGREE_DEFAULT_Z > 359.9)
		return (ft_printf("you need a degree lesson i guess!\n"), EXIT_FAILURE);
	if (HEIGHT_FAKTOR < 0.001 || HEIGHT_FAKTOR > 0.5)
		return (ft_printf("i have the highground Anakin!\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//----------------------------- mlx error-cases --------------------------------

//	save shutdown function for the mlx window in case of an error occuring
int	ft_shutdown_error(mlx_t *mlx)
{
	mlx_close_window(mlx);
	return (perror(mlx_strerror(mlx_errno)), ERROR);
}
