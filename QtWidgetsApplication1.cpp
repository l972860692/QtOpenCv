#include "QtWidgetsApplication1.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <seeta/FaceDetector.h>
using namespace cv;
using namespace std;

void DrawFaceRectangl(Mat image);
void TestSeatImage();
 
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

 

string xmlPath = "E:\\FaceProject\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml"; 
bool isOpen = true;
void QtWidgetsApplication1::on_imagefind_clicked()
{
    
    VideoSearch();

}
void QtWidgetsApplication1::on_closevideobtn_clicked()
{
    isOpen = false;
}
void QtWidgetsApplication1::VideoSearch()
{

    cv::VideoCapture capture;
    capture.open(1);
    cv::Mat frame;
    while (capture.isOpened() && isOpen)
    {
        capture >> frame;
        if (frame.empty()) continue;
 
        cv::cvtColor(frame, frame, CV_RGB2BGR);
        ui.label->setPixmap(QPixmap::fromImage(QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888)));
       // cv::imshow("Frame", frame);

        auto key = cv::waitKey(20);
        if (key == 27)
        {
            break;
        }
    }
    capture.release();
  



}
void TestSeatImage(Ui::QtWidgetsApplication1Class ui)
{
    ui.label->setText("AAAA");

    QImage Qtemp;
    Mat srcImg, temp;
    srcImg = imread("C:\\Users\\liusong\\Desktop\\cvtest\\111.jpg");
    if (srcImg.empty())
    {
        printf("Could not find the image!\n");
    }
    cvtColor(srcImg, temp, CV_BGR2RGB);

    Qtemp = QImage(temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    Qtemp = Qtemp.scaled(ui.label->width(), ui.label->height());

    //DrawFaceRectangl(srcImg);

    seeta::ModelSetting setting;
    SeetaImageData simage;
    setting.append("E:\\FaceProject\\sf3.0_models\\face_detector.csta");
    seeta::FaceDetector* new_fd = new seeta::FaceDetector(setting);
    simage.width = srcImg.cols;
    simage.height = srcImg.rows;
    simage.channels = srcImg.channels();
    simage.data = srcImg.data;

    auto faces = new_fd->detect(simage);
    for (int i = 0; i < faces.size; i++)
    {
        auto face = faces.data[i].pos;
        rectangle(srcImg, cv::Rect(face.x, face.y, face.width, face.height), cv::Scalar(0, 0, 255), 2, 8, 0);
    }


    namedWindow("testimage", 0);
    resizeWindow("testimage", ui.label->width(), ui.label->height());
    imshow("testimage", srcImg);

    ui.label->setPixmap(QPixmap::fromImage(Qtemp));
    ui.label->resize(Qtemp.size());
    //ui.label->show();

}

void DrawFaceRectangl(Mat img)
{



    CascadeClassifier ccf;
    ccf.load(xmlPath);
    vector<Rect> faces;
    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY);

    equalizeHist(gray, gray);    
    ccf.detectMultiScale(gray, faces, 1.1, 3, 0, Size(50, 50), Size(500, 500));   
    for (vector<Rect>::const_iterator iter = faces.begin(); iter != faces.end(); iter++)
    {
        rectangle(img, *iter, Scalar(0, 0, 255), 2, 8);
    }
 
}

 
 