#include "SQ_PointCloud.h"

SQ_PointCloud::SQ_PointCloud()
{

}


SQ_PointCloud::~SQ_PointCloud()
{
}

//点云数据降采样--Ptr
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::PCLDecreaseSampleToPtr(cv::Mat PointMat, float para)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);	//Mat转点云指针
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrFiltered(new pcl::PointCloud<pcl::PointXYZ>);

	pcl::VoxelGrid<pcl::PointXYZ> sor;// 创建滤波（降采样）对象
	sor.setInputCloud(PointPtrOriginal);//设置需要过滤的点云
	sor.setLeafSize(para, para, para);//设置滤波时创建的体素体积
	sor.filter(*PointPtrFiltered);//执行滤波处理，储存输出点云

	return PointPtrFiltered;
}

//点云数据降采样--Mat
cv::Mat SQ_PointCloud::PCLDecreaseSampleToMat(cv::Mat PointMat, float para)
{
	cv::Mat PointMatFiltered = PointXYZPrtToMat(PCLDecreaseSampleToPtr(PointMat, para));//点云指针转Mat
	return PointMatFiltered;
}

//点云数据均匀采样--Ptr
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::PCLUniformSampleToPtr(cv::Mat PointMat, float para)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);//Mat转点云指针
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrFiltered(new pcl::PointCloud<pcl::PointXYZ>);

	pcl::UniformSampling<pcl::PointXYZ> sor;// 创建均匀采样对象
	sor.setInputCloud(PointPtrOriginal);//设置需要过滤的点云
	sor.setRadiusSearch(para);//设置滤波时创建的体素体积
	sor.filter(*PointPtrFiltered);//执行滤波处理，储存输出点云 

	return PointPtrFiltered;
}

//点云数据均匀采样--Mat
cv::Mat SQ_PointCloud::PCLUniformSampleToMat(cv::Mat PointMat, float para)
{
	cv::Mat PointMatFiltered = PointXYZPrtToMat(PCLUniformSampleToPtr(PointMat, para));//点云指针转Mat
	return PointMatFiltered;
}

//点云数据增采样--Ptr
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::PCLIncreaseSampleToPtr(cv::Mat PointMat)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrFiltered(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ> sor;//滤波对象
	sor.setInputCloud(PointPtrOriginal);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree;//建立搜索对象
	sor.setSearchMethod(kdtree);
	sor.setSearchRadius(1);//设置搜索邻域的半径为3cm
	sor.setUpsamplingMethod(pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ>::SAMPLE_LOCAL_PLANE);  // Upsampling 采样的方法有SAMPLE_LOCAL_PLANE DISTINCT_CLOUD, RANDOM_UNIFORM_DENSIT
	sor.setUpsamplingRadius(0.2);//采样的半径是
	sor.setUpsamplingStepSize(0.3);//采样步数的大小
	sor.process(*PointPtrFiltered);

	return PointPtrFiltered;
}

//点云数据增采样--Mat
cv::Mat SQ_PointCloud::PCLIncreaseSampleToMat(cv::Mat PointMat)
{
	cv::Mat PointMatFiltered = PointXYZPrtToMat(PCLIncreaseSampleToPtr(PointMat));//点云指针转Mat
	return PointMatFiltered;
}

//点云数据增采样--参数问题
cv::Mat SQ_PointCloud::PCLIncreaseSampleToMat(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrFiltered(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ> sor;//滤波对象
	sor.setInputCloud(PointPtr);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree;//建立搜索对象
	sor.setSearchMethod(kdtree);
	sor.setSearchRadius(3);//设置搜索邻域的半径为3cm
	sor.setUpsamplingMethod(pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ>::SAMPLE_LOCAL_PLANE);  // Upsampling 采样的方法有SAMPLE_LOCAL_PLANE DISTINCT_CLOUD, RANDOM_UNIFORM_DENSIT
	sor.setUpsamplingRadius(0.2);//采样的半径是
	sor.setUpsamplingStepSize(0.3);//采样步数的大小
	sor.process(*PointPtrFiltered);

	cv::Mat PointMatFiltered = PointXYZPrtToMat(PointPtrFiltered);//点云指针转Mat

	return PointMatFiltered;
}

//获取点云的法向量
pcl::PointCloud<pcl::Normal>::Ptr SQ_PointCloud::PCLGetNormalToPtr(cv::Mat PointMat)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);//Mat转点云指针

	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;//法向计算
	pcl::PointCloud<pcl::Normal>::Ptr NormalPtr(new pcl::PointCloud<pcl::Normal>);
	
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);//建立kdtree来进行近邻点集搜索
	
	tree->setInputCloud(PointPtrOriginal);//为kdtree添加点云数据
	n.setInputCloud(PointPtrOriginal);
	n.setSearchMethod(tree);
	//n.setRadiusSearch(0.05); //设置半径邻域搜索 
	//点云法向计算时，需要搜索的近邻点大小
	n.setKSearch(20);
	n.compute(*NormalPtr);//开始进行法向计算

	return NormalPtr;
}

