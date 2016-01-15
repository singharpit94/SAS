import sys
import numpy

def GradDesc(X, y, theta, alpha, num_iters):

	for i in range(num_iters):
		h_theta = X * theta.T;
		temp = h_theta - y;
		delta = (alpha / len(y))*(temp.T*X);
		theta = theta - delta;

	return theta;

inp = sys.stdin.readline().split();
n = int(inp[0]);
m = int(inp[1]);
x=numpy.zeros(m*(n+1)).reshape((m,n+1));
y = numpy.zeros(m).reshape((m,1));

for i in range(m):
	inp = sys.stdin.readline().split();
	x[i][0] = 1.0;
	for j in range(n):
		x[i][j+1] = float(inp[j]);
	y[i][0] = float(inp[n]);
x = numpy.matrix(x);
y = numpy.matrix(y);

alpha = 0.1;
num_iters = 1500;

theta = numpy.matrix(numpy.zeros(n+1));

theta = GradDesc(x, y, theta, alpha, num_iters);
t = int(sys.stdin.readline());
t_matrix = numpy.zeros(t*(n+1)).reshape(t,n+1);
for i in range(t):
	inp = sys.stdin.readline().split();
	t_matrix[i][0] = 1;
	for j in range(n):
		t_matrix[i][j+1] = float(inp[j]);
t_matrix = numpy.matrix(t_matrix);
final = t_matrix * theta.T;
for i in range(t):
	print(final[i]);
