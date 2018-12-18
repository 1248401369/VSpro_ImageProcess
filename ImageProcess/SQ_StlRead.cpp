#include "SQ_StlRead.h"

SQ_StlRead::SQ_StlRead()
{
	pointcloud = new SQ_PointCloud();//�����ز���
}


//////////////////��ȡ��������Ϣ--�����--���������������
//////////////////һ�����ݰ���������ƽ�������-���������������
//////////////////				ƽ�ƹ��ķ������յ�����
////////////////cv::Mat SQ_StlRead::NormalVectorProcessInfo(QStringList path)
////////////////{
////////////////	cv::Mat StlPoint3D = ReadAllStlPoint(path, 3);//��ȡ.stl�ļ�����
////////////////	cv::Mat StlTriNormalPoint3D = ChangeCenterRange(StlPoint3D, 3);//�޸���ʾ��άͼ����λ�úʹ�С
////////////////	cv::Mat StlNormalProcessPoint3D(StlTriNormalPoint3D.rows/2, StlTriNormalPoint3D.cols, CV_32FC1);
////////////////	for (int i = 0; i < StlTriNormalPoint3D.rows / 4; i++)
////////////////	{
////////////////		StlNormalProcessPoint3D.at<float>(i * 2 + 0, 0) = (StlTriNormalPoint3D.at<float>(i * 4 + 1, 0) + StlTriNormalPoint3D.at<float>(i * 4 + 2, 0) + StlTriNormalPoint3D.at<float>(i * 4 + 3, 0)) / 3;
////////////////		StlNormalProcessPoint3D.at<float>(i * 2 + 0, 1) = (StlTriNormalPoint3D.at<float>(i * 4 + 1, 1) + StlTriNormalPoint3D.at<float>(i * 4 + 2, 1) + StlTriNormalPoint3D.at<float>(i * 4 + 3, 1)) / 3;
////////////////		StlNormalProcessPoint3D.at<float>(i * 2 + 0, 2) = (StlTriNormalPoint3D.at<float>(i * 4 + 1, 2) + StlTriNormalPoint3D.at<float>(i * 4 + 2, 2) + StlTriNormalPoint3D.at<float>(i * 4 + 3, 2)) / 3;
////////////////
////////////////		StlNormalProcessPoint3D.at<float>(i * 2 + 1, 0) = StlTriNormalPoint3D.at<float>(i * 4 + 0, 0) / 4 + StlNormalProcessPoint3D.at<float>(i * 2 + 0, 0);
////////////////		StlNormalProcessPoint3D.at<float>(i * 2 + 1, 1) = StlTriNormalPoint3D.at<float>(i * 4 + 0, 1) / 4 + StlNormalProcessPoint3D.at<float>(i * 2 + 0, 1);
////////////////		StlNormalProcessPoint3D.at<float>(i * 2 + 1, 2) = StlTriNormalPoint3D.at<float>(i * 4 + 0, 2) / 4 + StlNormalProcessPoint3D.at<float>(i * 2 + 0, 2);
////////////////	}
////////////////	return StlNormalProcessPoint3D;
////////////////}

//��ȡ��������Ϣ------2
//һ�����ݰ���������ƽ���1����
//				����ƽ���2����
//              ����ƽ���3����
cv::Mat SQ_StlRead::TrianglePatchInfo(QStringList path)
{
	cv::Mat StlPoint3D = ReadAllStlPoint(path, 2);//��ȡ.stl�ļ�����
	cv::Mat StlTriPoint3D = ChangeCenterRange(StlPoint3D, 2);//�޸���ʾ��άͼ����λ�úʹ�С
	return StlTriPoint3D;
}

//��ȡ��������Ϣ(ԭʼ��.stl�е�����)------2
//һ�����ݰ���������ƽ���1����
//				����ƽ���2����
//              ����ƽ���3����
cv::Mat SQ_StlRead::TrianglePatchOriginalInfo(QStringList path)
{
	cv::Mat StlPoint3D = ReadAllStlPoint(path, 2);//��ȡ.stl�ļ�����
	return StlPoint3D;
}


//��ȡ������ͷ�������Ϣ------3
//һ�����ݰ�����ԭʼ�ķ���������
//              ����ƽ���1����
//				����ƽ���2����
//              ����ƽ���3����
////////////////cv::Mat SQ_StlRead::PointALLInfo(QStringList path)
////////////////{
////////////////	cv::Mat StlPoint3D = ReadAllStlPoint(path, 3);//��ȡ.stl�ļ�����
////////////////	cv::Mat StlTriNormalPoint3D = ChangeCenterRange(StlPoint3D, 3);//�޸���ʾ��άͼ����λ�úʹ�С
////////////////	return StlTriNormalPoint3D;
////////////////}

//��ȡ������ͷ�������Ϣ�������������)--ԭʼ�Ķ�ȡ.stl������
//һ�����ݰ���������ƽ�������-���������������
//				ƽ�ƹ��ķ������յ�����
//              ����ƽ���1����
//				����ƽ���2����
////////////////////              ����ƽ���3����
//////////////////cv::Mat SQ_StlRead::PointALLProcessInfo(QStringList path)
//////////////////{
//////////////////	cv::Mat StlPoint3D = ReadAllStlPoint(path, 3);//��ȡ.stl�ļ�����
//////////////////	cv::Mat StlAllProcessPoint3D(StlPoint3D.rows * 5 / 4, StlPoint3D.cols, CV_32FC1);
//////////////////	for (int i = 0; i < StlAllProcessPoint3D.rows / 5; i++)
//////////////////	{
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 0, 0) = (StlPoint3D.at<float>(i * 4 + 1, 0) + StlPoint3D.at<float>(i * 4 + 2, 0) + StlPoint3D.at<float>(i * 4 + 3, 0)) / 3;
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 0, 1) = (StlPoint3D.at<float>(i * 4 + 1, 1) + StlPoint3D.at<float>(i * 4 + 2, 1) + StlPoint3D.at<float>(i * 4 + 3, 1)) / 3;
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 0, 2) = (StlPoint3D.at<float>(i * 4 + 1, 2) + StlPoint3D.at<float>(i * 4 + 2, 2) + StlPoint3D.at<float>(i * 4 + 3, 2)) / 3;
//////////////////
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 1, 0) = StlPoint3D.at<float>(i * 4 + 0, 0) + StlAllProcessPoint3D.at<float>(i * 5 + 0, 0);
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 1, 1) = StlPoint3D.at<float>(i * 4 + 0, 1) + StlAllProcessPoint3D.at<float>(i * 5 + 0, 1);
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 1, 2) = StlPoint3D.at<float>(i * 4 + 0, 2) + StlAllProcessPoint3D.at<float>(i * 5 + 0, 2);
//////////////////
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 2, 0) = StlPoint3D.at<float>(i * 4 + 1, 0);
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 2, 1) = StlPoint3D.at<float>(i * 4 + 1, 1);
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 2, 2) = StlPoint3D.at<float>(i * 4 + 1, 2);
//////////////////
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 3, 0) = StlPoint3D.at<float>(i * 4 + 2, 0);
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 3, 1) = StlPoint3D.at<float>(i * 4 + 2, 1);
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 3, 2) = StlPoint3D.at<float>(i * 4 + 2, 2);
//////////////////
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 4, 0) = StlPoint3D.at<float>(i * 4 + 3, 0);
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 4, 1) = StlPoint3D.at<float>(i * 4 + 3, 1);
//////////////////		StlAllProcessPoint3D.at<float>(i * 5 + 4, 2) = StlPoint3D.at<float>(i * 4 + 3, 2);
//////////////////	}
//////////////////	return StlAllProcessPoint3D;
//////////////////}


