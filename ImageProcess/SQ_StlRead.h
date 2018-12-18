#ifndef SQ_STLREAD_H
#define SQ_STLREAD_H

#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <QDebug>  
#include <fstream>
#include <string>
#include "SQ_PointCloud.h"

//********************************
//用于读取.stl文件中的数据，.stl文件可由solidworks软件生成
//********************************

//文件头，共84字节
struct Head
{
	wchar_t partName[80];//零件名称
	int  faceNum;//面的数目
};

//点，三个float类型的，大小为12字节
struct PointOne
{
	float x;
	float y;
	float z;
};
//法线
struct Normal
{
	float i;
	float j;
	float k;
};

//三角面，由一个法线，三个点，和一个两字节的保留项，一共50字节
struct Face
{
	Normal normal;
	PointOne  p1;
	PointOne  p2;
	PointOne  p3;
	char  info[2];//保留数据，可以不用管
};

//三角面，由一个法线，三个点 ASCII
struct FaceA
{
	Normal normal;
	PointOne vertex1;
	PointOne vertex2;
	PointOne vertex3;
};

//接收三角片面的链表结点
struct Faces
{
	FaceA data;
	Faces *pointer;
};

//三维物体中心点坐标和最大长度
struct CenterPoint_Range
{
	float center_x;
	float center_y;
	float center_z;
	float maxlength;
};

//三维物体中心点坐标
struct CenterPoint
{
	float center_x;
	float center_y;
	float center_z;
};

class SQ_StlRead{
public:
	SQ_StlRead();

	SQ_PointCloud *pointcloud;//点云库的对象

	cv::Mat PointCloudInfo(QStringList path);//读取点云信息
	cv::Mat PointCloudOriginalInfo(QStringList path);//读取原始的点云信息
	
	////////////////cv::Mat NormalVectorProcessInfo(QStringList path);//读取法向量信息--处理过--起点是三角面中心
	cv::Mat TrianglePatchInfo(QStringList path);//读取三角面信息
	cv::Mat TrianglePatchOriginalInfo(QStringList path);//读取原始的三角面信息

	////////////////cv::Mat PointALLInfo(QStringList path);//读取三角面和法向量信息
	////////////////cv::Mat PointALLProcessInfo(QStringList path);//读取三角面和法向量信息（法向量处理过）

	CenterPoint_Range GetCenterPoint(cv::Mat PointOriginalMat, int type);//三维物体中心点坐标和最大长度
	CenterPoint GetCenterPointOnly(cv::Mat PointOriginalMat, int type);//三维物体中心点坐标
	cv::Mat ChangeCenterRange(cv::Mat PointOriginalMat, int type);//格式转换--改变中心点
	cv::Mat ChangeCenterRange(cv::Mat PointOriginalMat, CenterPoint_Range centerPoint_Range, int type);//格式转换--改变中心点


	cv::Mat MergeRows(cv::Mat A, cv::Mat B);//矩阵拼接-A=[A;B]
	//type=1:法向量   type=2:三角面  type=3:法向量和三角面
	cv::Mat StlPointInfo(char* path, int type);//读取.stl文件--包括法向量和三角面信息

	cv::Mat PointCloudDeWeight(cv::Mat PointOriginalMat);//点云去重

	//升序排列 按照第一列、第二列、第三列的优先级顺序进行排序
	//先看第一列的数据的大小，当第一列数据相等时，再看第二列数据的大小，以此类推
	//U:unequal to  E:equal to
	cv::Mat SortAscendingDeleteEEU(cv::Mat PointOriginalMat);//三列中前两列元素相等，对第三列进行排序并删除相同的数据
	cv::Mat SortAscendingDeleteEUU(cv::Mat PointOriginalMat);//三列中前一列元素相等，对第二、三列进行排序并删除相同的数据
	////////////////cv::Mat SortAscendingDeleteUUU(cv::Mat PointOriginalMat);//三列中元素都不相等，对第一、二、三列进行排序并删除相同的数据

	cv::Mat SortAscendingEEU(cv::Mat PointOriginalMat);//三列中前两列元素相等，对第三列进行排序
	////////////////cv::Mat SortAscendingEUU(cv::Mat PointOriginalMat);//三列中前一列元素相等，对第二、三列进行排序
	////////////////cv::Mat SortAscendingUUU(cv::Mat PointOriginalMat);//三列中元素都不相等，对第一、二、三列进行排序

	float mean_mat(cv::Mat OriginalMat);//求单通道Mat均值
	float max_mat(cv::Mat OriginalMat);//求Mat最大值
	float min_mat(cv::Mat OriginalMat);//求Mat最小值

private:

	cv::Mat BinaryStlPointInfo(char* path, int type);//读取二进制格式的.stl文件
	cv::Mat AsciiStlPointInfo(char* path, int type);//读取ASCII格式的.stl文件
	int StlType(char* path);//判断.stl文件类型

	cv::Mat SQ_StlRead::ReadAllStlPoint(QStringList path, int type);//读取多个.stl文件的数据

	float max_four(float first, float second, float third, float fourth);//计算四个数中的最大值
	float min_four(float first, float second, float third, float fourth);//计算四个数中的最小值

private:
	float error = 0.1;
	
};
#endif