//获取点云的法向量
cv::Mat SQ_PointCloud::PCLGetNormalToMat(cv::Mat PointMat)
{
	cv::Mat NormalMat = NormalPrtToMat(PCLGetNormalToPtr(PointMat));
	return NormalMat;
}

//获取点云的曲率
cv::Mat SQ_PointCloud::PCLGetCurvatureToMat(cv::Mat PointMat)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);//Mat转点云指针
	//计算法线
	pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);
	cloud_normals = PCLGetNormalToPtr(PointMat);

	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
 
	//计算曲率
	pcl::PrincipalCurvaturesEstimation<pcl::PointXYZ, pcl::Normal, pcl::PrincipalCurvatures>pc;
	pcl::PointCloud<pcl::PrincipalCurvatures>::Ptr cloud_curvatures(new pcl::PointCloud<pcl::PrincipalCurvatures>);
	pc.setInputCloud(PointPtrOriginal);
	pc.setInputNormals(cloud_normals);
	pc.setSearchMethod(tree);
	//pc.setRadiusSearch(0.05);	
	pc.setKSearch(10);
	pc.compute(*cloud_curvatures);

	cv::Mat CurvatureMat(cloud_curvatures->size(), 1, CV_32FC1);
	float curvature = 0.0;
	for (int i = 0; i < cloud_curvatures->size(); i++)
	{
		//平均曲率
		//curvature = cloud_normals->points[i].curvature;
		curvature = ((*cloud_curvatures)[i].pc1 + (*cloud_curvatures)[i].pc2) / 2;
		//高斯曲率
		curvature = (*cloud_curvatures)[i].pc1 * (*cloud_curvatures)[i].pc2;

		CurvatureMat.at<float>(i, 0) = curvature;
	}
	return CurvatureMat;
}

//利用Harris3D是实现角点检测
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::PCLHarris3DToPtr(cv::Mat PointMat)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	cloud = MatToPointXYZPrt(PointMat);

	//注意Harris的输出点云必须是有强度(I)信息的，因为评估值保存在I分量里
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_out(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::HarrisKeypoint3D<pcl::PointXYZ, pcl::PointXYZI, pcl::Normal> harris;

	pcl::HarrisKeypoint3D<pcl::PointXYZ, pcl::PointXYZI, pcl::Normal>::ResponseMethod method = pcl::HarrisKeypoint3D<pcl::PointXYZ, pcl::PointXYZI, pcl::Normal>::HARRIS;
	harris.setMethod(method);
	harris.setInputCloud(cloud);
	harris.setNonMaxSupression(true);
	//harris.setRadius(0.04f);
	//harris.setThreshold(0.02f);

	harris.setRadius(0.003);//参数
	harris.setThreshold(0.002 );

	//新建的点云必须初始化，清零，否则指针会越界
	cloud_out->height = 1;
	cloud_out->width = 100;
	cloud_out->resize(cloud_out->height*cloud->width);
	cloud_out->clear();
	harris.compute(*cloud_out);
	int size = cloud_out->size();
		
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_harris(new pcl::PointCloud<pcl::PointXYZ>);
	cloud_harris->height = 1;
	cloud_harris->width = 100;
	cloud_harris->resize(cloud_out->height*cloud->width);
	cloud_harris->clear();
	
	pcl::PointXYZ point;
	//可视化结果不支持XYZI格式点云，所有又要导回XYZ格式。。。。
	for (int i = 0; i<size; i++)
	{
		point.x = cloud_out->at(i).x;
		point.y = cloud_out->at(i).y;
		point.z = cloud_out->at(i).z;
		cloud_harris->push_back(point);
	}
	return cloud_harris;
}

//利用Harris3D是实现角点检测
cv::Mat SQ_PointCloud::PCLHarris3DToMat(cv::Mat PointMat)
{
	cv::Mat Harris3DMat = PointXYZPrtToMat(PCLHarris3DToPtr(PointMat));
	return Harris3DMat;
}

//显示--单个
void SQ_PointCloud::PCLShow(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr)
{
	pcl::visualization::PCLVisualizer viewer("SHOW");

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_in_white(PointPtr, 255, 255, 255);//显示白色点云
	viewer.addPointCloud(PointPtr, cloud_in_white, "cloud_in");

	viewer.setSize(1280, 1024);//设置窗口大小

	while (!viewer.wasStopped())
	{
		viewer.spinOnce();
	}
}

