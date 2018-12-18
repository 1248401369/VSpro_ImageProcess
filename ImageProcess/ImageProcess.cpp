#include "ImageProcess.h"
//#include <QtCore/qmath.h> 

ImageProcess::ImageProcess(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);
	//三维图案初始化
	OpenGL_ui = new SQ_QOpenGLWidget(this);
	//图片缩放初始化
	Image_ui = new SQ_ImageZooming(ui.ImageShow, this);
	Image_ui->ui = &ui;
	//Image_ui->setFrameStyle(QFrame::Panel);
	Image_ui->setGeometry(QRect(20, 95, 600, 600));

	//Image_ui->ImageShow_0_X = ui.ImageShow->geometry().topLeft().x();//存储标签左上角的初始位置
	//Image_ui->ImageShow_0_Y = ui.ImageShow->geometry().topLeft().y();
	Image_ui->ImageShow_0_X = 0;//光标在Label中左上角的坐标为（0，0），因此标签左上角的初始位置记录为（0，0）即可
	Image_ui->ImageShow_0_Y = 0;

	Image_ui->setMouseTracking(true);//使能光标追踪

	//.stl文件调用初始化
	stlread = new SQ_StlRead();

	//数据库
	Mysql_ui = new SQ_Mysql();
	Mysql_ui->main_ui = &ui;

	//关于
	About_ui = new SQ_About();

	//点云处理
	pointcloud = new SQ_PointCloud();

	//四元数
	quaternion = new SQ_Quaternion();

	ui.ImageShow->setFocusPolicy(Qt::StrongFocus);//按下TAB,可以响应按键事件

	/*CentrolWIdget是QMainWindow的子类，在子类上响应鼠标事件，只会触发子类的mouseMoveEvent，
	根据C++继承和重载的原理，所以子类也要setMouseTracking(true); 所以如果你想响应鼠标事件的
	控件被某个父控件包含，则该控件及其父控件或容器也需要setMouseTracking(true);*/
	ui.centralWidget->setMouseTracking(true);
	setMouseTracking(true);

	//ui.OpenGLWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);//解决鼠标在Label或Button上就捕捉不到的情况

	//连接加载图像按钮的点击信号和标签对象的加载图像槽,
	connect(this->ui.OpenImage, SIGNAL(clicked()), this->Image_ui, SLOT(OpenImageEvent()));
	connect(this->ui.SaveImage, SIGNAL(clicked()), this->Image_ui, SLOT(SaveImageEvent()));
	connect(this->ui.ImageRecover, SIGNAL(clicked()), this->Image_ui, SLOT(ImageRecoverEvent()));

	//关于
	connect(this->ui.About, SIGNAL(triggered()), this, SLOT(ImageProcess_About()));
	//数据库
	connect(this->ui.Database, SIGNAL(triggered()), this, SLOT(ImageProcess_Database()));
	//复选框
	connect(this->ui.KeyPoint, SIGNAL(stateChanged(int)), this, SLOT(KeyPointChange(int)));//关键点
	

	//开启定时器
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

//关键点
void ImageProcess::KeyPointChange(int state)
{
	int number = 0;
	if (flag_cloud == 1)//导入的是单个零件的点云数据时才有效
	{
		if (state == Qt::Checked) // "选中"
		{
			number = OpenGL_ui->PCLCornerDetection(1);//传递是否显示角点信息，并返回角点个数
			ui.KeyPointNumber->setText("PointN=" + QString::number(int(PointNumber), 10) + ",KeyN=" + QString::number(int(number), 10));
		}
		else // 未选中 - Qt::Unchecked
		{
			number = OpenGL_ui->PCLCornerDetection(0);//传递是否显示角点信息，并返回角点个数
			ui.KeyPointNumber->setText("PointN=" + QString::number(int(PointNumber), 10));
		}
	}	
}


//定时器
void ImageProcess::onTimeout()
{
	/*Cursor_Opengl cursor_opengl;
	cursor_opengl = OpenGL_ui->GetCursor();
	int cursor_opengl_x = cursor_opengl.cursor_opengl_x,
		cursor_opengl_y = cursor_opengl.cursor_opengl_y;
	qDebug() << cursor_opengl_x << cursor_opengl_y;*/
}

