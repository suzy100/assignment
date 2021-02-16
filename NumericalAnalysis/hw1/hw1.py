# First, -1.5 and -1
# Second, 1 and 1.5
# Third, 3 and 3.5


def function(x):
    ans = 5*pow(x, 4)-22.4*pow(x, 3)+15.85272*pow(x, 2)+24.161472*x-23.4824832
    return ans


def derivative(x):
    ans = 20*pow(x, 3)-67.2*pow(x, 2)+31.70544*x+24.161472
    return ans


def bisection(lower, upper):
    flag = True
    while(flag):
        mid = (upper+lower)/2

        print(mid)

        mid_v = function(mid)
        low_v = function(lower)
        up_v = function(upper)

        print(mid_v, low_v, up_v)

        if low_v == 0:
            print("Found Exact root! %f\n" % lower)
            return lower, lower

        
        elif up_v == 0:
            print("Found Exact root! %f\n" % upper)
            return upper, upper


        elif low_v > 0 and up_v < 0:
            if mid_v > 0:
                old = lower
                lower = mid
                
            elif mid_v < 0:
                old = upper
                upper = mid
                
            else:
                print("Found Exact root! %f\n" % mid)
                return mid, mid
            

        elif low_v < 0 and up_v > 0:
            if mid_v > 0:
                old = upper
                upper = mid
                
            elif mid_v < 0:
                old = lower
                lower = mid
                
            else:
                print("Found Exact root! %f\n" % mid)
                return mid, mid

        if abs((mid - old)/mid)*100 < 0.000001:
            flag = False

    return lower, upper


def newton(ix):
    flag = True
    while(flag):
        i_value = function(ix)
        # nx is 'next_x'
        nx = ix - (i_value/derivative(ix))
        old = ix
        ix = nx
        print(ix)
        
        if (abs((nx - old)/nx)*100) < 0.000001:
            flag = False

    return ix

        
if __name__=="__main__":
    command = input()

    '''
    # when bisection
    lower, upper = map(float, command.split())
    print(lower, upper)
    
    lower, upper = bisection(lower, upper)
    print(lower, upper)
    print("The range of where the root is %f to %f\n" % (lower, upper))
    print("root : %f\n" % ((lower+upper)/2))
    '''
    
    # when newton
    initial_x = float(command)
    x = newton(initial_x)
    print(x)
    