//��ȡ������Ϣ------4
//һ�����ݰ�����ȥ�غ��ÿ���������
cv::Mat SQ_StlRead::PointCloudInfo(QStringList path)
{
	cv::Mat StlPoint3D = ReadAllStlPoint(path, 4);//��ȡ.stl�ļ�����
	cv::Mat CloudDeWeightPoint3D = PointCloudDeWeight(StlPoint3D);//����ȥ��

	//qDebug()�������
	//for (int i = 0; i < CloudDeWeightPoint3D.rows; i++)
	//	qDebug() << CloudDeWeightPoint3D.at<float>(i, 0) << CloudDeWeightPoint3D.at<float>(i, 1) << CloudDeWeightPoint3D.at<float>(i, 2);

	//cv::Mat CloudDeWeightPoint3D = StlPoint3D;//��ȥ��
	cv::Mat StlCloudPoint3D = ChangeCenterRange(CloudDeWeightPoint3D, 4);//�޸���ʾ��άͼ����λ�úʹ�С
	return StlCloudPoint3D;
}

//��ȡ������Ϣ(��ȡԭʼ��.stl�еĵ�������)------4
//һ�����ݰ�����ȥ�غ��ÿ���������
cv::Mat SQ_StlRead::PointCloudOriginalInfo(QStringList path)
{
	cv::Mat StlPoint3D = ReadAllStlPoint(path, 4);//��ȡ.stl�ļ�����
	cv::Mat CloudDeWeightPoint3D = PointCloudDeWeight(StlPoint3D);//����ȥ��
	return CloudDeWeightPoint3D;
}


//��ȡ���.stl�ļ�������
cv::Mat SQ_StlRead::ReadAllStlPoint(QStringList path,int type)
{
	//��ȡ.stl�ļ�����
	cv::Mat StlPoint3D = StlPointInfo(path[0].toLatin1().data(), type);
	for (int i = 1; i < path.size(); i++)
	{
		StlPoint3D = MergeRows(StlPoint3D, StlPointInfo(path[i].toLatin1().data(), type));
	}
	return StlPoint3D;
}

//��ȡ.stl�ļ�--��������������������Ϣ--������������1����2����3��
cv::Mat SQ_StlRead::StlPointInfo(char* path, int type)
{
	cv::Mat StlPoint3D(1, 3, CV_32FC1);//�������ļ�
	int flag_bin_ascii = StlType(path);
	if (flag_bin_ascii == 1)//�������ļ�
	{	
		switch (type)
		{
			case 1:{ StlPoint3D = BinaryStlPointInfo(path, 1); break; }
			case 2:{ StlPoint3D = BinaryStlPointInfo(path, 2); break; }
			case 3:{ StlPoint3D = BinaryStlPointInfo(path, 3); break; }
			case 4:{ StlPoint3D = BinaryStlPointInfo(path, 2); break; }
			default:break;
		}
	}
	else//ASCII�ļ�
	{
		switch (type)
		{
			case 1:{ StlPoint3D = AsciiStlPointInfo(path, 1); break; }
			case 2:{ StlPoint3D = AsciiStlPointInfo(path, 2); break; }
			case 3:{ StlPoint3D = AsciiStlPointInfo(path, 3); break; }
			case 4:{ StlPoint3D = AsciiStlPointInfo(path, 2); break; }
			default:break;
		}
	}
	return StlPoint3D;
}

//�ж�.stl�ļ�����
int SQ_StlRead::StlType(char* path)
{
	FILE *fp;
	char fileName[64];
	Faces *faces = (Faces*)malloc(sizeof(Faces));//����ı�ͷ
	Faces *p = faces;
	Faces *q;
	Head head;
	int i = 0;
	head.faceNum = 0;
	fp = fopen(path, "r");
	int flag_bin_ascii = 0;
	if (fp)
	{
		char str[24];
		fscanf_s(fp, "%s", str, 24);//�ô�������ý����ƶ��ļ�ָ�룬ʹָ��������ʶ����solid�������ļ�ָ���Ƶ��ļ����Ƶ�λ��
		fscanf_s(fp, "%s", head.partName, 80);//�����ļ�����

		//ѭ����ȡ����Ƭ��ķ��ߺͶ�������
		while (!feof(fp))
		{
			p->pointer = (Faces*)malloc(sizeof(Faces));//�����½�㣬���ڽ�������
			q = p;
			p = p->pointer;
			fscanf_s(fp, "%s", str, 24);//ʹ�ļ�ָ��������ʶ����facetnormal����ָ���������ݲ���
			if (str[0] == 'f')//�ж��ļ�����
				flag_bin_ascii = 2;//ASCII
			else
				flag_bin_ascii = 1;//������
			break;
		}
		free(q->pointer);//�����ļ�ĩβ��һ���ַ���endsolid .....������ɶഴ����һ����㣬�ý������������õģ����Ҫ�ͷ�
		q->pointer = NULL;//���һ�����������ͷ���֮�󣬽�ָ��������ָ����ΪNULL�������������
	}
	fclose(fp);
	free(faces);
	return flag_bin_ascii;
}

//��ȡ�����Ƹ�ʽ��.stl�ļ�
cv::Mat SQ_StlRead::BinaryStlPointInfo(char* path, int type)
{
	cv::Mat StlPoint3DZero(1, 3, CV_32FC1);
	Head head;
	FILE *fp;
	fopen_s(&fp, path, "rb");
	if (fp != NULL)
	{
		fread(head.partName, 80, 1, fp);//��ȡ������
		fread(&head.faceNum, 4, 1, fp);//��ȡ������Ƭ����Ŀ
	}
	Face *face = (Face*)malloc(head.faceNum * sizeof(Face));//����������Ƭ����Ŀ������һ��Face���͵�����

	//ѭ����ȡ������Ƭ����
	for (int i = 0; i < head.faceNum; i++)
	{
		fread(&face[i].normal, 12, 1, fp);//��ȡ��������
		fread(&face[i].p1, 12, 1, fp);//��ȡ����1������
		fread(&face[i].p2, 12, 1, fp);//��ȡ����2������
		fread(&face[i].p3, 12, 1, fp);//��ȡ����3������
		fread(&face[i].info, 2, 1, fp);//��ȡ���������ݣ���һ��һ��ûʲô�ã�����ѡ���ȡ��Ϊ���ƶ��ļ�ָ��
	}	
	fclose(fp);

	switch (type)
	{
		case 1:{ 
				   cv::Mat StlPoint3D(head.faceNum, 3, CV_32FC1);
				   for (int i = 0; i < head.faceNum; i++)
				   {
					   StlPoint3D.at<float>(i, 0) = face[i].normal.i;
					   StlPoint3D.at<float>(i, 1) = face[i].normal.j;
					   StlPoint3D.at<float>(i, 2) = face[i].normal.k;
				   }
				   free(face);
				   return StlPoint3D;
				   break; 
				 
				}
		case 2:{ 
				   cv::Mat StlPoint3D(head.faceNum * 3, 3, CV_32FC1);
				   for (int i = 0; i < head.faceNum; i++)
				   {
					   StlPoint3D.at<float>(i * 3 , 0) = face[i].p1.x;
					   StlPoint3D.at<float>(i * 3 , 1) = face[i].p1.y;
					   StlPoint3D.at<float>(i * 3 , 2) = face[i].p1.z;

					   StlPoint3D.at<float>(i * 3 + 1, 0) = face[i].p2.x;
					   StlPoint3D.at<float>(i * 3 + 1, 1) = face[i].p2.y;
					   StlPoint3D.at<float>(i * 3 + 1, 2) = face[i].p2.z;

					   StlPoint3D.at<float>(i * 3 + 2, 0) = face[i].p3.x;
					   StlPoint3D.at<float>(i * 3 + 2, 1) = face[i].p3.y;
					   StlPoint3D.at<float>(i * 3 + 2, 2) = face[i].p3.z;
				   }	
				   free(face);
				   return StlPoint3D;
				   break; 
				}
		case 3:{ 
				   cv::Mat StlPoint3D(head.faceNum * 4, 3, CV_32FC1);
				   for (int i = 0; i < head.faceNum; i++)
				   {
					   StlPoint3D.at<float>(i * 4, 0) = face[i].normal.i;
					   StlPoint3D.at<float>(i * 4, 1) = face[i].normal.j;
					   StlPoint3D.at<float>(i * 4, 2) = face[i].normal.k;

					   StlPoint3D.at<float>(i * 4 + 1, 0) = face[i].p1.x;
					   StlPoint3D.at<float>(i * 4 + 1, 1) = face[i].p1.y;
					   StlPoint3D.at<float>(i * 4 + 1, 2) = face[i].p1.z;

					   StlPoint3D.at<float>(i * 4 + 2, 0) = face[i].p2.x;
					   StlPoint3D.at<float>(i * 4 + 2, 1) = face[i].p2.y;
					   StlPoint3D.at<float>(i * 4 + 2, 2) = face[i].p2.z;

					   StlPoint3D.at<float>(i * 4 + 3, 0) = face[i].p3.x;
					   StlPoint3D.at<float>(i * 4 + 3, 1) = face[i].p3.y;
					   StlPoint3D.at<float>(i * 4 + 3, 2) = face[i].p3.z;
				   }	
				   free(face);
				   return StlPoint3D;
				   break; 
				 
				}
		default:break;
	}
	return StlPoint3DZero;
}