//关于
void ImageProcess::ImageProcess_About()
{
	if (About_ui != NULL)
	{
		//QMessageBox::warning(NULL, QStringLiteral("提示"), "open ok", QMessageBox::Yes);
		About_ui->show();
	}
}

//数据库
void ImageProcess::ImageProcess_Database()
{
	if (Mysql_ui != NULL)
	{
		Mysql_ui->show();
		Mysql_ui->Connect();//连接数据库
	}
}




//鼠标点击事件
//和SQ_ImageZooming中的按键独立
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

//按键事件，需要先按下TAB, 再按其他按键，可以响应按键事件
void ImageProcess::keyPressEvent(QKeyEvent *e)
{
	//if (e->key() == Qt::Key_W)
	//	qDebug() << "wwwwwwwwwwwwwwwwwwwwwwwwwwww";
	//if (e->key() == Qt::Key_S)
	//	qDebug() << "sssssssssssssssssssssssss";
}

//光标移动
void ImageProcess::mouseMoveEvent(QMouseEvent *event)
{

}

//显示3D点云-PCD
void ImageProcess::on_OpenCloudPCD_clicked()
{
	ui.Message->setText("");//清空显示
	ui.KeyPointNumber->setText("PointN=" + QString::number(0, 10));
	QString OpenStlPath = QFileDialog::getOpenFileName(this, tr("OpenPath"), ".\\..\\PCD", tr("(*.pcd)"));
	if (OpenStlPath.isEmpty())//如果路径为空
	{
		ui.Message->setText(QString::fromLocal8Bit("路径为空！"));
	}
	else
	{
		flag_cloud = 1;//为1表示导入点云
		ui.Message->setText(OpenStlPath);//显示文件路径
		cv::Mat Point3D = pointcloud->PCLReadPCDToMat(OpenStlPath);//读取PCD文件	
		Point3D = stlread->ChangeCenterRange(Point3D, 4);
		Point3DSave = Point3D;//存储需要保存的点云
		Point3DDepthImage = Point3D;//存储需要转化为深度图的点云数据
		//cv::Mat Point3D = pointcloud->InitCube(0.1);
		flag_cloud = 1;//选择单个零件的点云
		ui.KeyPoint->setCheckState(Qt::Unchecked);//设置复选框为未选中
		ui.KeyPointNumber->setText(QString::number(int(0), 10));//显示角点个数为0
		flag_arm = 0;//未选择机械臂
		////////////////horizontalSliderStart();//横滚条初始化
		//timer->start(300); //开启定时器
		PointNumber = Point3D.rows;//记录点云个数
		ui.KeyPointNumber->setText("PointN=" + QString::number(int(PointNumber), 10));
		OpenGL_ui->Display3D(Point3D, 4);//显示点云
	}
}

//显示点云图案-STL
void ImageProcess::on_OpenCloudSTL_clicked()
{
	ui.Message->setText("");//清空显示
	ui.KeyPointNumber->setText("PointN=" + QString::number(0, 10));
	QStringList OpenStlPath = QFileDialog::getOpenFileNames(this, tr("StlOpenPath"), ".\\..\\STL", tr("(*.stl)"));//获取多个.stl文件
	if (OpenStlPath.isEmpty())//如果路径为空
	{
		ui.Message->setText(QString::fromLocal8Bit("路径为空！"));
	}
	else
	{
		if (OpenStlPath.size() == 19 || OpenStlPath.size() == 13)//导入机械臂的操作
		{
			flag_cloud = 0;//未选择单个零件的点云
			////////////////horizontalSliderStart();//横滚条初始化
			GetArmInfo(OpenStlPath, 4, OpenStlPath.size());//获取机械臂的点云数据
			flag_arm = 1;//选择机械臂
		}
		else
		{
			flag_cloud = 1;//选择单个零件的点云
			ui.KeyPoint->setCheckState(Qt::Unchecked);//设置复选框为未选中
			ui.KeyPointNumber->setText(QString::number(int(0), 10));//显示角点个数为0
			//QTime timedebuge;//声明一个时钟对象
			//timedebuge.start();//开始计时
			flag_arm = 0;//未选择机械臂
			////////////////horizontalSliderStart();//横滚条初始化
			cv::Mat Point3D = stlread->PointCloudInfo(OpenStlPath);//获取点云数据
			Point3DSave = Point3D;//存储需要保存的点云
			Point3DDepthImage = Point3D;//存储需要转化为深度图的点云数据
			//timer->start(300);//开启定时器
			PointNumber = Point3D.rows;//记录点云个数
			ui.KeyPointNumber->setText("PointN=" + QString::number(int(PointNumber), 10));	
			OpenGL_ui->Display3D(Point3D, 4);//显示点云
			//qDebug() << "ALL" << timedebuge.elapsed() << "ms";//输出计时

		}
	}
}

