#include "SQ_Quaternion.h"

SQ_Quaternion::SQ_Quaternion()
{

}

//����ת��Ԫ��
Quaternion SQ_Quaternion::PointToQuaternion(Point point)
{
	Quaternion QuatTemp;

	QuatTemp.x = point.x;
	QuatTemp.y = point.y;
	QuatTemp.z = point.z;
	QuatTemp.w = 0;

	return QuatTemp;

}

//��Ԫ��ת����
Point SQ_Quaternion::QuaternionToPoint(Quaternion q)
{
	Point PointTemp;

	PointTemp.x = q.x;
	PointTemp.y = q.y;
	PointTemp.z = q.z;

	return PointTemp;
}

//��Ԫ���˷� q*p
Quaternion SQ_Quaternion::QuaternionMult(Quaternion q, Quaternion p)
{
	Quaternion QuatTemp;

	QuatTemp.x = q.y*p.z - q.z*p.y + q.x*p.w + q.w*p.x;
	QuatTemp.y = q.z*p.x - q.x*p.z + q.y*p.w + q.w*p.y;
	QuatTemp.z = q.x*p.y - q.y*p.x + q.z*p.w + q.w*p.z;
	QuatTemp.w = q.w*p.w - q.x*p.x - q.y*p.y - q.z*p.z;

	return QuatTemp;
}

//������Ԫ��
Quaternion SQ_Quaternion::QuaternionConjugate(Quaternion q)
{
	Quaternion QuatTemp;

	QuatTemp.x = -q.x;
	QuatTemp.y = -q.y;
	QuatTemp.z = -q.z;
	QuatTemp.w = q.w;

	return QuatTemp;
}

//��Ԫ����ģ
float SQ_Quaternion::QuaternionModule(Quaternion q)
{
	float QuaternionModuleTemp;

	QuaternionModuleTemp = sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);

	return QuaternionModuleTemp;
}

//��Ԫ������
Quaternion SQ_Quaternion::QuaternionInverse(Quaternion q)
{
	Quaternion QuatTemp;

	QuatTemp.x = -q.x / QuaternionModule(q);
	QuatTemp.y = -q.y / QuaternionModule(q);
	QuatTemp.z = -q.z / QuaternionModule(q);
	QuatTemp.w = q.w / QuaternionModule(q);

	return QuatTemp;
}

//RPY��ת��Ԫ��
Quaternion SQ_Quaternion::RPYToQuaternion(RotateAngle rotateAngle)
{
	Quaternion QuatTemp;

	float sin_d2_x = sin(rotateAngle.angle_x / 57.3), cos_d2_x = cos(rotateAngle.angle_x / 57.3),
		sin_d2_y = sin(rotateAngle.angle_y / 57.3), cos_d2_y = cos(rotateAngle.angle_y / 57.3),
		sin_d2_z = sin(rotateAngle.angle_z / 57.3), cos_d2_z = cos(rotateAngle.angle_z / 57.3);

	QuatTemp.x = cos_d2_y*cos_d2_z*sin_d2_x - sin_d2_y*sin_d2_z*cos_d2_x;
	QuatTemp.y = sin_d2_y*cos_d2_z*cos_d2_x + cos_d2_y*sin_d2_z*sin_d2_x;
	QuatTemp.z = cos_d2_y*sin_d2_z*cos_d2_x - sin_d2_y*cos_d2_z*sin_d2_x;
	QuatTemp.w = cos_d2_y*cos_d2_z*cos_d2_x + sin_d2_y*sin_d2_z*sin_d2_x;

	return QuatTemp;
}

//��Ԫ��תRPY��
RotateAngle SQ_Quaternion::QuaternionToRPY(Quaternion q)
{
	RotateAngle RotateAngleTemp;

	RotateAngleTemp.angle_x = 57.3*atan2(2 * (q.w*q.x + q.y*q.z), 1 - 2 * (q.x*q.x + q.y*q.y));
	RotateAngleTemp.angle_y = 57.3*asin(2 * (q.w*q.y - q.x*q.z));
	RotateAngleTemp.angle_z = 57.3*atan2(2 * (q.w*q.z + q.x*q.y), 1 - 2 * (q.y*q.y + q.z*q.z));

	return RotateAngleTemp;
}


