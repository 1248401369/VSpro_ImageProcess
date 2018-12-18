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
//用于显示三维图，UI中将OpenGL Widget提升为QOpenGLWidget
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

	SQ_Quaternion *Quaternion;//读取Quaternion文件的类
	SQ_PointCloud *pointcloud;//点云处理

	//type=2表示立体图，type=4表示点云图
	void Display3D(cv::Mat Point3D, int type);//显示三维图像，3DPoint为N*3的矩阵	
	void Display3DArm(QVector<cv::Mat> Point3D, int type);//显示三维图像，3DPoint为N*3的矩阵	 
	void GetCenterPoint(cv::Mat centerRotationAxis);////存储机械臂的6个中心点坐标以及初始轴向
	void Recover3D();//恢复原始观察视角与大小
	void GetRotateAngle(float angle_1, float angle_2, float angle_3, float angle_4, float angle_5, float angle_6);//获取三维物体的旋转角度	
	Cursor_Opengl GetCursor();//获取光标位置
	int PCLCornerDetection(int Flag);//传递是否显示角点信息，并返回角点个数
	cv::Mat UnitMat();//置为单位阵

private:

	void initializeGL();//初始化
	void resizeGL(int width, int height);
	void paintGL();//重新绘制

	void SQ_QOpenGLWidget::loadTextures();//装载纹理

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent*event);
	void mouseReleaseEvent(QMouseEvent *event);

	void ArmRotTransEvery(float angle, int number);//机械臂每个关节的旋转操作，number 0 1 2 3 4 5
	cv::Mat QVectorToMat(QVector<cv::Mat> Point3D);//把容器转成一个矩阵
	void normalizeAngle(float &angle);//旋转角度标准化	
	cv::Mat MergeRows(cv::Mat A, cv::Mat B);//矩阵拼接-A=[A;B]	
	cv::Point3f Get3Dpos(int x, int y);//根据屏幕坐标得到OPENGL中坐标
	float PointToLineDistance(cv::Point3f P, cv::Point3f A, cv::Point3f B);//点到直线的距离
	float NormOfVector(cv::Point3f A);//求向量的模
	cv::Mat PointDistanceShort(cv::Mat Point3D, cv::Point3f A, cv::Point3f B);//求距离直线最近的1个点的坐标
	float near_value = 0;//最短距离--相机距离屏幕的最短距离
	int flag_show_normal = 0;//为1表示显示

	int cursor_opengl_x = 0, cursor_opengl_y = 0;//存储光标实时位置
	float rotate_world_x = 0, rotate_world_y = 0;//存储世界坐标系的转动角度
	int cursor_mid_press_x = 0, cursor_mid_press_y = 0;//存储光标滚轮按压时的光标位置
	int flag_mid_press_release = 0;//0表示鼠标滚轮为释放状态 1表示触发了鼠标滚轮按下操作 2表示鼠标滚轮处于按下状态

	float move_world_x = 0, move_world_y = 0;//存储世界坐标系的移动角度
	float acc_move_world_x = 0, acc_move_world_y = 0;//存储世界坐标系的移动角度
	cv::Mat AccTransMat;//累计的平移矩阵

	int cursor_left_press_x = 0, cursor_left_press_y = 0;//存储光标左键按压时的光标位置
	int flag_left_press_release = 0;//0表示鼠标左键为释放状态 1表示触发了鼠标左键按下操作 2表示鼠标左键处于按下状态

	double ShowRatio = SHOWRATIO;//缩放显示比例
	double ScaleRatio = 1;//缩放比例
	int flag_display_type = 0;//存储显示类型
	int flag_display = 0;//存储是否已经显示3D

	QVector<cv::Mat> Point3DQVector;//存储读取到的机械臂的点坐标
	QVector<cv::Mat> Point3DQOriginalVector;//存储读取到的机械臂的原始点坐标
	cv::Mat ArmCenterPoint;//存储机械臂的中心点坐标--6个中心点
	cv::Mat ArmCenterPointOriginal;//存储机械臂的原始中心点坐标--6个中心点
	cv::Mat Point3DDisplay;//存储需要显示的坐标点
	cv::Mat Point3DOriginal;//存储需要原始的坐标点
	cv::Mat ArmRotationAxis;//存储导入时的旋转轴-6个

	int flag_rightbutton = 0;//为1表示显示选中的点
	cv::Mat Point3DDisplayPoint;//存储需要显示的选中的点
	cv::Mat Point3DDisplayPointOriginal;//存储需要显示的选中的点

	cv::Mat AccRotMat;//累计的旋转平移矩阵--Base

	float acc_angle_1 = 0, acc_angle_2 = 0,
	acc_angle_3 = 0, acc_angle_4 = 0,
	acc_angle_5 = 0, acc_angle_6 = 0;//累计的旋转角度值
	int flag_arm = 0;//1表示导入的三维图案是机械臂

	cv::Mat Corner3DMat;//存储单个零件的角点数据
	int flag_corner_show = 0;//为1表示需要显示3D展示角点
	int flag_corner_end = 0;//为1表示角点识别程序结束
	GLuint texture; //储存一个纹理
};

#endif // SQ_QOPENGLWIDGET_H