//显示.stl文件中的三维图案
void ImageProcess::on_OpenStl_clicked()
{
	flag_cloud = 0;//为1表示导入点云
	ui.Message->setText("");//清空显示
	QStringList OpenStlPath = QFileDialog::getOpenFileNames(this, tr("StlOpenPath"), ".\\..\\STL", tr("(*.stl)"));//获取多个.stl文件
	//QString OpenStlPath = QFileDialog::getOpenFileName(this, tr("StlOpenPath"), ".\\..\\STL", tr("(*.stl)"));
	if (OpenStlPath.isEmpty())//如果路径为空
	{
		ui.Message->setText(QString::fromLocal8Bit("路径为空！"));
	}
	else
	{
		flag_cloud = 0;//未选择单个零件的点云
		if (OpenStlPath.size() == 19 || OpenStlPath.size() == 13)//导入机械臂的操作
		{
			////////////////horizontalSliderStart();//横滚条初始化		
			GetArmInfo(OpenStlPath, 2, OpenStlPath.size());//获取机械臂的三角面数据
			flag_arm = 1;//选择机械臂
		}
		else
		{		
			flag_arm = 0;//未选择机械臂
			////////////////horizontalSliderStart();//横滚条初始化
			cv::Mat Point3D = stlread->TrianglePatchInfo(OpenStlPath);//获取三角面数据
			OpenGL_ui->Display3D(Point3D, 2);//显示三维图案
		}		
	}
}

