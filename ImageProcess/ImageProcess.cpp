#include "ImageProcess.h"
//#include <QtCore/qmath.h> 

ImageProcess::ImageProcess(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);
	//��άͼ����ʼ��
	OpenGL_ui = new SQ_QOpenGLWidget(this);
	//ͼƬ���ų�ʼ��
	Image_ui = new SQ_ImageZooming(ui.ImageShow, this);
	Image_ui->ui = &ui;
	//Image_ui->setFrameStyle(QFrame::Panel);
	Image_ui->setGeometry(QRect(20, 95, 600, 600));

	//Image_ui->ImageShow_0_X = ui.ImageShow->geometry().topLeft().x();//�洢��ǩ���Ͻǵĳ�ʼλ��
	//Image_ui->ImageShow_0_Y = ui.ImageShow->geometry().topLeft().y();
	Image_ui->ImageShow_0_X = 0;//�����Label�����Ͻǵ�����Ϊ��0��0������˱�ǩ���Ͻǵĳ�ʼλ�ü�¼Ϊ��0��0������
	Image_ui->ImageShow_0_Y = 0;

	Image_ui->setMouseTracking(true);//ʹ�ܹ��׷��

	//.stl�ļ����ó�ʼ��
	stlread = new SQ_StlRead();

	//���ݿ�
	Mysql_ui = new SQ_Mysql();
	Mysql_ui->main_ui = &ui;

	//����
	About_ui = new SQ_About();

	//���ƴ���
	pointcloud = new SQ_PointCloud();

	//��Ԫ��
	quaternion = new SQ_Quaternion();

	ui.ImageShow->setFocusPolicy(Qt::StrongFocus);//����TAB,������Ӧ�����¼�

	/*CentrolWIdget��QMainWindow�����࣬����������Ӧ����¼���ֻ�ᴥ�������mouseMoveEvent��
	����C++�̳к����ص�ԭ����������ҲҪsetMouseTracking(true); �������������Ӧ����¼���
	�ؼ���ĳ�����ؼ���������ÿؼ����丸�ؼ�������Ҳ��ҪsetMouseTracking(true);*/
	ui.centralWidget->setMouseTracking(true);
	setMouseTracking(true);

	//ui.OpenGLWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);//��������Label��Button�ϾͲ�׽���������

	//���Ӽ���ͼ��ť�ĵ���źźͱ�ǩ����ļ���ͼ���,
	connect(this->ui.OpenImage, SIGNAL(clicked()), this->Image_ui, SLOT(OpenImageEvent()));
	connect(this->ui.SaveImage, SIGNAL(clicked()), this->Image_ui, SLOT(SaveImageEvent()));
	connect(this->ui.ImageRecover, SIGNAL(clicked()), this->Image_ui, SLOT(ImageRecoverEvent()));

	//����
	connect(this->ui.About, SIGNAL(triggered()), this, SLOT(ImageProcess_About()));
	//���ݿ�
	connect(this->ui.Database, SIGNAL(triggered()), this, SLOT(ImageProcess_Database()));
	//��ѡ��
	connect(this->ui.KeyPoint, SIGNAL(stateChanged(int)), this, SLOT(KeyPointChange(int)));//�ؼ���
	

	//������ʱ��
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

//�ؼ���
void ImageProcess::KeyPointChange(int state)
{
	int number = 0;
	if (flag_cloud == 1)//������ǵ�������ĵ�������ʱ����Ч
	{
		if (state == Qt::Checked) // "ѡ��"
		{
			number = OpenGL_ui->PCLCornerDetection(1);//�����Ƿ���ʾ�ǵ���Ϣ�������ؽǵ����
			ui.KeyPointNumber->setText("PointN=" + QString::number(int(PointNumber), 10) + ",KeyN=" + QString::number(int(number), 10));
		}
		else // δѡ�� - Qt::Unchecked
		{
			number = OpenGL_ui->PCLCornerDetection(0);//�����Ƿ���ʾ�ǵ���Ϣ�������ؽǵ����
			ui.KeyPointNumber->setText("PointN=" + QString::number(int(PointNumber), 10));
		}
	}	
}


