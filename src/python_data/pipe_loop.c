/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 06:41:53 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/21 06:44:26 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	function to assign the visualize data to the data struct
void	assign_values_to_data_struct(t_win_data *data, int i)
{
	char	buf[12];

	if (i == 0)
	{
		ft_memcpy(buf, &data->map_sz.xm_rot_deg, sizeof(int));
		ft_memcpy(buf + sizeof(int), &data->map_sz.ym_rot_deg, sizeof(int));
		ft_memcpy(buf + 2 * sizeof(int), &data->map_sz.zm_rot_deg, sizeof(int));
	}
	else if (i == 1)
	{
		ft_memcpy(buf, &data->map_sz.xposmw, sizeof(int));
		ft_memcpy(buf + sizeof(int), &data->map_sz.yposmw, sizeof(int));
	}
	else if (i == 2)
	{
		ft_memcpy(buf, &data->mouse_posx, sizeof(int));
		ft_memcpy(buf + sizeof(int), &data->mouse_posy, sizeof(int));
	}
	else if (i == 3)
		ft_memcpy(buf, &data->map_sz.map_area, sizeof(int));
	pthread_mutex_lock(&data->thread_data[i].data_mutex);
	ft_memcpy(data->thread_data[i].data_buf, buf,
		data->thread_data[i].write_size);
	pthread_mutex_unlock(&data->thread_data[i].data_mutex);
}

//	function to store the data values inside buffer and write it to pipe
int	write_data_in_buf(t_pipe_thread_data *data, ssize_t *bytes_written)
{
	if (data->pipe_index < 0 || data->pipe_index > 3)
		return (-1);
	pthread_mutex_lock(&data->data_mutex);
	*bytes_written = write(data->pipe_fd[1], data->data_buf, data->write_size);
	if (*bytes_written != data->write_size || *bytes_written == -1)
		return (pthread_mutex_unlock(&data->data_mutex), -1);
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}

//	function to write data values in the struct using a buffer
int	write_into_pipes(t_pipe_thread_data *data)
{
	ssize_t	bytes_written;

	if (data->pipe_fd[1] <= 0)
		return (fprintf(stderr, "Invalid pipe %d\n", data->pipe_fd[1]), -1);
	bytes_written = 0;
	if (write_data_in_buf(data, &bytes_written) == -1)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
		{
			close(data->pipe_fd[1]);
			data->pipe_fd[1] = -1;
			return (-1);
		}
		else if (bytes_written == -1)
			fprintf(stderr, "Write error on pipe %d: %s\n",
				data->pipe_index, strerror(errno));
		else
			fprintf(stderr, "Partial write on pipe %d: %zd/%zd bytes\n",
				data->pipe_index, bytes_written, data->write_size);
	}
	return (0);
}

//	thread loop to write the right data into each thread (runs simultanly)
void	*pipe_writer(void *arg)
{
	t_pipe_thread_data		*data;
	static struct timeval	last_write_time = {0};
	struct timeval			current_time;
	long					elapsed_time;

	data = (t_pipe_thread_data *)arg;
	if (data->pipe_index < 0 || data->pipe_index >= 4)
		return (fprintf(stderr, "Invalid pipe %d\n", data->pipe_index), NULL);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - last_write_time.tv_sec) * 1000000
			+ (current_time.tv_usec - last_write_time.tv_usec);
		if (elapsed_time >= WRITE_INTERVAL)
		{
			if (write_into_pipes(data) == -1)
				return (NULL);
			last_write_time = current_time;
		}
		else
			usleep(10000);
	}
	return (NULL);
}