//��ȡASCII��ʽ��.stl�ļ�
cv::Mat SQ_StlRead::AsciiStlPointInfo(char* path, int type)
{
	cv::Mat StlPoint3D(1, 3, CV_32FC1);
	FILE *fp;
	char fileName[64];
	Faces *faces = (Faces*)malloc(sizeof(Faces));//����ı�ͷ
	Faces *p = faces;
	Faces *q;
	Head head;
	int i = 0;
	head.faceNum = 0;
	fp = fopen(path, "r");
	if (fp)
	{
		char str[24];
		fscanf_s(fp, "%s", str, 24);//�ô�������ý����ƶ��ļ�ָ�룬ʹָ��������ʶ����solid�������ļ�ָ���Ƶ��ļ����Ƶ�λ��
		fscanf_s(fp, "%s", head.partName, 80);//�����ļ�����
		//ѭ����ȡ����Ƭ��ķ��ߺͶ�������
		while (!feof(fp))
		{
			p->pointer = (Faces*)malloc(sizeof(Faces));//�����½�㣬���ڽ�������
			q = p;
			p = p->pointer;
			fscanf_s(fp, "%s", str, 24);//ʹ�ļ�ָ��������ʶ����facetnormal����ָ���������ݲ���
			fscanf_s(fp, "%f%f%f", &p->data.normal.i, &p->data.normal.j, &p->data.normal.k, 12);//��ȡ��������
			fscanf_s(fp, "%s", str, 24);//ʹ�ļ�ָ��������ʶ����facetloop��
			fscanf_s(fp, "%s", str, 24);//ʹ�ļ�ָ��������ʶ����vertex����ָ������1�����ݲ���
			fscanf_s(fp, "%f%f%f", &p->data.vertex1.x, &p->data.vertex1.y, &p->data.vertex1.z, 12);
			fscanf_s(fp, "%s", str, 24);//ʹ�ļ�ָ��������ʶ����vertex����ָ������2�����ݲ���
			fscanf_s(fp, "%f%f%f", &p->data.vertex2.x, &p->data.vertex2.y, &p->data.vertex2.z, 12);
			fscanf_s(fp, "%s", str, 24);//ʹ�ļ�ָ��������ʶ����vertex����ָ������3�����ݲ���
			fscanf_s(fp, "%f%f%f", &p->data.vertex3.x, &p->data.vertex3.y, &p->data.vertex3.z, 12);
			fscanf_s(fp, "%s", str, 24);//ʹ�ļ�ָ��������ʶ����endloop��
			fscanf_s(fp, "%s", str, 24);//ʹ�ļ�ָ��������ʶ����endfacet��
			head.faceNum++;
		}
		free(q->pointer);//�����ļ�ĩβ��һ���ַ���endsolid .....������ɶഴ����һ����㣬�ý������������õģ����Ҫ�ͷ�
		q->pointer = NULL;//���һ�����������ͷ���֮�󣬽�ָ��������ָ����ΪNULL�������������
	}
	else
	{
		printf("���ļ�ʧ�ܣ�");
	}
	fclose(fp);
	p = faces->pointer;//��ȡ����ڶ�������ָ��

	while (p != NULL)
	{
		switch (type)
		{
			case 1:{
					   cv::Mat StlPoint3D(head.faceNum, 3, CV_32FC1);
					   for (int i = 0; i < head.faceNum; i++)
					   {
						   StlPoint3D.at<float>(i, 0) = p->data.normal.i;
						   StlPoint3D.at<float>(i, 1) = p->data.normal.j;
						   StlPoint3D.at<float>(i, 2) = p->data.normal.k;
					   }

					   break;
					}
			case 2:{
					   cv::Mat StlPoint3D(head.faceNum * 3, 3, CV_32FC1);
					   for (int i = 0; i < head.faceNum; i++)
					   {
						   StlPoint3D.at<float>(i * 3 , 0) = p->data.vertex1.x;
						   StlPoint3D.at<float>(i * 3 , 1) = p->data.vertex1.y;
						   StlPoint3D.at<float>(i * 3 , 2) = p->data.vertex1.z;

						   StlPoint3D.at<float>(i * 3 + 1, 0) = p->data.vertex2.x;
						   StlPoint3D.at<float>(i * 3 + 1, 1) = p->data.vertex2.y;
						   StlPoint3D.at<float>(i * 3 + 1, 2) = p->data.vertex2.z;

						   StlPoint3D.at<float>(i * 3 + 2, 0) = p->data.vertex3.x;
						   StlPoint3D.at<float>(i * 3 + 2, 1) = p->data.vertex3.y;
						   StlPoint3D.at<float>(i * 3 + 2, 2) = p->data.vertex3.z;
					   }
					   break;
					}
			case 3:{
					   cv::Mat StlPoint3D(head.faceNum * 4, 3, CV_32FC1);
					   for (int i = 0; i < head.faceNum; i++)
					   {
						   StlPoint3D.at<float>(i * 3, 0) = p->data.normal.i;
						   StlPoint3D.at<float>(i * 3, 1) = p->data.normal.j;
						   StlPoint3D.at<float>(i * 3, 2) = p->data.normal.k;

						   StlPoint3D.at<float>(i * 3 + 1, 0) = p->data.vertex1.x;
						   StlPoint3D.at<float>(i * 3 + 1, 1) = p->data.vertex1.y;
						   StlPoint3D.at<float>(i * 3 + 1, 2) = p->data.vertex1.z;

						   StlPoint3D.at<float>(i * 3 + 2, 0) = p->data.vertex2.x;
						   StlPoint3D.at<float>(i * 3 + 2, 1) = p->data.vertex2.y;
						   StlPoint3D.at<float>(i * 3 + 2, 2) = p->data.vertex2.z;

						   StlPoint3D.at<float>(i * 3 + 3, 0) = p->data.vertex3.x;
						   StlPoint3D.at<float>(i * 3 + 3, 1) = p->data.vertex3.y;
						   StlPoint3D.at<float>(i * 3 + 3, 2) = p->data.vertex3.z;
					   }
					   break;
					}
			default:break;
		}		
		p = p->pointer;
		i++;
	}
	free(faces);
	return StlPoint3D;
}

