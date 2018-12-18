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
#include <pcl/visualization/cloud_viewer.h>//显示
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
	float dis_max, dis_min;//距离中心原点的距离值
	float angle_vertical_max, angle_vertical_min,
		angle_level_max, angle_level_min;//球坐标系中竖直角、水平角的范围
	int image_width, image_height;//二维灰度图的大小
};

class SQ_PointCloud
{
public:
	SQ_PointCloud();
	~SQ_PointCloud();

	cv::Mat PCLDecreaseSampleToMat(cv::Mat PointMat, float para);//点云数据降采样
	cv::Mat PCLUniformSampleToMat(cv::Mat PointMat, float para);//点云数据均匀采样
	cv::Mat PCLIncreaseSampleToMat(cv::Mat PointMat);//点云数据增采样
	cv::Mat PCLIncreaseSampleToMat(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr);//点云数据增采样
	 
	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLDecreaseSampleToPtr(cv::Mat PointMat, float para);//点云数据降采样
	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLUniformSampleToPtr(cv::Mat PointMat, float para);//点云数据均匀采样
	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLIncreaseSampleToPtr(cv::Mat PointMat);//点云数据增采样

	pcl::PointCloud<pcl::Normal>::Ptr PCLGetNormalToPtr(cv::Mat PointMat);//获取点云的法向量
	cv::Mat PCLGetNormalToMat(cv::Mat PointMat);//获取点云的法向量

	cv::Mat PCLGetCurvatureToMat(cv::Mat PointMat);//获取点云的曲率

	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLHarris3DToPtr(cv::Mat PointMat);//利用Harris3D是实现角点检测
	cv::Mat PCLHarris3DToMat(cv::Mat PointMat);//利用Harris3D是实现角点检测

	void PCLShow(cv::Mat PointMat1, cv::Mat PointMat2);//显示
	void PCLShow(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr1, pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr2);//显示
	void PCLShow(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr);//显示


	pcl::PointCloud<pcl::PointXYZ>::Ptr PCLReadPCDToPtr(QString path);//读取点云数据(.pcd)格式
	cv::Mat PCLReadPCDToMat(QString path);//读取点云数据(.pcd)格式

	cv::Mat PointXYZToPolar(cv::Mat PointMat);//直角坐标XYZ转球坐标
	cv::Mat PolarToPointXYZ(cv::Mat PointMat);//球坐标转空间坐标XYZ
	cv::Mat GreyImage2DToPointXYZ(cv::Mat CornersGray, float angularResolution, ImageRangePara imageRangePara);//二维灰度图转空间坐标XYZ
	cv::Mat DepthImage2DToPointXYZ(cv::Mat CornersGray, float angularResolution, ImageRangePara imageRangePara);//二维深度图转空间坐标XYZ
	ImageRangePara InitImageRangePara(cv::Mat PointPolar, float angularResolution);//参数初始化
	cv::Mat PointXYZToGreyImage2D(cv::Mat PointMat, float angularResolution);//直角坐标XYZ转二维灰度图像
	cv::Mat InOutDepthImage(ImageRangePara imageRangePara);//存储某像素在深度图的内部还是外部 0 - 外部 255 - 内部
	cv::Mat PointXYZToDepthImage2D(cv::Mat PointMat, float angularResolution);//由直角坐标转化成深度图--类似眼睛的图
	cv::Mat GetDepthRowColValue();//获取每个点云存储的行列

	cv::Mat PCLPointXYZToDepthImage2D(cv::Mat PointMat, float angularResolution);//PCL生成二维深度图
	boost::shared_ptr<pcl::RangeImage> PCLPointXYZToRangeImage(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr, float angularResolution);//PCL生成RangeImage

	cv::Mat InitCube(float resolution);//初始化一个立方体
	cv::Mat InitFace(char c, float resolution);//初始化一个平面
private:
	cv::Mat DepthRowColValue;//存储每个点云存储的行列
	cv::Mat PointXYZPrtToMat(pcl::PointCloud<pcl::PointXYZ>::Ptr PointPtr);//点云指针转Mat
	pcl::PointCloud<pcl::PointXYZ>::Ptr MatToPointXYZPrt(cv::Mat PointMat);//Mat转点云指针

	cv::Mat NormalPrtToMat(pcl::PointCloud<pcl::Normal>::Ptr NormalPtr);//法向量指针转Mat
	pcl::PointCloud<pcl::Normal>::Ptr MatToNormalPrt(cv::Mat NormalMat);//Mat转法向量指针

	float max_mat(cv::Mat OriginalMat);//求Mat最大值
	float min_mat(cv::Mat OriginalMat);//求Mat最小值
};
#endif 