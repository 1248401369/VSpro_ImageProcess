#include "sq_qopenglwidget.h"


SQ_QOpenGLWidget::SQ_QOpenGLWidget(QWidget *parent)
: QOpenGLWidget(parent)
{
	setMouseTracking(true);//使能鼠标捕获
	//Quaternion文件调用初始化
	Quaternion = new SQ_Quaternion();
	//点云处理
	pointcloud = new SQ_PointCloud();

	AccRotMat = UnitMat();

	near_value = 2.0;//最短距离--相机距离屏幕的最短距离
	// 设置OpenGL的版本信息
	//QSurfaceFormat format;
	//format.setRenderableType(QSurfaceFormat::OpenGL);
	//format.setProfile(QSurfaceFormat::CoreProfile);
	//format.setVersion(3, 3);
	//setFormat(format);
}

SQ_QOpenGLWidget::~SQ_QOpenGLWidget()
{

}

void SQ_QOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();//初始化OpenGL函数
	setGeometry(640, 95, 600, 560);//窗口位置和大小
	//使用纹理需要的语句
	//loadTextures();//纹理
	//glEnable(GL_TEXTURE_2D);//允许采用2D纹理技术--纹理
	glShadeModel(GL_SMOOTH);//设置阴影平滑模式
	glClearColor(0, 0, 0, 0);//改变窗口的背景颜色
	glClearDepth(1.0);//设置深度缓存
	glEnable(GL_DEPTH_TEST);//允许深度测试
	glDepthFunc(GL_LEQUAL);//设置深度测试类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//进行透视校正
	glRenderMode(GL_RENDER);//渲染模式,默认
}

