import os
import struct
import sys
import fcntl
import threading
import matplotlib.pyplot as plt
from collections import deque
from time import sleep

class PipeVisualizer:
	def __init__(self, max_points=1000):
		# Initialize pipe file descriptors
		self.pipe_fds = [sys.stdin.fileno()] + list(range(3, 7))
		self.exit_program = False
		self.lock = threading.Lock()
		self.max_points = max_points

		# Use deque with maxlen for efficient data storage
		self.rotation_data = {
			'x': deque(maxlen=max_points),
			'y': deque(maxlen=max_points),
			'z': deque(maxlen=max_points)
		}
		self.shift_data = deque(maxlen=max_points)

		# Buffers for incomplete data
		self.pipe1_buffer = b''
		self.pipe2_buffer = b''

		self._setup_pipes()
		self._setup_plots()

	def _setup_pipes(self):
		"""Set up non-blocking pipes"""
		for fd in self.pipe_fds:
			try:
				flags = fcntl.fcntl(fd, fcntl.F_GETFL)
				fcntl.fcntl(fd, fcntl.F_SETFL, flags | os.O_NONBLOCK)
			except Exception as e:
				print(f"Error setting up pipe {fd}: {e}")
				sys.exit(1)

	def _setup_plots(self):
		"""Initialize matplotlib plots"""
		plt.ion()
		self.fig, self.axes = plt.subplots(2, 2, figsize=(12, 10))
		self.axes = self.axes.flatten()

		# Set up rotation plot
		self.axes[0].set_title('Rotation Data')
		self.axes[0].set_xlabel('Time')
		self.axes[0].set_ylabel('Degrees')
		self.axes[0].grid(True)

		# Set up shift plot
		self.axes[1].set_title('Position Map')
		self.axes[1].set_xlim(-512, 512)
		self.axes[1].set_ylim(-512, 512)
		self.axes[1].grid(True)

		# Add key event handler
		self.fig.canvas.mpl_connect('key_press_event', self._on_key)

	def _on_key(self, event):
		"""Handle key press events"""
		if event.key == 'escape':
			self.exit_program = True

	def update_rotation_plot(self, x_rot, y_rot, z_rot):
		"""Update rotation data plot"""
		with self.lock:
			self.rotation_data['x'].append(x_rot)
			self.rotation_data['y'].append(y_rot)
			self.rotation_data['z'].append(z_rot)

			self.axes[0].clear()
			self.axes[0].plot(list(self.rotation_data['x']), label='X', color='r')
			self.axes[0].plot(list(self.rotation_data['y']), label='Y', color='g')
			self.axes[0].plot(list(self.rotation_data['z']), label='Z', color='b')
			self.axes[0].legend()
			self.axes[0].grid(True)
			self.axes[0].set_title('Rotation Data')

	def update_shift_plot(self, x, y):
		"""Update position map plot"""
		with self.lock:
			self.shift_data.append((x, y))

			self.axes[1].clear()
			if self.shift_data:
				x_data, y_data = zip(*self.shift_data)
				self.axes[1].plot(x_data, y_data, 'b-', marker='o', markersize=2)

			self.axes[1].set_xlim(-512, 512)
			self.axes[1].set_ylim(-512, 512)
			self.axes[1].axhline(0, color='black', linewidth=0.5, ls='--')
			self.axes[1].axvline(0, color='black', linewidth=0.5, ls='--')
			self.axes[1].grid(True)
			self.axes[1].set_title('Position Map')

	def read_pipe1(self):
		"""Read rotation data from pipe 1"""
		while not self.exit_program:
			try:
				chunk = os.read(self.pipe_fds[1], 12 - len(self.pipe1_buffer))
				if chunk:
					self.pipe1_buffer += chunk
					if len(self.pipe1_buffer) == 12:
						x_rot, y_rot, z_rot = struct.unpack('iii', self.pipe1_buffer)
						self.update_rotation_plot(x_rot, y_rot, z_rot)
						self.pipe1_buffer = b''
			except BlockingIOError:
				sleep(0.001)  # Prevent CPU hogging
			except Exception as e:
				print(f"Error reading pipe 1: {e}")
				break

	def read_pipe2(self):
		"""Read position data from pipe 2"""
		while not self.exit_program:
			try:
				chunk = os.read(self.pipe_fds[2], 8 - len(self.pipe2_buffer))
				if chunk:
					self.pipe2_buffer += chunk
					if len(self.pipe2_buffer) == 8:
						xposmw, yposmw = struct.unpack('ii', self.pipe2_buffer)
						print(xposmw)
						xpos_adjusted = xposmw - 512
						ypos_adjusted = 512 - yposmw
						self.update_shift_plot(xpos_adjusted, ypos_adjusted)
						self.pipe2_buffer = b''
			except BlockingIOError:
				sleep(0.001)  # Prevent CPU hogging
			except Exception as e:
				print(f"Error reading pipe 2: {e}")
				break

	def run(self):
		"""Main execution method"""
		try:
			# Start reader threads
			threads = [
				threading.Thread(target=self.read_pipe1),
				threading.Thread(target=self.read_pipe2)
			]
			for thread in threads:
				thread.daemon = True
				thread.start()

			# Main loop for plot updates
			while not self.exit_program:
				plt.pause(0.01)  # Allow plot updates and reduce CPU usage

		except KeyboardInterrupt:
			print("\nExiting due to keyboard interrupt...")
		finally:
			self.exit_program = True
			plt.close(self.fig)
			for thread in threads:
				thread.join(timeout=1.0)

if __name__ == "__main__":
	visualizer = PipeVisualizer()
	visualizer.run()
