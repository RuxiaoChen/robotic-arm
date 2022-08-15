"""
调用的包和yolov5的官方代码一样，但是多加了jixiebi和serial这两个包。建议先上网找yolov5教程，运行一下没问题再试试这个。
如果你没用过yolov5建议先看这个教程的1-5集
（https://www.bilibili.com/video/BV1tf4y1t7ru?spm_id_from=333.337.search-card.all.click）

我主要是在主函数detec里面加了串口通信的内容，再plot函数里面加了求坐标的内容。
"""
import argparse
import time
from pathlib import Path

from jixiebi import rjtojx,fuzhu       # jixiebi是我自己写的程序，要把jixiebi.py放进此文件的路径
import serial    # 串口通信的包
import numpy as np
import cv2
import torch
import torch.backends.cudnn as cudnn
from numpy import random
import stereoconfig

from models.experimental import attempt_load
from utils.datasets import LoadStreams, LoadImages
from utils.general import check_img_size, check_requirements, check_imshow, non_max_suppression, apply_classifier, \
    scale_coords, xyxy2xywh, strip_optimizer, set_logging, increment_path
from utils.plots import plot_one_box
from utils.torch_utils import select_device, load_classifier, time_synchronized

def getDepthMapWithConfig(config : stereoconfig.stereoCamera,disparity) -> np.ndarray:
    fb = config.cam_matrix_left[0, 0] * (-config.T[0])
    doffs = config.doffs
    depth = fb/(disparity + doffs)
    return depth