void SQ_QOpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, ShowRatio); //移入屏幕
	//gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	float ColorArray[7][3] = { { 0, 1, 0 }, { 1, 0.5, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 0.8, 0.5, 0 } };
	//glBindTexture(GL_TEXTURE_2D, texture);//纹理

	//glColor3f(0.0f, 1.0f, 0.0f);//绿色
	//glColor3f(1.0f, 0.5f, 0.0f);//橙色
	//glColor3f(1.0f, 0.0f, 0.0f);//红色
	//glColor3f(1.0f, 1.0f, 0.0f);//黄色
	//glColor3f(0.0f, 0.0f, 1.0f);//蓝色
	//glColor3f(1.0f, 0.0f, 1.0f);//紫色

	//***********************************绘制三角面***********************************
	if (flag_display_type == 2)
	{
		glBegin(GL_TRIANGLES);
		if (flag_arm == 1)//机械臂--直接利用Point3DQVector数据进行显示
		{
			for (int i = 0; i < Point3DQVector.size(); i++)
			{
				if (i>6)
				{
					glColor3f(ColorArray[6][0], ColorArray[6][1], ColorArray[6][2]);
				}
				else
				{
					glColor3f(ColorArray[i][0], ColorArray[i][1], ColorArray[i][2]);
				}
				for (int j = 0; j < Point3DQVector[i].rows; j++)
				{
					glVertex3f(Point3DQVector[i].at<float>(j, 0), Point3DQVector[i].at<float>(j, 1), Point3DQVector[i].at<float>(j, 2));
				}
			}
		}
		else
		{
			for (int i = 0; i < Point3DDisplay.rows; i++)
			{
				switch (i % 3){
					case 0:{ glColor3f(0.0f, 0.0f, 1.0f); break; }
					case 1:{ glColor3f(1.0f, 1.0f, 0.0f); break; }
					case 2:{ glColor3f(1.0f, 0.0f, 1.0f); break; }
					default:{ glColor3f(1.0f, 0.0f, 1.0f); break; }
				}
				//glTexCoord2f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1));//纹理
				glVertex3f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1), Point3DDisplay.at<float>(i, 2));
			}
		}		
		glEnd();
	}
	//glRotatef(0, 1.0f, 0.0f, 0.0f);//绕x轴旋转四边形

	//***********************************绘制点云***********************************
	if (flag_display_type == 4)
	{
		glPointSize(1.0f);//在绘制之前要设置要相关参数，这里设置点的大小为5像素
		glBegin(GL_POINTS);
		if (flag_arm == 1)//机械臂
		{
			for (int i = 0; i < Point3DQVector.size(); i++)
			{
				if (i>6)
				{
					glColor3f(ColorArray[6][0], ColorArray[6][1], ColorArray[6][2]);
				}
				else
				{
					glColor3f(ColorArray[i][0], ColorArray[i][1], ColorArray[i][2]);
				}
				for (int j = 0; j < Point3DQVector[i].rows; j++)
				{
					glVertex3f(Point3DQVector[i].at<float>(j, 0), Point3DQVector[i].at<float>(j, 1), Point3DQVector[i].at<float>(j, 2));
				}
			}
		}
		else
		{			
			glPointSize(1.0f);//在绘制之前要设置要相关参数，这里设置点的大小为5像素
			glBegin(GL_POINTS);
			for (int i = 0; i < Point3DDisplay.rows; i++)
			{
				if (Point3DDisplay.at<float>(i, 2)>0)
					glColor3f(0.0f, 1.0f, 0.0f);//绿色
				else
					glColor3f(1.0f, 0.0f, 1.0f);//紫色
				glVertex3f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1), Point3DDisplay.at<float>(i, 2));
			}
			glEnd();

			glPointSize(3.0f);//在绘制之前要设置要相关参数，这里设置点的大小为5像素
			glBegin(GL_POINTS);
			if (flag_corner_show == 1)//需要显示角点
			{
				glColor3f(0.0f, 1.0f, 0.0f);//绿色
				for (int i = 0; i < Corner3DMat.rows; i++)
				{
					glVertex3f(Corner3DMat.at<float>(i, 0), Corner3DMat.at<float>(i, 1), Corner3DMat.at<float>(i, 2));
				}				
			}			
		}		
		glEnd();
	}
	//**************************************画点云和法向量*********************
	if (flag_display_type == 5)
	{
		//点云
		glPointSize(2.0f);//在绘制之前要设置要相关参数，这里设置点的大小为5像素
		glBegin(GL_POINTS);
		for (int i = 0; i < Point3DDisplay.rows/2; i++)
		{
			if (Point3DDisplay.at<float>(i, 2)>0)
				glColor3f(0.0f, 1.0f, 0.0f);//绿色
			else
				glColor3f(1.0f, 0.0f, 1.0f);//紫色
			glVertex3f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1), Point3DDisplay.at<float>(i, 2));
		}		
		glEnd();

		//法向量
		if (flag_show_normal == 1)//为1表示显示
		{
			glColor3f(1.0f, 0.0f, 0.0f);//红色
			glLineWidth(0.5);
			glBegin(GL_LINES);
			for (int i = 0; i < Point3DDisplay.rows / 2; i++)
			{
				glVertex3f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1), Point3DDisplay.at<float>(i, 2));
				glVertex3f(Point3DDisplay.at<float>(i + Point3DDisplay.rows / 2, 0),
					Point3DDisplay.at<float>(i + Point3DDisplay.rows / 2, 1),
					Point3DDisplay.at<float>(i + Point3DDisplay.rows / 2, 2));
			}
			glEnd();
		}		
	}
	//***********************************画连续的线段***********************************
	if (flag_display_type == 1)
	{
		glColor3f(1.0f, 0.0f, 1.0f);//紫色
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < Point3DDisplay.rows; i++)
		{
			glVertex3f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1), Point3DDisplay.at<float>(i, 2));
		}
		glEnd();
	}

	//************************************画由中心点指向屏幕的直线****************8
	if (flag_rightbutton == 1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);//绿色
		glPointSize(6.0f);//在绘制之前要设置要相关参数，这里设置点的大小为5像素
		glBegin(GL_POINTS);
		for (int i = 0; i < Point3DDisplayPoint.rows; i++)
		{
			glVertex3f(Point3DDisplayPoint.at<float>(i, 0), Point3DDisplayPoint.at<float>(i, 1), Point3DDisplayPoint.at<float>(i, 2));
		}
		glEnd();
	}
	glFlush();//glFlush，保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）

}