//显示--Ptr
void SQ_PointCloud::PCLShow(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr1, pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr2)
{
	pcl::visualization::PCLVisualizer viewer("SHOW");

	int v1(1);//设置左右两个子窗口
	int v2(2);

	viewer.createViewPort(0.0, 0.0, 0.5, 1.0, v1);//设置窗口位置
	viewer.setBackgroundColor(0, 0, 0, v1);

	viewer.createViewPort(0.5, 0.0, 1.0, 1.0, v2);
	viewer.setBackgroundColor(0, 0, 0, v2);

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_in_white(PointPtr1, 255, 255, 255);//显示白色点云
	viewer.addPointCloud(PointPtr1, cloud_in_white, "cloud_in", v1);

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_out_purple(PointPtr2, 255, 0, 255);//显示紫色点云
	viewer.addPointCloud(PointPtr2, cloud_out_purple, "cloud_out", v2);

	viewer.setSize(1280, 1024);//设置窗口大小

	while (!viewer.wasStopped())
	{
		viewer.spinOnce();
	}
}

//显示--Mat
void SQ_PointCloud::PCLShow(cv::Mat PointMat1, cv::Mat PointMat2)
{
	PCLShow(MatToPointXYZPrt(PointMat1), MatToPointXYZPrt(PointMat2));
}

//点云指针转Mat
cv::Mat SQ_PointCloud::PointXYZPrtToMat(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr)
{
	cv::Mat PointMat(PointPtr->points.size(), 3, CV_32FC1);
	for (int i = 0; i < PointPtr->points.size(); i++)
	{
		PointMat.at<float>(i, 0) = PointPtr->points[i].x;
		PointMat.at<float>(i, 1) = PointPtr->points[i].y;
		PointMat.at<float>(i, 2) = PointPtr->points[i].z;
	}
	return PointMat;
}

//Mat转点云指针
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::MatToPointXYZPrt(cv::Mat PointMat)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtr->height = 1;
	PointPtr->width = 100;
	PointPtr->resize(PointMat.rows);
	PointPtr->clear();
	//PointPtr->width = PointMat.rows;
	//PointPtr->height = 1;
	pcl::PointXYZ point;
	for (int i = 0; i < PointMat.rows; i++)
	{
		point.x = PointMat.at<float>(i, 0);
		point.y = PointMat.at<float>(i, 1);
		point.z = PointMat.at<float>(i, 2);
		PointPtr->points.push_back(point);
	}
	return PointPtr;
}

//法向量指针转Mat
cv::Mat SQ_PointCloud::NormalPrtToMat(pcl::PointCloud<pcl::Normal>::Ptr NormalPtr)
{
	cv::Mat NormalMat(NormalPtr->points.size(), 3, CV_32FC1);
	for (int i = 0; i < NormalPtr->points.size(); i++)
	{
		NormalMat.at<float>(i, 0) = NormalPtr->points[i].normal_x;
		NormalMat.at<float>(i, 1) = NormalPtr->points[i].normal_y;
		NormalMat.at<float>(i, 2) = NormalPtr->points[i].normal_z;
	}
	return NormalMat;
}

//Mat转法向量指针
pcl::PointCloud<pcl::Normal>::Ptr SQ_PointCloud::MatToNormalPrt(cv::Mat NormalMat)
{
	pcl::PointCloud<pcl::Normal>::Ptr NormalPtr(new pcl::PointCloud<pcl::Normal>);
	NormalPtr->width = NormalMat.rows;
	NormalPtr->height = 1;
	pcl::Normal normal;
	for (int i = 0; i < NormalMat.rows; i++)
	{
		normal.normal_x = NormalMat.at<float>(i, 0);
		normal.normal_y = NormalMat.at<float>(i, 1);
		normal.normal_z = NormalMat.at<float>(i, 2);
		NormalPtr->points.push_back(normal);
	}
	return NormalPtr;
}

//读取点云数据(.pcd)格式
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::PCLReadPCDToPtr(QString path)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCDReader reader;
	reader.read(path.toLatin1().data(), *PointPtr); // Remember to download the file first!

	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrResult(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointXYZ point;
	for (int i = 0; i < PointPtr->size();i++)
	{
		if (isnan(PointPtr->points[i].x) != 1 && isnan(PointPtr->points[i].y) != 1 && isnan(PointPtr->points[i].z) != 1)
		{
			point.x = PointPtr->points[i].x;
			point.y = PointPtr->points[i].y;
			point.z = PointPtr->points[i].z;
			PointPtrResult->points.push_back(point); //循环添加点数据到点云对象
		}	
	}
	return PointPtrResult;
}