def detect(save_img=False):
    source, weights, view_img, save_txt, imgsz = opt.source, opt.weights, opt.view_img, opt.save_txt, opt.img_size
    save_img = not opt.nosave and not source.endswith('.txt')  # save inference images
    webcam = source.isnumeric() or source.endswith('.txt') or source.lower().startswith(
        ('rtsp://', 'rtmp://', 'http://', 'https://'))

    # Directories
    save_dir = Path(increment_path(Path(opt.project) / opt.name, exist_ok=opt.exist_ok))  # increment run
    (save_dir / 'labels' if save_txt else save_dir).mkdir(parents=True, exist_ok=True)  # make dir

    # Initialize
    set_logging()
    device = select_device(opt.device)
    half = device.type != 'cpu'  # half precision only supported on CUDA

    # Load model
    model = attempt_load(weights, map_location=device)  # load FP32 model
    stride = int(model.stride.max())  # model stride
    imgsz = check_img_size(imgsz, s=stride)  # check img_size
    if half:
        model.half()  # to FP16

    # Second-stage classifier
    classify = False
    if classify:
        modelc = load_classifier(name='resnet101', n=2)  # initialize
        modelc.load_state_dict(torch.load('weights/resnet101.pt', map_location=device)['model']).to(device).eval()

    # Set Dataloader
    vid_path, vid_writer = None, None
    if webcam:
        view_img = check_imshow()
        cudnn.benchmark = True  # set True to speed up constant image size inference
        dataset = LoadStreams(source, img_size=imgsz, stride=stride)
    else:
        dataset = LoadImages(source, img_size=imgsz, stride=stride)

    # Get names and colors
    names = model.module.names if hasattr(model, 'module') else model.names
    colors = [[random.randint(0, 255) for _ in range(3)] for _ in names]

    # Run inference
    if device.type != 'cpu':
        model(torch.zeros(1, 3, imgsz, imgsz).to(device).type_as(next(model.parameters())))  # run once
    t0 = time.time()
    flag_ck = 1
    for path, img, im0s, vid_cap in dataset:
        img = torch.from_numpy(img).to(device)
        img = img.half() if half else img.float()  # uint8 to fp16/32
        img /= 255.0  # 0 - 255 to 0.0 - 1.0
        if img.ndimension() == 3:
            img = img.unsqueeze(0)

        # Inference
        t1 = time_synchronized()
        pred = model(img, augment=opt.augment)[0]

        # Apply NMS
        pred = non_max_suppression(pred, opt.conf_thres, opt.iou_thres, classes=opt.classes, agnostic=opt.agnostic_nms)
        t2 = time_synchronized()

        # Apply Classifier
        if classify:
            pred = apply_classifier(pred, modelc, img, im0s)

        # Process detections
        for i, det in enumerate(pred):  # detections per image
            if webcam:  # batch_size >= 1
                p, s, im0, frame = path[i], '%g: ' % i, im0s[i].copy(), dataset.count
            else:
                p, s, im0, frame = path, '', im0s, getattr(dataset, 'frame', 0)

            p = Path(p)  # to Path
            save_path = str(save_dir / p.name)  # img.jpg
            txt_path = str(save_dir / 'labels' / p.stem) + ('' if dataset.mode == 'image' else f'_{frame}')  # img.txt
            s += '%gx%g ' % img.shape[2:]  # print string
            gn = torch.tensor(im0.shape)[[1, 0, 1, 0]]  # normalization gain whwh
            if len(det):
                # Rescale boxes from img_size to im0 size
                det[:, :4] = scale_coords(img.shape[2:], det[:, :4], im0.shape).round()

                # Print results
                for c in det[:, -1].unique():
                    n = (det[:, -1] == c).sum()  # detections per class
                    s += f"{n} {names[int(c)]}{'s' * (n > 1)}, "  # add to string

                # Write results
                X = [0, 1,0,0]
                Y = [0, 1,0,0]
                a=0
                for *xyxy, conf, cls in reversed(det):
                    if save_txt:  # Write to file
                        xywh = (xyxy2xywh(torch.tensor(xyxy).view(1, 4)) / gn).view(-1).tolist()  # normalized xywh
                        line = (cls, *xywh, conf) if opt.save_conf else (cls, *xywh)  # label format
                        with open(txt_path + '.txt', 'a') as f:
                            f.write(('%g ' * len(line)).rstrip() % line + '\n')

                    if save_img or view_img:  # Add bbox to image
                        label = f'{names[int(cls)]} {conf:.2f}'
                        plot_one_box(xyxy, im0, label=label, color=colors[int(cls)], line_thickness=3)
                        X[a]=(int(xyxy[0])+int(xyxy[2]))/2
                        Y[a]=(int(xyxy[1])+int(xyxy[3]))/2
                        a=a+1
                if X[0]<X[1]:
                    real_x=int(X[0])
                    real_y=int(Y[0])
                else:
                    real_x=int(X[1])
                    real_y=int(Y[1])

                disparity=X[1]-X[0]
                # z = getDepthMapWithConfig(config,disparity)
                z=abs(disparity)

                text = str(real_x) + ',' + str(real_y)+','+str(z)
                cv2.putText(im0, text, (real_x, real_y), 0, 1, [225, 255, 255], thickness=3,
                            lineType=cv2.LINE_AA)
                flag_ck = flag_ck + 1

            if flag_ck == 2:
                x_first, y_first, z_first = real_x, real_y, z
            if flag_ck % 2 == 0:
                # cm_eachpe = 0.0193 * (z ** 2) - 3.135 * z + 236.2
                xc, yc, zc = (xcc + 6 * (real_x - x_first) / 200), (ycc - 4 * (real_y - y_first) / 200), (
                        zcc + (z - z_first) * 0.682 * 0.1)
                # 根据传送的值算出舵机的角度
                if fuzhu(xc, yc, zc) == 0:
                    j1, j2, j3, jd = j11, j21, j31, jd1  # 当不存在的时候就保持原样吧~
                else:
                    j1, j2, j3, jd = fuzhu(xc, yc, zc)
                    print('\ntheta1的真值：', j1, '\ntheta2的真值：', j2, '\ntheta3的真值：', j3, '\n舵机角的真值：', jd)
                    j1, j2, j3, jd = rjtojx(j1, j2, j3, jd)
                print(xc, yc, zc)
                print('\ntheta1的值：', j1, '\ntheta2的值：', j2, '\ntheta3的值：', j3, '\n舵机角的值：', jd)
                j11, j21, j31, jd1 = j1, j2, j3, jd

                # 将数据传入机械臂
                angle_data = [j1, j2, j3, jd]
                for i in angle_data:
                    i = int(i)
                    if i > 255:
                        i = 255
                    data = hex(i)
                    data = str(data)  # 发送的数据
                    if i < 16:
                        data = '0' + data[-1]
                    else:
                        data = data[2] + data[3]
                    data = bytes.fromhex(data)
                    serial.write(data)  # 串口写数据
                    time.sleep(0.01)
                    print('成功传入')
                    # rec_data = serial.read(80)  # 串口读20位数据
                    # print(rec_data)
                else:
                    pass

            # Print time (inference + NMS)
            print(f'{s}Done. ({t2 - t1:.3f}s)')

            # Stream results
            if view_img:
                cv2.imshow(str(p), im0)
                cv2.waitKey(1)  # 1 millisecond

            # Save results (image with detections)
            if save_img:
                if dataset.mode == 'image':
                    cv2.imwrite(save_path, im0)
                else:  # 'video' or 'stream'
                    if vid_path != save_path:  # new video
                        vid_path = save_path
                        if isinstance(vid_writer, cv2.VideoWriter):
                            vid_writer.release()  # release previous video writer
                        if vid_cap:  # video
                            fps = vid_cap.get(cv2.CAP_PROP_FPS)
                            w = int(vid_cap.get(cv2.CAP_PROP_FRAME_WIDTH))
                            h = int(vid_cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
                        else:  # stream
                            fps, w, h = 30, im0.shape[1], im0.shape[0]
                            save_path += '.mp4'
                        vid_writer = cv2.VideoWriter(save_path, cv2.VideoWriter_fourcc(*'mp4v'), fps, (w, h))
                    vid_writer.write(im0)

    if save_txt or save_img:
        s = f"\n{len(list(save_dir.glob('labels/*.txt')))} labels saved to {save_dir / 'labels'}" if save_txt else ''
        print(f"Results saved to {save_dir}{s}")

    print(f'Done. ({time.time() - t0:.3f}s)')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--weights', nargs='+', type=str, default='yolov5s.pt', help='model.pt path(s)')
    parser.add_argument('--source', type=str, default='0', help='source')  # file/folder, 0 for webcam
    parser.add_argument('--img-size', type=int, default=1280, help='inference size (pixels)')
    parser.add_argument('--conf-thres', type=float, default=0.25, help='object confidence threshold')
    parser.add_argument('--iou-thres', type=float, default=0.45, help='IOU threshold for NMS')   # 交并比大于default就认为是一个框
    parser.add_argument('--device', default='', help='cuda device, i.e. 0 or 0,1,2,3 or cpu')
    parser.add_argument('--view-img', action='store_true', help='display results')
    parser.add_argument('--save-txt', action='store_true', help='save results to *.txt')
    parser.add_argument('--save-conf', action='store_true', help='save confidences in --save-txt labels')
    parser.add_argument('--nosave', action='store_true', help='do not save images/videos')
    parser.add_argument('--classes', nargs='+', type=int, help='filter by class: --class 0, or --class 0 2 3')
    parser.add_argument('--agnostic-nms', action='store_true', help='class-agnostic NMS')
    parser.add_argument('--augment', action='store_true', help='augmented inference')
    parser.add_argument('--update', action='store_true', help='update all models')
    parser.add_argument('--project', default='runs/detect', help='save results to project/name')
    parser.add_argument('--name', default='exp', help='save results to project/name')
    parser.add_argument('--exist-ok', action='store_true', help='existing project/name ok, do not increment')
    opt = parser.parse_args()
    config = stereoconfig.stereoCamera()
    config.setMiddleBurryParams()
    print(opt)
    check_requirements(exclude=('pycocotools', 'thop'))

    with torch.no_grad():
        if opt.update:  # update all models (to fix SourceChangeWarning)
            for opt.weights in ['yolov5s.pt', 'yolov5m.pt', 'yolov5l.pt', 'yolov5x.pt']:
                detect()
                strip_optimizer(opt.weights)
        else:
            # 连接串口并初始化
            flag_ck = 1    # 标志位
            xcc, ycc, zcc = 11, 16, 0     # 给机械臂设置一个初值，让它一开机就转到这个坐标
            serial = serial.Serial('COM6', 115200)    # 串口号和波特率
            a, b, c, d = fuzhu(xcc, ycc, zcc)
            j11, j21, j31, jd1 = rjtojx(a, b, c, d)
            angle_data = [j11, j21, j31, jd1]
            if serial.isOpen():
                print('串口已打开')
                for i in angle_data:
                    i = int(i)
                    if i > 255:
                        i = 255
                    data = hex(i)
                    data = str(data)  # 发送的数据

                    # 因为传的是字符串，所以当发送的数据是个位数时会接收bug，所以要在个位数前面加个0
                    if i < 16:
                        data = '0' + data[-1]
                    else:
                        data = data[2:]

                    data = bytes.fromhex(data)
                    serial.write(data)  # 串口写数据
                    time.sleep(1)
            detect()