//��ʱ��
void ImageProcess::onTimeout()
{
	/*Cursor_Opengl cursor_opengl;
	cursor_opengl = OpenGL_ui->GetCursor();
	int cursor_opengl_x = cursor_opengl.cursor_opengl_x,
		cursor_opengl_y = cursor_opengl.cursor_opengl_y;
	qDebug() << cursor_opengl_x << cursor_opengl_y;*/
}

//����
void ImageProcess::ImageProcess_About()
{
	if (About_ui != NULL)
	{
		//QMessageBox::warning(NULL, QStringLiteral("��ʾ"), "open ok", QMessageBox::Yes);
		About_ui->show();
	}
}

//���ݿ�
void ImageProcess::ImageProcess_Database()
{
	if (Mysql_ui != NULL)
	{
		Mysql_ui->show();
		Mysql_ui->Connect();//�������ݿ�
	}
}




//������¼�
//��SQ_ImageZooming�еİ�������
void ImageProcess::mousePressEvent(QMouseEvent *event)
{
	switch (event->button())
	{
		case Qt::LeftButton:{
				
			break; }
		case Qt::RightButton:{								
				
			break; }
		case Qt::MidButton:{
			
			break; }
		default:break;
	}
}

//�����¼�����Ҫ�Ȱ���TAB, �ٰ�����������������Ӧ�����¼�
void ImageProcess::keyPressEvent(QKeyEvent *e)
{
	//if (e->key() == Qt::Key_W)
	//	qDebug() << "wwwwwwwwwwwwwwwwwwwwwwwwwwww";
	//if (e->key() == Qt::Key_S)
	//	qDebug() << "sssssssssssssssssssssssss";
}

//����ƶ�
void ImageProcess::mouseMoveEvent(QMouseEvent *event)
{

}

//��ʾ3D����-PCD
void ImageProcess::on_OpenCloudPCD_clicked()
{
	ui.Message->setText("");//�����ʾ
	ui.KeyPointNumber->setText("PointN=" + QString::number(0, 10));
	QString OpenStlPath = QFileDialog::getOpenFileName(this, tr("OpenPath"), ".\\..\\PCD", tr("(*.pcd)"));
	if (OpenStlPath.isEmpty())//���·��Ϊ��
	{
		ui.Message->setText(QString::fromLocal8Bit("·��Ϊ�գ�"));
	}
	else
	{
		flag_cloud = 1;//Ϊ1��ʾ�������
		ui.Message->setText(OpenStlPath);//��ʾ�ļ�·��
		cv::Mat Point3D = pointcloud->PCLReadPCDToMat(OpenStlPath);//��ȡPCD�ļ�	
		Point3D = stlread->ChangeCenterRange(Point3D, 4);
		Point3DSave = Point3D;//�洢��Ҫ����ĵ���
		Point3DDepthImage = Point3D;//�洢��Ҫת��Ϊ���ͼ�ĵ�������
		//cv::Mat Point3D = pointcloud->InitCube(0.1);
		flag_cloud = 1;//ѡ�񵥸�����ĵ���
		ui.KeyPoint->setCheckState(Qt::Unchecked);//���ø�ѡ��Ϊδѡ��
		ui.KeyPointNumber->setText(QString::number(int(0), 10));//��ʾ�ǵ����Ϊ0
		flag_arm = 0;//δѡ���е��
		////////////////horizontalSliderStart();//�������ʼ��
		//timer->start(300); //������ʱ��
		PointNumber = Point3D.rows;//��¼���Ƹ���
		ui.KeyPointNumber->setText("PointN=" + QString::number(int(PointNumber), 10));
		OpenGL_ui->Display3D(Point3D, 4);//��ʾ����
	}
}

