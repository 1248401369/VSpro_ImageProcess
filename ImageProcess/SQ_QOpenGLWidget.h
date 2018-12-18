#ifndef SQ_QOPENGLWIDGET_H
#define SQ_QOPENGLWIDGET_H

#include <QtGui>
#include <QtCore>
#include <QtOpenGL>
#include <QWidget.h>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QDebug>  
#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include <QKeyEvent>
#include <GL/glu.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "SQ_Quaternion.h"
#include "SQ_StlRead.h"
#include <QtOpenGL>
#include "SQ_PointCloud.h"

#define SHOWRATIO (-4)

//********************************
//������ʾ��άͼ��UI�н�OpenGL Widget����ΪQOpenGLWidget
//********************************

struct Cursor_Opengl
{
	int cursor_opengl_x;
	int cursor_opengl_y;
};


class SQ_QOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit  SQ_QOpenGLWidget(QWidget *parent = 0);
	~SQ_QOpenGLWidget();

	SQ_Quaternion *Quaternion;//��ȡQuaternion�ļ�����
	SQ_PointCloud *pointcloud;//���ƴ���

	//type=2��ʾ����ͼ��type=4��ʾ����ͼ
	void Display3D(cv::Mat Point3D, int type);//��ʾ��άͼ��3DPointΪN*3�ľ���	
	void Display3DArm(QVector<cv::Mat> Point3D, int type);//��ʾ��άͼ��3DPointΪN*3�ľ���	 
	void GetCenterPoint(cv::Mat centerRotationAxis);////�洢��е�۵�6�����ĵ������Լ���ʼ����
	void Recover3D();//�ָ�ԭʼ�۲��ӽ����С
	void GetRotateAngle(float angle_1, float angle_2, float angle_3, float angle_4, float angle_5, float angle_6);//��ȡ��ά�������ת�Ƕ�	
	Cursor_Opengl GetCursor();//��ȡ���λ��
	int PCLCornerDetection(int Flag);//�����Ƿ���ʾ�ǵ���Ϣ�������ؽǵ����
	cv::Mat UnitMat();//��Ϊ��λ��

private:

	void initializeGL();//��ʼ��
	void resizeGL(int width, int height);
	void paintGL();//���»���

	void SQ_QOpenGLWidget::loadTextures();//װ������

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent*event);
	void mouseReleaseEvent(QMouseEvent *event);

	void ArmRotTransEvery(float angle, int number);//��е��ÿ���ؽڵ���ת������number 0 1 2 3 4 5
	cv::Mat QVectorToMat(QVector<cv::Mat> Point3D);//������ת��һ������
	void normalizeAngle(float &angle);//��ת�Ƕȱ�׼��	
	cv::Mat MergeRows(cv::Mat A, cv::Mat B);//����ƴ��-A=[A;B]	
	cv::Point3f Get3Dpos(int x, int y);//������Ļ����õ�OPENGL������
	float PointToLineDistance(cv::Point3f P, cv::Point3f A, cv::Point3f B);//�㵽ֱ�ߵľ���
	float NormOfVector(cv::Point3f A);//��������ģ
	cv::Mat PointDistanceShort(cv::Mat Point3D, cv::Point3f A, cv::Point3f B);//�����ֱ�������1���������
	float near_value = 0;//��̾���--���������Ļ����̾���
	int flag_show_normal = 0;//Ϊ1��ʾ��ʾ

	int cursor_opengl_x = 0, cursor_opengl_y = 0;//�洢���ʵʱλ��
	float rotate_world_x = 0, rotate_world_y = 0;//�洢��������ϵ��ת���Ƕ�
	int cursor_mid_press_x = 0, cursor_mid_press_y = 0;//�洢�����ְ�ѹʱ�Ĺ��λ��
	int flag_mid_press_release = 0;//0��ʾ������Ϊ�ͷ�״̬ 1��ʾ�����������ְ��²��� 2��ʾ�����ִ��ڰ���״̬

	float move_world_x = 0, move_world_y = 0;//�洢��������ϵ���ƶ��Ƕ�
	float acc_move_world_x = 0, acc_move_world_y = 0;//�洢��������ϵ���ƶ��Ƕ�
	cv::Mat AccTransMat;//�ۼƵ�ƽ�ƾ���

	int cursor_left_press_x = 0, cursor_left_press_y = 0;//�洢��������ѹʱ�Ĺ��λ��
	int flag_left_press_release = 0;//0��ʾ������Ϊ�ͷ�״̬ 1��ʾ���������������²��� 2��ʾ���������ڰ���״̬

	double ShowRatio = SHOWRATIO;//������ʾ����
	double ScaleRatio = 1;//���ű���
	int flag_display_type = 0;//�洢��ʾ����
	int flag_display = 0;//�洢�Ƿ��Ѿ���ʾ3D

	QVector<cv::Mat> Point3DQVector;//�洢��ȡ���Ļ�е�۵ĵ�����
	QVector<cv::Mat> Point3DQOriginalVector;//�洢��ȡ���Ļ�е�۵�ԭʼ������
	cv::Mat ArmCenterPoint;//�洢��е�۵����ĵ�����--6�����ĵ�
	cv::Mat ArmCenterPointOriginal;//�洢��е�۵�ԭʼ���ĵ�����--6�����ĵ�
	cv::Mat Point3DDisplay;//�洢��Ҫ��ʾ�������
	cv::Mat Point3DOriginal;//�洢��Ҫԭʼ�������
	cv::Mat ArmRotationAxis;//�洢����ʱ����ת��-6��

	int flag_rightbutton = 0;//Ϊ1��ʾ��ʾѡ�еĵ�
	cv::Mat Point3DDisplayPoint;//�洢��Ҫ��ʾ��ѡ�еĵ�
	cv::Mat Point3DDisplayPointOriginal;//�洢��Ҫ��ʾ��ѡ�еĵ�

	cv::Mat AccRotMat;//�ۼƵ���תƽ�ƾ���--Base

	float acc_angle_1 = 0, acc_angle_2 = 0,
	acc_angle_3 = 0, acc_angle_4 = 0,
	acc_angle_5 = 0, acc_angle_6 = 0;//�ۼƵ���ת�Ƕ�ֵ
	int flag_arm = 0;//1��ʾ�������άͼ���ǻ�е��

	cv::Mat Corner3DMat;//�洢��������Ľǵ�����
	int flag_corner_show = 0;//Ϊ1��ʾ��Ҫ��ʾ3Dչʾ�ǵ�
	int flag_corner_end = 0;//Ϊ1��ʾ�ǵ�ʶ��������
	GLuint texture; //����һ������
};

#endif // SQ_QOPENGLWIDGET_H
