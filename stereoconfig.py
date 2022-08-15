# 存放相机的参数

import numpy as np

class stereoCamera(object):
    def __init__(self):
        # 左相机内参
        self.cam_matrix_left = np.array([[684.8165, 0, 637.2704], [0, 685.4432, 320.5347],
                                         [0, 0, 1]])
        # 右相机内参
        self.cam_matrix_right = np.array([[778.2081, 0, 602.9231], [0, 781.9883, 319.6632],
                                          [0, 0, 1]])

        # 左右相机畸变系数:[k1, k2, p1, p2, k3]
        self.distortion_l = np.array([[0.1342, -0.3101, 0, 0, 0.1673]])
        self.distortion_r = np.array([[0.4604, -2.3963, 0, 0, 5.2266]])

        # 旋转矩阵
        self.R = np.array([[0.9993, -0.0038, -0.0364],
                          [0.0033, 0.9999, -0.0143],
                          [0.0365, 0.0142, 0.9992]])
        # 平移矩阵
        self.T = np.array([[-44.8076], [5.7648], [51.7586]])

        # 主点列坐标的差
        self.doffs = 0.0

        # 指示上述内外参是否为经过立体校正后的结果
        self.isRectified = False

    def setMiddleBurryParams(self):
        self.cam_matrix_left = np.array([[684.8165, 0, 637.2704], [0, 685.4432, 320.5347],
                                         [0, 0, 1]])
        self.cam_matrix_right = np.array([[778.2081, 0, 602.9231], [0, 781.9883, 319.6632],
                                          [0, 0, 1]])
        self.distortion_l = np.array([[0.1342, -0.3101, 0, 0, 0.1673]])
        self.distortion_r = np.array([[0.4604, -2.3963, 0, 0, 5.2266]])
        self.R = np.array([[0.9993, -0.0038, -0.0364],
                          [0.0033, 0.9999, -0.0143],
                          [0.0365, 0.0142, 0.9992]])
        self.T = np.array([[-44.8076], [5.7648], [51.7586]])
        self.doffs = 131.111
        self.isRectified = True

