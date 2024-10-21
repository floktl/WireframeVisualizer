import os
import struct
import sys
import fcntl
import matplotlib.pyplot as plt
import threading
import queue
from threading import Lock
import time
from plot_handlers import PlotHandlers

class DataPlotter:
	def __init__(self):
		# Initialize pipes
		self.pipe_fds = [sys.stdin.fileno()] + list(range(3, 7))
		self._setup_pipes()

		# Initialize plot
		plt.ion()
		self.fig, axes = plt.subplots(2, 2, figsize=(10, 8))
		self.axes = axes.flatten()

		# Data storage
		self.data = [[] for _ in range(4)]
		self.rotation_data = {'x': [], 'y': [], 'z': []}
		self.buffer_sizes = {1: 12, 2: 8, 3: 8, 4: 4}

		# Thread safety
		self.plot_locks = [Lock() for _ in range(4)]
		self.data_queues = [queue.Queue() for _ in range(4)]
		self.exit_program = False

		# Connect event handler
		self.fig.canvas.mpl_connect('key_press_event', self._on_key)

		# Create threads
		self.threads = []
		for i in range(1, 5):
			thread = threading.Thread(target=self._pipe_thread, args=(i,))
			thread.daemon = True
			self.threads.append(thread)

	def _setup_pipes(self):
		"""Set up non-blocking pipes"""
		for fd in self.pipe_fds:
			if not fd:
				return
			flags = fcntl.fcntl(fd, fcntl.F_GETFL)
			fcntl.fcntl(fd, fcntl.F_SETFL, flags | os.O_NONBLOCK)

	def update_rotation_plot(self, x_rot, y_rot, z_rot):
		if not (0 <= x_rot <= 360 and 0 <= y_rot <= 360 and 0 <= z_rot <= 360):
			return
		"""Update rotation data plot (Pipe 1)"""
		with self.plot_locks[0]:
			self.rotation_data['x'].append(x_rot)
			self.rotation_data['y'].append(y_rot)
			self.rotation_data['z'].append(z_rot)
			PlotHandlers.update_rotation_plot(self.axes[0], self.rotation_data)

	def update_position_plot(self, x, y, index, title):
		"""Update position plots (Pipe 2 and 3)"""
		with self.plot_locks[index]:
			self.data[index].append((x, y))
			PlotHandlers.update_position_plot(self.axes[index], self.data[index], title)

	def update_area_plot(self, area, index):
		"""Update area plot (Pipe 4)"""
		with self.plot_locks[index]:
			PlotHandlers.update_area_plot(self.axes[index], area)

	def _pipe_thread(self, pipe_num):
		"""Thread function for reading from a pipe"""
		buffer = b''
		buffer_size = self.buffer_sizes[pipe_num]

		while not self.exit_program:
			try:
				# Read from pipe
				line = os.read(self.pipe_fds[pipe_num], buffer_size - len(buffer))
				if line:
					buffer += line
					if len(buffer) == buffer_size:
						# Process complete buffer
						self.data_queues[pipe_num - 1].put(buffer)
						buffer = b''
			except BlockingIOError:
				time.sleep(0.001)  # Small sleep to prevent CPU hogging
			except Exception as e:
				print(f"Error in pipe {pipe_num}: {e}")

	def _process_queue_data(self):
		"""Process data from all queues"""
		for pipe_num in range(1, 5):
			queue_idx = pipe_num - 1
			while not self.data_queues[queue_idx].empty():
				buffer_data = self.data_queues[queue_idx].get()

				if pipe_num == 1:  # Rotation data
					x_rot, y_rot, z_rot = struct.unpack('iii', buffer_data)
					self.update_rotation_plot(x_rot, y_rot, z_rot)

				elif pipe_num in [2, 3]:  # Position data
					x_pos, y_pos = struct.unpack('ii', buffer_data)
					x_adjusted = x_pos - 512
					y_adjusted = 512 - y_pos
					title = 'Map Middle Position' if pipe_num == 2 else 'Mouse Position'
					self.update_position_plot(x_adjusted, y_adjusted, pipe_num - 1, title)

				elif pipe_num == 4:  # Area data
					area_value = struct.unpack('i', buffer_data)[0]
					self.update_area_plot(area_value, pipe_num - 1)

	def _on_key(self, event):
		"""Handle key press events"""
		if event.key == 'escape':
			self.exit_program = True
			plt.close(self.fig)
			print("Escape key pressed. Exiting program.")

	def run(self):
		"""Main loop"""
		try:
			print("\nPython: Plot initialized")

			# Start all threads
			for thread in self.threads:
				thread.start()

			# Main loop for updating plots
			while not self.exit_program:
				self._process_queue_data()
				plt.pause(0.1)

		except KeyboardInterrupt:
			print("Exiting due to keyboard interrupt.")
			self.exit_program = True

		finally:
			self.exit_program = True
			# Wait for all threads to finish
			for thread in self.threads:
				thread.join(timeout=1.0)
			plt.close(self.fig)
			sys.exit(0)

if __name__ == "__main__":
	plotter = DataPlotter()
	plotter.run()
