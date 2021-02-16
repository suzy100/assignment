# hw2
# Find the min locations using Newton method

# First, -1.5 and -1
# Second, 1 and 1.5
# Third, 3 and 3.5


def function(x):
    ans = 5*pow(x, 4)-22.4*pow(x, 3)+15.85272*pow(x, 2)+24.161472*x-23.4824832
    return ans


def derivative(x):
    ans = 20*pow(x, 3)-67.2*pow(x, 2)+31.70544*x+24.161472
    return ans


def dderivative(x):
    ans = 60*pow(x, 2)-134.4*x+31.70544
    return ans


def a_derivative(x):
    h = 0.000001
    
    first = (function(x+h)-function(x))/h
    second = (function(x+h)-2*function(x)+function(x-h))/pow(h, 2)

    return first, second
    
    
def newton(ix):
    flag = True
    while(flag):
        i_value = derivative(ix)
        # nx is 'next_x'
        nx = ix - (i_value/dderivative(ix))
        old = ix
        ix = nx
        print(ix)
        
        if (abs((nx - old)/nx)*100) < 0.000001:
            flag = False

    return ix


def newton2(ix):
    flag = True
    while(flag):
        first, second = a_derivative(ix)
        # nx is 'next_x'
        nx = ix - (first/second)
        old = ix
        ix = nx
        print(ix)
        
        if (abs((nx - old)/nx)*100) < 0.000001:
            flag = False

    return ix
    

if __name__=="__main__":
    command = input()

    initial_x = float(command)
    x = newton2(initial_x)
    print(x)
    print("x's value : %f" % function(x))
    
