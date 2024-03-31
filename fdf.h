/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:26:16 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/25 16:25:57 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
------------------------------- initial setup ----------------------------------
 */

//	header file
#ifndef FDF_H
# define FDF_H

/* -------------------- non-adjustable pre-settings ------------------------- */

//	macros for better code structure
# define ZOOM_DEFAULT 1.0
# define MARGIN 15
# define ROTATION_SPEED 1.0
# define HEIGHT_DEFAULT 1.0
# define Z 0
# define COLOR 1
# define ON 1
# define OFF -1
# define ROTATION_FACTOR 0.3
# define CHANGE 1
# define NO_CHANGE 0
# define ERROR -1

//	colors
# define RED      0xEE000000
# define GREEN    0x00EE0000
# define BLUE     0x0000EE00
# define WHITE    0xFFFFFF00
# define BLACK    0x00000000
# define YELLOW   0xEEEE0000
# define CYAN     0x00EEEE00
# define MAGENTA  0xEE00EE00
# define ORANGE   0xEE770000
# define PURPLE   0xEE008800
# define GRAY     0x88888800
# define PINK     0xEE99CC00
# define BROWN    0x8B451300

//	math data values
# define PI 3.14159265358979323846
# define EPSILON  0.00000001

//	macros for better code structure for get next line
# define NO_NEW_LINE 0
# define NEW_LINE INT_MAX
# define MAP_NOT_SQUARED INT_MIN

/* ----------------------- adjustable pre-settings -------------------------- */

//
# define DEFAULT_WINDOW_COLOR 0x000000EE
// window size between 100-2500
# define WIDTH 1024
# define HEIGHT 1024
// zoom factor between 0,50-0.99(ZOOM_M) and 1.01-1.50(ZOOM_P)
# define ZOOM_P 1.1
# define ZOOM_M 0.9
// Map movement in x and y direction between 1 and 30
# define SHIFT_DEFAULT 15
//	offset of the map center from the middle point of the window
# define OFFSET_DEFAULT 0.0
// Max zooming faktor end from 1-10(MAX) 11-30(MIN)
# define MAX_MAP_SIZE 35
# define MIN_MAP_SIZE 30
//	color for the z_axis of the map, if not given in the map choose a color
# define COLOR_DEFAULT_CEN WHITE
# define COLOR_DEFAULT_PLUS RED
# define COLOR_DEFAULT_MIN 0x00DDBB00
//	brightness for the map choose between 0x00 and 0xEE
# define BRIGHTNESS_DEFAULT 0xEE
//	rotation degree in x, y, z direction between 0.0 and 359.9 degrees
# define DEGREE_DEFAULT_X 320.0
# define DEGREE_DEFAULT_Y 130.0
# define DEGREE_DEFAULT_Z 320.0
//	height_change between 0.001 and 0.5
# define HEIGHT_FAKTOR 0.1

/* ------------------------------- libraries -------------------------------- */

//	mlx library
# include "MLX42/include/MLX42/MLX42.h"
//	my own libraries
# include "libft/libft.h"
//	public libraries, no math.h :D
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

/* -------------------------------- structs --------------------------------- */

//	struct to calculate the rgba part of the color in Hexadezimal range
typedef struct s_rgba_color
{
	int32_t		color_a;
	int32_t		color_b;
	int32_t		r_a;
	int32_t		g_a;
	int32_t		b_a;
	int32_t		a_a;
	int32_t		r_b;
	int32_t		g_b;
	int32_t		b_b;
	int32_t		a_b;
	int32_t		r;
	int32_t		g;
	int32_t		b;
	int32_t		a;
	int32_t		new_color;
}			t_color;

// This struct represents a point in a space (x, y, z)axis
// mid_x/y is the pixel distance to the middle point
// deg_mid_x/y is the degree to the middle point in each axis
// color is the default color of the point
typedef struct s_coordinates
{
	int						pos_xm;
	int						pos_ym;
	int						xw;
	int						yw;
	int						zw;
	double					xm;
	double					ym;
	double					zm;
	int32_t					color;
	struct s_coordinates	*next;
	struct s_coordinates	*before;
	struct s_coordinates	*next_y;
	struct s_coordinates	*before_y;
}	t_coord;

// size of the map, each point is one value
// x = x-axis coordinate , y = y-axis z = z = z-axis
//	m = map object, w = window, cent = center/middlepoint
//
typedef struct s_arr_size
{
	int		xm_size;
	int		ym_size;
	int		maxsz_x_p;
	int		maxsz_x_m;
	int		maxsz_y_p;
	int		maxsz_y_m;
	int		maxsz_z_p;
	int		maxsz_z_m;
	int		xposmw;
	int		yposmw;
	int		zcentmw;
	int		zmcent_plus;
	int		zmcent_minus;
	double	xm_offset;
	double	ym_offset;
	double	zm_offset;
	int		xm_rot_deg;
	int		ym_rot_deg;
	int		zm_rot_deg;
	double	height_change;
	int32_t	color_plus;
	int32_t	color_minus;
	int		map_area;
}	t_sz;

//	struct for images for the manual, independent from the map
typedef struct s_manual
{
	mlx_image_t		*str;
	char			*string;
	struct s_manual	*next;
}	t_man;

// settings for the window, map is an array woth the map values, in coord
// are the coordinates for each points, map size with map size values
typedef struct s_window
{
	mlx_t		*mlx;
	mlx_t		*mlx_info;
	mlx_image_t	*image;
	mlx_image_t	*man;
	t_man		*manual;
	int			width;
	int			height;
	void		*win;
	int32_t		***map;
	t_sz		map_sz;
	t_coord		*coord;
	int			cent_xw;
	int			cent_yw;
	double		zoom;
	int			start_size;
	int			debug_mode;
	int			mouse_posx;
	int			mouse_posy;
	t_coord		debug_point_1;
	t_coord		debug_point_2;
	t_coord		debug_point_3;
	t_coord		debug_point_4;
	float		max_zoom_size;
	float		min_zoom_size;
}	t_window;

