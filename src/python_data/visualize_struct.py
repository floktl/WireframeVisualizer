import matplotlib.pyplot as plt
import struct
import sys

# Prepare a plot for visualization
plt.ion()  # Turn on interactive mode
fig, ax = plt.subplots()
x_data = []
y_data = []

# Function to update the plot
def update_plot(x, y):
	ax.clear()
	x_data.append(x)
	y_data.append(y)

	# Set limits to represent quadrants
	ax.set_xlim(-512, 512)  # Adjust according to your window size
	ax.set_ylim(-512, 512)  # Adjust according to your window size

	# Add grid and center lines
	ax.axhline(0, color='black', linewidth=0.5, ls='--')
	ax.axvline(0, color='black', linewidth=0.5, ls='--')
	ax.grid(color='gray', linestyle='--', linewidth=0.5)

	ax.plot(x_data, y_data, marker='o')
	plt.draw()
	plt.pause(0.01)  # Adjust pause for visualization speed

update_plot(0, 0)

# Read from the pipe
while True:
	line = sys.stdin.buffer.read(8)
	if not line:
		print("Pipe closed, exiting the program.")
		break
	if len(line) == 8:
		try:
			xposmw, yposmw = struct.unpack('ii', line)
			update_plot(xposmw - 512, 512 - yposmw)  # Adjust coordinates to fit into quadrants
		except struct.error as e:
			print(f"Struct error: {e}")
			break

plt.ioff()  # Turn off interactive mode
plt.show()  # Show the final plot