//ͨ����Ԫ������������ת�任--һ����
Point SQ_Quaternion::RotQuaternionPoint(Point point, RotateAngle rotateAngle)
{
	Point PointTemp;
	Quaternion PointToQuatTemp;//�洢����ת������Ԫ��
	Quaternion RPYToQuatTemp;//�洢RPYת������Ԫ��
	Quaternion RPYToQuatInvTemp;//�洢RPYת������Ԫ��

	PointToQuatTemp = PointToQuaternion(point);//��ת��Ԫ��
	RPYToQuatTemp = RPYToQuaternion(rotateAngle);//RPY��ת��Ԫ��
	RPYToQuatInvTemp = QuaternionInverse(RPYToQuatTemp);//��Ԫ������

	PointToQuatTemp = QuaternionMult(RPYToQuatTemp, PointToQuatTemp);//��Ԫ����ת����
	PointToQuatTemp = QuaternionMult(PointToQuatTemp, RPYToQuatInvTemp);

	PointTemp = QuaternionToPoint(PointToQuatTemp);//��Ԫ��ת����

	return PointTemp;
}

//ͨ����Ԫ������������ת�任--�����ʽ�ĵ�����
cv::Mat SQ_Quaternion::RotQuaternionMat(cv::Mat Point3DOriginal, RotateAngle rotateAngle)
{
	cv::Mat Point3DResult(Point3DOriginal.rows, Point3DOriginal.cols, CV_32FC1);
	Point PointTemp;
	for (int i = 0; i < Point3DOriginal.rows; i++)
	{
		PointTemp.x = Point3DOriginal.at<float>(i, 0);
		PointTemp.y = Point3DOriginal.at<float>(i, 1);
		PointTemp.z = Point3DOriginal.at<float>(i, 2);

		PointTemp = RotQuaternionPoint(PointTemp, rotateAngle);

		Point3DResult.at<float>(i, 0) = PointTemp.x;
		Point3DResult.at<float>(i, 1) = PointTemp.y;
		Point3DResult.at<float>(i, 2) = PointTemp.z;
	}
	return Point3DResult;
}

//��תƽ�ƾ���ʵ������ת��--���
cv::Mat SQ_Quaternion::RotTransMat(cv::Mat Point3DOriginal, cv::Mat rotTransMat)
{
	cv::Mat Point3DResult(Point3DOriginal.rows, Point3DOriginal.cols, CV_32FC1);
	cv::Mat PointMatrix(4, 1, CV_32FC1);//�洢ÿ���������
	float c00 = rotTransMat.at<float>(0, 0), c01 = rotTransMat.at<float>(0, 1), c02 = rotTransMat.at<float>(0, 2), c03 = rotTransMat.at<float>(0, 3),
		c10 = rotTransMat.at<float>(1, 0), c11 = rotTransMat.at<float>(1, 1), c12 = rotTransMat.at<float>(1, 2), c13 = rotTransMat.at<float>(1, 3),
		c20 = rotTransMat.at<float>(2, 0), c21 = rotTransMat.at<float>(2, 1), c22 = rotTransMat.at<float>(2, 2), c23 = rotTransMat.at<float>(2, 3);

	for (int i = 0; i < Point3DOriginal.rows; i++)
	{
		////Point3DResult.at<float>(i, 0) = c00*Point3DOriginal.at<float>(i, 0) + c01*Point3DOriginal.at<float>(i, 1) + c02*Point3DOriginal.at<float>(i, 2) + c03;
		////Point3DResult.at<float>(i, 1) = c10*Point3DOriginal.at<float>(i, 0) + c11*Point3DOriginal.at<float>(i, 1) + c12*Point3DOriginal.at<float>(i, 2) + c13;
		////Point3DResult.at<float>(i, 2) = c20*Point3DOriginal.at<float>(i, 0) + c21*Point3DOriginal.at<float>(i, 1) + c22*Point3DOriginal.at<float>(i, 2) + c23;

		Point3DResult.ptr<float>(i)[0] = c00*Point3DOriginal.ptr<float>(i)[0] + c01*Point3DOriginal.ptr<float>(i)[1] + c02*Point3DOriginal.ptr<float>(i)[2] + c03;
		Point3DResult.ptr<float>(i)[1] = c10*Point3DOriginal.ptr<float>(i)[0] + c11*Point3DOriginal.ptr<float>(i)[1] + c12*Point3DOriginal.ptr<float>(i)[2] + c13;
		Point3DResult.ptr<float>(i)[2] = c20*Point3DOriginal.ptr<float>(i)[0] + c21*Point3DOriginal.ptr<float>(i)[1] + c22*Point3DOriginal.ptr<float>(i)[2] + c23;		
	}

	////for (int i = 0; i < Point3DOriginal.rows; i++)
	////{
	////	PointMatrix.at<float>(0, 0) = Point3DOriginal.at<float>(i, 0);
	////	PointMatrix.at<float>(1, 0) = Point3DOriginal.at<float>(i, 1);
	////	PointMatrix.at<float>(2, 0) = Point3DOriginal.at<float>(i, 2);
	////	PointMatrix.at<float>(3, 0) = 1;

	////	PointMatrix = rotTransMat*PointMatrix;�ٶ�̫��

	////	Point3DResult.at<float>(i, 0) = PointMatrix.at<float>(0, 0);
	////	Point3DResult.at<float>(i, 1) = PointMatrix.at<float>(1, 0);
	////	Point3DResult.at<float>(i, 2) = PointMatrix.at<float>(2, 0);
	////}
	return Point3DResult;
}