//读取点云数据(.pcd)格式
cv::Mat SQ_PointCloud::PCLReadPCDToMat(QString path)
{
	cv::Mat PointMat = PointXYZPrtToMat(PCLReadPCDToPtr(path));
	return PointMat;
}

//初始化一个平面
cv::Mat SQ_PointCloud::InitFace(char c, float resolution)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointXYZ point;
	switch (c)
	{
		case 'X':{
					 for (float y = -0.5f; y <= 0.5f; y += resolution)
					 {
						 for (float z = -0.5f; z <= 0.5f; z += resolution)
						 {
							 point.x = 0.5;
							 point.y = y;
							 point.z = z;
							 point_cloud_ptr->points.push_back(point); //循环添加点数据到点云对象
						 }
					 }
					 break;
		}
		case 'Y':{
					 for (float z = -0.5f; z <= 0.5f; z += resolution)
					 {
						 for (float x = -0.5f; x <= 0.5f; x += resolution)
						 {
							 point.x = x;
							 point.y = 0.5;
							 point.z = z;
							 point_cloud_ptr->points.push_back(point); //循环添加点数据到点云对象
						 }
					 }
					 break;
		}
		case 'Z':{
					 for (float x = -0.5f; x <= 0.5f; x += resolution)
					 {
						 for (float y = -0.5f; y <= 0.5f; y += resolution)
						 {
							 point.x = x;
							 point.y = y;
							 point.z = -0.5;
							 point_cloud_ptr->points.push_back(point); //循环添加点数据到点云对象
						 }
					 }
					 break;
		}
		default:break;
	}
	cv::Mat PointXYZMat = PointXYZPrtToMat(point_cloud_ptr);
	return PointXYZMat;
}

//初始化一个立方体
cv::Mat SQ_PointCloud::InitCube(float resolution)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointXYZ point;
	for (float x = -0.5f; x <= 0.5f; x += resolution)
	{
		for (float y = -0.5f; y <= 0.5f; y += resolution)
		{
			point.x = x;
			point.y = y;
			point.z = -0.5;
			point_cloud_ptr->points.push_back(point); //循环添加点数据到点云对象
			point.z = 0.5;
			point_cloud_ptr->points.push_back(point); //循环添加点数据到点云对象
		}
	}
	for (float y = -0.5f; y <= 0.5f; y += resolution)
	{
		for (float z = -0.5f; z <= 0.5f; z += resolution)
		{
			point.x = -0.5;
			point.y = y;
			point.z = z;
			point_cloud_ptr->points.push_back(point); //循环添加点数据到点云对象
			point.x = 0.5;
			point_cloud_ptr->points.push_back(point); //循环添加点数据到点云对象
		}
	}
	for (float z = -0.5f; z <= 0.5f; z += resolution)
	{
		for (float x = -0.5f; x <= 0.5f; x += resolution)
		{
			point.x = x;
			point.y = -0.5;
			point.z = z;
			point_cloud_ptr->points.push_back(point); //循环添加点数据到点云对象
			point.y = 0.5;
			point_cloud_ptr->points.push_back(point); //循环添加点数据到点云对象
		}
	}
	cv::Mat PointXYZMat = PointXYZPrtToMat(point_cloud_ptr);
	return PointXYZMat;
}


//直角坐标XYZ转球坐标
//球坐标三个参数：距离
//竖直角--与Y轴夹角--(0-pi)--弧度
//水平角--XOZ平面内与X轴的夹角--(0-2pi)--弧度
cv::Mat SQ_PointCloud::PointXYZToPolar(cv::Mat PointMat)
{
	cv::Mat PointPolar(PointMat.rows, PointMat.cols, CV_32FC1);
	for (int i = 0; i < PointMat.rows; i++)
	{
		PointPolar.at<float>(i, 0) = sqrt(PointMat.at<float>(i, 0)*PointMat.at<float>(i, 0) +
			PointMat.at<float>(i, 1)*PointMat.at<float>(i, 1) +
			PointMat.at<float>(i, 2)*PointMat.at<float>(i, 2));
		if (PointPolar.at<float>(i, 0) < 0.00000001)
		{
			PointPolar.at<float>(i, 1) = acos(double(-1))/2;
		}
		else
			PointPolar.at<float>(i, 1) = acos(PointMat.at<float>(i, 1) / PointPolar.at<float>(i, 0));
		PointPolar.at<float>(i, 2) = atan2(PointMat.at<float>(i, 2), PointMat.at<float>(i, 0)) + acos(double(-1));//atan2(y,x)计算的值相当于点(x,y)的角度值
	}
	return PointPolar;
}

