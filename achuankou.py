"""
这是一个测试程序，只向单片机发送一次数据
"""
import serial
import time
from jixiebi import rjtojx,fuzhu


a,b,c,d=fuzhu(6,14,0)
print('\ntheta1的真值：',a, '\ntheta2的真值：',b,'\ntheta3的真值：', c,'\n舵机角的真值：', d)
a,b,c,d=rjtojx(a,b,c,d)
print('\ntheta1的值：',a, '\ntheta2的值：',b,'\ntheta3的值：', c,'\n舵机角的值：', d)
angle=[a,b,c,d]

# 连接串口
serial = serial.Serial('COM6', 115200)
if serial.isOpen():
    print('串口已打开')
    for i in angle:
            i=int(i)
            if i>255:
                i=255
            data = hex(i)
            data = str(data)  # 发送的数据
            if i<16:
                data='0'+data[-1]
            else:
                data = data[2:]
            data = bytes.fromhex(data)
            serial.write(data)  # 串口写数据
            # rec_data = serial.read(20)  # 串口读20位数据
            # print(rec_data)
            time.sleep(0.01)
    print('成功接收')
else:
    print('串口未打开')

# 关闭串口
serial.close()
if serial.isOpen():
    print('串口未关闭')
else:
    print('串口已关闭')