//��ʾ����ͼ��-STL
void ImageProcess::on_OpenCloudSTL_clicked()
{
	ui.Message->setText("");//�����ʾ
	ui.KeyPointNumber->setText("PointN=" + QString::number(0, 10));
	QStringList OpenStlPath = QFileDialog::getOpenFileNames(this, tr("StlOpenPath"), ".\\..\\STL", tr("(*.stl)"));//��ȡ���.stl�ļ�
	if (OpenStlPath.isEmpty())//���·��Ϊ��
	{
		ui.Message->setText(QString::fromLocal8Bit("·��Ϊ�գ�"));
	}
	else
	{
		if (OpenStlPath.size() == 19 || OpenStlPath.size() == 13)//�����е�۵Ĳ���
		{
			flag_cloud = 0;//δѡ�񵥸�����ĵ���
			////////////////horizontalSliderStart();//�������ʼ��
			GetArmInfo(OpenStlPath, 4, OpenStlPath.size());//��ȡ��е�۵ĵ�������
			flag_arm = 1;//ѡ���е��
		}
		else
		{
			flag_cloud = 1;//ѡ�񵥸�����ĵ���
			ui.KeyPoint->setCheckState(Qt::Unchecked);//���ø�ѡ��Ϊδѡ��
			ui.KeyPointNumber->setText(QString::number(int(0), 10));//��ʾ�ǵ����Ϊ0
			//QTime timedebuge;//����һ��ʱ�Ӷ���
			//timedebuge.start();//��ʼ��ʱ
			flag_arm = 0;//δѡ���е��
			////////////////horizontalSliderStart();//�������ʼ��
			cv::Mat Point3D = stlread->PointCloudInfo(OpenStlPath);//��ȡ��������
			Point3DSave = Point3D;//�洢��Ҫ����ĵ���
			Point3DDepthImage = Point3D;//�洢��Ҫת��Ϊ���ͼ�ĵ�������
			//timer->start(300);//������ʱ��
			PointNumber = Point3D.rows;//��¼���Ƹ���
			ui.KeyPointNumber->setText("PointN=" + QString::number(int(PointNumber), 10));	
			OpenGL_ui->Display3D(Point3D, 4);//��ʾ����
			//qDebug() << "ALL" << timedebuge.elapsed() << "ms";//�����ʱ

		}
	}
}

//��ʾ.stl�ļ��е���άͼ��
void ImageProcess::on_OpenStl_clicked()
{
	flag_cloud = 0;//Ϊ1��ʾ�������
	ui.Message->setText("");//�����ʾ
	QStringList OpenStlPath = QFileDialog::getOpenFileNames(this, tr("StlOpenPath"), ".\\..\\STL", tr("(*.stl)"));//��ȡ���.stl�ļ�
	//QString OpenStlPath = QFileDialog::getOpenFileName(this, tr("StlOpenPath"), ".\\..\\STL", tr("(*.stl)"));
	if (OpenStlPath.isEmpty())//���·��Ϊ��
	{
		ui.Message->setText(QString::fromLocal8Bit("·��Ϊ�գ�"));
	}
	else
	{
		flag_cloud = 0;//δѡ�񵥸�����ĵ���
		if (OpenStlPath.size() == 19 || OpenStlPath.size() == 13)//�����е�۵Ĳ���
		{
			////////////////horizontalSliderStart();//�������ʼ��		
			GetArmInfo(OpenStlPath, 2, OpenStlPath.size());//��ȡ��е�۵�����������
			flag_arm = 1;//ѡ���е��
		}
		else
		{		
			flag_arm = 0;//δѡ���е��
			////////////////horizontalSliderStart();//�������ʼ��
			cv::Mat Point3D = stlread->TrianglePatchInfo(OpenStlPath);//��ȡ����������
			OpenGL_ui->Display3D(Point3D, 2);//��ʾ��άͼ��
		}		
	}
}