//获取机械臂的数据
void ImageProcess::GetArmInfo(QStringList OpenStlPath, int type, int quantity)
{
	QMap<QString, int> StlPathName;//存储机械臂文件名称
	StlPathName.insert("Base", 1); StlPathName.insert("Link1", 2); StlPathName.insert("Link2", 3);
	StlPathName.insert("Link3", 4); StlPathName.insert("Link4", 5); StlPathName.insert("Link5", 6);
	StlPathName.insert("Link6", 7); StlPathName.insert("Cube1", 8); StlPathName.insert("Cube2", 9);
	StlPathName.insert("Cube3", 10); StlPathName.insert("Cube4", 11); StlPathName.insert("Cube5", 12);
	StlPathName.insert("Cube6", 13); StlPathName.insert("Axial1", 14); StlPathName.insert("Axial2", 15);
	StlPathName.insert("Axial3", 16); StlPathName.insert("Axial4", 17); StlPathName.insert("Axial5", 18);
	StlPathName.insert("Axial6", 19);
	QVector<cv::Mat> ArmPoint3D;//存储机械臂的原始数据--7个部件
	cv::Mat ArmPoint3DArray[7];
	cv::Mat Point3DAll(0, 3, CV_32FC1);//存储整个机械臂的三维图案数据
	cv::Mat Point3D;//暂存读取到的原始三维图案数据
	//前6行为各个坐标系的原点--后6行为各个转动轴的轴向
	cv::Mat ArmCenterRotationAxis(12, 3, CV_32FC1, cv::Scalar::all(0));//存储机械臂6个关节的坐标系的原点以及对应的转动轴方向
	CenterPoint ArmCenterPointArray[12];
	CenterPoint_Range centerPoint_range;//存储整个机械臂的中心点坐标和最大宽度
	CenterPoint centerpoint;//存储中心点坐标
	int number;//文件名称编号
	QList<QString> PathTempSplit;//存储路径分割结果
	QString PathTempSplitLast;//存储机械臂零部份的名称
	QStringList OpenStlPathOne;//将.stl文件的类型转化成QStringList
	for (int i = 0; i < quantity; i++)
	{
		PathTempSplit = OpenStlPath[i].split('/');//存储路径分割结果
		PathTempSplitLast = PathTempSplit[PathTempSplit.size() - 1].split('.')[0];//存储机械臂零部份的名称				
		OpenStlPathOne.append(OpenStlPath[i]);//将.stl文件的类型转化成QStringList
		number = StlPathName.value(PathTempSplitLast);//获取文件名称编号

		if (type == 2)
			Point3D = stlread->TrianglePatchOriginalInfo(OpenStlPathOne);//获取原始的三角面数据
		if (type == 4)
			Point3D = stlread->PointCloudOriginalInfo(OpenStlPathOne);//获取原始的点云数据

		OpenStlPathOne.clear();//清空
		if (number >= 1 && number <= 7)//机械臂的零部件
		{
			ArmPoint3DArray[number - 1] = Point3D;
		}
		if (number >= 8 && number <= quantity)//机械臂的中心点坐标以及对应的转动轴方向
		{
			centerpoint = stlread->GetCenterPointOnly(Point3D, type);
			ArmCenterPointArray[number - 8] = centerpoint;
		}
	}

	for (int i = 0; i < 7; i++)
	{
		Point3DAll = stlread->MergeRows(Point3DAll, ArmPoint3DArray[i]);//存储整个机械臂的三维图案数据
	}
	//qDebug() << "point number" << Point3DAll.rows;//输出计时

	centerPoint_range = stlread->GetCenterPoint(Point3DAll, type);//存储整个机械臂的中心点坐标和最大宽度

	for (int i = 0; i < 7; i++)
	{
		ArmPoint3D.append(stlread->ChangeCenterRange(ArmPoint3DArray[i], centerPoint_range, type));//将每个机械臂零部件的坐标进行移动和缩放处理
	}
	for (int i = 0; i < quantity - 7; i++)
	{
		//将每个机械臂零部件的中心的坐标进行移动和缩放处理
		ArmCenterRotationAxis.at<float>(i, 0) = (ArmCenterPointArray[i].center_x - centerPoint_range.center_x) / centerPoint_range.maxlength;
		ArmCenterRotationAxis.at<float>(i, 1) = (ArmCenterPointArray[i].center_y - centerPoint_range.center_y) / centerPoint_range.maxlength;
		ArmCenterRotationAxis.at<float>(i, 2) = (ArmCenterPointArray[i].center_z - centerPoint_range.center_z) / centerPoint_range.maxlength;
	}
	if (quantity == 19)
	{
		//存储机械臂6个关节对应的转动轴方向
		for (int i = 0; i < 6; i++)
		{
			ArmCenterRotationAxis.at<float>(i + 6, 0) = ArmCenterRotationAxis.at<float>(i + 6, 0) - ArmCenterRotationAxis.at<float>(i, 0);
			ArmCenterRotationAxis.at<float>(i + 6, 1) = ArmCenterRotationAxis.at<float>(i + 6, 1) - ArmCenterRotationAxis.at<float>(i, 1);
			ArmCenterRotationAxis.at<float>(i + 6, 2) = ArmCenterRotationAxis.at<float>(i + 6, 2) - ArmCenterRotationAxis.at<float>(i, 2);
		}
	}
	else//此时旋转方向均与坐标轴平行
	{		
		//0第一个转动关节--Z
		//1第二个转动关节--Y
		//2第三个转动关节--Y
		//3第四个转动关节--X
		//4第五个转动关节--Z
		//5第六个转动关节--X
		ArmCenterRotationAxis.at<float>(6, 2) = 1;
		ArmCenterRotationAxis.at<float>(7, 1) = 1;
		ArmCenterRotationAxis.at<float>(8, 1) = 1;
		ArmCenterRotationAxis.at<float>(9, 0) = 1;
		ArmCenterRotationAxis.at<float>(10, 2) = 1;
		ArmCenterRotationAxis.at<float>(11, 0) = 1;
	}
	
	OpenGL_ui->GetCenterPoint(ArmCenterRotationAxis);//传递中心点坐标以及对应的转动轴方向

	OpenGL_ui->Display3DArm(ArmPoint3D, type);//显示机械臂

}


