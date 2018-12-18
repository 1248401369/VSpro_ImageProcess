#include "sq_qopenglwidget.h"


SQ_QOpenGLWidget::SQ_QOpenGLWidget(QWidget *parent)
: QOpenGLWidget(parent)
{
	setMouseTracking(true);//ʹ����겶��
	//Quaternion�ļ����ó�ʼ��
	Quaternion = new SQ_Quaternion();
	//���ƴ���
	pointcloud = new SQ_PointCloud();

	AccRotMat = UnitMat();

	near_value = 2.0;//��̾���--���������Ļ����̾���
	// ����OpenGL�İ汾��Ϣ
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
	initializeOpenGLFunctions();//��ʼ��OpenGL����
	setGeometry(640, 95, 600, 560);//����λ�úʹ�С
	//ʹ��������Ҫ�����
	//loadTextures();//����
	//glEnable(GL_TEXTURE_2D);//�������2D������--����
	glShadeModel(GL_SMOOTH);//������Ӱƽ��ģʽ
	glClearColor(0, 0, 0, 0);//�ı䴰�ڵı�����ɫ
	glClearDepth(1.0);//������Ȼ���
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glDepthFunc(GL_LEQUAL);//������Ȳ�������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//����͸��У��
	glRenderMode(GL_RENDER);//��Ⱦģʽ,Ĭ��
}

void SQ_QOpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, ShowRatio); //������Ļ
	//gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	float ColorArray[7][3] = { { 0, 1, 0 }, { 1, 0.5, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 0.8, 0.5, 0 } };
	//glBindTexture(GL_TEXTURE_2D, texture);//����

	//glColor3f(0.0f, 1.0f, 0.0f);//��ɫ
	//glColor3f(1.0f, 0.5f, 0.0f);//��ɫ
	//glColor3f(1.0f, 0.0f, 0.0f);//��ɫ
	//glColor3f(1.0f, 1.0f, 0.0f);//��ɫ
	//glColor3f(0.0f, 0.0f, 1.0f);//��ɫ
	//glColor3f(1.0f, 0.0f, 1.0f);//��ɫ

	//***********************************����������***********************************
	if (flag_display_type == 2)
	{
		glBegin(GL_TRIANGLES);
		if (flag_arm == 1)//��е��--ֱ������Point3DQVector���ݽ�����ʾ
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
				//glTexCoord2f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1));//����
				glVertex3f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1), Point3DDisplay.at<float>(i, 2));
			}
		}		
		glEnd();
	}
	//glRotatef(0, 1.0f, 0.0f, 0.0f);//��x����ת�ı���

	//***********************************���Ƶ���***********************************
	if (flag_display_type == 4)
	{
		glPointSize(1.0f);//�ڻ���֮ǰҪ����Ҫ��ز������������õ�Ĵ�СΪ5����
		glBegin(GL_POINTS);
		if (flag_arm == 1)//��е��
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
			glPointSize(1.0f);//�ڻ���֮ǰҪ����Ҫ��ز������������õ�Ĵ�СΪ5����
			glBegin(GL_POINTS);
			for (int i = 0; i < Point3DDisplay.rows; i++)
			{
				if (Point3DDisplay.at<float>(i, 2)>0)
					glColor3f(0.0f, 1.0f, 0.0f);//��ɫ
				else
					glColor3f(1.0f, 0.0f, 1.0f);//��ɫ
				glVertex3f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1), Point3DDisplay.at<float>(i, 2));
			}
			glEnd();

			glPointSize(3.0f);//�ڻ���֮ǰҪ����Ҫ��ز������������õ�Ĵ�СΪ5����
			glBegin(GL_POINTS);
			if (flag_corner_show == 1)//��Ҫ��ʾ�ǵ�
			{
				glColor3f(0.0f, 1.0f, 0.0f);//��ɫ
				for (int i = 0; i < Corner3DMat.rows; i++)
				{
					glVertex3f(Corner3DMat.at<float>(i, 0), Corner3DMat.at<float>(i, 1), Corner3DMat.at<float>(i, 2));
				}				
			}			
		}		
		glEnd();
	}
	//**************************************�����ƺͷ�����*********************
	if (flag_display_type == 5)
	{
		//����
		glPointSize(2.0f);//�ڻ���֮ǰҪ����Ҫ��ز������������õ�Ĵ�СΪ5����
		glBegin(GL_POINTS);
		for (int i = 0; i < Point3DDisplay.rows/2; i++)
		{
			if (Point3DDisplay.at<float>(i, 2)>0)
				glColor3f(0.0f, 1.0f, 0.0f);//��ɫ
			else
				glColor3f(1.0f, 0.0f, 1.0f);//��ɫ
			glVertex3f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1), Point3DDisplay.at<float>(i, 2));
		}		
		glEnd();

		//������
		if (flag_show_normal == 1)//Ϊ1��ʾ��ʾ
		{
			glColor3f(1.0f, 0.0f, 0.0f);//��ɫ
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
	//***********************************���������߶�***********************************
	if (flag_display_type == 1)
	{
		glColor3f(1.0f, 0.0f, 1.0f);//��ɫ
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < Point3DDisplay.rows; i++)
		{
			glVertex3f(Point3DDisplay.at<float>(i, 0), Point3DDisplay.at<float>(i, 1), Point3DDisplay.at<float>(i, 2));
		}
		glEnd();
	}

	//************************************�������ĵ�ָ����Ļ��ֱ��****************8
	if (flag_rightbutton == 1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);//��ɫ
		glPointSize(6.0f);//�ڻ���֮ǰҪ����Ҫ��ز������������õ�Ĵ�СΪ5����
		glBegin(GL_POINTS);
		for (int i = 0; i < Point3DDisplayPoint.rows; i++)
		{
			glVertex3f(Point3DDisplayPoint.at<float>(i, 0), Point3DDisplayPoint.at<float>(i, 1), Point3DDisplayPoint.at<float>(i, 2));
		}
		glEnd();
	}
	glFlush();//glFlush����֤ǰ���OpenGL��������ִ�У��������������ڻ������еȴ���

}

