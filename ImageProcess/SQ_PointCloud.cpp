#include "SQ_PointCloud.h"

SQ_PointCloud::SQ_PointCloud()
{

}


SQ_PointCloud::~SQ_PointCloud()
{
}

//�������ݽ�����--Ptr
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::PCLDecreaseSampleToPtr(cv::Mat PointMat, float para)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);	//Matת����ָ��
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrFiltered(new pcl::PointCloud<pcl::PointXYZ>);

	pcl::VoxelGrid<pcl::PointXYZ> sor;// �����˲���������������
	sor.setInputCloud(PointPtrOriginal);//������Ҫ���˵ĵ���
	sor.setLeafSize(para, para, para);//�����˲�ʱ�������������
	sor.filter(*PointPtrFiltered);//ִ���˲����������������

	return PointPtrFiltered;
}

//�������ݽ�����--Mat
cv::Mat SQ_PointCloud::PCLDecreaseSampleToMat(cv::Mat PointMat, float para)
{
	cv::Mat PointMatFiltered = PointXYZPrtToMat(PCLDecreaseSampleToPtr(PointMat, para));//����ָ��תMat
	return PointMatFiltered;
}

//�������ݾ��Ȳ���--Ptr
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::PCLUniformSampleToPtr(cv::Mat PointMat, float para)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);//Matת����ָ��
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrFiltered(new pcl::PointCloud<pcl::PointXYZ>);

	pcl::UniformSampling<pcl::PointXYZ> sor;// �������Ȳ�������
	sor.setInputCloud(PointPtrOriginal);//������Ҫ���˵ĵ���
	sor.setRadiusSearch(para);//�����˲�ʱ�������������
	sor.filter(*PointPtrFiltered);//ִ���˲���������������� 

	return PointPtrFiltered;
}

//�������ݾ��Ȳ���--Mat
cv::Mat SQ_PointCloud::PCLUniformSampleToMat(cv::Mat PointMat, float para)
{
	cv::Mat PointMatFiltered = PointXYZPrtToMat(PCLUniformSampleToPtr(PointMat, para));//����ָ��תMat
	return PointMatFiltered;
}

//��������������--Ptr
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::PCLIncreaseSampleToPtr(cv::Mat PointMat)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrFiltered(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ> sor;//�˲�����
	sor.setInputCloud(PointPtrOriginal);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree;//������������
	sor.setSearchMethod(kdtree);
	sor.setSearchRadius(1);//������������İ뾶Ϊ3cm
	sor.setUpsamplingMethod(pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ>::SAMPLE_LOCAL_PLANE);  // Upsampling �����ķ�����SAMPLE_LOCAL_PLANE DISTINCT_CLOUD, RANDOM_UNIFORM_DENSIT
	sor.setUpsamplingRadius(0.2);//�����İ뾶��
	sor.setUpsamplingStepSize(0.3);//���������Ĵ�С
	sor.process(*PointPtrFiltered);

	return PointPtrFiltered;
}

//��������������--Mat
cv::Mat SQ_PointCloud::PCLIncreaseSampleToMat(cv::Mat PointMat)
{
	cv::Mat PointMatFiltered = PointXYZPrtToMat(PCLIncreaseSampleToPtr(PointMat));//����ָ��תMat
	return PointMatFiltered;
}

//��������������--��������
cv::Mat SQ_PointCloud::PCLIncreaseSampleToMat(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrFiltered(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ> sor;//�˲�����
	sor.setInputCloud(PointPtr);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree;//������������
	sor.setSearchMethod(kdtree);
	sor.setSearchRadius(3);//������������İ뾶Ϊ3cm
	sor.setUpsamplingMethod(pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ>::SAMPLE_LOCAL_PLANE);  // Upsampling �����ķ�����SAMPLE_LOCAL_PLANE DISTINCT_CLOUD, RANDOM_UNIFORM_DENSIT
	sor.setUpsamplingRadius(0.2);//�����İ뾶��
	sor.setUpsamplingStepSize(0.3);//���������Ĵ�С
	sor.process(*PointPtrFiltered);

	cv::Mat PointMatFiltered = PointXYZPrtToMat(PointPtrFiltered);//����ָ��תMat

	return PointMatFiltered;
}

//��ȡ���Ƶķ�����
pcl::PointCloud<pcl::Normal>::Ptr SQ_PointCloud::PCLGetNormalToPtr(cv::Mat PointMat)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);//Matת����ָ��

	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;//�������
	pcl::PointCloud<pcl::Normal>::Ptr NormalPtr(new pcl::PointCloud<pcl::Normal>);
	
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);//����kdtree�����н��ڵ㼯����
	
	tree->setInputCloud(PointPtrOriginal);//Ϊkdtree��ӵ�������
	n.setInputCloud(PointPtrOriginal);
	n.setSearchMethod(tree);
	//n.setRadiusSearch(0.05); //���ð뾶�������� 
	//���Ʒ������ʱ����Ҫ�����Ľ��ڵ��С
	n.setKSearch(20);
	n.compute(*NormalPtr);//��ʼ���з������

	return NormalPtr;
}