//恢复三维原始图案
void ImageProcess::on_ThreeDRecover_clicked()
{
	//////QString OpenStlPath = QFileDialog::getOpenFileName(this, tr("StlOpenPath"), ".\\..\\STL", tr("(*.stl)"));
	//////if (OpenStlPath.isEmpty())//如果路径为空
	//////{
	//////	ui.Message->setText(QString::fromLocal8Bit("路径为空！"));
	//////}
	//////else
	//////{
	//////	cv::Mat Point3D = stlread->StlPointInfo(OpenStlPath.toLatin1().data(), 4);//获取未去重的原始数据
	//////	cv::Mat Point3DDecrease = pointcloud->PCLDecreaseSampleToMat(Point3D, 0.5);//降采样

	//////	Point3D = stlread->ChangeCenterRange(Point3D, 4);//改变中心点及大小
	//////	Point3DDecrease = stlread->ChangeCenterRange(Point3DDecrease, 4);//改变中心点及大小

	//////	Point3D = quaternion->TransScaleMat(Point3D,300, 300, 0.1);
	//////	Point3DDecrease = quaternion->TransScaleMat(Point3DDecrease,300, 300, 0.1);
	//////
	//////	pointcloud->PCLShow(Point3D, Point3DDecrease);
	//////}

	
	/************************************显示点云和法向量**********************************************/
	//cv::Mat Point3D(4, 3, CV_32FC1);//原始的点云
	//float Point_array[4][3] = { { 1, 1, 0 }, { 1, -1,0 }, { -1, 1, 0 }, { -1, -1, 0 }};
	//for (int i = 0; i < Point3D.rows; i++)
	//	for (int j = 0; j < Point3D.cols; j++)
	//		Point3D.at<float>(i, j) = Point_array[i][j];
	//Point3D = stlread->ChangeCenterRange(Point3D, 4);//改变中心点及大小
	//cv::Mat Point3DNormal(Point3D.rows*2, 3, CV_32FC1);//前面是点云，后面是法向量
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
	//OpenGL_ui->Display3D(Point3DNormal, 5);//显示点云和法向量


	////////////////horizontalSliderStart();//横滚条初始化	
	OpenGL_ui->Recover3D();//恢复三维原始图案
}

//生成二维深度图
void ImageProcess::on_GetDepthImage2D_clicked()
{
	if (flag_cloud == 1)//选择单个零件的点云--读取txt中的点云数据
	{
		//cv::Mat Point3D = pointcloud->InitCube(0.01);//初始化立方体
		cv::Mat Point3D = Point3DDepthImage;//存储需要转化为深度图的点云数据

		float AngularResolution = 0.5*3.1415926/180.0;//转化为灰度图的分辨率
		cv::Mat Image = pointcloud->PointXYZToDepthImage2D(Point3D, AngularResolution);//获取二维深度图
		ImageRangePara imageRangeParaGlobal = pointcloud->InitImageRangePara(Point3D, AngularResolution);//保留参数待用		
		cv::Mat DepthRowColValue = pointcloud->GetDepthRowColValue();//获取每个点云存储的行列
		cv::Mat PointNormal(Point3D.rows, Point3D.cols, CV_32FC1, cv::Scalar(0));//存储每个点对应的法向量信息

		//////************************求得法向量*********************************
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
		
		OpenGL_ui->Display3D(Point3DNormal, 5);//显示点云和法向量		
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

		//PCL库中生成二维深度图
		cv::Mat Ima = pointcloud->PCLPointXYZToDepthImage2D(Point3D, AngularResolution);//获取二维深度图
		cv::namedWindow("INOUT", CV_WINDOW_AUTOSIZE);
		cv::imshow("INOUT", Ima);

	}	
	//QString ImageOpenPath = QFileDialog::getOpenFileName(this, tr("ImageOpenPath"), ".\\..\\Image", tr("(*.png *.bmp *.jpg *.tif *.gif *.jpeg)"));//获取图片路径信息
	//cv::Mat Image = cv::imread(ImageOpenPath.toLatin1().data(), 1);
	//Image_ui->ShowDepthImage2D(Image);
}