//��תƽ�ƾ���ʵ������ת��--�ҳ�
cv::Mat SQ_Quaternion::RotTransMatRight(cv::Mat Point3DOriginal, cv::Mat rotTransMat)
{
	cv::Mat Point3DResult(Point3DOriginal.rows, Point3DOriginal.cols, CV_32FC1);

	float c00 = rotTransMat.at<float>(0, 0), c01 = rotTransMat.at<float>(0, 1), c02 = rotTransMat.at<float>(0, 2), c03 = rotTransMat.at<float>(0, 3),
		c10 = rotTransMat.at<float>(1, 0), c11 = rotTransMat.at<float>(1, 1), c12 = rotTransMat.at<float>(1, 2), c13 = rotTransMat.at<float>(1, 3),
		c20 = rotTransMat.at<float>(2, 0), c21 = rotTransMat.at<float>(2, 1), c22 = rotTransMat.at<float>(2, 2), c23 = rotTransMat.at<float>(2, 3);

	for (int i = 0; i < Point3DOriginal.rows; i++)
	{
		Point3DResult.at<float>(i, 0) = c00*Point3DOriginal.at<float>(i, 0) + c10*Point3DOriginal.at<float>(i, 1) + c20*Point3DOriginal.at<float>(i, 2);
		Point3DResult.at<float>(i, 1) = c01*Point3DOriginal.at<float>(i, 0) + c11*Point3DOriginal.at<float>(i, 1) + c21*Point3DOriginal.at<float>(i, 2);
		Point3DResult.at<float>(i, 2) = c02*Point3DOriginal.at<float>(i, 0) + c12*Point3DOriginal.at<float>(i, 1) + c22*Point3DOriginal.at<float>(i, 2);
	}
	return Point3DResult;
}


