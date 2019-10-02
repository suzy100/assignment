import glfw
from OpenGL.GL import *
import numpy as np

deg = np.radians(10)

T = np.array([[1.,0.,0.],
		 	  [0.,1.,0.],
		 	  [0.,0.,1.]])

def render(T):
	glClear(GL_COLOR_BUFFER_BIT)
	glLoadIdentity()
	
	# draw cooridnate
	glBegin(GL_LINES)
	glColor3ub(255, 0, 0)
	glVertex2fv(np.array([0.,0.]))
	glVertex2fv(np.array([1.,0.]))
	glColor3ub(0, 255, 0)
	glVertex2fv(np.array([0.,0.]))
	glVertex2fv(np.array([0.,1.]))
	glEnd()
	
	# draw triangle
	glBegin(GL_TRIANGLES)
	glColor3ub(255, 255, 255)
	glVertex2fv( (T @ np.array([.0,.5,1.]))[:-1] )
	glVertex2fv( (T @ np.array([.0,.0,1.]))[:-1] )
	glVertex2fv( (T @ np.array([.5,.0,1.]))[:-1] )
	glEnd()


def key_callback(window, key, scancode, action, mods):
	global T, deg
	if action==glfw.PRESS:
		if key==glfw.KEY_Q:
			T = T - np.array([[0., 0., .1],
							  [0., 0., 0.],
							  [0., 0., 0.]])
		elif key==glfw.KEY_E:
			T = T + np.array([[0., 0., 0.1],
							  [0., 0., 0.],
							  [0., 0., 0.]])
		elif key==glfw.KEY_A:
			T = T @ np.array([[np.cos(+deg), -np.sin(+deg),0.],
						  [np.sin(+deg), np.cos(+deg),0.],
		 				  [0., 0., 1.]])
		elif key==glfw.KEY_D:
			T = T @ np.array([[np.cos(-deg), -np.sin(-deg),0.],
						  [np.sin(-deg), np.cos(-deg),0.],
		 				  [0., 0., 1.]]) 
		elif key==glfw.KEY_1:
			T = np.array([[1.,0.,0.],
		 	  			  [0.,1.,0.],
		 	  			  [0.,0.,1.]])
		elif key==glfw.KEY_W:
			T = np.array([[.9, 0., 0.],
						  [0., 1., 0.],
						  [0., 0., 1.]]) @ T
		elif key==glfw.KEY_S:
			T = np.array([[np.cos(+deg), -np.sin(+deg),0.],
						  [np.sin(+deg), np.cos(+deg),0.],
		 				  [0., 0., 1.]]) @ T

		return


def main():
	# Initialize the library
	if not glfw.init():
		return
	# Create a windowed mode window and its OpenGL context
	window = glfw.create_window(480,480,"2017029752-3-1", None,None)
	if not window:
		glfw.terminate()
		return

	glfw.set_key_callback(window, key_callback)

	# Make the window's context current
	glfw.make_context_current(window)

	# set the number of screen refresh to wait before calling glfw.swap_buffer().
	# if your monitor refresh rate is 60Hz, the while loop is repeated every 1/60 sec
	glfw.swap_interval(1)
	
	while not glfw.window_should_close(window):
		glfw.poll_events()
		
		render(T)

		glfw.swap_buffers(window)
	glfw.terminate()

if __name__ == "__main__":
	main()