//����ȥ��--û�з���������
cv::Mat SQ_StlRead::PointCloudDeWeight(cv::Mat PointCloudOriginalMat)
{
	cv::Mat StlPoint3D(PointCloudOriginalMat.rows, PointCloudOriginalMat.cols, CV_32FC1);
	PointCloudOriginalMat.copyTo(StlPoint3D);
	//StlPoint3D = SortAscendingDeleteUUU(StlPoint3D);//ɾ����ͬ������
	StlPoint3D = pointcloud->PCLDecreaseSampleToMat(StlPoint3D, 0.5);//�������ٶȿ�
	return StlPoint3D;
}

//������ǰ����Ԫ����ȣ��Ե����н�������ɾ����ͬ������
cv::Mat SQ_StlRead::SortAscendingDeleteEEU(cv::Mat PointOriginalMat)
{
	int row_result = 0;//�洢���ս���е��еĸ���
	cv::Mat StlPointThree3D = PointOriginalMat.col(2).clone();//��ȡ���������
	cv::Mat StlPointThreeIndex3D(StlPointThree3D.rows, StlPointThree3D.cols, CV_32FC1);//���水���������к�Ķ�Ӧ�е�����
	cv::sortIdx(StlPointThree3D, StlPointThreeIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//�Ծ�������н����������У������Ӧ�е�����
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//�����������Ľ��

	for (int i = 0; i < PointOriginalMat.rows-1; i++)
	{
		if (abs(PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 2) - PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i + 1, 0), 2)) > error)
		{
			//���治ͬ������
			StlPoint3D.at<float>(row_result, 0) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 0);
			StlPoint3D.at<float>(row_result, 1) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 1);
			StlPoint3D.at<float>(row_result, 2) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 2);//�����а���������
			row_result ++;
		}	
	}
	//�������һ������
	StlPoint3D.at<float>(row_result, 0) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(PointOriginalMat.rows - 1, 0), 0);
	StlPoint3D.at<float>(row_result, 1) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(PointOriginalMat.rows - 1, 0), 1);
	StlPoint3D.at<float>(row_result, 2) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(PointOriginalMat.rows - 1, 0), 2);//�����а���������
	
	StlPoint3D = StlPoint3D.rowRange(0, row_result + 1);

	return StlPoint3D;
}

//������ǰ����Ԫ����ȣ��Ե����н�������
cv::Mat SQ_StlRead::SortAscendingEEU(cv::Mat PointOriginalMat)
{
	cv::Mat StlPointThree3D = PointOriginalMat.col(2).clone();//��ȡ���������
	cv::Mat StlPointThreeIndex3D(StlPointThree3D.rows, StlPointThree3D.cols, CV_32FC1);//���水���������к�Ķ�Ӧ�е�����
	cv::sortIdx(StlPointThree3D, StlPointThreeIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//�Ծ�������н����������У������Ӧ�е�����
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//�����������Ľ��

	for (int i = 0; i < PointOriginalMat.rows; i++)
	{
		//�����������к�ľ���
		StlPoint3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 0);
		StlPoint3D.at<float>(i, 1) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 1);
		StlPoint3D.at<float>(i, 2) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 2);//�����а���������
	}	

	return StlPoint3D;
}

//������ǰһ��Ԫ����ȣ��Եڶ������н�������ɾ����ͬ������
cv::Mat SQ_StlRead::SortAscendingDeleteEUU(cv::Mat PointOriginalMat)
{
	int row = 0;//�洢�ڶ�����ֵ��ͬ���еĸ���
	int row_result = 0;//�洢���ս���е��еĸ���
	int flag_last_row = 0;//Ϊ1��ʾ���һ����ǰһ�еĵڶ������ݲ���
	cv::Mat StlPointTwo3D = PointOriginalMat.colRange(1, 2);//��ȡ����ڶ���
	cv::Mat StlPointTwoThreeOk3D;
	cv::Mat StlPointTwoIndex3D(StlPointTwo3D.rows, StlPointTwo3D.cols, CV_32FC1);
	cv::sortIdx(StlPointTwo3D, StlPointTwoIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//�Ծ���ڶ��н����������У������Ӧ�е�����
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//�洢���Ľ��

	cv::Mat StlPointTwoOk3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//�洢���յڶ����������к������
	for (int i = 0; i < PointOriginalMat.rows; i++)
	{
		StlPointTwoOk3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 0);
		StlPointTwoOk3D.at<float>(i, 1) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 1);//�ڶ��а���������
		StlPointTwoOk3D.at<float>(i, 2) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 2);
	}

	cv::Mat StlPoint3DTemp(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//�洢�ڶ�����ͬ������

	for (int i = 0; i < StlPointTwoOk3D.rows - 1; i++)
	{
		if (abs(StlPointTwoOk3D.at<float>(i, 1) - StlPointTwoOk3D.at<float>(i + 1, 1)) < error)//�����i�к͵�i+1�еĵڶ���������ͬ��������ݴ�
		{
			StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i, 0);
			StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i, 1);
			StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i, 2);
			row++;

			if (i == StlPointTwoOk3D.rows - 2)//�������һ������
			{
				//��ʱ���һ�����ݺ���һ�����ݵĵڶ�����ͬ����˽��д洢
				StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i + 1, 0);
				StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i + 1, 1);
				StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i + 1, 2);

				StlPointTwoThreeOk3D = SortAscendingDeleteEEU(StlPoint3DTemp.rowRange(0, row + 1));//�Եڶ�����ͬ�����ݽ���ɾ�ز���

				//�洢������Ҫ����Ľ��
				for (int i = row_result; i < row_result + StlPointTwoThreeOk3D.rows; i++)
				{
					StlPoint3D.at<float>(i, 0) = StlPointTwoThreeOk3D.at<float>(i - row_result, 0);
					StlPoint3D.at<float>(i, 1) = StlPointTwoThreeOk3D.at<float>(i - row_result, 1);
					StlPoint3D.at<float>(i, 2) = StlPointTwoThreeOk3D.at<float>(i - row_result, 2);
				}

				row_result += StlPointTwoThreeOk3D.rows;//��¼����������������
			}
		}
		else
		{
			//�����i�к͵�i+1�еĵڶ������ݲ���ͬ����洢��i�����ݣ�Ȼ��Ե��������ݽ���ȥ�ز���
			StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i, 0);
			StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i, 1);
			StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i, 2);
			if (i == StlPointTwoOk3D.rows - 2)//�������һ������
			{			
				flag_last_row = 1;
			}

			StlPointTwoThreeOk3D = SortAscendingDeleteEEU(StlPoint3DTemp.rowRange(0, row + 1));

			for (int i = row_result; i < row_result + StlPointTwoThreeOk3D.rows; i++)
			{
				StlPoint3D.at<float>(i, 0) = StlPointTwoThreeOk3D.at<float>(i - row_result, 0);
				StlPoint3D.at<float>(i, 1) = StlPointTwoThreeOk3D.at<float>(i - row_result, 1);
				StlPoint3D.at<float>(i, 2) = StlPointTwoThreeOk3D.at<float>(i - row_result, 2);
			}
			row_result += StlPointTwoThreeOk3D.rows;
			row = 0;
		}
	}

	//������һ������һ�����ݵĵڶ��в�ͬ����ֱ�Ӵ��������������ľ�����
	if (flag_last_row == 1)
	{
		StlPoint3D.at<float>(row_result, 0) = StlPointTwoOk3D.at<float>(StlPointTwoOk3D.rows - 1, 0);
		StlPoint3D.at<float>(row_result, 1) = StlPointTwoOk3D.at<float>(StlPointTwoOk3D.rows - 1, 1);
		StlPoint3D.at<float>(row_result, 2) = StlPointTwoOk3D.at<float>(StlPointTwoOk3D.rows - 1, 2);
		StlPoint3D = StlPoint3D.rowRange(0, row_result + 1);
	}
	else
	{
		StlPoint3D = StlPoint3D.rowRange(0, row_result);
	}

	return StlPoint3D;
}

