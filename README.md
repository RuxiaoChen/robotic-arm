# robotic-arm
With this program, you can control the robotic arm with your hands with the help of binocular vision and YOLOV5.....
先把yolov5的官方代码跑的没问题了，再把这几个文件复制到官方代码里面，替换掉。
主函数是detect.py，求三维坐标的代码在plot函数里面，achuankou.py是负责串口通信的代码，jixiebi.py负责根据三维坐标求机械臂各个轴转动角度
