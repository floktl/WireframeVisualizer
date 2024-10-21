import matplotlib.pyplot as plt
import numpy as np

class PlotHandlers:
	@staticmethod
	def setup_plot_common(ax):
		"""Common plot setup for coordinate-based plots"""
		ax.set_xlim(-512, 512)
		ax.set_ylim(-512, 512)
		ax.axhline(0, color='black', linewidth=0.5, ls='--')
		ax.axvline(0, color='black', linewidth=0.5, ls='--')
		ax.grid(color='gray', linestyle='--', linewidth=0.5)

	@staticmethod
	def update_rotation_plot(ax, rotation_data, time_window=2, sampling_rate=0.01):
		"""Update rotation data plot (Pipe 1) to show live plot of the last 2 seconds"""
		ax.clear()

		max_points = int(time_window / sampling_rate)

		for key, color in zip(['x', 'y', 'z'], ['r', 'g', 'b']):
			data_to_plot = rotation_data[key][-max_points:]
			ax.plot(data_to_plot, label=f'{key.upper()} Rotation', color=color)

		# Update plot titles, labels, and legend
		ax.set_title('Rotation Data (Last 2 Seconds)')
		ax.set_xlabel('Time (s)')
		ax.set_ylabel('Degrees')
		ax.legend()
		ax.grid(True)

	@staticmethod
	def update_position_plot(ax, data_points, title):
		"""Update position plots (Pipe 2 and 3)"""
		ax.clear()
		PlotHandlers.setup_plot_common(ax)

		if data_points:
			x_data, y_data = zip(*data_points)
			ax.plot(x_data, y_data, marker='o', markersize=0.5, color='red')
		ax.set_title(title)

	@staticmethod
	def update_area_plot(ax, area):
		"""Update area plot (Pipe 4)"""
		ax.clear()

		radius = np.sqrt(area / np.pi)
		PlotHandlers.setup_plot_common(ax)

		circle = plt.Circle((0, 0), radius, color='blue', fill=True)
		ax.add_artist(circle)
		ax.set_aspect('equal')
		ax.set_title(f'Map Area: {area} square units')