//////////////////������ǰһ��Ԫ����ȣ��Եڶ������н�������
////////////////cv::Mat SQ_StlRead::SortAscendingEUU(cv::Mat PointOriginalMat)
////////////////{
////////////////	int row = 0;//�洢�ڶ�����ֵ��ͬ���еĸ���
////////////////	int row_result = 0;//�洢���ս���е��еĸ���
////////////////	int flag_last_row = 0;//Ϊ1��ʾ���һ����ǰһ�еĵڶ������ݲ���
////////////////	cv::Mat StlPointTwo3D = PointOriginalMat.colRange(1, 2);//��ȡ����ڶ���
////////////////
////////////////	cv::Mat StlPointTwoIndex3D(StlPointTwo3D.rows, StlPointTwo3D.cols, CV_32FC1);
////////////////	cv::sortIdx(StlPointTwo3D, StlPointTwoIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//�Ծ���ڶ��н����������У������Ӧ�е�����
////////////////
////////////////	cv::Mat StlPointTwoOk3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
////////////////	for (int i = 0; i < PointOriginalMat.rows; i++)
////////////////	{
////////////////		StlPointTwoOk3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 0);
////////////////		StlPointTwoOk3D.at<float>(i, 1) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 1);//�ڶ��а���������
////////////////		StlPointTwoOk3D.at<float>(i, 2) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 2);
////////////////	}
////////////////
////////////////	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//�洢���Ľ��
////////////////
////////////////	cv::Mat StlPoint3DTemp(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//
////////////////
////////////////	for (int i = 0; i < StlPointTwoOk3D.rows-1; i++)
////////////////	{
////////////////		if (abs(StlPointTwoOk3D.at<float>(i, 1) - StlPointTwoOk3D.at<float>(i + 1, 1)) < error)
////////////////		{
////////////////			StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i, 0);
////////////////			StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i, 1);
////////////////			StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i, 2);
////////////////			row++;
////////////////			if (i == StlPointTwoOk3D.rows - 2)//�������һ������
////////////////			{
////////////////				
////////////////				StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i + 1, 0);
////////////////				StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i + 1, 1);
////////////////				StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i + 1, 2);
////////////////
////////////////				cv::Mat StlPointTwoThreeOk3D = SortAscendingEEU(StlPoint3DTemp.rowRange(0, row + 1));
////////////////
////////////////				for (int i = row_result; i < row_result + row + 1; i++)
////////////////				{
////////////////					StlPoint3D.at<float>(i, 0) = StlPointTwoThreeOk3D.at<float>(i - row_result, 0);
////////////////					StlPoint3D.at<float>(i, 1) = StlPointTwoThreeOk3D.at<float>(i - row_result, 1);
////////////////					StlPoint3D.at<float>(i, 2) = StlPointTwoThreeOk3D.at<float>(i - row_result, 2);
////////////////				}
////////////////			}
////////////////		}
////////////////		else
////////////////		{
////////////////			StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i, 0);
////////////////			StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i, 1);
////////////////			StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i, 2);
////////////////			if (i == StlPointTwoOk3D.rows - 2)//�������һ������
////////////////			{
////////////////				if (abs(StlPointTwoOk3D.at<float>(i, 1) - StlPointTwoOk3D.at<float>(i + 1, 1)) < error)
////////////////				{
////////////////					row ++;
////////////////					StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i + 1, 0);
////////////////					StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i + 1, 1);
////////////////					StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i + 1, 2);
////////////////				}
////////////////				else
////////////////				{
////////////////					flag_last_row = 1;
////////////////				}
////////////////			}
////////////////			cv::Mat StlPointTwoThreeOk3D = SortAscendingEEU(StlPoint3DTemp.rowRange(0, row + 1));
////////////////
////////////////			for (int i = row_result; i < row_result + row+1; i++)
////////////////			{
////////////////				StlPoint3D.at<float>(i, 0) = StlPointTwoThreeOk3D.at<float>(i - row_result, 0);
////////////////				StlPoint3D.at<float>(i, 1) = StlPointTwoThreeOk3D.at<float>(i - row_result, 1);
////////////////				StlPoint3D.at<float>(i, 2) = StlPointTwoThreeOk3D.at<float>(i - row_result, 2);
////////////////			}
////////////////			row_result += row + 1;
////////////////			row = 0;
////////////////		}
////////////////	}
////////////////	if (flag_last_row == 1)
////////////////	{
////////////////		StlPoint3D.at<float>(row_result, 0) = StlPointTwoOk3D.at<float>(StlPointTwoOk3D.rows - 1, 0);
////////////////		StlPoint3D.at<float>(row_result, 1) = StlPointTwoOk3D.at<float>(StlPointTwoOk3D.rows - 1, 1);
////////////////		StlPoint3D.at<float>(row_result, 2) = StlPointTwoOk3D.at<float>(StlPointTwoOk3D.rows - 1, 2);
////////////////	}
////////////////	return StlPoint3D;
////////////////}
////////////////
//////////////////������Ԫ�ض�����ȣ��Ե�һ���������н�������ɾ����ͬ������
////////////////cv::Mat SQ_StlRead::SortAscendingDeleteUUU(cv::Mat PointOriginalMat)
////////////////{
////////////////	int row = 0;//�洢��һ����ֵ��ͬ���еĸ���
////////////////	int row_result = 0;//�洢���ս���е��еĸ���
////////////////	int flag_last_row = 0;//Ϊ1��ʾ���һ����ǰһ�еĵ�һ�����ݲ���
////////////////	cv::Mat StlPointOneTwoThreeOk3D;
////////////////	cv::Mat StlPointOne3D = PointOriginalMat.col(0).clone();//��ȡ�����һ��
////////////////	cv::Mat StlPointOneIndex3D(StlPointOne3D.rows, StlPointOne3D.cols, CV_32FC1);
////////////////	cv::sortIdx(StlPointOne3D, StlPointOneIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//�Ծ����һ�н����������У������Ӧ�е�����
////////////////
////////////////	cv::Mat StlPointOneOk3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
////////////////	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//�洢���Ľ��
////////////////
////////////////	cv::Mat StlPoint3DTemp(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
////////////////	for (int i = 0; i < PointOriginalMat.rows; i++)
////////////////	{
////////////////		StlPointOneOk3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 0);//��һ�а���������
////////////////		StlPointOneOk3D.at<float>(i, 1) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 1);
////////////////		StlPointOneOk3D.at<float>(i, 2) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 2);
////////////////	}
////////////////
////////////////	for (int i = 0; i < StlPointOneOk3D.rows - 1; i++)
////////////////	{
////////////////		if (abs(StlPointOneOk3D.at<float>(i, 0) - StlPointOneOk3D.at<float>(i + 1, 0)) < error)
////////////////		{
////////////////			StlPoint3DTemp.at<float>(row, 0) = StlPointOneOk3D.at<float>(i, 0);
////////////////			StlPoint3DTemp.at<float>(row, 1) = StlPointOneOk3D.at<float>(i, 1);
////////////////			StlPoint3DTemp.at<float>(row, 2) = StlPointOneOk3D.at<float>(i, 2);
////////////////			row++;
////////////////			if (i == StlPointOneOk3D.rows - 2)//�������һ������
////////////////			{
////////////////
////////////////				StlPoint3DTemp.at<float>(row, 0) = StlPointOneOk3D.at<float>(i + 1, 0);
////////////////				StlPoint3DTemp.at<float>(row, 1) = StlPointOneOk3D.at<float>(i + 1, 1);
////////////////				StlPoint3DTemp.at<float>(row, 2) = StlPointOneOk3D.at<float>(i + 1, 2);
////////////////
////////////////				StlPointOneTwoThreeOk3D = SortAscendingDeleteEUU(StlPoint3DTemp.rowRange(0, row + 1));
////////////////
////////////////				for (int i = row_result; i < row_result + StlPointOneTwoThreeOk3D.rows; i++)
////////////////				{
////////////////					StlPoint3D.at<float>(i, 0) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 0);
////////////////					StlPoint3D.at<float>(i, 1) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 1);
////////////////					StlPoint3D.at<float>(i, 2) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 2);
////////////////				}
////////////////				row_result += StlPointOneTwoThreeOk3D.rows;
////////////////			}
////////////////		}
////////////////		else
////////////////		{
////////////////			StlPoint3DTemp.at<float>(row, 0) = StlPointOneOk3D.at<float>(i, 0);
////////////////			StlPoint3DTemp.at<float>(row, 1) = StlPointOneOk3D.at<float>(i, 1);
////////////////			StlPoint3DTemp.at<float>(row, 2) = StlPointOneOk3D.at<float>(i, 2);
////////////////
////////////////			if (i == StlPointOneOk3D.rows - 2)//�������һ������
////////////////			{		
////////////////				flag_last_row = 1;
////////////////			}
////////////////
////////////////			StlPointOneTwoThreeOk3D = SortAscendingDeleteEUU(StlPoint3DTemp.rowRange(0, row + 1));
////////////////
////////////////			for (int i = row_result; i < row_result + StlPointOneTwoThreeOk3D.rows; i++)
////////////////			{
////////////////				StlPoint3D.at<float>(i, 0) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 0);
////////////////				StlPoint3D.at<float>(i, 1) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 1);
////////////////				StlPoint3D.at<float>(i, 2) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 2);
////////////////			}
////////////////			row_result += StlPointOneTwoThreeOk3D.rows;
////////////////			row = 0;
////////////////		}
////////////////	}
////////////////
////////////////	if (flag_last_row == 1)
////////////////	{
////////////////		StlPoint3D.at<float>(row_result, 0) = StlPointOneOk3D.at<float>(StlPointOneOk3D.rows - 1, 0);
////////////////		StlPoint3D.at<float>(row_result, 1) = StlPointOneOk3D.at<float>(StlPointOneOk3D.rows - 1, 1);
////////////////		StlPoint3D.at<float>(row_result, 2) = StlPointOneOk3D.at<float>(StlPointOneOk3D.rows - 1, 2);
////////////////		StlPoint3D = StlPoint3D.rowRange(0, row_result + 1);
////////////////	}
////////////////	else
////////////////	{
////////////////		StlPoint3D = StlPoint3D.rowRange(0, row_result);
////////////////	}
////////////////	return StlPoint3D;
////////////////}