void SQ_QOpenGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, (GLint)width, (GLint)height);//���õ�ǰ���ӿ�  
	glMatrixMode(GL_PROJECTION);//ѡ��ͶӰ����  
	glLoadIdentity();//����ͶӰ����    
	//gluPerspective(53.0, (GLfloat)width / (GLfloat)height, 2, 100.0);//�����ӿڵĴ�С 
	//2*atan(1.0/2)*57.3
	gluPerspective(2 * atan(1.0 / near_value)*57.3, (GLfloat)width / (GLfloat)height, near_value, 100.0);//�����ӿڵĴ�С 
	glMatrixMode(GL_MODELVIEW);//ѡ��ģ�͹۲����  
	glLoadIdentity();//����ģ�͹۲����  
}

//������¼�
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
						flag_rightbutton = 1;//Ϊ1��ʾ��ʾѡ�еĵ�
						Point3DDisplayPoint = PointDistanceShort(Point3DDisplay, A, B);//�洢��Ҫ��ʾ��ֱ��
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

//����ͷ��¼�
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

//��������-�Ŵ����С��άͼ��
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
		if (flag_arm == 1)//��е��
		{			
			//��е�۵Ĺؽ�ͬʱ���ж�������
			for (int i = 0; i < 7; i++)
			{
				Point3DQVector[i] = Quaternion->TransScaleMat(Point3DQVector[i], cursor_opengl_x, cursor_opengl_y, ScaleRatio);
			}
			//Point3DDisplay = QVectorToMat(Point3DQVector);
			//��е�۵Ĺؽڵ�����ϵԭ����ж�������
  			ArmCenterPoint = Quaternion->TransScaleMat(ArmCenterPoint, cursor_opengl_x, cursor_opengl_y, ScaleRatio);
		}
		else
		{			
			//��������
			Point3DDisplay = Quaternion->TransScaleMat(Point3DDisplay, cursor_opengl_x, cursor_opengl_y, ScaleRatio);
			//ѡ���ƶ���
			Point3DDisplayPoint = Quaternion->TransScaleMat(Point3DDisplayPoint, cursor_opengl_x, cursor_opengl_y, ScaleRatio);
			//�ǵ�����
			Corner3DMat = Quaternion->TransScaleMat(Corner3DMat, cursor_opengl_x, cursor_opengl_y, ScaleRatio);
		}		
		update();
	}
}


