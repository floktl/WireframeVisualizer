import os
import struct
import sys
import fcntl
import matplotlib.pyplot as plt

# Create a list for file descriptors (0-3 for 4 pipes)
pipe_fds = [sys.stdin.fileno()] + list(range(3, 7))  # Replace with your actual pipe file descriptors

# Set pipes to non-blocking mode
for fd in pipe_fds:
	flags = fcntl.fcntl(fd, fcntl.F_GETFL)
	fcntl.fcntl(fd, fcntl.F_SETFL, flags | os.O_NONBLOCK)

# Prepare a single figure with subplots for each data set
plt.ion()
fig, axes = plt.subplots(2, 2, figsize=(10, 8))
axes = axes.flatten()

# Initialize data for each plot
data = [[] for _ in range(4)]
rotation_data = {'x': [], 'y': [], 'z': []}
pipe1_buffer = b''
pipe2_buffer = b''

# Flag to indicate when to exit
exit_program = False

# Function to update the plot for rotation
def update_rotation_plot(x_rot, y_rot, z_rot):
	ax = axes[0]  # Graph for rotations
	ax.clear()
	rotation_data['x'].append(x_rot)
	rotation_data['y'].append(y_rot)
	rotation_data['z'].append(z_rot)

	ax.plot(rotation_data['x'], label='X Rotation', color='r')
	ax.plot(rotation_data['y'], label='Y Rotation', color='g')
	ax.plot(rotation_data['z'], label='Z Rotation', color='b')

	# Set labels and legend
	ax.set_title('Rotation Data for Pipe 1')
	ax.set_xlabel('Time')
	ax.set_ylabel('Degrees')
	ax.legend()
	ax.grid(True)

# Function to update the plot for the other pipes
def update_plot(x, y):
	ax = axes[1]  # Adjust index as necessary
	ax.clear()
	data[1].append((x, y))

	# Set limits and labels
	ax.set_xlim(-512, 512)
	ax.set_ylim(-512, 512)
	ax.axhline(0, color='black', linewidth=0.5, ls='--')
	ax.axvline(0, color='black', linewidth=0.5, ls='--')
	ax.grid(color='gray', linestyle='--', linewidth=0.5)

	# Unzip data points and plot
	if data[1]:
		x_data, y_data = zip(*data[1])
		ax.plot(x_data, y_data, marker='o')
	ax.set_title(f'Pipe {1 + 1} Data Plot')

# Event handler for key press
def on_key(event):
	global exit_program
	if event.key == 'escape':
		exit_program = True  # Set the exit flag

# Connect the key press event to the handler
fig.canvas.mpl_connect('key_press_event', on_key)

# Read from the pipes
try:
	print("Plot initialized")
	while not exit_program:  # Loop until exit flag is set
		for i in range(4):
			if i == 1:  # Pipe for rotation degrees
				try:
					line = os.read(pipe_fds[i], 12 - len(pipe2_buffer))
					if line:
						pipe2_buffer += line
						if len(pipe2_buffer) == 12:
							x_rot, y_rot, z_rot = struct.unpack('iii', pipe2_buffer)
							update_rotation_plot(x_rot, y_rot, z_rot)
							pipe2_buffer = b''
				except BlockingIOError:
					continue
			elif i == 2:  # Pipe for x and y coordinates
				try:
					line = os.read(pipe_fds[i], 8 - len(pipe1_buffer))
					if line:
						pipe1_buffer += line
						if len(pipe1_buffer) == 8:
							xposmw, yposmw = struct.unpack('ii', pipe1_buffer)
							xpos_adjusted = xposmw - 512
							ypos_adjusted = 512 - yposmw
							update_plot(xpos_adjusted, ypos_adjusted)
							pipe1_buffer = b''
				except BlockingIOError:
					continue
			else:
				continue
		plt.pause(0.01)  # Pause for a brief moment to update plots
except KeyboardInterrupt:
	print("Exiting due to keyboard interrupt.")

# Clean up and close the figure
finally:
	plt.close(fig)  # Close the figure properly
	sys.exit(0)  # Exit the program