//球坐标转空间坐标XYZ
cv::Mat SQ_PointCloud::PolarToPointXYZ(cv::Mat PointMat)
{
	cv::Mat PointXYZ(PointMat.rows, PointMat.cols, CV_32FC1);
	for (int i = 0; i < PointMat.rows; i++)
	{
		PointXYZ.at<float>(i, 0) = PointMat.at<float>(i, 0)*sin(PointMat.at<float>(i, 1))*cos(PointMat.at<float>(i, 2));
		PointXYZ.at<float>(i, 1) = PointMat.at<float>(i, 0)*cos(PointMat.at<float>(i, 1));
		PointXYZ.at<float>(i, 2) = PointMat.at<float>(i, 0)*sin(PointMat.at<float>(i, 1))*sin(PointMat.at<float>(i, 2));
	}
	return PointXYZ;
}

//二维灰度图转空间坐标XYZ
cv::Mat SQ_PointCloud::GreyImage2DToPointXYZ(cv::Mat CornersGray, float angularResolution, ImageRangePara imageRangePara)
{
	cv::Mat PointPolar(CornersGray.rows, 3, CV_32FC1);
	//二维灰度图转球坐标
	for (int i = 0; i < CornersGray.rows; i++)
	{
		PointPolar.at<float>(i, 0) = (CornersGray.at<float>(i, 2) - 1)*(imageRangePara.dis_max - imageRangePara.dis_min) / 254 + imageRangePara.dis_min;//球坐标系中的距离值
		//PointPolar.at<float>(i, 0) = (CornersGray.at<float>(i, 2) / 255)*(CornersGray.at<float>(i, 2) / 255)*(dis_max - dis_min) + dis_min;
		//PointPolar.at<float>(i, 0) = sqrt(CornersGray.at<float>(i, 2) / 255)*(dis_max - dis_min) + dis_min;
		PointPolar.at<float>(i, 1) = CornersGray.at<float>(i, 0)*angularResolution + imageRangePara.angle_vertical_min;//球坐标系中竖直角
		PointPolar.at<float>(i, 2) = CornersGray.at<float>(i, 1)*angularResolution + imageRangePara.angle_level_min;//球坐标系中水平角
	}
	cv::Mat PointXYZ = PolarToPointXYZ(PointPolar);//球坐标转空间坐标XYZ
	return PointXYZ;
}

//二维深度图转空间坐标XYZ
//CornersGray--灰度图中像素点的横坐标-纵坐标-灰度值
cv::Mat SQ_PointCloud::DepthImage2DToPointXYZ(cv::Mat CornersGray, float angularResolution, ImageRangePara imageRangePara)
{
	cv::Mat PointPolar(CornersGray.rows, 3, CV_32FC1);
	//二维深度图转球坐标
	for (int i = 0; i < CornersGray.rows; i++)
	{
		PointPolar.at<float>(i, 0) = (CornersGray.at<float>(i, 2) - 1)*(imageRangePara.dis_max - imageRangePara.dis_min) / 254 + imageRangePara.dis_min;//球坐标系中的距离值
		PointPolar.at<float>(i, 1) = CornersGray.at<float>(i, 0)*angularResolution + imageRangePara.angle_vertical_min;//球坐标系中竖直角

		//将压缩后的像素坐标转化成未压缩前的像素坐标
		float scale = cos((floor((PointPolar.at<float>(i, 1) - imageRangePara.angle_vertical_min) / angularResolution + 0.5) / float(imageRangePara.image_height) - 0.5) * acos(double(-1)));
		if (CornersGray.at<float>(i, 1) < imageRangePara.image_width / 2)
		{
			CornersGray.at<float>(i, 1) = (CornersGray.at<float>(i, 1) - imageRangePara.image_width / 2 * (1 - scale)) / scale;
		}
		else
		{
			CornersGray.at<float>(i, 1) = (CornersGray.at<float>(i, 1) - imageRangePara.image_width / 2) / scale + imageRangePara.image_width / 2;
		}

		PointPolar.at<float>(i, 2) = CornersGray.at<float>(i, 1)*angularResolution + imageRangePara.angle_level_min;//球坐标系中水平角
	}
	cv::Mat PointXYZ = PolarToPointXYZ(PointPolar);//球坐标转空间坐标XYZ
	return PointXYZ;
}