//��ȡ���Ƶķ�����
cv::Mat SQ_PointCloud::PCLGetNormalToMat(cv::Mat PointMat)
{
	cv::Mat NormalMat = NormalPrtToMat(PCLGetNormalToPtr(PointMat));
	return NormalMat;
}

//��ȡ���Ƶ�����
cv::Mat SQ_PointCloud::PCLGetCurvatureToMat(cv::Mat PointMat)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtrOriginal(new pcl::PointCloud<pcl::PointXYZ>);
	PointPtrOriginal = MatToPointXYZPrt(PointMat);//Matת����ָ��
	//���㷨��
	pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);
	cloud_normals = PCLGetNormalToPtr(PointMat);

	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
 
	//��������
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
		//ƽ������
		//curvature = cloud_normals->points[i].curvature;
		curvature = ((*cloud_curvatures)[i].pc1 + (*cloud_curvatures)[i].pc2) / 2;
		//��˹����
		curvature = (*cloud_curvatures)[i].pc1 * (*cloud_curvatures)[i].pc2;

		CurvatureMat.at<float>(i, 0) = curvature;
	}
	return CurvatureMat;
}

//����Harris3D��ʵ�ֽǵ���
pcl::PointCloud<pcl::PointXYZ>::Ptr SQ_PointCloud::PCLHarris3DToPtr(cv::Mat PointMat)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	cloud = MatToPointXYZPrt(PointMat);

	//ע��Harris��������Ʊ�������ǿ��(I)��Ϣ�ģ���Ϊ����ֵ������I������
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_out(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::HarrisKeypoint3D<pcl::PointXYZ, pcl::PointXYZI, pcl::Normal> harris;

	pcl::HarrisKeypoint3D<pcl::PointXYZ, pcl::PointXYZI, pcl::Normal>::ResponseMethod method = pcl::HarrisKeypoint3D<pcl::PointXYZ, pcl::PointXYZI, pcl::Normal>::HARRIS;
	harris.setMethod(method);
	harris.setInputCloud(cloud);
	harris.setNonMaxSupression(true);
	//harris.setRadius(0.04f);
	//harris.setThreshold(0.02f);

	harris.setRadius(0.003);//����
	harris.setThreshold(0.002 );

	//�½��ĵ��Ʊ����ʼ�������㣬����ָ���Խ��
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
	//���ӻ������֧��XYZI��ʽ���ƣ�������Ҫ����XYZ��ʽ��������
	for (int i = 0; i<size; i++)
	{
		point.x = cloud_out->at(i).x;
		point.y = cloud_out->at(i).y;
		point.z = cloud_out->at(i).z;
		cloud_harris->push_back(point);
	}
	return cloud_harris;
}

//����Harris3D��ʵ�ֽǵ���
cv::Mat SQ_PointCloud::PCLHarris3DToMat(cv::Mat PointMat)
{
	cv::Mat Harris3DMat = PointXYZPrtToMat(PCLHarris3DToPtr(PointMat));
	return Harris3DMat;
}

//��ʾ--����
void SQ_PointCloud::PCLShow(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr)
{
	pcl::visualization::PCLVisualizer viewer("SHOW");

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_in_white(PointPtr, 255, 255, 255);//��ʾ��ɫ����
	viewer.addPointCloud(PointPtr, cloud_in_white, "cloud_in");

	viewer.setSize(1280, 1024);//���ô��ڴ�С

	while (!viewer.wasStopped())
	{
		viewer.spinOnce();
	}
}

