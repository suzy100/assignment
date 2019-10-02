import glfw
from OpenGL.GL import *
import numpy as np
stat = GL_LINE_LOOP
T = [GL_POLYGON,
	GL_POINTS,
	GL_LINES,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_TRIANGLES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_QUADS,
	GL_QUAD_STRIP]
def render():
	glClear(GL_COLOR_BUFFER_BIT)
	glLoadIdentity()
	glBegin(stat)
	glColor3ub(255, 255, 255)
	for n in range (0, 12):
		glVertex2f(np.cos(np.pi*2*(n/12)), np.sin(np.pi*2*(n/12)))
	glEnd()
def key_callback(window, key, scancode, action, mods):
	global stat
	if action==glfw.PRESS:
		if key==glfw.KEY_0:
			stat = T[0]
		elif key==glfw.KEY_1:
			stat = T[1]
		elif key==glfw.KEY_2:
			stat = T[2]
		elif key==glfw.KEY_3:
			stat = T[3]
		elif key==glfw.KEY_4:
			stat = T[4]
		elif key==glfw.KEY_5:
			stat = T[5]
		elif key==glfw.KEY_6:
			stat = T[6]
		elif key==glfw.KEY_7:
			stat = T[7]
		elif key==glfw.KEY_8:
			stat = T[8]
		elif key==glfw.KEY_9:
			stat = T[9]
		return
def main():
	# Initialize the library
	if not glfw.init():
		return
	# Create a windowed mode window and its OpenGL context
	window = glfw.create_window(480,480,"2017029752-2-1", None,None)
	if not window:
		glfw.terminate()
		return
	glfw.set_key_callback(window, key_callback)
	# Make the window's context current
	glfw.make_context_current(window)
	
	# Loop until the user closes the window
	while not glfw.window_should_close(window):
		# Poll events
		glfw.poll_events()
		# Render here, e.g. using pyOpenGL
		render()
		# Swap front and back buffers
		glfw.swap_buffers(window)
	glfw.terminate()
if __name__ == "__main__":
	main()