/*
--------------------------------- functions ------------------------------------
*/

// --------------------------- start and setup ---------------------------------

//	assigning values

int		set_default_window_data(t_window *window);
int		map_size_default_setting(t_sz *map_sz, t_sz size);
int32_t	set_coord(t_window *window);
int		assign_coord_position(t_window *window, t_coord *coord, int x, int y);
int		assign_color(t_window *window, t_coord *coord, int x, int y);

//	initial setup

int		initialize_window_from_args(t_window *window, char *argv[]);
int		assign_map_values(int32_t ***map, char **collumn, int line);
int		get_map_size(t_window *window);

//	main loop

void	ft_render(void *param);
int		ft_hook_key(t_window *window, int *x_offset, int *y_offset);

//	mlx initiate

int		create_manual(t_window *window);
int		initialize_mlx_image(t_window *window);

//	reading_map

int32_t	***assign(int32_t ***map, char **collumn,
			int collumn_counter, int *row);
int32_t	***read_map_and_assign_data(int fd);
int		read_line_into_collumn(int fd, int *collumn_counter, char ***collumn);
void	delete_spaces(int *collumn_counter, char ***collumn);

//	setup help functions

void	ft_set_before_y(t_coord **head, int iterations, t_window *window);
void	ft_set_after_y(t_coord *head, t_window *window);
int		get_index(t_window *window, int pos_xm, int pos_ym);
int32_t	link_add_pt(t_coord **coord, int x, int y);
void	lstadd_back(t_man **lst, t_man *new);

//-------------------------------- user input ----------------------------------

//	key functions

int		shift_map(t_window *window, int *x_set, int *y_set);
double	zoom_map(t_window *window);
double	rotate_map(t_window *window);
int		change_height_map(t_window *window);

//	mouse functions

int		check_mouse_clicked(t_window *window, int x, int y, enum mouse_key key);
int		mouse_shift(t_window *window, int *x_set, int *y_set);
int		mouse_rotation(t_window *window);

//	user input

int		check_change_height(t_window *window);
int		check_change_in_rotation(t_window *window);

//	key additional functions

int		reset_map(t_window *window);
int		debug_mode_map(t_window *window);

int		information(t_window *window);

//	user input helpers

void	remove_manual_from_window(t_window *window);
void	set_map_to_middle(t_window *window);
void	print_manual(t_window *window);

//--------------------------------- rendering ----------------------------------

//	draw pixel

int		check_error_pixel(t_coord *pt_a, t_coord *pt_b, int *x0, int *y0);
int32_t	find_color(int32_t color_a, int32_t color_b, float t);
void	connect_points(t_window *window, t_coord *point_a, t_coord *point_b);

//	update values

int32_t	update_coord(t_window *window, int x_offset, int y_offset);
int		calculate_height_change(t_window *window);
void	reset_map_size(t_window *window);
int		update_mapsize(t_sz *map_sz, t_coord *temp);

//--------------------------------- mathematics --------------------------------

//	angle mathematics

double	factorial(double n);
double	power(double n, double power);
double	ft_sin(double x);
double	ft_cos(double x);

//	mathematics

float	round_float(float num, int range);
double	ft_sqrt(double a);
float	calc_z(t_coord *point_a, t_coord *point_b, float x_p, float y_p);

//	mathematics 2

int		ft_atan(int x);
double	radians(double degrees);
int		ft_round(double num);
int		ft_abs(int num);
void	degree(int *rot);

//-------------------------------- help functions ------------------------------

//	clear functions

void	free_map_coordinates(t_coord **stack);
void	clear_image(t_window *window, uint32_t color);
void	free_map(int32_t ***map);
int32_t	***free_map_data(int32_t ***map, char **collumn, int row);
void	free_manual(t_man **stack);

//	help functions

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int		find_highest_and_lowest(t_window *map);
double	check_zoom_direction(int map_middle, int zoom_position, double zoom);
int32_t	convert_str_to_hex(char *comma_pos);

//----------------------------------- error ------------------------------------

//	error functions

int		check_defines(void);
int		check_more_defines(void);
int		ft_shutdown_error(mlx_t *mlx);

//	map errors
int		check_map_integer(int32_t ***map_collumn, char **collumn,
			int x, int line);
int		check_for_map_errors(int line, int row, int collumn_counter);
int		check_colorcode(char *hex_str, char *digit);

//--------------------------------- debugging ----------------------------------

// debugging

int		print_coord_data(t_window *window, t_coord *current, const char *color);
void	print_map(int32_t ***map);
void	print_stacks(t_window *window, t_coord *current);
void	print_debug_point_1(t_window *window);
void	print_debug_point_2(t_window *window);

//------------------------------- calculations ---------------------------------

//	limits

int		range_check(t_window *window, int x, int y, int z);
int		check_margin_border(t_window *window);

//	rotate functions

void	rotate(double *a, double *b, t_window window, char axis);
int		rotation_calc(t_window *window, t_coord *cur_point);

//	window resize functions

void	ft_resize(int width, int height, void *param);
void	check_if_map_is_outside_window(t_window *window);

//	zoom functions

int		check_mouse_position(t_window *window, double *zoom_x, double *zoom_y);
void	calculate_zoom_pos(t_window *window);
void	ft_scroll(double xoffset, double yoffset, void *param);
int		zoom_calc(t_window *window, t_coord *cur_point);

#endif
