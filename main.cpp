#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "TCPSerial.h"
#include "USBSerial.h"
#include "HardwareController.h"

using namespace std;
using namespace cv;

// 测试程序, 接口在"HardwareController.h"
int main() {
    cout << "Communication test" << endl;
    //TCPSerial serial("192.168.4.1", 9000, true);
    USBSerial serial("/dev/ttyUSB0");
    HardwareController hardware(&serial);
    hardware.startControlMode();
    VideoCapture capture(0);
    Mat frame;
    while (capture.read(frame)) {
        putText(frame, "WASD ->gimbal; K L->shooting motor; O P -> friction wheel", Point(0, 25), FONT_HERSHEY_SIMPLEX,
                0.5, Scalar(0, 0, 0));
        imshow("Test", frame);
        char key = (char)waitKey(1);
        key = tolower(key);
        switch (key) {
            case 'w': {
                hardware.moveGimbalBy(0, 50);
                break;
            }
            case 'a': {
                hardware.moveGimbalBy(-50, 0);
                break;
            }
            case 's': {
                hardware.moveGimbalBy(0, -50);
                break;
            }
            case 'd': {
                hardware.moveGimbalBy(50, 0);
                break;
            }
            case 'k': {
                hardware.startShooting();
                break;
            }
            case 'l': {
                hardware.stopShooting();
                break;
            }
            case 'o': {
                hardware.startFrictionWheel();
                break;
            }
            case 'p': {
                hardware.stopFrictionWheel();
                break;
            }
            case '/': {
                hardware.requestCurrentState();
                break;
            }
            case '0':{
                hardware.reset();
                break;
            }
            case ' ':{
                hardware.stopGimble();
                break;
            }
            default: {
                //hardware.stopGimble();
            }
        }
    }
    return 0;
}