//绘制点云图--PlotCloud(Point3D);
void ImageProcess::PlotCloud(cv::Mat Point3D)
{
	//cv::Mat CloudDeWeightPoint3D = PointCloudDeWeight(Point3D);//点云去重
	cv::Mat Point3DResult = stlread->ChangeCenterRange(Point3D, 4);
	OpenGL_ui->Display3D(Point3DResult, 4);//画点云
}


//绘制连续线段--PlotLine(Point3D);
void ImageProcess::PlotLine(cv::Mat Point3D)
{
	cv::Mat Point3DResult = stlread->ChangeCenterRange(Point3D, 2);
	OpenGL_ui->Display3D(Point3DResult, 1);//画线段--依次连接
}

//保存点云数据
void ImageProcess::on_SaveCloudData_clicked()
{
	////cv::Mat Point3D = stlread->PointALLProcessInfo(OpenStlPath);//获取读取原始的.stl数据，包括法向量的坐标和三角面数据
	//cv::Mat Point3D = pointcloud->InitFace('Y',0.001);//初始化平面
	if (Point3DSave.rows > 1)
	{
		cv::Mat Point3D = Point3DSave;//存储需要保存的点云
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy-MM-dd hh-mm-ss");
		QString path = QString(".\\..\\TXT\\txt-") + QString(current_date) + QString(".txt");
		SavePointInfo(Point3D, path);//保存数据		
		QMessageBox::warning(NULL, QStringLiteral("保存完成"), "save ok", QMessageBox::Yes);
	}
}

//读取点云数据
void ImageProcess::on_ReadCloudData_clicked()
{
	QString OpenStlPath = QFileDialog::getOpenFileName(this, tr("StlOpenPath"), ".\\..\\TXT", tr("(*.txt)"));
	cv::Mat Point3D = ReadPointInfo(OpenStlPath);
	////Point3D = stlread->ChangeCenterRange(Point3D, 4);//此处不需要
	Point3DDepthImage = Point3D;//存储需要转化为深度图的点云数据
	flag_cloud = 1;//为1表示导入点云
	OpenGL_ui->Display3D(Point3D, 4);//显示点云
}

//保存数据
void ImageProcess::SavePointInfo(cv::Mat Point3D, QString path)
{
	QFile ExpandData(path);
	if (ExpandData.open(QIODevice::WriteOnly))
	{
		/*文本输出流，用于保存数据*/
		QTextStream Out(&ExpandData);
		/*加入空格的好处是以流的形式读取恰好是相反的操作，这样一来方便快速对参数的读取*/
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

//读取数据
cv::Mat ImageProcess::ReadPointInfo(QString path)
{
	QVector<QVector<float>> vec_vec_int;
	QVector<float> vec_int;
	int count = 0;
	cv::Mat Point3D(0, 3, CV_32FC1);
	cv::Mat Point3DTemp(10000, 3, CV_32FC1);
	if (path.isEmpty())//如果路径为空
	{
		ui.Message->setText(QString::fromLocal8Bit("路径为空！"));
	}
	else
	{
		QString str;
		QStringList list;
		QFile ExpandData(path);
		if (ExpandData.open(QIODevice::ReadOnly))
		{
			/*文本输出流，用于保存数据*/
			QTextStream In(&ExpandData);
			while (!In.atEnd()) //未到文件尾
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
