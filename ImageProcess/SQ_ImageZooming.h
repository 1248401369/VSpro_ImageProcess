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

	QString R_Value = "0";//��¼RGB��ֵ
	QString G_Value = "0";
	QString B_Value = "0";
	int flag_image = 0;//��¼�Ƿ���ͼƬ
	int ImageShow_0_X = 0, ImageShow_0_Y = 0;//��¼Label���Ϸ������������Ϣ
	int mouse_X = 0, mouse_Y = 0;//��¼����괦��������Ϣ
	int mouse_image_X = 0, mouse_image_Y = 0;//��¼����괦��ͼƬ����ϵ�е�������Ϣ
	int mouse_label_0_X = 0, mouse_label_0_Y = 0;//��¼Label�󶥵���ͼƬ����ϵ�е�������Ϣ
	double ImageScaleRatio_init = 0;//��¼ͼƬ��ʼ���ű���
	double ImageScaleRatio = 1.0;//��¼ͼƬ���ű���
	cv::Mat ImageOriginalCv; //�洢ԭʼͼƬ
	cv::Mat ImageScaleCv;//�洢���ź�ͼƬ-Cv
	QImage ImageScaleQt;//�洢���ź��ͼƬ

	void ShowDepthImage2D(cv::Mat ImageDepth);//��ʾ��ά���ͼ

private:

	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent*event);
	void mousePressEvent(QMouseEvent *event);


private slots:
	void OpenImageEvent();//��ͼƬ
	void SaveImageEvent();//����ͼƬ
	void ImageRecoverEvent();//�ָ�ͼƬ

};
#endif

