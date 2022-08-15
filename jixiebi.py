from math import pi, sin, cos, sqrt, asin, acos,atan

# 机械杆的长度
l0=11.5
l1=9.5
l2=6.9

# 从-100度开始到151度的范围内寻找合适的末端执行器的角度
def fuzhu(x,y,z):
    for i in range(-100,151):
        if findjiao_brandnew(x,y,z,i)==0:
            print('没解啦啊')
            if i==150:
                return 0
        else:
            print('alpha:',i)
            a,b,c,d=findjiao_brandnew(x,y,z,i)
            return a,b,c,d

# 用于逆运动学求解角度，因为改了很多版，这个是最新版，所以是brandnew
def findjiao_brandnew(x, y, z, alpha):
    # 初始化和矫正
    alpha=(alpha/180) * pi   # 转化为弧度制
    # 求云台角度
    if x==0:
        jd=0
    else:
        tanjd = z / x
        jd = atan(tanjd)
    if x>0:
        jd=jd
    if x<0:
        jd=jd+pi
    x = x / cos(jd)   # 把输入的x值转化为z=0时的值

    # 求角度一
    m = l2 * cos(alpha) - x
    n = l2 * sin(alpha) - y
    # (-b - sqrt(b**2 - 4 * a * c)) / (2*a)

    k = (l1 ** 2 - l0 ** 2 - m ** 2 - n ** 2) / (2 * l0)
    a = m**2 + n**2
    b = -2*n*k
    c = k**2 - m**2
    # 判断判别式是否大于0
    san=b ** 2 - 4 * a * c
    if san>=0:
        sinc1=(-b+sqrt(san))/(2*a)
    else:
        print("出错了，平方根要大于等于0")
        return 0
    if abs(sinc1)<=1:
        j1=asin(sinc1)
    else:
        print('sinc1大于1了，尝试其他值')
        return 0

    # 求角度二
    sumofj1j2 = (-m-l0*cos(j1))/l1
    if abs(sumofj1j2)<=1:
        j=acos(sumofj1j2)
    elif abs((-m-l0*cos(pi-j1))/l1)<=1:
        sumofj1j2=(-m - l0 * cos(pi - j1)) / l1
        j=acos(sumofj1j2)
    else:
        print('矫正失败，角1角2的和的cos值绝对值仍然大于1')
        return 0

    # 判断符合要求否
    if judge_of_j1(j1, j, alpha, x, y)==0:
        print('误差过大')
        return 0
    else:
        j1,j=judge_of_j1(j1, j, alpha, x, y)
        j2 = j - j1
        j3 = alpha - j
        xtest = l0 * cos(j1) + l1 * cos(j) + l2 * cos(alpha)
        ytest = l0 * sin(j1) + l1 * sin(j) + l2 * sin(alpha)
        print('x值:', xtest, 'y值:', ytest,'j2:',(j2 / pi) * 180,'j1',(j1 / pi) * 180)

        # 弧度制转化为角度制
        j1 = (j1 / pi) * 180
        j2 = (j2 / pi) * 180
        j3 = (j3 / pi) * 180
        jd = (jd / pi) * 180

        # 不能让角度值变化太大，不然的话舵机需要转很大的角度达到目标坐标（这也是目前较大的一个bug）
        if j1<70 or j2<-140 or j3<-120:
            return 0
        return j1, j2, j3, jd

def rjtojx(j1,j2,j3,jd):
    # 用于把真实的角度转化为舵机需要转到的角度（舵机为0度时关节可能是其他角度）
    j1=135+90-j1
    j2=135-j2
    j3=135-j3
    jd=jd+135

    # 转动的角度不能大于255，因为我写的单片机程序一次只能传两位16进制....两位16进制最大值是255。
    if j1>255:
        j1=255
    if j2>255:
        j2=255
    if j3>255:
        j3=255
    if jd>255:
        jd=255
    if j2<0:
        j2=0
    if j1<0:
        j1=0
    if j3<0:
        j3=0
    if jd<0:
        jd=0

    return j1,j2,j3,jd

# 角度不太对的时候用这个函数矫正
def judge_of_j1(j1,j,alpha,x,y):
    m = l2 * cos(alpha) - x
    # 算j1是哪边的
    xtest = l0 * cos(j1) + l1 * cos(j) + l2 * cos(alpha)
    ytest = l0 * sin(j1) + l1 * sin(j) + l2 * sin(alpha)
    if (abs(ytest-y)<=0.7) and (abs(xtest-x)<0.7):
        return j1,j
    else:
        j=pi-j
        ytest = l0 * sin(j1) + l1 * sin(j) + l2 * sin(alpha)
        xtest = l0 * cos(j1) + l1 * cos(j) + l2 * cos(alpha)
        if (abs(ytest-y)<=0.7) and (abs(xtest-x)<0.7):
            return j1,j
        else:
            j1=pi-j1
            sumofj1j2 = (-m - l0 * cos(j1)) / l1
            if abs(sumofj1j2)<1:
                j = acos(sumofj1j2)
                ytest = l0 * sin(j1) + l1 * sin(j) + l2 * sin(alpha)
                xtest = l0 * cos(j1) + l1 * cos(j) + l2 * cos(alpha)
            else:
                print('你重开吧')
                return 0
            if (abs(ytest-y)<=0.7) and (abs(xtest-x)<0.7):
                return j1,j
            else:
                j = pi - j
                ytest = l0 * sin(j1) + l1 * sin(j) + l2 * sin(alpha)
                xtest = l0 * cos(j1) + l1 * cos(j) + l2 * cos(alpha)
                if (abs(ytest-y)<=0.7) and (abs(xtest-x)<0.7):
                    return j1, j
                else:
                    print('你重开吧')
                    return 0