//��ȡ��е�۵�����
void ImageProcess::GetArmInfo(QStringList OpenStlPath, int type, int quantity)
{
	QMap<QString, int> StlPathName;//�洢��е���ļ�����
	StlPathName.insert("Base", 1); StlPathName.insert("Link1", 2); StlPathName.insert("Link2", 3);
	StlPathName.insert("Link3", 4); StlPathName.insert("Link4", 5); StlPathName.insert("Link5", 6);
	StlPathName.insert("Link6", 7); StlPathName.insert("Cube1", 8); StlPathName.insert("Cube2", 9);
	StlPathName.insert("Cube3", 10); StlPathName.insert("Cube4", 11); StlPathName.insert("Cube5", 12);
	StlPathName.insert("Cube6", 13); StlPathName.insert("Axial1", 14); StlPathName.insert("Axial2", 15);
	StlPathName.insert("Axial3", 16); StlPathName.insert("Axial4", 17); StlPathName.insert("Axial5", 18);
	StlPathName.insert("Axial6", 19);
	QVector<cv::Mat> ArmPoint3D;//�洢��е�۵�ԭʼ����--7������
	cv::Mat ArmPoint3DArray[7];
	cv::Mat Point3DAll(0, 3, CV_32FC1);//�洢������е�۵���άͼ������
	cv::Mat Point3D;//�ݴ��ȡ����ԭʼ��άͼ������
	//ǰ6��Ϊ��������ϵ��ԭ��--��6��Ϊ����ת���������
	cv::Mat ArmCenterRotationAxis(12, 3, CV_32FC1, cv::Scalar::all(0));//�洢��е��6���ؽڵ�����ϵ��ԭ���Լ���Ӧ��ת���᷽��
	CenterPoint ArmCenterPointArray[12];
	CenterPoint_Range centerPoint_range;//�洢������е�۵����ĵ�����������
	CenterPoint centerpoint;//�洢���ĵ�����
	int number;//�ļ����Ʊ��
	QList<QString> PathTempSplit;//�洢·���ָ���
	QString PathTempSplitLast;//�洢��е���㲿�ݵ�����
	QStringList OpenStlPathOne;//��.stl�ļ�������ת����QStringList
	for (int i = 0; i < quantity; i++)
	{
		PathTempSplit = OpenStlPath[i].split('/');//�洢·���ָ���
		PathTempSplitLast = PathTempSplit[PathTempSplit.size() - 1].split('.')[0];//�洢��е���㲿�ݵ�����				
		OpenStlPathOne.append(OpenStlPath[i]);//��.stl�ļ�������ת����QStringList
		number = StlPathName.value(PathTempSplitLast);//��ȡ�ļ����Ʊ��

		if (type == 2)
			Point3D = stlread->TrianglePatchOriginalInfo(OpenStlPathOne);//��ȡԭʼ������������
		if (type == 4)
			Point3D = stlread->PointCloudOriginalInfo(OpenStlPathOne);//��ȡԭʼ�ĵ�������

		OpenStlPathOne.clear();//���
		if (number >= 1 && number <= 7)//��е�۵��㲿��
		{
			ArmPoint3DArray[number - 1] = Point3D;
		}
		if (number >= 8 && number <= quantity)//��е�۵����ĵ������Լ���Ӧ��ת���᷽��
		{
			centerpoint = stlread->GetCenterPointOnly(Point3D, type);
			ArmCenterPointArray[number - 8] = centerpoint;
		}
	}

	for (int i = 0; i < 7; i++)
	{
		Point3DAll = stlread->MergeRows(Point3DAll, ArmPoint3DArray[i]);//�洢������е�۵���άͼ������
	}
	//qDebug() << "point number" << Point3DAll.rows;//�����ʱ

	centerPoint_range = stlread->GetCenterPoint(Point3DAll, type);//�洢������е�۵����ĵ�����������

	for (int i = 0; i < 7; i++)
	{
		ArmPoint3D.append(stlread->ChangeCenterRange(ArmPoint3DArray[i], centerPoint_range, type));//��ÿ����е���㲿������������ƶ������Ŵ���
	}
	for (int i = 0; i < quantity - 7; i++)
	{
		//��ÿ����е���㲿�������ĵ���������ƶ������Ŵ���
		ArmCenterRotationAxis.at<float>(i, 0) = (ArmCenterPointArray[i].center_x - centerPoint_range.center_x) / centerPoint_range.maxlength;
		ArmCenterRotationAxis.at<float>(i, 1) = (ArmCenterPointArray[i].center_y - centerPoint_range.center_y) / centerPoint_range.maxlength;
		ArmCenterRotationAxis.at<float>(i, 2) = (ArmCenterPointArray[i].center_z - centerPoint_range.center_z) / centerPoint_range.maxlength;
	}
	if (quantity == 19)
	{
		//�洢��е��6���ؽڶ�Ӧ��ת���᷽��
		for (int i = 0; i < 6; i++)
		{
			ArmCenterRotationAxis.at<float>(i + 6, 0) = ArmCenterRotationAxis.at<float>(i + 6, 0) - ArmCenterRotationAxis.at<float>(i, 0);
			ArmCenterRotationAxis.at<float>(i + 6, 1) = ArmCenterRotationAxis.at<float>(i + 6, 1) - ArmCenterRotationAxis.at<float>(i, 1);
			ArmCenterRotationAxis.at<float>(i + 6, 2) = ArmCenterRotationAxis.at<float>(i + 6, 2) - ArmCenterRotationAxis.at<float>(i, 2);
		}
	}
	else//��ʱ��ת�������������ƽ��
	{		
		//0��һ��ת���ؽ�--Z
		//1�ڶ���ת���ؽ�--Y
		//2������ת���ؽ�--Y
		//3���ĸ�ת���ؽ�--X
		//4�����ת���ؽ�--Z
		//5������ת���ؽ�--X
		ArmCenterRotationAxis.at<float>(6, 2) = 1;
		ArmCenterRotationAxis.at<float>(7, 1) = 1;
		ArmCenterRotationAxis.at<float>(8, 1) = 1;
		ArmCenterRotationAxis.at<float>(9, 0) = 1;
		ArmCenterRotationAxis.at<float>(10, 2) = 1;
		ArmCenterRotationAxis.at<float>(11, 0) = 1;
	}
	
	OpenGL_ui->GetCenterPoint(ArmCenterRotationAxis);//�������ĵ������Լ���Ӧ��ת���᷽��

	OpenGL_ui->Display3DArm(ArmPoint3D, type);//��ʾ��е��

}