void SQ_QOpenGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, (GLint)width, (GLint)height);//重置当前的视口  
	glMatrixMode(GL_PROJECTION);//选择投影矩阵  
	glLoadIdentity();//重置投影矩阵    
	//gluPerspective(53.0, (GLfloat)width / (GLfloat)height, 2, 100.0);//设置视口的大小 
	//2*atan(1.0/2)*57.3
	gluPerspective(2 * atan(1.0 / near_value)*57.3, (GLfloat)width / (GLfloat)height, near_value, 100.0);//设置视口的大小 
	glMatrixMode(GL_MODELVIEW);//选择模型观察矩阵  
	glLoadIdentity();//重置模型观察矩阵  
}

//鼠标点击事件
void SQ_QOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
	switch (event->button())
	{
	case Qt::LeftButton:{
					flag_left_press_release = 1;
					break; }
	case Qt::RightButton:{
					if (flag_arm == 0 && flag_display == 1)//
					{
						cv::Point3f cursor_in_opengl = Get3Dpos(cursor_opengl_x, cursor_opengl_y);
						cv::Point3f A, B;
						A.x = cursor_in_opengl.x * (-1.0)*SHOWRATIO / near_value;
						A.y = cursor_in_opengl.y * (-1.0)*SHOWRATIO / near_value;
						A.z = 0;
						B.x = cursor_in_opengl.x;
						B.y = cursor_in_opengl.y;
						B.z = cursor_in_opengl.z;
						flag_rightbutton = 1;//为1表示显示选中的点
						Point3DDisplayPoint = PointDistanceShort(Point3DDisplay, A, B);//存储需要显示的直线
						Point3DDisplayPoint.copyTo(Point3DDisplayPointOriginal);
						update();
					}					
					break; }
	case Qt::MidButton:{
					flag_mid_press_release = 1;
					break; }
	default:break;
	}
}

//鼠标释放事件
void SQ_QOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	switch (event->button())
	{
	case Qt::LeftButton:{
					flag_left_press_release = 0;
					break; }
	case Qt::RightButton:{
					break; }
	case Qt::MidButton:{
					flag_mid_press_release = 0;
					break; }
	default:break;
	}

}

//滚轮缩放-放大或缩小三维图案
void SQ_QOpenGLWidget::wheelEvent(QWheelEvent*event)
{
	if (flag_display == 1)
	{
		if (event->delta() > 0)
		{
			//ShowRatio /= 1.1;
			ScaleRatio = 1.1;
		}
		else
		{
			//ShowRatio *= 1.1;
			ScaleRatio = 0.9;
		}
		if (flag_arm == 1)//机械臂
		{			
			//机械臂的关节同时进行定点缩放
			for (int i = 0; i < 7; i++)
			{
				Point3DQVector[i] = Quaternion->TransScaleMat(Point3DQVector[i], cursor_opengl_x, cursor_opengl_y, ScaleRatio);
			}
			//Point3DDisplay = QVectorToMat(Point3DQVector);
			//机械臂的关节的坐标系原点进行定点缩放
  			ArmCenterPoint = Quaternion->TransScaleMat(ArmCenterPoint, cursor_opengl_x, cursor_opengl_y, ScaleRatio);
		}
		else
		{			
			//定点缩放
			Point3DDisplay = Quaternion->TransScaleMat(Point3DDisplay, cursor_opengl_x, cursor_opengl_y, ScaleRatio);
			//选择制定点
			Point3DDisplayPoint = Quaternion->TransScaleMat(Point3DDisplayPoint, cursor_opengl_x, cursor_opengl_y, ScaleRatio);
			//角点数据
			Corner3DMat = Quaternion->TransScaleMat(Corner3DMat, cursor_opengl_x, cursor_opengl_y, ScaleRatio);
		}		
		update();
	}
}


//获取三维物体的旋转角度	
void SQ_QOpenGLWidget::GetRotateAngle(float angle_1, float angle_2, float angle_3, float angle_4, float angle_5, float angle_6)
{
	acc_angle_1 += angle_1;
	acc_angle_2 += angle_2;
	acc_angle_3 += angle_3;
	acc_angle_4 += angle_4;
	acc_angle_5 += angle_5;
	acc_angle_6 += angle_6;

	//第一个转动关节
	ArmRotTransEvery(angle_1, 0);
	//第二个转动关节
	ArmRotTransEvery(angle_2, 1);
	//第三个转动关节
	ArmRotTransEvery(angle_3, 2);
	//第四个转动关节
	ArmRotTransEvery(angle_4, 3);
	//第五个转动关节
	ArmRotTransEvery(angle_5, 4);
	//第六个转动关节
	ArmRotTransEvery(angle_6, 5);

	//Point3DDisplay = QVectorToMat(Point3DQVector);
	update();
}

