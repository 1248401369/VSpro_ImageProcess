#ifndef SQ_POINTCLOUD_H
#define SQ_POINTCLOUD_H

//#include <vtkAutoInit.h> 
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/keypoints/uniform_sampling.h>
#include <pcl/surface/mls.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <opencv2/opencv.hpp>
#include <QTime>
#include <qDebug>
#include <pcl/visualization/cloud_viewer.h>//��ʾ
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/features/principal_curvatures.h>
#include <pcl/io/io.h>
#include <pcl/keypoints/harris_3d.h>
#include <pcl/keypoints/harris_2d.h>
#include <cstdlib>
#include <vector>
#include <pcl/range_image/range_image.h>
#include <pcl/visualization/range_image_visualizer.h>
#include <boost/thread/thread.hpp>
#include <math.h>
struct ImageRangePara
{
	float dis_max, dis_min;//��������ԭ��ľ���ֵ
	float angle_vertical_max, angle_vertical_min,
		angle_level_max, angle_level_min;//������ϵ����ֱ�ǡ�ˮƽ�ǵķ�Χ
	int image_width, image_height;//��ά�Ҷ�ͼ�Ĵ�С
};

class SQ_PointCloud
{
public:
	SQ_PointCloud();
	~SQ_PointCloud();

	cv::Mat PCLDecreaseSampleToMat(cv::Mat PointMat, float para);//�������ݽ�����
	cv::Mat PCLUniformSampleToMat(cv::Mat PointMat, float para);//�������ݾ��Ȳ���
	cv::Mat PCLIncreaseSampleToMat(cv::Mat PointMat);//��������������
	cv::Mat PCLIncreaseSampleToMat(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr);//��������������
	 
	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLDecreaseSampleToPtr(cv::Mat PointMat, float para);//�������ݽ�����
	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLUniformSampleToPtr(cv::Mat PointMat, float para);//�������ݾ��Ȳ���
	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLIncreaseSampleToPtr(cv::Mat PointMat);//��������������

	pcl::PointCloud<pcl::Normal>::Ptr PCLGetNormalToPtr(cv::Mat PointMat);//��ȡ���Ƶķ�����
	cv::Mat PCLGetNormalToMat(cv::Mat PointMat);//��ȡ���Ƶķ�����

	cv::Mat PCLGetCurvatureToMat(cv::Mat PointMat);//��ȡ���Ƶ�����

	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLHarris3DToPtr(cv::Mat PointMat);//����Harris3D��ʵ�ֽǵ���
	cv::Mat PCLHarris3DToMat(cv::Mat PointMat);//����Harris3D��ʵ�ֽǵ���

	void PCLShow(cv::Mat PointMat1, cv::Mat PointMat2);//��ʾ
	void PCLShow(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr1, pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr2);//��ʾ
	void PCLShow(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr);//��ʾ


	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLReadPCDToPtr(QString path);//��ȡ��������(.pcd)��ʽ
	cv::Mat PCLReadPCDToMat(QString path);//��ȡ��������(.pcd)��ʽ

	cv::Mat PointXYZToPolar(cv::Mat PointMat);//ֱ������XYZת������
	cv::Mat PolarToPointXYZ(cv::Mat PointMat);//������ת�ռ�����XYZ
	cv::Mat GreyImage2DToPointXYZ(cv::Mat CornersGray, float angularResolution, ImageRangePara imageRangePara);//��ά�Ҷ�ͼת�ռ�����XYZ
	cv::Mat DepthImage2DToPointXYZ(cv::Mat CornersGray, float angularResolution, ImageRangePara imageRangePara);//��ά���ͼת�ռ�����XYZ
	ImageRangePara InitImageRangePara(cv::Mat PointPolar, float angularResolution);//������ʼ��
	cv::Mat PointXYZToGreyImage2D(cv::Mat PointMat, float angularResolution);//ֱ������XYZת��ά�Ҷ�ͼ��
	cv::Mat InOutDepthImage(ImageRangePara imageRangePara);//�洢ĳ���������ͼ���ڲ������ⲿ 0 - �ⲿ 255 - �ڲ�
	cv::Mat PointXYZToDepthImage2D(cv::Mat PointMat, float angularResolution);//��ֱ������ת�������ͼ--�����۾���ͼ
	cv::Mat GetDepthRowColValue();//��ȡÿ�����ƴ洢������

	cv::Mat PCLPointXYZToDepthImage2D(cv::Mat PointMat, float angularResolution);//PCL���ɶ�ά���ͼ
	boost::shared_ptr<pcl::RangeImage> PCLPointXYZToRangeImage(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr, float angularResolution);//PCL����RangeImage

	cv::Mat InitCube(float resolution);//��ʼ��һ��������
	cv::Mat InitFace(char c, float resolution);//��ʼ��һ��ƽ��
private:
	cv::Mat DepthRowColValue;//�洢ÿ�����ƴ洢������
	cv::Mat PointXYZPrtToMat(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr);//����ָ��תMat
	pcl::PointCloud<pcl::PointXYZ>::Ptr MatToPointXYZPrt(cv::Mat PointMat);//Matת����ָ��

	cv::Mat NormalPrtToMat(pcl::PointCloud<pcl::Normal>::Ptr NormalPtr);//������ָ��תMat
	pcl::PointCloud<pcl::Normal>::Ptr MatToNormalPrt(cv::Mat NormalMat);//Matת������ָ��

	float max_mat(cv::Mat OriginalMat);//��Mat���ֵ
	float min_mat(cv::Mat OriginalMat);//��Mat��Сֵ
};
#endif 