//参数初始化
ImageRangePara SQ_PointCloud::InitImageRangePara(cv::Mat PointPolar, float angularResolution)
{
	ImageRangePara imageRangePara;

	imageRangePara.dis_max = max_mat(PointPolar.col(0).clone());//距离最大值
	imageRangePara.dis_min = min_mat(PointPolar.col(0).clone());//距离最小值
	imageRangePara.angle_vertical_max = max_mat(PointPolar.col(1).clone());//竖直角最大值
	imageRangePara.angle_vertical_min = min_mat(PointPolar.col(1).clone());//竖直角最小值
	imageRangePara.angle_level_max = max_mat(PointPolar.col(2).clone());//水平角最大值
	imageRangePara.angle_level_min = min_mat(PointPolar.col(2).clone());//水平角最小值

	imageRangePara.image_height = floor(abs(imageRangePara.angle_vertical_max - imageRangePara.angle_vertical_min) / angularResolution + 0.5) + 1;//图片的高
	imageRangePara.image_width = floor(abs(imageRangePara.angle_level_max - imageRangePara.angle_level_min) / angularResolution + 0.5) + 1;//图片的宽

	return imageRangePara;
}

//直角坐标XYZ转二维灰度图像
cv::Mat SQ_PointCloud::PointXYZToGreyImage2D(cv::Mat PointMat, float angularResolution)
{
	cv::Mat PointPolar = PointXYZToPolar(PointMat);//直角坐标XYZ转球坐标
	ImageRangePara imageRangePara = InitImageRangePara(PointPolar, angularResolution);//获取参数

	cv::Mat ImageMat(imageRangePara.image_height, imageRangePara.image_width, CV_8U, cv::Scalar::all(0));//二维灰度图像
	cv::Mat AngleMat(imageRangePara.image_height, imageRangePara.image_width, CV_32FC2, cv::Scalar::all(0));//存储点云距离像素中心点云的距离和某像素内是否已经存在点云标志--角度之间的距离、标志

	int row_x = 0, col_y = 0;//点云对应的像素行--点云对应的像素列
	float angle_row_x = 0, angle_col_y = 0, dis_new = 0;//存储每个像素中心对应的竖直角--水平角--新来的的点云到中心点的距离
	for (int i = 0; i < PointPolar.rows; i++)
	{
		row_x = floor((PointPolar.at<float>(i, 1) - imageRangePara.angle_vertical_min) / angularResolution + 0.5);//点云对应的像素行
		col_y = floor((PointPolar.at<float>(i, 2) - imageRangePara.angle_level_min) / angularResolution + 0.5);//点云对应的像素列

		angle_row_x = row_x * angularResolution + angularResolution / 2;//存储每个像素中心对应的竖直角
		angle_col_y = col_y * angularResolution + angularResolution / 2;//存储每个像素中心对应的水平角
		dis_new = sqrt((PointPolar.at<float>(i, 1) - angle_row_x)*(PointPolar.at<float>(i, 1) - angle_row_x) +
			(PointPolar.at<float>(i, 2) - angle_col_y)*(PointPolar.at<float>(i, 2) - angle_col_y));//新来的的点云到中心点的距离

		if (AngleMat.at<cv::Vec2f>(row_x, col_y)[1] > 1)//某像素内是否已经存在点云
		{
			if (dis_new < AngleMat.at<cv::Vec2f>(row_x, col_y)[0])//需要判断新来的点云是否更加靠近像素中心
			{
				ImageMat.at<unsigned char>(row_x, col_y) = 254 * (PointPolar.at<float>(i, 0) - imageRangePara.dis_min) / (imageRangePara.dis_max - imageRangePara.dis_min) + 1;//点云对应的灰度值
				AngleMat.at<cv::Vec2f>(row_x, col_y)[0] = dis_new;
			}
		}
		else
		{
			ImageMat.at<unsigned char>(row_x, col_y) = 254 * (PointPolar.at<float>(i, 0) - imageRangePara.dis_min) / (imageRangePara.dis_max - imageRangePara.dis_min) + 1;//点云对应的灰度值
			AngleMat.at<cv::Vec2f>(row_x, col_y)[0] = dis_new;
			AngleMat.at<cv::Vec2f>(row_x, col_y)[1] = 2;
		}
		//ImageMat.at<unsigned char>(row_x, col_y) = 255*sqrt((PointPolar.at<float>(i, 0) - dis_min) / (dis_max - dis_min));
		//ImageMat.at<unsigned char>(row_x, col_y) = 255 * ((PointPolar.at<float>(i, 0) - dis_min) / (dis_max - dis_min))
		//	*((PointPolar.at<float>(i, 0) - dis_min) / (dis_max - dis_min));
	}
	return ImageMat;
}

////插值
//cv::Mat SQ_PointCloud::DepthImageInterpolation(cv::Mat ImageMat, cv::Mat InOutMat)
//{
//
//}

