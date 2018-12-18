#ifndef SQ_IMAGEPROCESS_H
#define SQ_IMAGEPROCESS_H

#include <QtWidgets/QMainWindow>
#include "ui_ImageProcess.h"
#include <QDebug>  
#include <QList>  
#include <QFileDialog> 
#include <QMouseEvent>
#include <QKeyEvent>
#include <opencv2/opencv.hpp>
////#include "sq_qopenglwidget.h"
#include "SQ_StlRead.h"
#include "SQ_ImageZooming.h"
#include "SQ_Quaternion.h"
#include "QTextCodec.h"
#include "ui_SQ_About.h"
#include "SQ_About.h"
#include "SQ_Mysql.h"
#include <QMap> 
#include <ActiveQt/QAxObject>
#include <QTime>
#include "SQ_Quaternion.h"
#include "AIV_qwx_NormalVector.h"

class ImageProcess : public QMainWindow
{
	Q_OBJECT

public:
	ImageProcess(QWidget *parent = Q_NULLPTR);


private:
	Ui::ImageProcessClass ui;//������

	SQ_Mysql *Mysql_ui;//���ݿ⣨���账��
	SQ_About *About_ui;//���ڣ����账��
	SQ_QOpenGLWidget *OpenGL_ui;//OpenGL�Ľ���
	SQ_ImageZooming *Image_ui;//ͼƬ�Ľ���
	SQ_StlRead *stlread;//��ȡ.stl�ļ�����
	QTimer *timer;//������ʱ�������账��
	SQ_PointCloud *pointcloud;//���ƴ���
	SQ_Quaternion *quaternion;//��Ԫ�������账��
	AIV_qwx_NormalVector qwx_NormalVector;//��ȡ�����������账��


	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);


	//QStringList OpenStlPath;//������άͼ����·��
	void PlotLine(cv::Mat Point3D);//���������߶�
	void PlotCloud(cv::Mat Point3D);//���Ƶ���ͼ--PlotCloud(Point3D);
	void GetArmInfo(QStringList OpenStlPath, int type, int quantity);//��ȡ��е�۵�����
	void SavePointInfo(cv::Mat Point3D, QString path);//��������
	cv::Mat ReadPointInfo(QString path);//��ȡ����
	////////////////void horizontalSliderStart();//�������ʼ��

	float angle_start_1 = 0, angle_start_2 = 0,
		angle_start_3 = 0, angle_start_4 = 0,
		angle_start_5 = 0, angle_start_6 = 0;//�洢�������Ŀ̶�ֵ��ʼֵ

	float angle_before_1 = 0, angle_before_2 = 0,
		angle_before_3 = 0, angle_before_4 = 0,
		angle_before_5 = 0, angle_before_6 = 0;//�洢��һʱ�̹������Ŀ̶�ֵ
	
	//*************����ĳ�ö������*******//
	int flag_arm = 0;//Ϊ1��ʾ������ǻ�е��
	int flag_cloud = 0;//Ϊ1��ʾ�������
	int PointNumber = 0;//��¼���Ƹ���
	cv::Mat Point3DDepthImage;//�洢��Ҫת��Ϊ���ͼ�ĵ�������
	cv::Mat Point3DSave;//�洢����ĵ���

private slots:
	void on_ThreeDRecover_clicked();//�ָ�3Dͼ��
	void on_OpenStl_clicked();//��3Dͼ��
	void on_OpenCloudSTL_clicked();//��ʾ3D����-STL
	void on_OpenCloudPCD_clicked();//��ʾ3D����-PCD
	void on_GetDepthImage2D_clicked();//���ɶ�ά���ͼ

	void on_SaveCloudData_clicked();//�����������
	void on_ReadCloudData_clicked();//��ȡ��������
	void ImageProcess_About();//����
	void ImageProcess_Database();//���ݿ�

	//////////////void Rotate_X_Y();//X_Y������
	void KeyPointChange(int state);//�ؼ���
	void onTimeout();//��ʱ��

};
#endif 