//��ת����ת��
cv::Mat SQ_Quaternion::RotRPYMat(cv::Mat Point3DOriginal, RotateAngle rotateAngle)
{
	cv::Mat Point3DResult(Point3DOriginal.rows, Point3DOriginal.cols, CV_32FC1);
	//*********************ֱ�Ӽ���**********************
	float sin_x = sin(rotateAngle.angle_x / 57.3), sin_y = sin(rotateAngle.angle_y / 57.3), sin_z = sin(rotateAngle.angle_z / 57.3),
		cos_x = cos(rotateAngle.angle_x / 57.3), cos_y = cos(rotateAngle.angle_y / 57.3), cos_z = cos(rotateAngle.angle_z / 57.3);
	float c11 = cos_y*cos_z, c12 = sin_x*sin_y*cos_z - cos_x*sin_z, c13 = cos_x*sin_y*cos_z + sin_x*sin_z,
		c21 = cos_y*sin_z, c22 = sin_x*sin_y*sin_z + cos_x*cos_z, c23 = cos_x*sin_y*sin_z - sin_x*cos_z,
		c31 = -sin_y, c32 = sin_x*cos_y, c33 = cos_x*cos_y;
	for (int i = 0; i < Point3DOriginal.rows; i++)
	{
		//ŷ���任����ΪZ*Y*X
		Point3DResult.at<float>(i, 0) = Point3DOriginal.at<float>(i, 0)*c11 + Point3DOriginal.at<float>(i, 1)*c12 + Point3DOriginal.at<float>(i, 2)*c13;
		Point3DResult.at<float>(i, 1) = Point3DOriginal.at<float>(i, 0)*c21 + Point3DOriginal.at<float>(i, 1)*c22 + Point3DOriginal.at<float>(i, 2)*c23;
		Point3DResult.at<float>(i, 2) = Point3DOriginal.at<float>(i, 0)*c31 + Point3DOriginal.at<float>(i, 1)*c32 + Point3DOriginal.at<float>(i, 2)*c33;
	}

	////*********************����**********************
	//cv::Mat PointMatrix(4, 1, CV_32FC1);//�洢ÿ���������

	//for (int i = 0; i < Point3DOriginal.rows; i++)
	//{
	//	PointMatrix.at<float>(0, 0) = Point3DOriginal.at<float>(i, 0);
	//	PointMatrix.at<float>(1, 0) = Point3DOriginal.at<float>(i, 1);
	//	PointMatrix.at<float>(2, 0) = Point3DOriginal.at<float>(i, 2);
	//	PointMatrix.at<float>(3, 0) = 1;

	//	PointMatrix = RotMat_Z(rotateAngle.angle_z)*RotMat_Y(rotateAngle.angle_y)*RotMat_X(rotateAngle.angle_x)*PointMatrix;

	//	Point3DResult.at<float>(i, 0) = PointMatrix.at<float>(0, 0);
	//	Point3DResult.at<float>(i, 1) = PointMatrix.at<float>(1, 0);
	//	Point3DResult.at<float>(i, 2) = PointMatrix.at<float>(2, 0);
	//}

	return Point3DResult;
}

//ƽ�Ʋ���
cv::Mat SQ_Quaternion::TransMoveMat(cv::Mat Point3DDisplay, float move_world_x, float move_world_y)
{
	cv::Mat Point3DResult(Point3DDisplay.rows, Point3DDisplay.cols, CV_32FC1);
	for (int i = 0; i < Point3DResult.rows; i++)
	{
		Point3DResult.at<float>(i, 0) = Point3DDisplay.at<float>(i, 0) + move_world_x;
		Point3DResult.at<float>(i, 1) = Point3DDisplay.at<float>(i, 1) + move_world_y;
		Point3DResult.at<float>(i, 2) = Point3DDisplay.at<float>(i, 2);
	}
	return Point3DResult;
}

//��������
cv::Mat SQ_Quaternion::TransScaleMat(cv::Mat Point3DDisplay,int cursor_opengl_x, int cursor_opengl_y, float ScaleRatio)
{
	cv::Mat Point3DResult(Point3DDisplay.rows, Point3DDisplay.cols, CV_32FC1);
	for (int i = 0; i < Point3DResult.rows; i++)
	{
		////Point3DResult.at<float>(i, 0) = Point3DDisplay.at<float>(i, 0)*ScaleRatio - (300 - cursor_opengl_x)*(1 - ScaleRatio)*0.004;//300Ϊopengl���ڿ��һ��
		////Point3DResult.at<float>(i, 1) = Point3DDisplay.at<float>(i, 1)*ScaleRatio - (300 - cursor_opengl_y)*(ScaleRatio - 1)*0.004;//300Ϊopengl���ڸߵ�һ��
		Point3DResult.at<float>(i, 0) = Point3DDisplay.at<float>(i, 0)*ScaleRatio;
		Point3DResult.at<float>(i, 1) = Point3DDisplay.at<float>(i, 1)*ScaleRatio;
		Point3DResult.at<float>(i, 2) = Point3DDisplay.at<float>(i, 2)*ScaleRatio;
	}
	return Point3DResult;
}