//��ʾ--Ptr
void SQ_PointCloud::PCLShow(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr1, pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr2)
{
	pcl::visualization::PCLVisualizer viewer("SHOW");

	int v1(1);//�������������Ӵ���
	int v2(2);

	viewer.createViewPort(0.0, 0.0, 0.5, 1.0, v1);//���ô���λ��
	viewer.setBackgroundColor(0, 0, 0, v1);

	viewer.createViewPort(0.5, 0.0, 1.0, 1.0, v2);
	viewer.setBackgroundColor(0, 0, 0, v2);

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_in_white(PointPtr1, 255, 255, 255);//��ʾ��ɫ����
	viewer.addPointCloud(PointPtr1, cloud_in_white, "cloud_in", v1);

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_out_purple(PointPtr2, 255, 0, 255);//��ʾ��ɫ����
	viewer.addPointCloud(PointPtr2, cloud_out_purple, "cloud_out", v2);

	viewer.setSize(1280, 1024);//���ô��ڴ�С

	while (!viewer.wasStopped())
	{
		viewer.spinOnce();
	}
}

//��ʾ--Mat
void SQ_PointCloud::PCLShow(cv::Mat PointMat1, cv::Mat PointMat2)
{
	PCLShow(MatToPointXYZPrt(PointMat1), MatToPointXYZPrt(PointMat2));
}

//����ָ��תMat
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

//Matת����ָ��
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

//������ָ��תMat
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

//Matת������ָ��
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

//��ȡ��������(.pcd)��ʽ
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
			PointPtrResult->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
		}	
	}
	return PointPtrResult;
}

//��ȡ��������(.pcd)��ʽ
cv::Mat SQ_PointCloud::PCLReadPCDToMat(QString path)
{
	cv::Mat PointMat = PointXYZPrtToMat(PCLReadPCDToPtr(path));
	return PointMat;
}

//��ʼ��һ��ƽ��
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
							 point_cloud_ptr->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
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
							 point_cloud_ptr->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
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
							 point_cloud_ptr->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
						 }
					 }
					 break;
		}
		default:break;
	}
	cv::Mat PointXYZMat = PointXYZPrtToMat(point_cloud_ptr);
	return PointXYZMat;
}

//��ʼ��һ��������
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
			point_cloud_ptr->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
			point.z = 0.5;
			point_cloud_ptr->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
		}
	}
	for (float y = -0.5f; y <= 0.5f; y += resolution)
	{
		for (float z = -0.5f; z <= 0.5f; z += resolution)
		{
			point.x = -0.5;
			point.y = y;
			point.z = z;
			point_cloud_ptr->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
			point.x = 0.5;
			point_cloud_ptr->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
		}
	}
	for (float z = -0.5f; z <= 0.5f; z += resolution)
	{
		for (float x = -0.5f; x <= 0.5f; x += resolution)
		{
			point.x = x;
			point.y = -0.5;
			point.z = z;
			point_cloud_ptr->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
			point.y = 0.5;
			point_cloud_ptr->points.push_back(point); //ѭ����ӵ����ݵ����ƶ���
		}
	}
	cv::Mat PointXYZMat = PointXYZPrtToMat(point_cloud_ptr);
	return PointXYZMat;
}


//ֱ������XYZת������
//��������������������
//��ֱ��--��Y��н�--(0-pi)--����
//ˮƽ��--XOZƽ������X��ļн�--(0-2pi)--����
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
		PointPolar.at<float>(i, 2) = atan2(PointMat.at<float>(i, 2), PointMat.at<float>(i, 0)) + acos(double(-1));//atan2(y,x)�����ֵ�൱�ڵ�(x,y)�ĽǶ�ֵ
	}
	return PointPolar;
}

//������ת�ռ�����XYZ
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

