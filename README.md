

<div align="center">

  <h1>Wireframe Visualizer- a 42 Project</h1>

  <p>
    A Porgram to display wireframe maps!
  </p>

<br />

<!-- About the Project -->
# :star2: About the Project

This project is a 3D wireframe visualizer that demonstrates rendering and manipulating 3D maps, including zooming, shifting functionalities or window resize management.


  <img src="https://github.com/floktl/WireframeVisualizer/assets/147641602/e2fc293a-a417-4f95-91b2-a0aebaa5ac61" alt="screenshot" width="205">

<img width="200" alt="Screenshot 2024-07-12 at 14 15 37" src="https://github.com/user-attachments/assets/6042a75f-7839-4f62-b763-738ee6f5e97b">

<img width="260" alt="Screenshot 2024-07-12 at 14 18 25" src="https://github.com/user-attachments/assets/9082627c-9d6f-43e3-a09d-7c99710b1d6e">

It highlights efficient coding practices and custom solutions, providing a solid foundation for exploring computer graphics and 3D visualization.

<!-- Run Locally -->
# :running: Getting Started

## Clone the project

```bash
  git clone https://github.com/floktl/WireframeVisualizer
```

## Go to the project directory and compile

```bash
  cd WireframeVisualizer && make
```

## running the executable with a map (choose map from test_map directory)

```bash
  ./fdf 42.fdf
```
<!-- Usage -->
# :star2: Usage

You can zoom the map with the scroll wheel Or shift the map with left mouse button clicked

Press <I> for the full manual

<img src="https://github.com/floktl/42-Projects/assets/147641602/e01b80c4-be14-4106-9a60-dd5dad0712da" alt="fdf_mapzoom" width="300">

<img src="https://github.com/user-attachments/assets/ec288172-bda4-465d-80db-3383b7159afc" alt="fdf_mapshift" width="325">

<!-- Code details -->
# :star2: Code details

Here are some examples that showcase why the code in this project is safe and easy to read:

## Safe and Clean Memory Management

All dynamically allocated memory is properly freed to avoid memory leaks.

```cpp
int32_t	***free_map_data(int32_t ***map, char **collumn, int row)
{
	map[row] = NULL;
	free_two_dimensional_array(collumn);
	free_map(map);
	return (NULL);
}
```

## Clear and Descriptive Function Names

Function names are descriptive, making it easy to understand what each function does.

```cpp
void	remove_manual_from_window(t_window *window);
void	set_map_to_middle(t_window *window);
void	print_manual(t_window *window);
```

## Robust Error Handling

The code includes checks to handle errors gracefully.

```cpp
//	function to assign the coordinate data from the map into 3-dimensional array
int	assign_map_values(int32_t ***map_x_axis, char **collumn, int line)
{
	char	*color;
	int		x;

	x = 0;
	while (collumn[x] != NULL)
	{
		(*map_x_axis)[x] = malloc(2 * sizeof(int));
		if (!(*map_x_axis)[x])
			return (EXIT_FAILURE); // returns an Error if there is a mallocation error
```

## Custom functions

To prove my mathematical skills, i didn't us the math.h library, so i created my own math functions

for example a sqrt() replacement-function:
```cpp
//	replace function for square root, why not, Math is fun!
//	Newton-Raphson Method
double	ft_sqrt(double a)
{
	double	x;
	double	next;

	x = a;
	while (1)
	{
		next = 0.5 * (x + a / x);
		if ((next - x) * (next - x) < EPSILON * EPSILON)
			break ;
		x = next;
	}
	return (x);
}
```

<!-- Contact -->
# :handshake: Contact

Florian Keitel - https://www.linkedin.com/in/fkeitel/ - fl.keitel@gmail.com

Project Link: [https://github.com/floktl/WireframeVisualizer)](#https://github.com/floktl/WireframeVisualizer)]

<!-- Acknowledgments -->
## :gem: Acknowledgements

 - [[mlx42 Lybrary](https://shields.io/)](https://github.com/codam-coding-college/MLX42)