//�ָ���άԭʼͼ��
void ImageProcess::on_ThreeDRecover_clicked()
{
	//////QString OpenStlPath = QFileDialog::getOpenFileName(this, tr("StlOpenPath"), ".\\..\\STL", tr("(*.stl)"));
	//////if (OpenStlPath.isEmpty())//���·��Ϊ��
	//////{
	//////	ui.Message->setText(QString::fromLocal8Bit("·��Ϊ�գ�"));
	//////}
	//////else
	//////{
	//////	cv::Mat Point3D = stlread->StlPointInfo(OpenStlPath.toLatin1().data(), 4);//��ȡδȥ�ص�ԭʼ����
	//////	cv::Mat Point3DDecrease = pointcloud->PCLDecreaseSampleToMat(Point3D, 0.5);//������

	//////	Point3D = stlread->ChangeCenterRange(Point3D, 4);//�ı����ĵ㼰��С
	//////	Point3DDecrease = stlread->ChangeCenterRange(Point3DDecrease, 4);//�ı����ĵ㼰��С

	//////	Point3D = quaternion->TransScaleMat(Point3D,300, 300, 0.1);
	//////	Point3DDecrease = quaternion->TransScaleMat(Point3DDecrease,300, 300, 0.1);
	//////
	//////	pointcloud->PCLShow(Point3D, Point3DDecrease);
	//////}

	
	/************************************��ʾ���ƺͷ�����**********************************************/
	//cv::Mat Point3D(4, 3, CV_32FC1);//ԭʼ�ĵ���
	//float Point_array[4][3] = { { 1, 1, 0 }, { 1, -1,0 }, { -1, 1, 0 }, { -1, -1, 0 }};
	//for (int i = 0; i < Point3D.rows; i++)
	//	for (int j = 0; j < Point3D.cols; j++)
	//		Point3D.at<float>(i, j) = Point_array[i][j];
	//Point3D = stlread->ChangeCenterRange(Point3D, 4);//�ı����ĵ㼰��С
	//cv::Mat Point3DNormal(Point3D.rows*2, 3, CV_32FC1);//ǰ���ǵ��ƣ������Ƿ�����
	//for (int i = 0; i < Point3D.rows; i++)
	//{
	//	Point3DNormal.at<float>(i, 0) = Point3D.at<float>(i, 0);
	//	Point3DNormal.at<float>(i, 1) = Point3D.at<float>(i, 1);
	//	Point3DNormal.at<float>(i, 2) = Point3D.at<float>(i, 2);
	//}
	//for (int i = Point3D.rows; i < Point3DNormal.rows; i++)
	//{
	//	Point3DNormal.at<float>(i, 0) = 0;
	//	Point3DNormal.at<float>(i, 1) = 0;
	//	Point3DNormal.at<float>(i, 2) = 0.5;
	//}
	//OpenGL_ui->Display3D(Point3DNormal, 5);//��ʾ���ƺͷ�����


	////////////////horizontalSliderStart();//�������ʼ��	
	OpenGL_ui->Recover3D();//�ָ���άԭʼͼ��
}