//��ά�Ҷ�ͼת�ռ�����XYZ
cv::Mat SQ_PointCloud::GreyImage2DToPointXYZ(cv::Mat CornersGray, float angularResolution, ImageRangePara imageRangePara)
{
	cv::Mat PointPolar(CornersGray.rows, 3, CV_32FC1);
	//��ά�Ҷ�ͼת������
	for (int i = 0; i < CornersGray.rows; i++)
	{
		PointPolar.at<float>(i, 0) = (CornersGray.at<float>(i, 2) - 1)*(imageRangePara.dis_max - imageRangePara.dis_min) / 254 + imageRangePara.dis_min;//������ϵ�еľ���ֵ
		//PointPolar.at<float>(i, 0) = (CornersGray.at<float>(i, 2) / 255)*(CornersGray.at<float>(i, 2) / 255)*(dis_max - dis_min) + dis_min;
		//PointPolar.at<float>(i, 0) = sqrt(CornersGray.at<float>(i, 2) / 255)*(dis_max - dis_min) + dis_min;
		PointPolar.at<float>(i, 1) = CornersGray.at<float>(i, 0)*angularResolution + imageRangePara.angle_vertical_min;//������ϵ����ֱ��
		PointPolar.at<float>(i, 2) = CornersGray.at<float>(i, 1)*angularResolution + imageRangePara.angle_level_min;//������ϵ��ˮƽ��
	}
	cv::Mat PointXYZ = PolarToPointXYZ(PointPolar);//������ת�ռ�����XYZ
	return PointXYZ;
}

//��ά���ͼת�ռ�����XYZ
//CornersGray--�Ҷ�ͼ�����ص�ĺ�����-������-�Ҷ�ֵ
cv::Mat SQ_PointCloud::DepthImage2DToPointXYZ(cv::Mat CornersGray, float angularResolution, ImageRangePara imageRangePara)
{
	cv::Mat PointPolar(CornersGray.rows, 3, CV_32FC1);
	//��ά���ͼת������
	for (int i = 0; i < CornersGray.rows; i++)
	{
		PointPolar.at<float>(i, 0) = (CornersGray.at<float>(i, 2) - 1)*(imageRangePara.dis_max - imageRangePara.dis_min) / 254 + imageRangePara.dis_min;//������ϵ�еľ���ֵ
		PointPolar.at<float>(i, 1) = CornersGray.at<float>(i, 0)*angularResolution + imageRangePara.angle_vertical_min;//������ϵ����ֱ��

		//��ѹ�������������ת����δѹ��ǰ����������
		float scale = cos((floor((PointPolar.at<float>(i, 1) - imageRangePara.angle_vertical_min) / angularResolution + 0.5) / float(imageRangePara.image_height) - 0.5) * acos(double(-1)));
		if (CornersGray.at<float>(i, 1) < imageRangePara.image_width / 2)
		{
			CornersGray.at<float>(i, 1) = (CornersGray.at<float>(i, 1) - imageRangePara.image_width / 2 * (1 - scale)) / scale;
		}
		else
		{
			CornersGray.at<float>(i, 1) = (CornersGray.at<float>(i, 1) - imageRangePara.image_width / 2) / scale + imageRangePara.image_width / 2;
		}

		PointPolar.at<float>(i, 2) = CornersGray.at<float>(i, 1)*angularResolution + imageRangePara.angle_level_min;//������ϵ��ˮƽ��
	}
	cv::Mat PointXYZ = PolarToPointXYZ(PointPolar);//������ת�ռ�����XYZ
	return PointXYZ;
}

//������ʼ��
ImageRangePara SQ_PointCloud::InitImageRangePara(cv::Mat PointPolar, float angularResolution)
{
	ImageRangePara imageRangePara;

	imageRangePara.dis_max = max_mat(PointPolar.col(0).clone());//�������ֵ
	imageRangePara.dis_min = min_mat(PointPolar.col(0).clone());//������Сֵ
	imageRangePara.angle_vertical_max = max_mat(PointPolar.col(1).clone());//��ֱ�����ֵ
	imageRangePara.angle_vertical_min = min_mat(PointPolar.col(1).clone());//��ֱ����Сֵ
	imageRangePara.angle_level_max = max_mat(PointPolar.col(2).clone());//ˮƽ�����ֵ
	imageRangePara.angle_level_min = min_mat(PointPolar.col(2).clone());//ˮƽ����Сֵ

	imageRangePara.image_height = floor(abs(imageRangePara.angle_vertical_max - imageRangePara.angle_vertical_min) / angularResolution + 0.5) + 1;//ͼƬ�ĸ�
	imageRangePara.image_width = floor(abs(imageRangePara.angle_level_max - imageRangePara.angle_level_min) / angularResolution + 0.5) + 1;//ͼƬ�Ŀ�

	return imageRangePara;
}

