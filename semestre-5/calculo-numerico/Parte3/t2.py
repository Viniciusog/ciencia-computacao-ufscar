def f(x):
    return 0.99*x**5 +2.991*x**2-1.007*x+0.99

def f_deriv(x):
    return 0.99*5*x**4 +2.991*2*x-1.007

def phi(x):
    return x - f(x)/f_deriv(x)

max_iterations = 1000
xk=0
n=0
for k in range(max_iterations):
    xk_plus_1 = phi(xk)
    # Verifica o critério de parada
    if round(xk, 8) == round(xk_plus_1, 8):
         print ("K=",n,"Xk=",round(xk,8))
         break
    else:
         xk = xk_plus_1
         n = n + 1