//���ɶ�ά���ͼ
void ImageProcess::on_GetDepthImage2D_clicked()
{
	if (flag_cloud == 1)//ѡ�񵥸�����ĵ���--��ȡtxt�еĵ�������
	{
		//cv::Mat Point3D = pointcloud->InitCube(0.01);//��ʼ��������
		cv::Mat Point3D = Point3DDepthImage;//�洢��Ҫת��Ϊ���ͼ�ĵ�������

		float AngularResolution = 0.5*3.1415926/180.0;//ת��Ϊ�Ҷ�ͼ�ķֱ���
		cv::Mat Image = pointcloud->PointXYZToDepthImage2D(Point3D, AngularResolution);//��ȡ��ά���ͼ
		ImageRangePara imageRangeParaGlobal = pointcloud->InitImageRangePara(Point3D, AngularResolution);//������������		
		cv::Mat DepthRowColValue = pointcloud->GetDepthRowColValue();//��ȡÿ�����ƴ洢������
		cv::Mat PointNormal(Point3D.rows, Point3D.cols, CV_32FC1, cv::Scalar(0));//�洢ÿ�����Ӧ�ķ�������Ϣ

		//////************************��÷�����*********************************
	/*	qwx_NormalVector.setImage(Image);
		qwx_NormalVector.compute();
		cv::Mat NormalMat = qwx_NormalVector.Getnormalvectors();*/

		cv::Mat NormalMat(Image.rows, Image.cols, CV_32FC3, cv::Scalar(0));
		for (int i = 0; i < Image.rows; i++)
			for (int j = 0; j < Image.cols; j++)
			{
				NormalMat.at<cv::Vec3f>(i, j)[0] = 1;
				NormalMat.at<cv::Vec3f>(i, j)[1] = 10;
				NormalMat.at<cv::Vec3f>(i, j)[2] = 1;
			}
		/////***************************END************************************

		float normalize = 0;
		for (int i = 0; i < Point3D.rows; i++)
		{
			normalize = 6 * sqrt(NormalMat.at<cv::Vec3f>(DepthRowColValue.at<int>(i, 0), DepthRowColValue.at<int>(i, 1))[0] * NormalMat.at<cv::Vec3f>(DepthRowColValue.at<int>(i, 0), DepthRowColValue.at<int>(i, 1))[0] +
				NormalMat.at<cv::Vec3f>(DepthRowColValue.at<int>(i, 0), DepthRowColValue.at<int>(i, 1))[1] * NormalMat.at<cv::Vec3f>(DepthRowColValue.at<int>(i, 0), DepthRowColValue.at<int>(i, 1))[1] +
				NormalMat.at<cv::Vec3f>(DepthRowColValue.at<int>(i, 0), DepthRowColValue.at<int>(i, 1))[2] * NormalMat.at<cv::Vec3f>(DepthRowColValue.at<int>(i, 0), DepthRowColValue.at<int>(i, 1))[2] );
			PointNormal.at<float>(i, 0) = NormalMat.at<cv::Vec3f>(DepthRowColValue.at<int>(i, 0), DepthRowColValue.at<int>(i, 1))[0] / normalize;
			PointNormal.at<float>(i, 1) = NormalMat.at<cv::Vec3f>(DepthRowColValue.at<int>(i, 0), DepthRowColValue.at<int>(i, 1))[1] / normalize;
			PointNormal.at<float>(i, 2) = NormalMat.at<cv::Vec3f>(DepthRowColValue.at<int>(i, 0), DepthRowColValue.at<int>(i, 1))[2] / normalize;		
		}

		cv::Mat Point3DNormal = stlread->MergeRows(Point3D, PointNormal);
		for (int i = 0; i < Point3D.rows; i++)
		{
			Point3DNormal.at<float>(i + Point3D.rows, 0) += Point3DNormal.at<float>(i, 0);
			Point3DNormal.at<float>(i + Point3D.rows, 1) += Point3DNormal.at<float>(i, 1);
			Point3DNormal.at<float>(i + Point3D.rows, 2) += Point3DNormal.at<float>(i, 2);
		}
		
		OpenGL_ui->Display3D(Point3DNormal, 5);//��ʾ���ƺͷ�����		
		cv::Mat ImageMat(Image.rows, Image.cols, CV_8UC3, cv::Scalar::all(0));
		for (int i = 0; i < Image.rows; i++)
		{
			for (int j = 0; j < Image.cols; j++)
			{
				ImageMat.at<cv::Vec3b>(i, j)[0] = Image.at<uchar>(i, j);
				ImageMat.at<cv::Vec3b>(i, j)[1] = Image.at<uchar>(i, j);
				ImageMat.at<cv::Vec3b>(i, j)[2] = Image.at<uchar>(i, j);
			}
		}
		Image_ui->ShowDepthImage2D(ImageMat);

		//PCL�������ɶ�ά���ͼ
		cv::Mat Ima = pointcloud->PCLPointXYZToDepthImage2D(Point3D, AngularResolution);//��ȡ��ά���ͼ
		cv::namedWindow("INOUT", CV_WINDOW_AUTOSIZE);
		cv::imshow("INOUT", Ima);

	}	
	//QString ImageOpenPath = QFileDialog::getOpenFileName(this, tr("ImageOpenPath"), ".\\..\\Image", tr("(*.png *.bmp *.jpg *.tif *.gif *.jpeg)"));//��ȡͼƬ·����Ϣ
	//cv::Mat Image = cv::imread(ImageOpenPath.toLatin1().data(), 1);
	//Image_ui->ShowDepthImage2D(Image);
}