//ֱ������XYZת��ά�Ҷ�ͼ��
cv::Mat SQ_PointCloud::PointXYZToGreyImage2D(cv::Mat PointMat, float angularResolution)
{
	cv::Mat PointPolar = PointXYZToPolar(PointMat);//ֱ������XYZת������
	ImageRangePara imageRangePara = InitImageRangePara(PointPolar, angularResolution);//��ȡ����

	cv::Mat ImageMat(imageRangePara.image_height, imageRangePara.image_width, CV_8U, cv::Scalar::all(0));//��ά�Ҷ�ͼ��
	cv::Mat AngleMat(imageRangePara.image_height, imageRangePara.image_width, CV_32FC2, cv::Scalar::all(0));//�洢���ƾ����������ĵ��Ƶľ����ĳ�������Ƿ��Ѿ����ڵ��Ʊ�־--�Ƕ�֮��ľ��롢��־

	int row_x = 0, col_y = 0;//���ƶ�Ӧ��������--���ƶ�Ӧ��������
	float angle_row_x = 0, angle_col_y = 0, dis_new = 0;//�洢ÿ���������Ķ�Ӧ����ֱ��--ˮƽ��--�����ĵĵ��Ƶ����ĵ�ľ���
	for (int i = 0; i < PointPolar.rows; i++)
	{
		row_x = floor((PointPolar.at<float>(i, 1) - imageRangePara.angle_vertical_min) / angularResolution + 0.5);//���ƶ�Ӧ��������
		col_y = floor((PointPolar.at<float>(i, 2) - imageRangePara.angle_level_min) / angularResolution + 0.5);//���ƶ�Ӧ��������

		angle_row_x = row_x * angularResolution + angularResolution / 2;//�洢ÿ���������Ķ�Ӧ����ֱ��
		angle_col_y = col_y * angularResolution + angularResolution / 2;//�洢ÿ���������Ķ�Ӧ��ˮƽ��
		dis_new = sqrt((PointPolar.at<float>(i, 1) - angle_row_x)*(PointPolar.at<float>(i, 1) - angle_row_x) +
			(PointPolar.at<float>(i, 2) - angle_col_y)*(PointPolar.at<float>(i, 2) - angle_col_y));//�����ĵĵ��Ƶ����ĵ�ľ���

		if (AngleMat.at<cv::Vec2f>(row_x, col_y)[1] > 1)//ĳ�������Ƿ��Ѿ����ڵ���
		{
			if (dis_new < AngleMat.at<cv::Vec2f>(row_x, col_y)[0])//��Ҫ�ж������ĵ����Ƿ���ӿ�����������
			{
				ImageMat.at<unsigned char>(row_x, col_y) = 254 * (PointPolar.at<float>(i, 0) - imageRangePara.dis_min) / (imageRangePara.dis_max - imageRangePara.dis_min) + 1;//���ƶ�Ӧ�ĻҶ�ֵ
				AngleMat.at<cv::Vec2f>(row_x, col_y)[0] = dis_new;
			}
		}
		else
		{
			ImageMat.at<unsigned char>(row_x, col_y) = 254 * (PointPolar.at<float>(i, 0) - imageRangePara.dis_min) / (imageRangePara.dis_max - imageRangePara.dis_min) + 1;//���ƶ�Ӧ�ĻҶ�ֵ
			AngleMat.at<cv::Vec2f>(row_x, col_y)[0] = dis_new;
			AngleMat.at<cv::Vec2f>(row_x, col_y)[1] = 2;
		}
		//ImageMat.at<unsigned char>(row_x, col_y) = 255*sqrt((PointPolar.at<float>(i, 0) - dis_min) / (dis_max - dis_min));
		//ImageMat.at<unsigned char>(row_x, col_y) = 255 * ((PointPolar.at<float>(i, 0) - dis_min) / (dis_max - dis_min))
		//	*((PointPolar.at<float>(i, 0) - dis_min) / (dis_max - dis_min));
	}
	return ImageMat;
}