//��ȡ��ά�������ת�Ƕ�	
void SQ_QOpenGLWidget::GetRotateAngle(float angle_1, float angle_2, float angle_3, float angle_4, float angle_5, float angle_6)
{
	acc_angle_1 += angle_1;
	acc_angle_2 += angle_2;
	acc_angle_3 += angle_3;
	acc_angle_4 += angle_4;
	acc_angle_5 += angle_5;
	acc_angle_6 += angle_6;

	//��һ��ת���ؽ�
	ArmRotTransEvery(angle_1, 0);
	//�ڶ���ת���ؽ�
	ArmRotTransEvery(angle_2, 1);
	//������ת���ؽ�
	ArmRotTransEvery(angle_3, 2);
	//���ĸ�ת���ؽ�
	ArmRotTransEvery(angle_4, 3);
	//�����ת���ؽ�
	ArmRotTransEvery(angle_5, 4);
	//������ת���ؽ�
	ArmRotTransEvery(angle_6, 5);

	//Point3DDisplay = QVectorToMat(Point3DQVector);
	update();
}

//ÿ���ؽڵ���ת����
void SQ_QOpenGLWidget::ArmRotTransEvery(float angle, int number)//number 0 1 2 3 4 5
{
	cv::Mat RotTransMat, AccRotTransLink;
	float Ox_offset, Oy_offset, Oz_offset;//��¼ԭ��֮���ƫ����
	cv::Mat MatTemp(1, 3, CV_32FC1);

	//��number+1��ת���ؽ�
	Ox_offset = ArmCenterPoint.at<float>(number, 0) ;
	Oy_offset = ArmCenterPoint.at<float>(number, 1);
	Oz_offset = ArmCenterPoint.at<float>(number, 2);
	
	//����ϵת�����Ӷ��õ��µ�����ϵ
	//1.�������ÿ���ؽ���ת�ĽǶ�ֵ
	//2.�������������ϵ����ת����--AccRotMat������������ϵ����ת����
	//3.�ƶ�ÿ���ؽ�����ϵ��ԭ��
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
	//������������嶼������������ϵ�ڵģ�����һ��������ת����ƽ�ƺ󣬿ɵõ���һ�����������ϵ����תƽ�ƾ���M
	//1.���ڶ������������ת������һ�����������ϵ�ڵ�����--���M����
	//2.����һ�����������ϵ�����ǵڶ����������������ϵ��������ת�任--��˵ڶ����������ת����
	//3.���ڶ������������ת�����������������ϵ��--���M

	//��Ҫ֪��ÿ���ؽڳ�ʼ״̬����ת��ķ�������
	RotTransMat = AccRotTransLink * Quaternion->RotMat(ArmRotationAxis.at<float>(number, 0),ArmRotationAxis.at<float>(number, 1),ArmRotationAxis.at<float>(number, 2), angle)* AccRotTransLink.inv();

	//��е�۵Ĺؽڽ�����ת����
	for (int i = number + 1; i < 7; i++)
	{
		Point3DQVector[i] = Quaternion->RotTransMat(Point3DQVector[i], RotTransMat);
	}
	//��е�۵Ĺؽڵ�����ϵԭ�������ת����
	for (int i = number + 1; i < ArmCenterPoint.rows; i++)
	{
		MatTemp = Quaternion->RotTransMat(ArmCenterPoint.rowRange(i, i + 1), RotTransMat);
		ArmCenterPoint.at<float>(i, 0) = MatTemp.at<float>(0, 0);
		ArmCenterPoint.at<float>(i, 1) = MatTemp.at<float>(0, 1);
		ArmCenterPoint.at<float>(i, 2) = MatTemp.at<float>(0, 2);
	}
}

//��ȡ���λ��
Cursor_Opengl SQ_QOpenGLWidget::GetCursor()
{
	Cursor_Opengl cursor_opengl;
	cursor_opengl.cursor_opengl_x = cursor_opengl_x;
	cursor_opengl.cursor_opengl_y = cursor_opengl_y;
	return cursor_opengl;
}

//������Ļ����õ��ӵ�ռ�����
cv::Point3f SQ_QOpenGLWidget::Get3Dpos(int x, int y)
{
	cv::Point3f cursor_in_opengl;
	cursor_in_opengl.x = (-1 + x / 300.0);
	cursor_in_opengl.y = (1 - y / 280.0);
	//cursor_in_opengl.z = (1-sqrt(cursor_in_opengl.x*cursor_in_opengl.x + cursor_in_opengl.y*cursor_in_opengl.y))/0.67;
	cursor_in_opengl.z =(-1.0)* SHOWRATIO - near_value;
	return cursor_in_opengl;
}