//���Ƶ���ͼ--PlotCloud(Point3D);
void ImageProcess::PlotCloud(cv::Mat Point3D)
{
	//cv::Mat CloudDeWeightPoint3D = PointCloudDeWeight(Point3D);//����ȥ��
	cv::Mat Point3DResult = stlread->ChangeCenterRange(Point3D, 4);
	OpenGL_ui->Display3D(Point3DResult, 4);//������
}


//���������߶�--PlotLine(Point3D);
void ImageProcess::PlotLine(cv::Mat Point3D)
{
	cv::Mat Point3DResult = stlread->ChangeCenterRange(Point3D, 2);
	OpenGL_ui->Display3D(Point3DResult, 1);//���߶�--��������
}

//�����������
void ImageProcess::on_SaveCloudData_clicked()
{
	////cv::Mat Point3D = stlread->PointALLProcessInfo(OpenStlPath);//��ȡ��ȡԭʼ��.stl���ݣ����������������������������
	//cv::Mat Point3D = pointcloud->InitFace('Y',0.001);//��ʼ��ƽ��
	if (Point3DSave.rows > 1)
	{
		cv::Mat Point3D = Point3DSave;//�洢��Ҫ����ĵ���
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy-MM-dd hh-mm-ss");
		QString path = QString(".\\..\\TXT\\txt-") + QString(current_date) + QString(".txt");
		SavePointInfo(Point3D, path);//��������		
		QMessageBox::warning(NULL, QStringLiteral("�������"), "save ok", QMessageBox::Yes);
	}
}