////��ֵ
//cv::Mat SQ_PointCloud::DepthImageInterpolation(cv::Mat ImageMat, cv::Mat InOutMat)
//{
//
//}

//�洢ĳ���������ͼ���ڲ������ⲿ 0 - �ⲿ 255 - �ڲ�
cv::Mat SQ_PointCloud::InOutDepthImage(ImageRangePara imageRangePara)
{
	cv::Mat InOutMat(imageRangePara.image_height, imageRangePara.image_width, CV_8U, cv::Scalar(0));
	int col_left = 0, col_right = 0;
	int count_eye = 0;//�۾��е�ĸ���
	float scale = 0;//���ű���
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

//��ֱ������ת�������ͼ--�����۾���ͼ
cv::Mat SQ_PointCloud::PointXYZToDepthImage2D(cv::Mat PointMat, float angularResolution)
{
	cv::Mat PointPolar = PointXYZToPolar(PointMat);//Depth
	ImageRangePara imageRangePara = InitImageRangePara(PointPolar, angularResolution);//��ȡ����

	cv::Mat ImageMat(imageRangePara.image_height, imageRangePara.image_width, CV_8U, cv::Scalar(0));//��ά�Ҷ�ͼ��--����1-255--0��ʾû������
	cv::Mat DepthRowColValueTemp(PointMat.rows, 2, CV_32SC1);//�洢ÿ�����ƴ洢������
	cv::Mat AngleMat(imageRangePara.image_height, imageRangePara.image_width, CV_32FC2, cv::Scalar::all(0));//�洢���ƾ����������ĵ��Ƶľ����ĳ�������Ƿ��Ѿ����ڵ��Ʊ�־--�Ƕ�֮��ľ��롢��־

	int count_eye_kong = 0;//�۾��е�Ϊ�յĸ���
	int count_eye_chongfu = 0;//�۾��е��ظ��ĸ���
	float scale = 0;//���ű���
	int row_x = 0, col_y = 0;//���ƶ�Ӧ��������--���ƶ�Ӧ��������
	float angle_row_x = 0, angle_col_y = 0, dis_new = 0;//�洢ÿ���������Ķ�Ӧ����ֱ��--ˮƽ��--�����ĵĵ��Ƶ����ĵ�ľ���

	for (int i = 0; i < PointPolar.rows; i++)
	{
		row_x = floor((PointPolar.at<float>(i, 1) - imageRangePara.angle_vertical_min) / angularResolution + 0.5);
		col_y = floor((PointPolar.at<float>(i, 2) - imageRangePara.angle_level_min) / angularResolution + 0.5);

		//��δѹ��ǰ����������ת����ѹ�������������
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

		angle_row_x = row_x * angularResolution + angularResolution / 2;//�洢ÿ���������Ķ�Ӧ����ֱ��
		angle_col_y = col_y * angularResolution + angularResolution / 2;//�洢ÿ���������Ķ�Ӧ��ˮƽ��
		dis_new = sqrt((PointPolar.at<float>(i, 1) - angle_row_x)*(PointPolar.at<float>(i, 1) - angle_row_x) +
			(PointPolar.at<float>(i, 2) - angle_col_y)*(PointPolar.at<float>(i, 2) - angle_col_y));//�����ĵĵ��Ƶ����ĵ�ľ���

		if (AngleMat.at<cv::Vec2f>(row_x, col_y)[1] > 1)//ĳ�������Ƿ��Ѿ����ڵ���
		{
			count_eye_chongfu++;
			if (dis_new < AngleMat.at<cv::Vec2f>(row_x, col_y)[0])//��Ҫ�ж������ĵ����Ƿ���ӿ�����������
			{
				ImageMat.at<unsigned char>(row_x, col_y) = 254 * (PointPolar.at<float>(i, 0) - imageRangePara.dis_min) / (imageRangePara.dis_max - imageRangePara.dis_min) + 1;//���ƶ�Ӧ�ĻҶ�ֵ
				
				AngleMat.at<cv::Vec2f>(row_x, col_y)[0] = dis_new;
			}
		}
		else
		{
			count_eye_kong++;
			ImageMat.at<unsigned char>(row_x, col_y) = 254 * (PointPolar.at<float>(i, 0) - imageRangePara.dis_min) / (imageRangePara.dis_max - imageRangePara.dis_min) + 1;//���ƶ�Ӧ�ĻҶ�ֵ
			AngleMat.at<cv::Vec2f>(row_x, col_y)[0] = dis_new;
			AngleMat.at<cv::Vec2f>(row_x, col_y)[1] = 2;
		}

		DepthRowColValueTemp.at<int>(i, 0) = row_x;//�洢ÿ�����ƴ洢����
		DepthRowColValueTemp.at<int>(i, 1) = col_y;//�洢ÿ�����ƴ洢����

	}

	DepthRowColValue = DepthRowColValueTemp;//�洢ÿ�����ƴ洢�������Լ��Ҷ�ֵ
	//�洢ĳ���������ͼ���ڲ������ⲿ 0-�ⲿ 255-�ڲ�
	cv::Mat InOutMat = InOutDepthImage(imageRangePara);
	//AngleMat = DepthImageInterpolation(ImageMat, InOutMat);//��ֵ
	return ImageMat;
}

//��ȡÿ�����ƴ洢�������Լ��Ҷ�ֵ
cv::Mat SQ_PointCloud::GetDepthRowColValue()
{
	return DepthRowColValue;
}

//PCL���ɶ�ά���ͼ
cv::Mat SQ_PointCloud::PCLPointXYZToDepthImage2D(cv::Mat PointMat, float angularResolution)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr = MatToPointXYZPrt(PointMat);
	boost::shared_ptr<pcl::RangeImage> range_image_ptr(new pcl::RangeImage); //����RangeImage����ָ�룩
	range_image_ptr = PCLPointXYZToRangeImage(PointPtr, angularResolution);
	pcl::RangeImage& range_image = *range_image_ptr;  //����

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

//PCL����RangeImage
boost::shared_ptr<pcl::RangeImage> SQ_PointCloud::PCLPointXYZToRangeImage(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr, float angularResolution)
{
	pcl::PointCloud<pcl::PointXYZ>& point_cloud = *PointPtr;//������Ƶı���

	//�ӵ������ݣ��������ͼ��	
	float AngularResolution = angularResolution;//0.5��ת���ȣ��Ƕȷֱ���	
	float maxAngleWidth = pcl::deg2rad(360.0f);//360.0��ת���ȣ�ˮƽ�������Ƕ�
	float maxAngleHeight = pcl::deg2rad(180.0f);//180.0��ת���ȣ���ֱ�����������Ƕ�
	Eigen::Affine3f sensorPose = (Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);//������λ��
	pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME; //CAMERA_FRAME��LASER_FRAME
	float noise_level = 0.0;//���ڵ�Բ�ѯ�����ֵ��Ӱ��ˮƽ
	float min_range = 0.0f;//��С�Ļ�ȡ���룬С������Ϊä��
	int border_size = 1;//���ͼ��ı�Ե
	boost::shared_ptr<pcl::RangeImage> range_image_ptr(new pcl::RangeImage); //����RangeImage����ָ�룩
	pcl::RangeImage& range_image = *range_image_ptr;  //����
	range_image.createFromPointCloud(point_cloud, AngularResolution, maxAngleWidth, maxAngleHeight,
		sensorPose, coordinate_frame, noise_level, min_range, border_size); //�ӵ��ƴ������ͼ��
	//range_image.integrateFarRanges(far_ranges); //����Զ�������
	range_image.setUnseenToMaxRange();//�����в��ɼ��ĵ� ���� ������
	return range_image_ptr;
}

//��Mat���ֵ
float SQ_PointCloud::max_mat(cv::Mat OriginalMat)
{
	double max, min;
	cv::Point min_loc, max_loc;
	cv::minMaxLoc(OriginalMat, &min, &max, &min_loc, &max_loc);
	return max;
}

//��Mat��Сֵ
float SQ_PointCloud::min_mat(cv::Mat OriginalMat)
{
	double max, min;
	cv::Point min_loc, max_loc;
	cv::minMaxLoc(OriginalMat, &min, &max, &min_loc, &max_loc);
	return min;
}