//������Ԫ�ض�����ȣ��Ե�һ���������н�������
////////////////cv::Mat SQ_StlRead::SortAscendingUUU(cv::Mat PointOriginalMat)
////////////////{
////////////////	int row = 0;//�洢��һ����ֵ��ͬ���еĸ���
////////////////	int row_result = 0;//�洢���ս���е��еĸ���
////////////////	int flag_last_row = 0;//Ϊ1��ʾ���һ����ǰһ�еĵ�һ�����ݲ���
////////////////
////////////////	cv::Mat StlPointOne3D = PointOriginalMat.col(0).clone();//��ȡ�����һ��
////////////////	cv::Mat StlPointOneIndex3D(StlPointOne3D.rows, StlPointOne3D.cols, CV_32FC1);
////////////////	cv::sortIdx(StlPointOne3D, StlPointOneIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//�Ծ����һ�н����������У������Ӧ�е�����
////////////////
////////////////	cv::Mat StlPointOneOk3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
////////////////	for (int i = 0; i < PointOriginalMat.rows; i++)
////////////////	{
////////////////		StlPointOneOk3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 0);//��һ�а���������
////////////////		StlPointOneOk3D.at<float>(i, 1) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 1);
////////////////		StlPointOneOk3D.at<float>(i, 2) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 2);
////////////////	}
////////////////
////////////////	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//�洢���Ľ��
////////////////
////////////////	cv::Mat StlPoint3DTemp(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//
////////////////
////////////////	for (int i = 0; i < StlPointOneOk3D.rows - 1; i++)
////////////////	{
////////////////		if (abs(StlPointOneOk3D.at<float>(i, 0) - StlPointOneOk3D.at<float>(i + 1, 0)) < error)
////////////////		{
////////////////			StlPoint3DTemp.at<float>(row, 0) = StlPointOneOk3D.at<float>(i, 0);
////////////////			StlPoint3DTemp.at<float>(row, 1) = StlPointOneOk3D.at<float>(i, 1);
////////////////			StlPoint3DTemp.at<float>(row, 2) = StlPointOneOk3D.at<float>(i, 2);
////////////////			row++;
////////////////			if (i == StlPointOneOk3D.rows - 2)//�������һ������
////////////////			{
////////////////
////////////////				StlPoint3DTemp.at<float>(row, 0) = StlPointOneOk3D.at<float>(i + 1, 0);
////////////////				StlPoint3DTemp.at<float>(row, 1) = StlPointOneOk3D.at<float>(i + 1, 1);
////////////////				StlPoint3DTemp.at<float>(row, 2) = StlPointOneOk3D.at<float>(i + 1, 2);
////////////////
////////////////				cv::Mat StlPointOneTwoThreeOk3D = SortAscendingEUU(StlPoint3DTemp.rowRange(0, row + 1));
////////////////
////////////////				for (int i = row_result; i < row_result + row + 1; i++)
////////////////				{
////////////////					StlPoint3D.at<float>(i, 0) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 0);
////////////////					StlPoint3D.at<float>(i, 1) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 1);
////////////////					StlPoint3D.at<float>(i, 2) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 2);
////////////////				}
////////////////			}
////////////////		}
////////////////		else
////////////////		{
////////////////			StlPoint3DTemp.at<float>(row, 0) = StlPointOneOk3D.at<float>(i, 0);
////////////////			StlPoint3DTemp.at<float>(row, 1) = StlPointOneOk3D.at<float>(i, 1);
////////////////			StlPoint3DTemp.at<float>(row, 2) = StlPointOneOk3D.at<float>(i, 2);
////////////////			if (i == StlPointOneOk3D.rows - 2)//�������һ������
////////////////			{
////////////////				if (abs(StlPointOneOk3D.at<float>(i, 0) - StlPointOneOk3D.at<float>(i + 1, 0)) < error)
////////////////				{
////////////////					row++;
////////////////					StlPoint3DTemp.at<float>(row, 0) = StlPointOneOk3D.at<float>(i + 1, 0);
////////////////					StlPoint3DTemp.at<float>(row, 1) = StlPointOneOk3D.at<float>(i + 1, 1);
////////////////					StlPoint3DTemp.at<float>(row, 2) = StlPointOneOk3D.at<float>(i + 1, 2);
////////////////				}
////////////////				else
////////////////				{
////////////////					flag_last_row = 1;
////////////////				}
////////////////			}
////////////////			cv::Mat StlPointOneTwoThreeOk3D = SortAscendingEUU(StlPoint3DTemp.rowRange(0, row + 1));
////////////////
////////////////			for (int i = row_result; i < row_result + row + 1; i++)
////////////////			{
////////////////				StlPoint3D.at<float>(i, 0) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 0);
////////////////				StlPoint3D.at<float>(i, 1) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 1);
////////////////				StlPoint3D.at<float>(i, 2) = StlPointOneTwoThreeOk3D.at<float>(i - row_result, 2);
////////////////			}
////////////////			row_result += row + 1;
////////////////			row = 0;
////////////////		}
////////////////	}
////////////////	if (flag_last_row == 1)
////////////////	{
////////////////		StlPoint3D.at<float>(row_result, 0) = StlPointOneOk3D.at<float>(StlPointOneOk3D.rows - 1, 0);
////////////////		StlPoint3D.at<float>(row_result, 1) = StlPointOneOk3D.at<float>(StlPointOneOk3D.rows - 1, 1);
////////////////		StlPoint3D.at<float>(row_result, 2) = StlPointOneOk3D.at<float>(StlPointOneOk3D.rows - 1, 2);
////////////////	}
////////////////
////////////////	return StlPoint3D;
////////////////}