//��ȡ��������
void ImageProcess::on_ReadCloudData_clicked()
{
	QString OpenStlPath = QFileDialog::getOpenFileName(this, tr("StlOpenPath"), ".\\..\\TXT", tr("(*.txt)"));
	cv::Mat Point3D = ReadPointInfo(OpenStlPath);
	////Point3D = stlread->ChangeCenterRange(Point3D, 4);//�˴�����Ҫ
	Point3DDepthImage = Point3D;//�洢��Ҫת��Ϊ���ͼ�ĵ�������
	flag_cloud = 1;//Ϊ1��ʾ�������
	OpenGL_ui->Display3D(Point3D, 4);//��ʾ����
}

//��������
void ImageProcess::SavePointInfo(cv::Mat Point3D, QString path)
{
	QFile ExpandData(path);
	if (ExpandData.open(QIODevice::WriteOnly))
	{
		/*�ı�����������ڱ�������*/
		QTextStream Out(&ExpandData);
		/*����ո�ĺô�����������ʽ��ȡǡ�����෴�Ĳ���������һ��������ٶԲ����Ķ�ȡ*/
		for (int i = 0; i < Point3D.rows; i++)
		{
			for (int j = 0; j < Point3D.cols; j++)
			{
				/*if (Point3D.at<float>(i, j) >= 0 && Point3D.at<float>(i, j) < 0.01)
					Out << 0;
				else*/
					Out << Point3D.at<float>(i, j);
				if (j != Point3D.cols - 1)
					Out << " ";
			}
			Out << "\r\n";
		}
		ExpandData.close();
	}
}

//��ȡ����
cv::Mat ImageProcess::ReadPointInfo(QString path)
{
	QVector<QVector<float>> vec_vec_int;
	QVector<float> vec_int;
	int count = 0;
	cv::Mat Point3D(0, 3, CV_32FC1);
	cv::Mat Point3DTemp(10000, 3, CV_32FC1);
	if (path.isEmpty())//���·��Ϊ��
	{
		ui.Message->setText(QString::fromLocal8Bit("·��Ϊ�գ�"));
	}
	else
	{
		QString str;
		QStringList list;
		QFile ExpandData(path);
		if (ExpandData.open(QIODevice::ReadOnly))
		{
			/*�ı�����������ڱ�������*/
			QTextStream In(&ExpandData);
			while (!In.atEnd()) //δ���ļ�β
			{			
				 str = In.readLine();
				 list = str.split(" ");
				 Point3DTemp.at<float>(count, 0) = list[0].toFloat();
				 Point3DTemp.at<float>(count, 1) = list[1].toFloat();
				 Point3DTemp.at<float>(count, 2) = list[2].toFloat();
				 count++;
				 if (count == 10000)
				 {
					 count = 0;
					 Point3D = stlread->MergeRows(Point3D, Point3DTemp);
				 }		
			}
			ExpandData.close();
		}
	}
	Point3D = stlread->MergeRows(Point3D, Point3DTemp.rowRange(0,count));
	/*for (int i = 0; i < Point3D.rows; i++)
		qDebug() << Point3D.at<float>(i, 0) << Point3D.at<float>(i, 1) << Point3D.at<float>(i, 2);*/
	return Point3D;
}