//����ƶ��¼�
void SQ_QOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	RotateAngle rotateAngle;
	//��¼��ǰ���λ��
	cursor_opengl_x = event->pos().x();
	cursor_opengl_y = event->pos().y();

	/******************�ƶ�����**********************/
	if (flag_left_press_release == 1)
	{
		//�洢������������ʱ�Ĺ��λ��
		cursor_left_press_x = cursor_opengl_x;
		cursor_left_press_y = cursor_opengl_y;
		flag_left_press_release = 2;
	}
	if (flag_left_press_release == 2)
	{
		//�洢����ƶ��ľ���
		move_world_x = (cursor_opengl_x - cursor_left_press_x)*0.003;
		move_world_y = (cursor_left_press_y - cursor_opengl_y)*0.003;

		if (flag_arm == 1)//��е��
		{
			//��е�۵Ĺؽ�ͬʱ����ƽ�Ʋ���
			for (int i = 0; i < 7; i++)
			{
				Point3DQVector[i] = Quaternion->RotTransMat(Point3DQVector[i], Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
			}
			//Point3DDisplay = QVectorToMat(Point3DQVector);
			//��е�۵Ĺؽ�����ϵԭ�����ƽ�Ʋ���
			ArmCenterPoint = Quaternion->RotTransMat(ArmCenterPoint, Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
		}
		else
		{
			//ƽ�Ʊ任
			Point3DDisplay = Quaternion->RotTransMat(Point3DDisplay, Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
			//��ת�Լ���ǵĵ�
			Point3DDisplayPoint = Quaternion->RotTransMat(Point3DDisplayPoint, Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
			//�ǵ�����
			Corner3DMat = Quaternion->RotTransMat(Corner3DMat, Quaternion->TransMat_Y(move_world_y) * Quaternion->TransMat_X(move_world_x));
		}

		update();

		//���´洢�Ĺ��λ��
		cursor_left_press_x = cursor_opengl_x;
		cursor_left_press_y = cursor_opengl_y;
	}
	/******************��ת����**********************/
	if (flag_mid_press_release == 1)
	{
		//�洢������������ʱ�Ĺ��λ��
		cursor_mid_press_x = cursor_opengl_x;
		cursor_mid_press_y = cursor_opengl_y;
		flag_mid_press_release = 2;
	}
	if (flag_mid_press_release == 2)
	{
		//�洢����ƶ��ľ���--�ȼ�����άͼ����Ҫ��ת�Ƕ�
		rotate_world_x = (cursor_opengl_y - cursor_mid_press_y)*0.3;
		rotate_world_y = (cursor_opengl_x - cursor_mid_press_x)*0.3;

		//��ת�Ƕȱ�׼��
		normalizeAngle(rotate_world_x);
		normalizeAngle(rotate_world_y);
	
		if (flag_arm == 1)//��е��
		{
			//������תƽ�ƾ���--���ۼƵ���תƽ�ƾ���
			AccRotMat = Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x) * AccRotMat;
			//��е�۵Ĺؽ�ͬʱ������ת����
			for (int i = 0; i < 7; i++)
			{
				Point3DQVector[i] = Quaternion->RotTransMat(Point3DQVector[i], Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
			}
			//Point3DDisplay = QVectorToMat(Point3DQVector);
			//��е�۵Ĺؽ�����ϵԭ�������ת����
			ArmCenterPoint = Quaternion->RotTransMat(ArmCenterPoint, Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
		}
		else
		{
			//��ת�任
			Point3DDisplay = Quaternion->RotTransMat(Point3DDisplay, Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
			//��ת�Լ���ǵĵ�
			Point3DDisplayPoint = Quaternion->RotTransMat(Point3DDisplayPoint, Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
			//�ǵ�����
			Corner3DMat = Quaternion->RotTransMat(Corner3DMat, Quaternion->RotMat_Y(rotate_world_y) * Quaternion->RotMat_X(rotate_world_x));
		}	
		update();

		//���´洢�Ĺ��λ��
		cursor_mid_press_x = cursor_opengl_x;
		cursor_mid_press_y = cursor_opengl_y;
	}
}

//�ָ���ʼ״̬�µ���άͼ����ʾ
void SQ_QOpenGLWidget::Recover3D()
{
	flag_show_normal = 0;//Ϊ1��ʾ��ʾ
	ShowRatio = SHOWRATIO;
	Point3DDisplayPoint = Point3DDisplayPointOriginal;//�ָ����ѡ�еĵ���
	flag_rightbutton = 0;//����ʾѡ�еĵ�
	//�ָ���е�۵�ԭʼ����
	ArmCenterPoint = ArmCenterPointOriginal;//�ָ����ĵ�����
	AccRotMat = UnitMat();//���õ�λ��
	Point3DDisplay = Point3DOriginal;//�ָ���Ҫ��ʾ��ԭʼ��ԭʼ����
	Point3DQVector = Point3DQOriginalVector;//�ָ���Ҫ��ʾ�Ļ�е�۵ĵ�ԭʼ����--Vector��ʽ
	update();
}

//��ʾ��άͼ��3DPointΪN*3�ľ���	 
void SQ_QOpenGLWidget::Display3DArm(QVector<cv::Mat> Point3D, int type)
{
	//��ʼ��ÿ���ؽڵ�ת���Ƕȵ��ۼ�ֵ
	acc_angle_1 = 0;
	acc_angle_2 = 0;
	acc_angle_3 = 0;
	acc_angle_4 = 0;
	acc_angle_5 = 0;
	acc_angle_6 = 0;

	AccRotMat = UnitMat();//���õ�λ��
	flag_arm = 1;//��ǰ�����е��
	Point3DQVector = Point3D;
	Point3DQOriginalVector = Point3D;//�洢ԭʼ����

	flag_display_type = type;//��ȡ��ʾ����
	ShowRatio = SHOWRATIO;//��ʼ���۲����
	flag_display = 1;//ȷ�ϵ�����άͼ��
	update();
}

//�洢��е�۵�6�����ĵ������Լ���ʼ��ת��
void SQ_QOpenGLWidget::GetCenterPoint(cv::Mat centerRotationAxis)
{
	cv::Mat ArmCenterPointTemp(6, 3, CV_32FC1);
	cv::Mat ArmRotationAxisTemp(6, 3, CV_32FC1);
	for (int i = 0; i < centerRotationAxis.rows / 2; i++)
	{
		//�洢���ĵ�
		ArmCenterPointTemp.at<float>(i, 0) = centerRotationAxis.at<float>(i, 0);
		ArmCenterPointTemp.at<float>(i, 1) = centerRotationAxis.at<float>(i, 1);
		ArmCenterPointTemp.at<float>(i, 2) = centerRotationAxis.at<float>(i, 2);
		//�洢��ʼ��ת��
		ArmRotationAxisTemp.at<float>(i, 0) = centerRotationAxis.at<float>(i + 6, 0);
		ArmRotationAxisTemp.at<float>(i, 1) = centerRotationAxis.at<float>(i + 6, 1);
		ArmRotationAxisTemp.at<float>(i, 2) = centerRotationAxis.at<float>(i + 6, 2);
	}
	ArmCenterPoint = ArmCenterPointTemp;//�洢���ĵ�
	ArmCenterPoint.copyTo(ArmCenterPointOriginal);//�洢ԭʼ������
	ArmRotationAxis = ArmRotationAxisTemp;//�洢��ʼ��ת��
}

//��¼��άͼ������
void SQ_QOpenGLWidget::Display3D(cv::Mat Point3D, int type)
{
	flag_rightbutton = 0;//Ϊ1��ʾ��ʾѡ�еĵ�
	flag_arm = 0;//����Ĳ��ǻ�е��
	Point3DDisplay = Point3D;
	Point3DDisplay.copyTo(Point3DOriginal);//�洢��άͼ��ԭʼ����
	flag_display_type = type;//��ȡ��ʾ����
	ShowRatio = SHOWRATIO;//��ʼ���۲����
	flag_display = 1;//ȷ�ϵ�����άͼ��
	flag_show_normal = 1;//Ϊ1��ʾ��ʾ
	//if (flag_display_type == 4)
	//{			
	//}
	update();
	return;
}

//�����Ƿ���ʾ�ǵ���Ϣ�������ؽǵ����
int SQ_QOpenGLWidget::PCLCornerDetection(int Flag)
{
	int number = 0;//��¼�ǵ����
	if (Flag == 1)//��ʾ���ƽǵ�
	{
		if (Point3DDisplay.rows > 150000)
		{
			cv::Mat Point3DDisplayTemp;//�洢�����������άͼ��
			Point3DDisplay.copyTo(Point3DDisplayTemp);
			Point3DDisplayTemp = pointcloud->PCLDecreaseSampleToMat(Point3DDisplayTemp, 0.0000001);//�������ٶȿ�
			//qDebug() << Point3DDisplayTemp.rows;//�����������ĸ���
			Corner3DMat = pointcloud->PCLHarris3DToMat(Point3DDisplayTemp);//��ȡ�ǵ�
		}
		else
		{
			Corner3DMat = pointcloud->PCLHarris3DToMat(Point3DDisplay);//��ȡ�ǵ�
		}
		flag_corner_end = 1;//Ϊ1��ʾ�ǵ�ʶ��������
		//��ʾ�ǵ�ʶ�����
		QMessageBox message(QMessageBox::Information, "Information", "success!");
		message.exec();

		number = Corner3DMat.rows;//��¼�ǵ����
		flag_corner_show = 1;//��Ҫ��ʾ�ǵ���Ϣ
		update();
	}
	else//����ʾ���ƽǵ�
	{	
		flag_corner_show = 0;//����Ҫ��ʾ�ǵ���Ϣ
		number = 0;//��¼�ǵ����
		update();
	}
	return number;
}


//��ת�Ƕȱ�׼��
void SQ_QOpenGLWidget::normalizeAngle(GLfloat &angle)
{
	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
}

//װ������
void SQ_QOpenGLWidget::loadTextures()
{
	QImage tex, buf;
	if (!buf.load(".\\..\\Texture\\wenli.png"))
	{
		qWarning("Cannot open the image...");
		QImage dummy(128, 128, QImage::Format_RGB32);//��û�ҵ�����򿪵�ͼƬʱ������һ��128*128��С�����Ϊ32λ��λͼ
		dummy.fill(Qt::green);
		buf = dummy;
	}
	tex = QGLWidget::convertToGLFormat(buf);//��QtͼƬ�ĸ�ʽbufת����opengl��ͼƬ��ʽtex
	glGenTextures(1, &texture);//����һ�������ڴ棬�ڴ�ָ��texture[0]
	glBindTexture(GL_TEXTURE_2D, texture);//�������������ڴ�ָ������ݰ󶨵��������GL_TEXTURE_2D�ϣ�������������Ժ��
	//GL_TEXTURE_2D�Ĳ������κβ�����ͬʱ��Ӧ�������󶨵��������
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());//��ʼ����������������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//������ʾ������ȼ��ؽ���������Сʱ������GL_LINEAR�ķ���������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//������ʾ������ȼ��ؽ����������ʱ������GL_LINEAR�ķ���������
}

//������ת��һ������
cv::Mat SQ_QOpenGLWidget::QVectorToMat(QVector<cv::Mat> Point3D)
{
	cv::Mat Point3DResult(0, 3, CV_32FC1);
	for (int i = 0; i < Point3D.size(); i++)
	{
		Point3DResult = MergeRows(Point3DResult, Point3D[i]);
	}
	return Point3DResult;
}


//����ƴ��-A=[A;B]
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

//��Ϊ��λ��
cv::Mat SQ_QOpenGLWidget::UnitMat()
{
	cv::Mat RotTransMatTemp(4, 4, CV_32FC1);//�ݴ���תƽ�ƾ��� 4*4
	float RotTransArray[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			RotTransMatTemp.at<float>(i, j) = RotTransArray[i][j];
		}
		return RotTransMatTemp;
	//RotTransMatTemp.copyTo(AccRotMat);//���
}

//��������ģ
float SQ_QOpenGLWidget::NormOfVector(cv::Point3f A)
{
	float Norm = sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
	return Norm;
}

//���P��ֱ��a�ľ���
//A��B:��ֱ��a�ϵ�������
//m:ֱ�ߵķ�����
//d:����AP��ֱ��a�ϴ�ֱͶӰ�ľ���
//h:��P��ֱ��a�ľ���
float SQ_QOpenGLWidget::PointToLineDistance(cv::Point3f P, cv::Point3f A, cv::Point3f B)
{
	cv::Point3f m = A - B;
	cv::Point3f AP = P - A;
	float d = abs(m.dot(AP)) / (NormOfVector(m));
	float h = sqrt(NormOfVector(AP) * NormOfVector(AP) - d*d);
	return h;
}

//�����ֱ������ĵ������
//ֻ�ж�Z����0�ĵ�
//numberȡ1
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