//��ȡ���ĵ�����ͷ�Χ
CenterPoint_Range SQ_StlRead::GetCenterPoint(cv::Mat PointOriginalMat, int type)
{
	CenterPoint_Range centerPoint_Range;
	cv::Mat PointCloudMat;
	float max_x = 0, max_y = 0, max_z = 0;
	float min_x = 0, min_y = 0, min_z = 0;
	if (type == 2)
	{
		//PointCloudMat = PointCloudDeWeight(PointOriginalMat);//����ȥ��
		PointCloudMat = PointOriginalMat;//����δȥ��
	}
	if (type == 3)
	{
		cv::Mat TriNormalPointMat(PointOriginalMat.rows*3/4, 3, CV_32FC1);
		for (int i = 0; i < TriNormalPointMat.rows / 3; i++)
		{
			TriNormalPointMat.at<float>(i * 3 + 0, 0) = PointOriginalMat.at<float>(i * 4 + 1, 0);
			TriNormalPointMat.at<float>(i * 3 + 0, 1) = PointOriginalMat.at<float>(i * 4 + 1, 1);
			TriNormalPointMat.at<float>(i * 3 + 0, 2) = PointOriginalMat.at<float>(i * 4 + 1, 2);

			TriNormalPointMat.at<float>(i * 3 + 1, 0) = PointOriginalMat.at<float>(i * 4 + 2, 0);
			TriNormalPointMat.at<float>(i * 3 + 1, 1) = PointOriginalMat.at<float>(i * 4 + 2, 1);
			TriNormalPointMat.at<float>(i * 3 + 1, 2) = PointOriginalMat.at<float>(i * 4 + 2, 2);

			TriNormalPointMat.at<float>(i * 3 + 2, 0) = PointOriginalMat.at<float>(i * 4 + 3, 0);
			TriNormalPointMat.at<float>(i * 3 + 2, 1) = PointOriginalMat.at<float>(i * 4 + 3, 1);
			TriNormalPointMat.at<float>(i * 3 + 2, 2) = PointOriginalMat.at<float>(i * 4 + 3, 2);
		}
		//PointCloudMat = PointCloudDeWeight(TriNormalPointMat);//����ȥ��
		PointCloudMat = TriNormalPointMat;//����δȥ��

	}
	if (type == 4)
	{
		PointCloudMat = PointOriginalMat;
	}

	//////centerPoint_Range.center_x = mean_mat(PointCloudMat.colRange(0, 1));//ȡ��һ��x��ֵ
	//////centerPoint_Range.center_y = mean_mat(PointCloudMat.colRange(1, 2));//ȡ�ڶ���y��ֵ
	//////centerPoint_Range.center_z = mean_mat(PointCloudMat.colRange(2, 3));//ȡ������z��ֵ
		
	max_x = max_mat(PointCloudMat.col(0).clone());//ȡ��һ��x���ֵ
	max_y = max_mat(PointCloudMat.colRange(1, 2));//ȡ�ڶ���y���ֵ
	max_z = max_mat(PointCloudMat.colRange(2, 3));//ȡ������z���ֵ

	min_x = min_mat(PointCloudMat.colRange(0, 1));//ȡ��һ��x��Сֵ
	min_y = min_mat(PointCloudMat.colRange(1, 2));//ȡ�ڶ���y��Сֵ
	min_z = min_mat(PointCloudMat.colRange(2, 3));//ȡ������z��Сֵ

	centerPoint_Range.center_x = (max_x + min_x) / 2;
	centerPoint_Range.center_y = (max_y + min_y) / 2;
	centerPoint_Range.center_z = (max_z + min_z) / 2;
	
	centerPoint_Range.maxlength = max_four(0.01, max_x - min_x, max_y - min_y, max_z - min_z);//��ȡ��������Χ

	return centerPoint_Range;
}

//��ά�������ĵ�����
CenterPoint SQ_StlRead::GetCenterPointOnly(cv::Mat PointOriginalMat, int type)
{
	CenterPoint centerPoint;
	cv::Mat PointCloudMat;
	float max_x = 0, max_y = 0, max_z = 0;
	float min_x = 0, min_y = 0, min_z = 0;
	if (type == 2)
	{
		//PointCloudMat = PointCloudDeWeight(PointOriginalMat);//����ȥ��
		PointCloudMat = PointOriginalMat;//����δȥ��
	}
	if (type == 3)
	{
		cv::Mat TriNormalPointMat(PointOriginalMat.rows * 3 / 4, 3, CV_32FC1);
		for (int i = 0; i < TriNormalPointMat.rows / 3; i++)
		{
			TriNormalPointMat.at<float>(i * 3 + 0, 0) = PointOriginalMat.at<float>(i * 4 + 1, 0);
			TriNormalPointMat.at<float>(i * 3 + 0, 1) = PointOriginalMat.at<float>(i * 4 + 1, 1);
			TriNormalPointMat.at<float>(i * 3 + 0, 2) = PointOriginalMat.at<float>(i * 4 + 1, 2);

			TriNormalPointMat.at<float>(i * 3 + 1, 0) = PointOriginalMat.at<float>(i * 4 + 2, 0);
			TriNormalPointMat.at<float>(i * 3 + 1, 1) = PointOriginalMat.at<float>(i * 4 + 2, 1);
			TriNormalPointMat.at<float>(i * 3 + 1, 2) = PointOriginalMat.at<float>(i * 4 + 2, 2);

			TriNormalPointMat.at<float>(i * 3 + 2, 0) = PointOriginalMat.at<float>(i * 4 + 3, 0);
			TriNormalPointMat.at<float>(i * 3 + 2, 1) = PointOriginalMat.at<float>(i * 4 + 3, 1);
			TriNormalPointMat.at<float>(i * 3 + 2, 2) = PointOriginalMat.at<float>(i * 4 + 3, 2);
		}
		//PointCloudMat = PointCloudDeWeight(TriNormalPointMat);//����ȥ��
		PointCloudMat = TriNormalPointMat;//����δȥ��

	}
	if (type == 4)
	{
		PointCloudMat = PointOriginalMat;
	}

	max_x = max_mat(PointCloudMat.colRange(0, 1));//ȡ��һ��x���ֵ
	max_y = max_mat(PointCloudMat.colRange(1, 2));//ȡ�ڶ���y���ֵ
	max_z = max_mat(PointCloudMat.colRange(2, 3));//ȡ������z���ֵ

	min_x = min_mat(PointCloudMat.colRange(0, 1));//ȡ��һ��x��Сֵ
	min_y = min_mat(PointCloudMat.colRange(1, 2));//ȡ�ڶ���y��Сֵ
	min_z = min_mat(PointCloudMat.colRange(2, 3));//ȡ������z��Сֵ

	centerPoint.center_x = (max_x + min_x) / 2;
	centerPoint.center_y = (max_y + min_y) / 2;
	centerPoint.center_z = (max_z + min_z) / 2;
	
	return centerPoint;
}

