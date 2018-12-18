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
//���ڶ�ȡ.stl�ļ��е����ݣ�.stl�ļ�����solidworks�������
//********************************

//�ļ�ͷ����84�ֽ�
struct Head
{
	wchar_t partName[80];//�������
	int  faceNum;//�����Ŀ
};

//�㣬����float���͵ģ���СΪ12�ֽ�
struct PointOne
{
	float x;
	float y;
	float z;
};
//����
struct Normal
{
	float i;
	float j;
	float k;
};

//�����棬��һ�����ߣ������㣬��һ�����ֽڵı����һ��50�ֽ�
struct Face
{
	Normal normal;
	PointOne  p1;
	PointOne  p2;
	PointOne  p3;
	char  info[2];//�������ݣ����Բ��ù�
};

//�����棬��һ�����ߣ������� ASCII
struct FaceA
{
	Normal normal;
	PointOne vertex1;
	PointOne vertex2;
	PointOne vertex3;
};

//��������Ƭ���������
struct Faces
{
	FaceA data;
	Faces *pointer;
};

//��ά�������ĵ��������󳤶�
struct CenterPoint_Range
{
	float center_x;
	float center_y;
	float center_z;
	float maxlength;
};

//��ά�������ĵ�����
struct CenterPoint
{
	float center_x;
	float center_y;
	float center_z;
};

class SQ_StlRead{
public:
	SQ_StlRead();

	SQ_PointCloud *pointcloud;//���ƿ�Ķ���

	cv::Mat PointCloudInfo(QStringList path);//��ȡ������Ϣ
	cv::Mat PointCloudOriginalInfo(QStringList path);//��ȡԭʼ�ĵ�����Ϣ
	
	////////////////cv::Mat NormalVectorProcessInfo(QStringList path);//��ȡ��������Ϣ--�����--���������������
	cv::Mat TrianglePatchInfo(QStringList path);//��ȡ��������Ϣ
	cv::Mat TrianglePatchOriginalInfo(QStringList path);//��ȡԭʼ����������Ϣ

	////////////////cv::Mat PointALLInfo(QStringList path);//��ȡ������ͷ�������Ϣ
	////////////////cv::Mat PointALLProcessInfo(QStringList path);//��ȡ������ͷ�������Ϣ���������������

	CenterPoint_Range GetCenterPoint(cv::Mat PointOriginalMat, int type);//��ά�������ĵ��������󳤶�
	CenterPoint GetCenterPointOnly(cv::Mat PointOriginalMat, int type);//��ά�������ĵ�����
	cv::Mat ChangeCenterRange(cv::Mat PointOriginalMat, int type);//��ʽת��--�ı����ĵ�
	cv::Mat ChangeCenterRange(cv::Mat PointOriginalMat, CenterPoint_Range centerPoint_Range, int type);//��ʽת��--�ı����ĵ�


	cv::Mat MergeRows(cv::Mat A, cv::Mat B);//����ƴ��-A=[A;B]
	//type=1:������   type=2:������  type=3:��������������
	cv::Mat StlPointInfo(char* path, int type);//��ȡ.stl�ļ�--��������������������Ϣ

	cv::Mat PointCloudDeWeight(cv::Mat PointOriginalMat);//����ȥ��

	//�������� ���յ�һ�С��ڶ��С������е����ȼ�˳���������
	//�ȿ���һ�е����ݵĴ�С������һ���������ʱ���ٿ��ڶ������ݵĴ�С���Դ�����
	//U:unequal to  E:equal to
	cv::Mat SortAscendingDeleteEEU(cv::Mat PointOriginalMat);//������ǰ����Ԫ����ȣ��Ե����н�������ɾ����ͬ������
	cv::Mat SortAscendingDeleteEUU(cv::Mat PointOriginalMat);//������ǰһ��Ԫ����ȣ��Եڶ������н�������ɾ����ͬ������
	////////////////cv::Mat SortAscendingDeleteUUU(cv::Mat PointOriginalMat);//������Ԫ�ض�����ȣ��Ե�һ���������н�������ɾ����ͬ������

	cv::Mat SortAscendingEEU(cv::Mat PointOriginalMat);//������ǰ����Ԫ����ȣ��Ե����н�������
	////////////////cv::Mat SortAscendingEUU(cv::Mat PointOriginalMat);//������ǰһ��Ԫ����ȣ��Եڶ������н�������
	////////////////cv::Mat SortAscendingUUU(cv::Mat PointOriginalMat);//������Ԫ�ض�����ȣ��Ե�һ���������н�������

	float mean_mat(cv::Mat OriginalMat);//��ͨ��Mat��ֵ
	float max_mat(cv::Mat OriginalMat);//��Mat���ֵ
	float min_mat(cv::Mat OriginalMat);//��Mat��Сֵ

private:

	cv::Mat BinaryStlPointInfo(char* path, int type);//��ȡ�����Ƹ�ʽ��.stl�ļ�
	cv::Mat AsciiStlPointInfo(char* path, int type);//��ȡASCII��ʽ��.stl�ļ�
	int StlType(char* path);//�ж�.stl�ļ�����

	cv::Mat SQ_StlRead::ReadAllStlPoint(QStringList path, int type);//��ȡ���.stl�ļ�������

	float max_four(float first, float second, float third, float fourth);//�����ĸ����е����ֵ
	float min_four(float first, float second, float third, float fourth);//�����ĸ����е���Сֵ

private:
	float error = 0.1;
	
};
#endif

