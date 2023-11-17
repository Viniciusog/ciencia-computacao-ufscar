import math
x0 = -2.9
y0 = 3.0
x1 = 2.7
y1 = 1.8
ele = 6.24
def f1(c,a,h):
	return y0-1/c*math.cosh (c*(x0-a))-h
def f2(c,a,h):
	return y1-1/c*math.cosh (c*(x1-a))-h
def f3(c,a,h):
	return ele-1/c*(math.sinh(c*(x1-a))-math.sinh(c*(x0-a)))
def f1c(c,a,h):
	return 1/c**2*math.cosh(c*(x0-a))-1/c*math.sinh(c*(x0-a))*(x0-a)
def f1a(c,a,h):
	return math.sinh(c*(x0-a))
def f1h(c,a,h):
	return -1
def f2c(c,a,h):
	return 1/c**2*math.cosh(c*(x1-a))-1/c*math.sinh(c*(x1-a))*(x1-a)
def f2a(c,a,h):
	return math.sinh(c*(x1-a))
def f2h(c,a,h):
	return -1
def f3c(c,a,h):
	return 1/c**2*(math.sinh(c*(x1-a))-math.sinh(c*(x0-a)))-1/c*(math.cosh(c*(x1-a))*(x1-a)-math.cosh(c*(x0-a))*(x0-a)) 
def f3a(c,a,h):
	return -1/c*(-math.cosh (c*(x1-a))*c+math.cosh(c*(x0-a))*c)
def f3h(c,a,h):
	return 0
def det(aa1, aa2, aa3, bb1, bb2, bb3, cc1, cc2, cc3):
	return aa1*bb2*cc3+bb1*cc2*aa3+cc1*aa2*bb3-aa3*bb2*cc1-aa2*bb1*cc3-aa1*bb3*cc2
c = 1
a = 0
h = 0
print(c,a,h)
for k in range(10):
	A11 = f1c(c,a,h)
	A12 = f1a(c,a,h)
	A13 = f1h(c,a,h)
	A21 = f2c(c,a,h)
	A22 = f2a(c,a,h)
	A22 = f2a(c,a,h)
	A23 = f2h(c,a,h)
	A31 = f3c(c,a,h)
	A32 = f3a(c,a,h)
	A33 = f3h(c,a,h)
	B1 = A11*c+A12*a+A13*h-f1(c,a,h)
	B2 = A21*c+A22*a+A23*h-f2(c,a,h)
	B3 = A31*c+A32*a+A33*h-f3(c,a,h)
	c = det (B1, B2, B3, A12, A22, A32, A13, A23, A33)/det (A11, A21, A31, A12, A22,A32,A13,A23,A33)
	a = det (A11, A21, A31, B1, B2, B3, A13, A23, A33)/det (A11, A21, A31, A12, A22,A32,A13,A23,A33)
	h = det (A11, A21, A31, A12, A22, A32, B1, B2, B3)/det (A11, A21, A31, A12, A22, A32,A13,A23, A33) 
	print(c,a,h)