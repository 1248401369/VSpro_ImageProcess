#ifndef SQ_IMAGEZOOMING_H
#define SQ_IMAGEZOOMING_H

#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include "ui_ImageProcess.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog> 
#include <QDateTime>
#include "QTextCodec.h"

class SQ_ImageZooming :
	public QLabel
{
	Q_OBJECT
public:
	explicit SQ_ImageZooming(QLabel *label, QWidget *parent = 0);
	~SQ_ImageZooming();

	Ui::ImageProcessClass* ui;

	QString R_Value = "0";//记录RGB数值
	QString G_Value = "0";
	QString B_Value = "0";
	int flag_image = 0;//记录是否导入图片
	int ImageShow_0_X = 0, ImageShow_0_Y = 0;//记录Label左上方顶点的坐标信息
	int mouse_X = 0, mouse_Y = 0;//记录鼠标光标处的坐标信息
	int mouse_image_X = 0, mouse_image_Y = 0;//记录鼠标光标处在图片坐标系中的坐标信息
	int mouse_label_0_X = 0, mouse_label_0_Y = 0;//记录Label左顶点在图片坐标系中的坐标信息
	double ImageScaleRatio_init = 0;//记录图片初始缩放比例
	double ImageScaleRatio = 1.0;//记录图片缩放比例
	cv::Mat ImageOriginalCv; //存储原始图片
	cv::Mat ImageScaleCv;//存储缩放后图片-Cv
	QImage ImageScaleQt;//存储缩放后的图片

	void ShowDepthImage2D(cv::Mat ImageDepth);//显示二维深度图

private:

	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent*event);
	void mousePressEvent(QMouseEvent *event);


private slots:
	void OpenImageEvent();//打开图片
	void SaveImageEvent();//保存图片
	void ImageRecoverEvent();//恢复图片

};
#endif

