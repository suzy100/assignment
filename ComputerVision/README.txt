Environment: python
Steps to do
1. Read the checkerboard image (checkerboard.png)
2. Compute Harris matrix H at every pixel location
Can vary the size of supporting window
E.g., 3x3, 7x7, 11x11
Can ignore pixel values at the image boundaries
3. Find eigenvalues of H at every pixel location
Can use a library (e.g., numpy) to compute the eigenvalues
4. Visualize the lowest eigenvalue properly as shown in the lecture material