//每个关节的旋转操作
void SQ_QOpenGLWidget::ArmRotTransEvery(float angle, int number)//number 0 1 2 3 4 5
{
	cv::Mat RotTransMat, AccRotTransLink;
	float Ox_offset, Oy_offset, Oz_offset;//记录原点之间的偏移量
	cv::Mat MatTemp(1, 3, CV_32FC1);

	//第number+1个转动关节
	Ox_offset = ArmCenterPoint.at<float>(number, 0) ;
	Oy_offset = ArmCenterPoint.at<float>(number, 1);
	Oz_offset = ArmCenterPoint.at<float>(number, 2);
	
	//坐标系转换，从而得到新的坐标系
	//1.依次左乘每个关节旋转的角度值
	//2.左乘绕世界坐标系的旋转矩阵--AccRotMat是绕世界坐标系的旋转矩阵
	//3.移动每个关节坐标系的原点
	switch (number)
	{
		case 0:{ AccRotTransLink = Quaternion->TransMat_Z(Oz_offset) * Quaternion->TransMat_Y(Oy_offset) * Quaternion->TransMat_X(Ox_offset)
			* AccRotMat; break; }
		case 1:{ AccRotTransLink = Quaternion->TransMat_Z(Oz_offset) * Quaternion->TransMat_Y(Oy_offset) * Quaternion->TransMat_X(Ox_offset)
			* AccRotMat
			* Quaternion->RotMat(ArmRotationAxis.at<float>(0, 0), ArmRotationAxis.at<float>(0, 1), ArmRotationAxis.at<float>(0, 2), acc_angle_1);
			break; }
		case 2:{ AccRotTransLink = Quaternion->TransMat_Z(Oz_offset) * Quaternion->TransMat_Y(Oy_offset) * Quaternion->TransMat_X(Ox_offset)
			* AccRotMat
			* Quaternion->RotMat(ArmRotationAxis.at<float>(0, 0), ArmRotationAxis.at<float>(0, 1), ArmRotationAxis.at<float>(0, 2), acc_angle_1)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(1, 0), ArmRotationAxis.at<float>(1, 1), ArmRotationAxis.at<float>(1, 2), acc_angle_2);
			break; }
		case 3:{ AccRotTransLink = Quaternion->TransMat_Z(Oz_offset) * Quaternion->TransMat_Y(Oy_offset) * Quaternion->TransMat_X(Ox_offset)
			* AccRotMat
			* Quaternion->RotMat(ArmRotationAxis.at<float>(0, 0), ArmRotationAxis.at<float>(0, 1), ArmRotationAxis.at<float>(0, 2), acc_angle_1)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(1, 0), ArmRotationAxis.at<float>(1, 1), ArmRotationAxis.at<float>(1, 2), acc_angle_2)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(2, 0), ArmRotationAxis.at<float>(2, 1), ArmRotationAxis.at<float>(2, 2), acc_angle_3);
			break; }
		case 4:{ AccRotTransLink = Quaternion->TransMat_Z(Oz_offset) * Quaternion->TransMat_Y(Oy_offset) * Quaternion->TransMat_X(Ox_offset)
			* AccRotMat
			* Quaternion->RotMat(ArmRotationAxis.at<float>(0, 0), ArmRotationAxis.at<float>(0, 1), ArmRotationAxis.at<float>(0, 2), acc_angle_1)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(1, 0), ArmRotationAxis.at<float>(1, 1), ArmRotationAxis.at<float>(1, 2), acc_angle_2)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(2, 0), ArmRotationAxis.at<float>(2, 1), ArmRotationAxis.at<float>(2, 2), acc_angle_3)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(3, 0), ArmRotationAxis.at<float>(3, 1), ArmRotationAxis.at<float>(3, 2), acc_angle_4);
			break; }
		case 5:{ AccRotTransLink = Quaternion->TransMat_Z(Oz_offset) * Quaternion->TransMat_Y(Oy_offset) * Quaternion->TransMat_X(Ox_offset)
			* AccRotMat
			* Quaternion->RotMat(ArmRotationAxis.at<float>(0, 0), ArmRotationAxis.at<float>(0, 1), ArmRotationAxis.at<float>(0, 2), acc_angle_1)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(1, 0), ArmRotationAxis.at<float>(1, 1), ArmRotationAxis.at<float>(1, 2), acc_angle_2)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(2, 0), ArmRotationAxis.at<float>(2, 1), ArmRotationAxis.at<float>(2, 2), acc_angle_3)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(3, 0), ArmRotationAxis.at<float>(3, 1), ArmRotationAxis.at<float>(3, 2), acc_angle_4)
			* Quaternion->RotMat(ArmRotationAxis.at<float>(4, 0), ArmRotationAxis.at<float>(4, 1), ArmRotationAxis.at<float>(4, 2), acc_angle_5);
			break; }
		default:break;
	}
	//起初，两个物体都是在世界坐标系内的，当第一个物体旋转或者平移后，可得到第一个物体的坐标系的旋转平移矩阵M
	//1.将第二个物体的坐标转化至第一个物体的坐标系内的坐标--左乘M的逆
	//2.将第一个物体的坐标系当成是第二个物体的世界坐标系，进行旋转变换--左乘第二个物体的旋转矩阵
	//3.将第二个物体的坐标转换至最初的世界坐标系中--左乘M

	//需要知道每个关节初始状态的旋转轴的方向向量
	RotTransMat = AccRotTransLink * Quaternion->RotMat(ArmRotationAxis.at<float>(number, 0),ArmRotationAxis.at<float>(number, 1),ArmRotationAxis.at<float>(number, 2), angle)* AccRotTransLink.inv();

	//机械臂的关节进行旋转操作
	for (int i = number + 1; i < 7; i++)
	{
		Point3DQVector[i] = Quaternion->RotTransMat(Point3DQVector[i], RotTransMat);
	}
	//机械臂的关节的坐标系原点进行旋转操作
	for (int i = number + 1; i < ArmCenterPoint.rows; i++)
	{
		MatTemp = Quaternion->RotTransMat(ArmCenterPoint.rowRange(i, i + 1), RotTransMat);
		ArmCenterPoint.at<float>(i, 0) = MatTemp.at<float>(0, 0);
		ArmCenterPoint.at<float>(i, 1) = MatTemp.at<float>(0, 1);
		ArmCenterPoint.at<float>(i, 2) = MatTemp.at<float>(0, 2);
	}
}