//存储某像素在深度图的内部还是外部 0 - 外部 255 - 内部
cv::Mat SQ_PointCloud::InOutDepthImage(ImageRangePara imageRangePara)
{
	cv::Mat InOutMat(imageRangePara.image_height, imageRangePara.image_width, CV_8U, cv::Scalar(0));
	int col_left = 0, col_right = 0;
	int count_eye = 0;//眼睛中点的个数
	float scale = 0;//缩放比例
	for (int row = 0; row < imageRangePara.image_height; row++)
	{
		scale = cos((float(row) / float(imageRangePara.image_height) - 0.5) * acos(double(-1)));
		col_left = imageRangePara.image_width / 2 * (1 - scale);
		col_right = imageRangePara.image_width - col_left;
		for (int col = col_left; col < col_right; col++)
		{
			InOutMat.at<unsigned char>(row, col) = 255;
			count_eye++;
		}
	}
	return InOutMat;
}

//由直角坐标转化成深度图--类似眼睛的图
cv::Mat SQ_PointCloud::PointXYZToDepthImage2D(cv::Mat PointMat, float angularResolution)
{
	cv::Mat PointPolar = PointXYZToPolar(PointMat);//Depth
	ImageRangePara imageRangePara = InitImageRangePara(PointPolar, angularResolution);//获取参数

	cv::Mat ImageMat(imageRangePara.image_height, imageRangePara.image_width, CV_8U, cv::Scalar(0));//二维灰度图像--像素1-255--0表示没有数据
	cv::Mat DepthRowColValueTemp(PointMat.rows, 2, CV_32SC1);//存储每个点云存储的行列
	cv::Mat AngleMat(imageRangePara.image_height, imageRangePara.image_width, CV_32FC2, cv::Scalar::all(0));//存储点云距离像素中心点云的距离和某像素内是否已经存在点云标志--角度之间的距离、标志

	int count_eye_kong = 0;//眼睛中点为空的个数
	int count_eye_chongfu = 0;//眼睛中点重复的个数
	float scale = 0;//缩放比例
	int row_x = 0, col_y = 0;//点云对应的像素行--点云对应的像素列
	float angle_row_x = 0, angle_col_y = 0, dis_new = 0;//存储每个像素中心对应的竖直角--水平角--新来的的点云到中心点的距离

	for (int i = 0; i < PointPolar.rows; i++)
	{
		row_x = floor((PointPolar.at<float>(i, 1) - imageRangePara.angle_vertical_min) / angularResolution + 0.5);
		col_y = floor((PointPolar.at<float>(i, 2) - imageRangePara.angle_level_min) / angularResolution + 0.5);

		//将未压缩前的像素坐标转化成压缩后的像素坐标
		scale = cos((floor((PointPolar.at<float>(i, 1) - imageRangePara.angle_vertical_min) / angularResolution + 0.5) / float(imageRangePara.image_height) - 0.5) * acos(double(-1)));
		if (col_y < imageRangePara.image_width / 2)
		{
			col_y = col_y * scale + imageRangePara.image_width / 2 * (1 - scale);
			PointPolar.at<float>(i, 2) = PointPolar.at<float>(i, 2) * scale + imageRangePara.image_width / 2 * (1 - scale);
		}
		else
		{
			col_y = imageRangePara.image_width / 2 + (col_y - imageRangePara.image_width / 2) * scale;
			PointPolar.at<float>(i, 2) = imageRangePara.image_width / 2 + (PointPolar.at<float>(i, 2) - imageRangePara.image_width / 2) * scale;
		}

		angle_row_x = row_x * angularResolution + angularResolution / 2;//存储每个像素中心对应的竖直角
		angle_col_y = col_y * angularResolution + angularResolution / 2;//存储每个像素中心对应的水平角
		dis_new = sqrt((PointPolar.at<float>(i, 1) - angle_row_x)*(PointPolar.at<float>(i, 1) - angle_row_x) +
			(PointPolar.at<float>(i, 2) - angle_col_y)*(PointPolar.at<float>(i, 2) - angle_col_y));//新来的的点云到中心点的距离

		if (AngleMat.at<cv::Vec2f>(row_x, col_y)[1] > 1)//某像素内是否已经存在点云
		{
			count_eye_chongfu++;
			if (dis_new < AngleMat.at<cv::Vec2f>(row_x, col_y)[0])//需要判断新来的点云是否更加靠近像素中心
			{
				ImageMat.at<unsigned char>(row_x, col_y) = 254 * (PointPolar.at<float>(i, 0) - imageRangePara.dis_min) / (imageRangePara.dis_max - imageRangePara.dis_min) + 1;//点云对应的灰度值
				
				AngleMat.at<cv::Vec2f>(row_x, col_y)[0] = dis_new;
			}
		}
		else
		{
			count_eye_kong++;
			ImageMat.at<unsigned char>(row_x, col_y) = 254 * (PointPolar.at<float>(i, 0) - imageRangePara.dis_min) / (imageRangePara.dis_max - imageRangePara.dis_min) + 1;//点云对应的灰度值
			AngleMat.at<cv::Vec2f>(row_x, col_y)[0] = dis_new;
			AngleMat.at<cv::Vec2f>(row_x, col_y)[1] = 2;
		}

		DepthRowColValueTemp.at<int>(i, 0) = row_x;//存储每个点云存储的行
		DepthRowColValueTemp.at<int>(i, 1) = col_y;//存储每个点云存储的列

	}

	DepthRowColValue = DepthRowColValueTemp;//存储每个点云存储的行列以及灰度值
	//存储某像素再深度图的内部还是外部 0-外部 255-内部
	cv::Mat InOutMat = InOutDepthImage(imageRangePara);
	//AngleMat = DepthImageInterpolation(ImageMat, InOutMat);//插值
	return ImageMat;
}

