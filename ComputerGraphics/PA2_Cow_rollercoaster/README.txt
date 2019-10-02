Programming Assignment #2 (Cow roller coaster)
2017029752 ¹é½Â¼ö

What to do:
1) pick the cow
2) click the six control points
3) cow ride roller coaster for along the path that you clicked.
4) after third round, cow will stop on the first control point.
5) you can pick cow again

+) you can change viewpoint by type 'space' or just type the number of camera.
+) if you click during the cow rides a roller coaster, it will stop and you can pick cow again.
 
How:
1) Dragging
In Vertical Drag mode (V_DRAG mode), it should move only for vertical.
so save current x(cur_x) when user down-click the mouse.
and in v-dragging part code(in function 'onMouseDrag(window, x, y)'), put the value when make a 'ray' value.
	IN CODE :
		ray=screenCoordToRay(window, cur_x, y)

After V-drag, save the 'currentPos' to save cow's height.
then, if user do H-drag(Horizontal drag) after that, use them.
It's same when do V-drag after H-drag.
'flag_v' and 'flag_h' means is there any value that saved before.

2) Save cows' position until 6
In function 'onMouseButton', when mouse-up,
	if len(cows) < 6:
		cows.append(cow2wld)
		print("inputState:%d\n" % len(cows))
		# start animate when the number of cows becomes 6.
		if len(cows)==6:
			stop=1
			animStartTime = glfw.get_time()
			flag_v=0
			flag_h=0

3) flag 'stop'
flag 'stop' means the user's mouse clicking is expected to 'stop', literally.
When the number of cow's control point becomes 6, 'stop' flag becomes 1.
Then, the animating will start.
In function 'display()',
	if not stop:
		# draw cow for cursor
		drawCow(cow2wld, cursorOnCowBoundingBox)
		
		# duplicate cows when user click the control points
		for i in range(len(cows)):
			drawCow(cows[i], False)

	# if stop becomes 1, animate start.
	if stop:
		animate start.
		The path is drawn for every interval between points by Catmull-rom spline. (in function 'spline(t, p0, p1, p2, p3)'

		when animTime become more than 1, move to next interval.
		and if cow rode third round, initialize all, and make user pick again.

flag 'stop' also handles the mouse click during the cow's riding.
In function 'onMouseButton',
	if stop:
		return to the initial state.
		user can pick again.


Output:
Left mouse down-click : "Left mouse down-click at x y" (x, y is location where you click down.)
Left mouse up : "Left mouse up"
the number of input control points : "inputState:n" (n is the number)
Horizontal Drag mode : "in drag mode 1"
Vertical Drag mode : "in drag mode 2"