//获取光标位置
Cursor_Opengl SQ_QOpenGLWidget::GetCursor()
{
	Cursor_Opengl cursor_opengl;
	cursor_opengl.cursor_opengl_x = cursor_opengl_x;
	cursor_opengl.cursor_opengl_y = cursor_opengl_y;
	return cursor_opengl;
}

//根据屏幕坐标得到视点空间坐标
cv::Point3f SQ_QOpenGLWidget::Get3Dpos(int x, int y)
{
	cv::Point3f cursor_in_opengl;
	cursor_in_opengl.x = (-1 + x / 300.0);
	cursor_in_opengl.y = (1 - y / 280.0);
	//cursor_in_opengl.z = (1-sqrt(cursor_in_opengl.x*cursor_in_opengl.x + cursor_in_opengl.y*cursor_in_opengl.y))/0.67;
	cursor_in_opengl.z =(-1.0)* SHOWRATIO - near_value;
	return cursor_in_opengl;
}

//鼠标移动事件
void SQ_QOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	RotateAngle rotateAngle;
	//记录当前光标位置
	cursor_opengl_x = event->pos().x();
	cursor_opengl_y = event->pos().y();

	/******************移动操作**********************/
	if (flag_left_press_release == 1)
	{
		//存储当鼠标左键按下时的光标位置
		cursor_left_press_x = cursor_opengl_x;
		cursor_left_press_y = cursor_opengl_y;
		flag_left_press_release = 2;
	}
	if (flag_left_press_release == 2)
	{
		//存储光标移动的距离
		move_world_x = (cursor_opengl_x - cursor_left_press_x)*0.003;
		move_world_y = (cursor_left_press_y - cursor_opengl_y)*0.003;

		if (flag_arm == 1)//机械臂
		{
			//机械臂的关节同时进行平移操作
			for (int i = 0; i < 7; i++)
			{
				Point3DQVector[i] = Quaternion->RotTransMat(Point3DQVector[i], Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
			}
			//Point3DDisplay = QVectorToMat(Point3DQVector);
			//机械臂的关节坐标系原点进行平移操作
			ArmCenterPoint = Quaternion->RotTransMat(ArmCenterPoint, Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
		}
		else
		{
			//平移变换
			Point3DDisplay = Quaternion->RotTransMat(Point3DDisplay, Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
			//旋转自己标记的点
			Point3DDisplayPoint = Quaternion->RotTransMat(Point3DDisplayPoint, Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
			//角点数据
			Corner3DMat = Quaternion->RotTransMat(Corner3DMat, Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
		}

		update();

		//更新存储的光标位置
		cursor_left_press_x = cursor_opengl_x;
		cursor_left_press_y = cursor_opengl_y;
	}
	/******************旋转操作**********************/
	if (flag_mid_press_release == 1)
	{
		//存储当鼠标左键按下时的光标位置
		cursor_mid_press_x = cursor_opengl_x;
		cursor_mid_press_y = cursor_opengl_y;
		flag_mid_press_release = 2;
	}
	if (flag_mid_press_release == 2)
	{
		//存储光标移动的距离--等价于三维图案需要旋转角度
		rotate_world_x = (cursor_opengl_y - cursor_mid_press_y)*0.3;
		rotate_world_y = (cursor_opengl_x - cursor_mid_press_x)*0.3;

		//旋转角度标准化
		normalizeAngle(rotate_world_x);
		normalizeAngle(rotate_world_y);
	
		if (flag_arm == 1)//机械臂
		{
			//更新旋转平移矩阵--是累计的旋转平移矩阵
			AccRotMat = Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x) * AccRotMat;
			//机械臂的关节同时进行旋转操作
			for (int i = 0; i < 7; i++)
			{
				Point3DQVector[i] = Quaternion->RotTransMat(Point3DQVector[i], Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
			}
			//Point3DDisplay = QVectorToMat(Point3DQVector);
			//机械臂的关节坐标系原点进行旋转操作
			ArmCenterPoint = Quaternion->RotTransMat(ArmCenterPoint, Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
		}
		else
		{
			//旋转变换
			Point3DDisplay = Quaternion->RotTransMat(Point3DDisplay, Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
			//旋转自己标记的点
			Point3DDisplayPoint = Quaternion->RotTransMat(Point3DDisplayPoint, Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
			//角点数据
			Corner3DMat = Quaternion->RotTransMat(Corner3DMat, Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
		}	
		update();

		//更新存储的光标位置
		cursor_mid_press_x = cursor_opengl_x;
		cursor_mid_press_y = cursor_opengl_y;
	}
}

//恢复初始状态下的三维图案显示
void SQ_QOpenGLWidget::Recover3D()
{
	flag_show_normal = 0;//为1表示显示
	ShowRatio = SHOWRATIO;
	Point3DDisplayPoint = Point3DDisplayPointOriginal;//恢复鼠标选中的点云
	flag_rightbutton = 0;//不显示选中的点
	//恢复机械臂的原始数据
	ArmCenterPoint = ArmCenterPointOriginal;//恢复中心点坐标
	AccRotMat = UnitMat();//重置单位阵
	Point3DDisplay = Point3DOriginal;//恢复需要显示的原始的原始数据
	Point3DQVector = Point3DQOriginalVector;//恢复需要显示的机械臂的的原始数据--Vector形式
	update();
}

//显示三维图像，3DPoint为N*3的矩阵	 
void SQ_QOpenGLWidget::Display3DArm(QVector<cv::Mat> Point3D, int type)
{
	//初始化每个关节的转动角度的累计值
	acc_angle_1 = 0;
	acc_angle_2 = 0;
	acc_angle_3 = 0;
	acc_angle_4 = 0;
	acc_angle_5 = 0;
	acc_angle_6 = 0;

	AccRotMat = UnitMat();//重置单位阵
	flag_arm = 1;//当前导入机械臂
	Point3DQVector = Point3D;
	Point3DQOriginalVector = Point3D;//存储原始数据

	flag_display_type = type;//获取显示类型
	ShowRatio = SHOWRATIO;//初始化观察距离
	flag_display = 1;//确认导入三维图案
	update();
}

//存储机械臂的6个中心点坐标以及初始旋转轴
void SQ_QOpenGLWidget::GetCenterPoint(cv::Mat centerRotationAxis)
{
	cv::Mat ArmCenterPointTemp(6, 3, CV_32FC1);
	cv::Mat ArmRotationAxisTemp(6, 3, CV_32FC1);
	for (int i = 0; i < centerRotationAxis.rows / 2; i++)
	{
		//存储中心点
		ArmCenterPointTemp.at<float>(i, 0) = centerRotationAxis.at<float>(i, 0);
		ArmCenterPointTemp.at<float>(i, 1) = centerRotationAxis.at<float>(i, 1);
		ArmCenterPointTemp.at<float>(i, 2) = centerRotationAxis.at<float>(i, 2);
		//存储初始旋转轴
		ArmRotationAxisTemp.at<float>(i, 0) = centerRotationAxis.at<float>(i + 6, 0);
		ArmRotationAxisTemp.at<float>(i, 1) = centerRotationAxis.at<float>(i + 6, 1);
		ArmRotationAxisTemp.at<float>(i, 2) = centerRotationAxis.at<float>(i + 6, 2);
	}
	ArmCenterPoint = ArmCenterPointTemp;//存储中心点
	ArmCenterPoint.copyTo(ArmCenterPointOriginal);//存储原始的坐标
	ArmRotationAxis = ArmRotationAxisTemp;//存储初始旋转轴
}

//记录三维图案数据
void SQ_QOpenGLWidget::Display3D(cv::Mat Point3D, int type)
{
	flag_rightbutton = 0;//为1表示显示选中的点
	flag_arm = 0;//导入的不是机械臂
	Point3DDisplay = Point3D;
	Point3DDisplay.copyTo(Point3DOriginal);//存储三维图案原始数据
	flag_display_type = type;//获取显示类型
	ShowRatio = SHOWRATIO;//初始化观察距离
	flag_display = 1;//确认导入三维图案
	flag_show_normal = 1;//为1表示显示
	//if (flag_display_type == 4)
	//{			
	//}
	update();
	return;
}

//传递是否显示角点信息，并返回角点个数
int SQ_QOpenGLWidget::PCLCornerDetection(int Flag)
{
	int number = 0;//记录角点个数
	if (Flag == 1)//显示点云角点
	{
		if (Point3DDisplay.rows > 150000)
		{
			cv::Mat Point3DDisplayTemp;//存储降采样后的三维图案
			Point3DDisplay.copyTo(Point3DDisplayTemp);
			Point3DDisplayTemp = pointcloud->PCLDecreaseSampleToMat(Point3DDisplayTemp, 0.0000001);//降采样速度快
			//qDebug() << Point3DDisplayTemp.rows;//输出降采样后的个数
			Corner3DMat = pointcloud->PCLHarris3DToMat(Point3DDisplayTemp);//获取角点
		}
		else
		{
			Corner3DMat = pointcloud->PCLHarris3DToMat(Point3DDisplay);//获取角点
		}
		flag_corner_end = 1;//为1表示角点识别程序结束
		//提示角点识别结束
		QMessageBox message(QMessageBox::Information, "Information", "success!");
		message.exec();

		number = Corner3DMat.rows;//记录角点个数
		flag_corner_show = 1;//需要显示角点信息
		update();
	}
	else//不显示点云角点
	{	
		flag_corner_show = 0;//不需要显示角点信息
		number = 0;//记录角点个数
		update();
	}
	return number;
}


//旋转角度标准化
void SQ_QOpenGLWidget::normalizeAngle(GLfloat &angle)
{
	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
}

//装载纹理
void SQ_QOpenGLWidget::loadTextures()
{
	QImage tex, buf;
	if (!buf.load(".\\..\\Texture\\wenli.png"))
	{
		qWarning("Cannot open the image...");
		QImage dummy(128, 128, QImage::Format_RGB32);//当没找到所需打开的图片时，创建一副128*128大小，深度为32位的位图
		dummy.fill(Qt::green);
		buf = dummy;
	}
	tex = QGLWidget::convertToGLFormat(buf);//将Qt图片的格式buf转换成opengl的图片格式tex
	glGenTextures(1, &texture);//开辟一个纹理内存，内存指向texture[0]
	glBindTexture(GL_TEXTURE_2D, texture);//将创建的纹理内存指向的内容绑定到纹理对象GL_TEXTURE_2D上，经过这句代码后，以后对
	//GL_TEXTURE_2D的操作的任何操作都同时对应与它所绑定的纹理对象
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());//开始真正创建纹理数据
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//当所显示的纹理比加载进来的纹理小时，采用GL_LINEAR的方法来处理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//当所显示的纹理比加载进来的纹理大时，采用GL_LINEAR的方法来处理
}

//把容器转成一个矩阵
cv::Mat SQ_QOpenGLWidget::QVectorToMat(QVector<cv::Mat> Point3D)
{
	cv::Mat Point3DResult(0, 3, CV_32FC1);
	for (int i = 0; i < Point3D.size(); i++)
	{
		Point3DResult = MergeRows(Point3DResult, Point3D[i]);
	}
	return Point3DResult;
}


//矩阵拼接-A=[A;B]
cv::Mat SQ_QOpenGLWidget::MergeRows(cv::Mat A, cv::Mat B)
{
	int totalRows = A.rows + B.rows;
	cv::Mat mergedDescriptors(totalRows, A.cols, A.type());
	cv::Mat submat = mergedDescriptors.rowRange(0, A.rows);
	A.copyTo(submat);
	submat = mergedDescriptors.rowRange(A.rows, totalRows);
	B.copyTo(submat);
	return mergedDescriptors;
}

//置为单位阵
cv::Mat SQ_QOpenGLWidget::UnitMat()
{
	cv::Mat RotTransMatTemp(4, 4, CV_32FC1);//暂存旋转平移矩阵 4*4
	float RotTransArray[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			RotTransMatTemp.at<float>(i, j) = RotTransArray[i][j];
		}
		return RotTransMatTemp;
	//RotTransMatTemp.copyTo(AccRotMat);//深拷贝
}

//求向量的模
float SQ_QOpenGLWidget::NormOfVector(cv::Point3f A)
{
	float Norm = sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
	return Norm;
}

//求点P到直线a的距离
//A、B:是直线a上的两个点
//m:直线的法向量
//d:向量AP在直线a上垂直投影的距离
//h:点P到直线a的距离
float SQ_QOpenGLWidget::PointToLineDistance(cv::Point3f P, cv::Point3f A, cv::Point3f B)
{
	cv::Point3f m = A - B;
	cv::Point3f AP = P - A;
	float d = abs(m.dot(AP)) / (NormOfVector(m));
	float h = sqrt(NormOfVector(AP) * NormOfVector(AP) - d*d);
	return h;
}

//求距离直线最近的点的坐标
//只判断Z大于0的点
//number取1
cv::Mat SQ_QOpenGLWidget::PointDistanceShort(cv::Mat Point3D, cv::Point3f A, cv::Point3f B)
{
	cv::Mat PointReault(1, 3, CV_32FC1, cv::Scalar(0));
	int flag_first = 0;
	float min_dis = 0;
	int Number = 0;
	cv::Point3f P;
	float dis = 0;
	for (int i = 0; i < Point3D.rows; i++)
	{
		if (Point3D.at<float>(i, 2)>0)
		{
			P.x = Point3D.at<float>(i, 0);
			P.y = Point3D.at<float>(i, 1);
			P.z = Point3D.at<float>(i, 2);
			dis = PointToLineDistance(P, A, B);
			if (flag_first == 0)
			{
				flag_first = 1;
				min_dis = dis;
				Number = i;
			}
			else
			{				
				if (dis < min_dis)
				{
					min_dis = dis;
					Number = i;
				}
			}
		}
	}
	PointReault.at<float>(0, 0) = Point3D.at<float>(Number, 0);
	PointReault.at<float>(0, 1) = Point3D.at<float>(Number, 1);
	PointReault.at<float>(0, 2) = Point3D.at<float>(Number, 2);
	for (int i = 0; i < PointReault.rows; i++)
	{
		qDebug() << PointReault.at<float>(i, 0) << "," << PointReault.at<float>(i, 1) << "," << PointReault.at<float>(i, 2);
	}
	return PointReault;
}