//��ʽת��--�ı����ĵ�
cv::Mat SQ_StlRead::ChangeCenterRange(cv::Mat PointOriginalMat, CenterPoint_Range centerPoint_Range, int type)
{
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);

	if (type == 2 || type == 4)//û�з���������
	{
		for (int i = 0; i < PointOriginalMat.rows; i++)
		{
			StlPoint3D.at<float>(i, 0) = (PointOriginalMat.at<float>(i, 0) - centerPoint_Range.center_x) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i, 1) = (PointOriginalMat.at<float>(i, 1) - centerPoint_Range.center_y) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i, 2) = (PointOriginalMat.at<float>(i, 2) - centerPoint_Range.center_z) / centerPoint_Range.maxlength;
		}
	}
	if (type == 3)//�з���������
	{
		for (int i = 0; i < PointOriginalMat.rows / 4; i++)
		{
			//����������
			StlPoint3D.at<float>(i * 4, 0) = PointOriginalMat.at<float>(i * 4, 0);
			StlPoint3D.at<float>(i * 4, 1) = PointOriginalMat.at<float>(i * 4, 1);
			StlPoint3D.at<float>(i * 4, 2) = PointOriginalMat.at<float>(i * 4, 2);

			StlPoint3D.at<float>(i * 4 + 1, 0) = (PointOriginalMat.at<float>(i * 4 + 1, 0) - centerPoint_Range.center_x) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i * 4 + 1, 1) = (PointOriginalMat.at<float>(i * 4 + 1, 1) - centerPoint_Range.center_x) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i * 4 + 1, 2) = (PointOriginalMat.at<float>(i * 4 + 1, 2) - centerPoint_Range.center_x) / centerPoint_Range.maxlength;

			StlPoint3D.at<float>(i * 4 + 2, 0) = (PointOriginalMat.at<float>(i * 4 + 2, 0) - centerPoint_Range.center_y) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i * 4 + 2, 1) = (PointOriginalMat.at<float>(i * 4 + 2, 1) - centerPoint_Range.center_y) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i * 4 + 2, 2) = (PointOriginalMat.at<float>(i * 4 + 2, 2) - centerPoint_Range.center_y) / centerPoint_Range.maxlength;

			StlPoint3D.at<float>(i * 4 + 3, 0) = (PointOriginalMat.at<float>(i * 4 + 3, 0) - centerPoint_Range.center_z) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i * 4 + 3, 1) = (PointOriginalMat.at<float>(i * 4 + 3, 1) - centerPoint_Range.center_z) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i * 4 + 3, 2) = (PointOriginalMat.at<float>(i * 4 + 3, 2) - centerPoint_Range.center_z) / centerPoint_Range.maxlength;
		}
	}
	return StlPoint3D;
}

//��ʽת��
//****************************
//���⣺
//1.��.stl�ļ������ԭʼͼ����С��ȷ��
//2.����ͼ��������ϵ��opengl����ϵ��һ��
//****************************
//��ʽת��--�ı����ĵ�
cv::Mat SQ_StlRead::ChangeCenterRange(cv::Mat PointOriginalMat, int type)
{
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
	CenterPoint_Range centerPoint_Range = GetCenterPoint(PointOriginalMat, type);//��������������Χ
	StlPoint3D = ChangeCenterRange(PointOriginalMat, centerPoint_Range, type);
	return StlPoint3D;
}

//�����ĸ����е����ֵ
float SQ_StlRead::max_four(float first, float second, float third, float fourth)
{
	return std::max(std::max(first, second), std::max(third, fourth));
}

//�����ĸ����е���Сֵ
float SQ_StlRead::min_four(float first, float second, float third, float fourth)
{
	return std::min(std::min(first, second), std::min(third, fourth));
}

//��ͨ��Mat��ֵ
float SQ_StlRead::mean_mat(cv::Mat OriginalMat)
{
	return cv::mean(OriginalMat)[0];
}

//��Mat���ֵ
float SQ_StlRead::max_mat(cv::Mat OriginalMat)
{
	double max, min;
	cv::Point min_loc, max_loc;
	cv::minMaxLoc(OriginalMat, &min, &max, &min_loc, &max_loc);
	return max;
}

//��Mat��Сֵ
float SQ_StlRead::min_mat(cv::Mat OriginalMat)
{
	double max, min;
	cv::Point min_loc, max_loc;
	cv::minMaxLoc(OriginalMat, &min, &max, &min_loc, &max_loc);
	return min;
}

//����ƴ��-A=[A;B]
cv::Mat SQ_StlRead::MergeRows(cv::Mat A, cv::Mat B)
{
	int totalRows = A.rows + B.rows;
	cv::Mat mergedDescriptors(totalRows, A.cols, A.type());
	cv::Mat submat = mergedDescriptors.rowRange(0, A.rows);
	A.copyTo(submat);
	submat = mergedDescriptors.rowRange(A.rows, totalRows);
	B.copyTo(submat);
	return mergedDescriptors;
}

/*float Point_array[36][3] = { { 1, 1, -1 }, { -1, 1, -1 }, { -1, 1, 1 }, { 1, 1, -1 }, { 1, 1, 1 }, { -1, 1, 1 },
{ -1, -1, 1 }, { 1, -1, 1 }, { -1, -1, -1 }, { 1, -1, 1 }, { -1, -1, -1 }, { 1, -1, -1 },
{ -1, 1, -1 }, { -1, 1, 1 }, { -1, -1, -1 }, { -1, 1, 1 }, { -1, -1, -1 }, { -1, -1, 1 },
{ -1, 1, 1 }, { 1, 1, 1 }, { -1, -1, 1 }, { 1, 1, 1 }, { -1, -1, 1 }, { 1, -1, 1 },
{ -1, -1, -1 }, { 1, -1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 },
{ 1, 1, 1 }, { 1, 1, -1 }, { 1, -1, 1 }, { 1, 1, -1 }, { 1, -1, 1 }, { 1, -1, -1 } };
cv::Mat Point3D(36, 3, CV_32FC1);
for (int i = 0; i < Point3D.rows; i++)
	for (int j = 0; j < Point3D.cols; j++)
		Point3D.at<float>(i, j) = Point_array[i][j];
return Point3D;*/