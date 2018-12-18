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

//�洢��Ԫ���Ľṹ��
struct Quaternion{
	float x;
	float y;
	float z;
	float w;
};

//�洢����������ϵ��ת�ĽǶȵĽṹ��--��
struct RotateAngle{
	float angle_x;
	float angle_y;
	float angle_z;
};

//�洢����������ϵ�е�����Ľṹ��
struct Point{
	float x;
	float y;
	float z;
};

class SQ_Quaternion{
public:
	SQ_Quaternion();

	Quaternion PointToQuaternion(Point point);//����ת��Ԫ��
	Point QuaternionToPoint(Quaternion q);//��Ԫ��ת����

	Quaternion QuaternionMult(Quaternion q, Quaternion p);//��Ԫ���˷� q*p
	Quaternion QuaternionConjugate(Quaternion q);//������Ԫ��
	float QuaternionModule(Quaternion q);//��Ԫ����ģ
	Quaternion QuaternionInverse(Quaternion q);//��Ԫ������

	Quaternion RPYToQuaternion(RotateAngle rotateAngle);//RPY��ת��Ԫ��
	RotateAngle QuaternionToRPY(Quaternion q);//��Ԫ��תRPY��

	Point RotQuaternionPoint(Point point, RotateAngle rotateAngle);//ͨ����Ԫ������������ת�任--һ����
	cv::Mat RotQuaternionMat(cv::Mat Point3DOriginal, RotateAngle rotateAngle);//ͨ����Ԫ������������ת�任--�����ʽ�ĵ�����

	cv::Mat RotTransMat(cv::Mat Point3DOriginal, cv::Mat rotTransMat);//��תƽ�ƾ���ʵ������ת��
	cv::Mat RotTransMatRight(cv::Mat Point3DOriginal, cv::Mat rotTransMat);


	cv::Mat RotRPYMat(cv::Mat Point3DOriginal, RotateAngle rotateAngle);//��ת����ת��
	cv::Mat TransMoveMat(cv::Mat Point3DDisplay, float move_world_x, float move_world_y);//ƽ�Ʋ���
	cv::Mat TransScaleMat(cv::Mat Point3DDisplay,int cursor_opengl_x, int cursor_opengl_y, float ScaleRatio);//��������

	cv::Mat RotMat_X(float rotate_x);//������X�����ת���� 4*4
	cv::Mat RotMat_Y(float rotate_y);//������Y�����ת���� 4*4
	cv::Mat RotMat_Z(float rotate_z);//������Y�����ת���� 4*4

	cv::Mat RotMat(float x, float y, float z, float rotate);//����������ת�Ƕ� 4*4

	cv::Mat TransMat_X(float trans_x);//������X���ƽ�ƾ��� 4*4
	cv::Mat TransMat_Y(float trans_y);//������Y���ƽ�ƾ��� 4*4
	cv::Mat TransMat_Z(float trans_z);//������Y���ƽ�ƾ��� 4*4
};
#endif