//������X�����ת���� 4*4
cv::Mat SQ_Quaternion::RotMat_X(float rotate_x)
{
	float sin_x = sin(rotate_x / 57.3), cos_x = cos(rotate_x / 57.3);
	cv::Mat RotateMatrixX(4, 4, CV_32FC1);//��ת����-X
	float RotateArrayX[4][4] = { { 1, 0, 0, 0 }, { 0, cos_x, -sin_x, 0 }, { 0, sin_x, cos_x, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		RotateMatrixX.at<float>(i, j) = RotateArrayX[i][j];
	return RotateMatrixX;
}

//������Y�����ת���� 4*4
cv::Mat SQ_Quaternion::RotMat_Y(float rotate_y)
{
	float sin_y = sin(rotate_y / 57.3), cos_y = cos(rotate_y / 57.3);
	cv::Mat RotateMatrixY(4, 4, CV_32FC1);//��ת����-Y
	float RotateArrayY[4][4] = { { cos_y, 0, sin_y, 0 }, { 0, 1, 0, 0 }, { -sin_y, 0, cos_y, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		RotateMatrixY.at<float>(i, j) = RotateArrayY[i][j];
	return RotateMatrixY;
}

//������Y�����ת���� 4*4
cv::Mat SQ_Quaternion::RotMat_Z(float rotate_z)
{
	float sin_z = sin(rotate_z / 57.3), cos_z = cos(rotate_z / 57.3);
	cv::Mat RotateMatrixZ(4, 4, CV_32FC1);//��ת����-Z
	float RotateArrayZ[4][4] = { { cos_z, -sin_z, 0, 0 }, { sin_z, cos_z, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		RotateMatrixZ.at<float>(i, j) = RotateArrayZ[i][j];
	return RotateMatrixZ;
}

//����������ת�Ƕ� 4*4
cv::Mat SQ_Quaternion::RotMat(float x, float y, float z, float rotate)
{
	float sin_t = sin(rotate / 57.3), cos_t = cos(rotate / 57.3), minus_cos_t = 1 - cos_t;
	cv::Mat RotateMatrix(4, 4, CV_32FC1);
	float length = sqrt(x*x + y*y + z*z);
	float X = x / length, Y = y / length, Z = z / length;
	float RotateArray[4][4] = { { X * X * minus_cos_t + cos_t, X * Y * minus_cos_t - Z * sin_t, X * Z * minus_cos_t + Y * sin_t, 0 },
								{ X * Y * minus_cos_t + Z * sin_t, Y * Y * minus_cos_t + cos_t, Z * Y * minus_cos_t - X * sin_t, 0 },
								{ X * Z * minus_cos_t - Y * sin_t, Z * Y * minus_cos_t + X * sin_t, Z * Z * minus_cos_t + cos_t, 0 },
								{ 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			RotateMatrix.at<float>(i, j) = RotateArray[i][j];
	return RotateMatrix;
}

//������X���ƽ�ƾ��� 4*4
cv::Mat SQ_Quaternion::TransMat_X(float trans_x)
{
	cv::Mat TransMatrixX(4, 4, CV_32FC1);//ƽ�ƾ���-X
	float RotateArrayX[4][4] = { { 1, 0, 0, trans_x }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		TransMatrixX.at<float>(i, j) = RotateArrayX[i][j];
	return TransMatrixX;
}

//������Y���ƽ�ƾ��� 4*4
cv::Mat SQ_Quaternion::TransMat_Y(float trans_y)
{
	cv::Mat TransMatrixY(4, 4, CV_32FC1);//ƽ�ƾ���-Y
	float RotateArrayY[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, trans_y }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		TransMatrixY.at<float>(i, j) = RotateArrayY[i][j];
	return TransMatrixY;
}

//������Y���ƽ�ƾ��� 4*4
cv::Mat SQ_Quaternion::TransMat_Z(float trans_z)
{
	cv::Mat TransMatrixZ(4, 4, CV_32FC1);//ƽ�ƾ���-Z
	float RotateArrayZ[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, trans_z }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		TransMatrixZ.at<float>(i, j) = RotateArrayZ[i][j];
	return TransMatrixZ;
}

