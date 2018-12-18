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
	Ui::ImageProcessClass ui;//主界面

	SQ_Mysql *Mysql_ui;//数据库（无需处理）
	SQ_About *About_ui;//关于（无需处理）
	SQ_QOpenGLWidget *OpenGL_ui;//OpenGL的界面
	SQ_ImageZooming *Image_ui;//图片的界面
	SQ_StlRead *stlread;//读取.stl文件的类
	QTimer *timer;//开启定时器（无需处理）
	SQ_PointCloud *pointcloud;//点云处理
	SQ_Quaternion *quaternion;//四元数（无需处理）
	AIV_qwx_NormalVector qwx_NormalVector;//求取法向量（无需处理）


	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);


	//QStringList OpenStlPath;//保存三维图案的路径
	void PlotLine(cv::Mat Point3D);//绘制连续线段
	void PlotCloud(cv::Mat Point3D);//绘制点云图--PlotCloud(Point3D);
	void GetArmInfo(QStringList OpenStlPath, int type, int quantity);//获取机械臂的数据
	void SavePointInfo(cv::Mat Point3D, QString path);//保存数据
	cv::Mat ReadPointInfo(QString path);//读取数据
	////////////////void horizontalSliderStart();//横滚条初始化

	float angle_start_1 = 0, angle_start_2 = 0,
		angle_start_3 = 0, angle_start_4 = 0,
		angle_start_5 = 0, angle_start_6 = 0;//存储滚动条的刻度值初始值

	float angle_before_1 = 0, angle_before_2 = 0,
		angle_before_3 = 0, angle_before_4 = 0,
		angle_before_5 = 0, angle_before_6 = 0;//存储上一时刻滚动条的刻度值
	
	//*************建议改成枚举类型*******//
	int flag_arm = 0;//为1表示导入的是机械臂
	int flag_cloud = 0;//为1表示导入点云
	int PointNumber = 0;//记录点云个数
	cv::Mat Point3DDepthImage;//存储需要转化为深度图的点云数据
	cv::Mat Point3DSave;//存储保存的点云

private slots:
	void on_ThreeDRecover_clicked();//恢复3D图案
	void on_OpenStl_clicked();//打开3D图案
	void on_OpenCloudSTL_clicked();//显示3D点云-STL
	void on_OpenCloudPCD_clicked();//显示3D点云-PCD
	void on_GetDepthImage2D_clicked();//生成二维深度图

	void on_SaveCloudData_clicked();//保存点云数据
	void on_ReadCloudData_clicked();//读取点云数据
	void ImageProcess_About();//关于
	void ImageProcess_Database();//数据库

	//////////////void Rotate_X_Y();//X_Y滚动条
	void KeyPointChange(int state);//关键点
	void onTimeout();//定时器

};
#endif 