//获取每个点云存储的行列以及灰度值
cv::Mat SQ_PointCloud::GetDepthRowColValue()
{
	return DepthRowColValue;
}

//PCL生成二维深度图
cv::Mat SQ_PointCloud::PCLPointXYZToDepthImage2D(cv::Mat PointMat, float angularResolution)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr = MatToPointXYZPrt(PointMat);
	boost::shared_ptr<pcl::RangeImage> range_image_ptr(new pcl::RangeImage); //创建RangeImage对象（指针）
	range_image_ptr = PCLPointXYZToRangeImage(PointPtr, angularResolution);
	pcl::RangeImage& range_image = *range_image_ptr;  //引用

	float range_max = 0, range_min = 0;
	int flag_start = 0;
	int countt = 0;
	for (int i = 0; i < range_image.width * range_image.height; i++)
	{
		if (range_image.points[i].range < 1000000)
		{
			countt++;
			if (flag_start == 0)
			{
				flag_start = 1;
				range_max = range_image.points[i].range;
				range_min = range_image.points[i].range;
			}
			if (range_image.points[i].range > range_max)
				range_max = range_image.points[i].range;
			if (range_image.points[i].range < range_min)
				range_min = range_image.points[i].range;
		}
	}

	cv::Mat img(range_image.height, range_image.width, CV_8U, cv::Scalar::all(0));//CV_8U
	for (int i = 0; i < range_image.width * range_image.height; i++)
	{
		if (range_image.points[i].range < 1000000)
		{
			img.at<unsigned char>(i / range_image.width, i % range_image.width) = (range_image.points[i].range - range_min) * 254 / (range_max - range_min) + 1;
		}
	}
	return img;
}

//PCL生成RangeImage
boost::shared_ptr<pcl::RangeImage> SQ_PointCloud::PCLPointXYZToRangeImage(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr, float angularResolution)
{
	pcl::PointCloud<pcl::PointXYZ>& point_cloud = *PointPtr;//上面点云的别名

	//从点云数据，创建深度图像	
	float AngularResolution = angularResolution;//0.5度转弧度，角度分辨率	
	float maxAngleWidth = pcl::deg2rad(360.0f);//360.0度转弧度，水平最大采样角度
	float maxAngleHeight = pcl::deg2rad(180.0f);//180.0度转弧度，垂直方向最大采样角度
	Eigen::Affine3f sensorPose = (Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);//传感器位置
	pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME; //CAMERA_FRAME，LASER_FRAME
	float noise_level = 0.0;//近邻点对查询点距离值的影响水平
	float min_range = 0.0f;//最小的获取距离，小于设置为盲区
	int border_size = 1;//深度图像的边缘
	boost::shared_ptr<pcl::RangeImage> range_image_ptr(new pcl::RangeImage); //创建RangeImage对象（指针）
	pcl::RangeImage& range_image = *range_image_ptr;  //引用
	range_image.createFromPointCloud(point_cloud, AngularResolution, maxAngleWidth, maxAngleHeight,
		sensorPose, coordinate_frame, noise_level, min_range, border_size); //从点云创建深度图像
	//range_image.integrateFarRanges(far_ranges); //整合远距离点云
	range_image.setUnseenToMaxRange();//将所有不可见的点 看作 最大距离
	return range_image_ptr;
}

//求Mat最大值
float SQ_PointCloud::max_mat(cv::Mat OriginalMat)
{
	double max, min;
	cv::Point min_loc, max_loc;
	cv::minMaxLoc(OriginalMat, &min, &max, &min_loc, &max_loc);
	return max;
}

//求Mat最小值
float SQ_PointCloud::min_mat(cv::Mat OriginalMat)
{
	double max, min;
	cv::Point min_loc, max_loc;
	cv::minMaxLoc(OriginalMat, &min, &max, &min_loc, &max_loc);
	return min;
}
