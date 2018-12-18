#ifndef SQ_QUATERNION_H
#define SQ_QUATERNION_H

#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <QDebug>  
#include <fstream>
#include <string>

//存储四元数的结构体
struct Quaternion{
	float x;
	float y;
	float z;
	float w;
};

//存储绕世界坐标系旋转的角度的结构体--度
struct RotateAngle{
	float angle_x;
	float angle_y;
	float angle_z;
};

//存储绕世界坐标系中点坐标的结构体
struct Point{
	float x;
	float y;
	float z;
};

class SQ_Quaternion{
public:
	SQ_Quaternion();

	Quaternion PointToQuaternion(Point point);//坐标转四元数
	Point QuaternionToPoint(Quaternion q);//四元数转坐标

	Quaternion QuaternionMult(Quaternion q, Quaternion p);//四元数乘法 q*p
	Quaternion QuaternionConjugate(Quaternion q);//共轭四元数
	float QuaternionModule(Quaternion q);//四元数的模
	Quaternion QuaternionInverse(Quaternion q);//四元数的逆

	Quaternion RPYToQuaternion(RotateAngle rotateAngle);//RPY角转四元数
	RotateAngle QuaternionToRPY(Quaternion q);//四元数转RPY角

	Point RotQuaternionPoint(Point point, RotateAngle rotateAngle);//通过四元数进行坐标旋转变换--一个点
	cv::Mat RotQuaternionMat(cv::Mat Point3DOriginal, RotateAngle rotateAngle);//通过四元数进行坐标旋转变换--矩阵格式的点坐标

	cv::Mat RotTransMat(cv::Mat Point3DOriginal, cv::Mat rotTransMat);//旋转平移矩阵实现坐标转换
	cv::Mat RotTransMatRight(cv::Mat Point3DOriginal, cv::Mat rotTransMat);


	cv::Mat RotRPYMat(cv::Mat Point3DOriginal, RotateAngle rotateAngle);//旋转坐标转换
	cv::Mat TransMoveMat(cv::Mat Point3DDisplay, float move_world_x, float move_world_y);//平移操作
	cv::Mat TransScaleMat(cv::Mat Point3DDisplay,int cursor_opengl_x, int cursor_opengl_y, float ScaleRatio);//定点缩放

	cv::Mat RotMat_X(float rotate_x);//计算绕X轴的旋转矩阵 4*4
	cv::Mat RotMat_Y(float rotate_y);//计算绕Y轴的旋转矩阵 4*4
	cv::Mat RotMat_Z(float rotate_z);//计算绕Y轴的旋转矩阵 4*4

	cv::Mat RotMat(float x, float y, float z, float rotate);//绕任意轴旋转角度 4*4

	cv::Mat TransMat_X(float trans_x);//计算绕X轴的平移矩阵 4*4
	cv::Mat TransMat_Y(float trans_y);//计算绕Y轴的平移矩阵 4*4
	cv::Mat TransMat_Z(float trans_z);//计算绕Y轴的平移矩阵 4*4
};
#endif