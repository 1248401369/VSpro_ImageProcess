#include "SQ_StlRead.h"

SQ_StlRead::SQ_StlRead()
{
	pointcloud = new SQ_PointCloud();//点云重采样
}


//////////////////读取法向量信息--处理过--起点是三角面中心
//////////////////一组数据包括：三角平面的中心-法向量的起点坐标
//////////////////				平移过的法向量终点坐标
////////////////cv::Mat SQ_StlRead::NormalVectorProcessInfo(QStringList path)
////////////////{
////////////////	cv::Mat StlPoint3D = ReadAllStlPoint(path, 3);//读取.stl文件数据
////////////////	cv::Mat StlTriNormalPoint3D = ChangeCenterRange(StlPoint3D, 3);//修改显示三维图案的位置和大小
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

//读取三角面信息------2
//一组数据包括：三角平面点1坐标
//				三角平面点2坐标
//              三角平面点3坐标
cv::Mat SQ_StlRead::TrianglePatchInfo(QStringList path)
{
	cv::Mat StlPoint3D = ReadAllStlPoint(path, 2);//读取.stl文件数据
	cv::Mat StlTriPoint3D = ChangeCenterRange(StlPoint3D, 2);//修改显示三维图案的位置和大小
	return StlTriPoint3D;
}

//读取三角面信息(原始的.stl中的数据)------2
//一组数据包括：三角平面点1坐标
//				三角平面点2坐标
//              三角平面点3坐标
cv::Mat SQ_StlRead::TrianglePatchOriginalInfo(QStringList path)
{
	cv::Mat StlPoint3D = ReadAllStlPoint(path, 2);//读取.stl文件数据
	return StlPoint3D;
}


//读取三角面和法向量信息------3
//一组数据包括：原始的法向量数据
//              三角平面点1坐标
//				三角平面点2坐标
//              三角平面点3坐标
////////////////cv::Mat SQ_StlRead::PointALLInfo(QStringList path)
////////////////{
////////////////	cv::Mat StlPoint3D = ReadAllStlPoint(path, 3);//读取.stl文件数据
////////////////	cv::Mat StlTriNormalPoint3D = ChangeCenterRange(StlPoint3D, 3);//修改显示三维图案的位置和大小
////////////////	return StlTriNormalPoint3D;
////////////////}

//读取三角面和法向量信息（法向量处理过)--原始的读取.stl的数据
//一组数据包括：三角平面的中心-法向量的起点坐标
//				平移过的法向量终点坐标
//              三角平面点1坐标
//				三角平面点2坐标
////////////////////              三角平面点3坐标
//////////////////cv::Mat SQ_StlRead::PointALLProcessInfo(QStringList path)
//////////////////{
//////////////////	cv::Mat StlPoint3D = ReadAllStlPoint(path, 3);//读取.stl文件数据
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


//读取点云信息------4
//一组数据包括：去重后的每个点的坐标
cv::Mat SQ_StlRead::PointCloudInfo(QStringList path)
{
	cv::Mat StlPoint3D = ReadAllStlPoint(path, 4);//读取.stl文件数据
	cv::Mat CloudDeWeightPoint3D = PointCloudDeWeight(StlPoint3D);//点云去重

	//qDebug()输出坐标
	//for (int i = 0; i < CloudDeWeightPoint3D.rows; i++)
	//	qDebug() << CloudDeWeightPoint3D.at<float>(i, 0) << CloudDeWeightPoint3D.at<float>(i, 1) << CloudDeWeightPoint3D.at<float>(i, 2);

	//cv::Mat CloudDeWeightPoint3D = StlPoint3D;//不去重
	cv::Mat StlCloudPoint3D = ChangeCenterRange(CloudDeWeightPoint3D, 4);//修改显示三维图案的位置和大小
	return StlCloudPoint3D;
}

//读取点云信息(获取原始的.stl中的点云数据)------4
//一组数据包括：去重后的每个点的坐标
cv::Mat SQ_StlRead::PointCloudOriginalInfo(QStringList path)
{
	cv::Mat StlPoint3D = ReadAllStlPoint(path, 4);//读取.stl文件数据
	cv::Mat CloudDeWeightPoint3D = PointCloudDeWeight(StlPoint3D);//点云去重
	return CloudDeWeightPoint3D;
}


//读取多个.stl文件的数据
cv::Mat SQ_StlRead::ReadAllStlPoint(QStringList path,int type)
{
	//读取.stl文件数据
	cv::Mat StlPoint3D = StlPointInfo(path[0].toLatin1().data(), type);
	for (int i = 1; i < path.size(); i++)
	{
		StlPoint3D = MergeRows(StlPoint3D, StlPointInfo(path[i].toLatin1().data(), type));
	}
	return StlPoint3D;
}

//读取.stl文件--包括法向量和三角面信息--（法向量，点1，点2，点3）
cv::Mat SQ_StlRead::StlPointInfo(char* path, int type)
{
	cv::Mat StlPoint3D(1, 3, CV_32FC1);//二进制文件
	int flag_bin_ascii = StlType(path);
	if (flag_bin_ascii == 1)//二进制文件
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
	else//ASCII文件
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

//判断.stl文件类型
int SQ_StlRead::StlType(char* path)
{
	FILE *fp;
	char fileName[64];
	Faces *faces = (Faces*)malloc(sizeof(Faces));//链表的表头
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
		fscanf_s(fp, "%s", str, 24);//该代码的作用仅是移动文件指针，使指针跳过标识符“solid”，将文件指针移到文件名称的位置
		fscanf_s(fp, "%s", head.partName, 80);//读入文件名称

		//循环读取三角片面的法线和顶点数据
		while (!feof(fp))
		{
			p->pointer = (Faces*)malloc(sizeof(Faces));//创建新结点，用于接收数据
			q = p;
			p = p->pointer;
			fscanf_s(fp, "%s", str, 24);//使文件指针跳过标识符“facetnormal”，指到法线数据部分
			if (str[0] == 'f')//判断文件类型
				flag_bin_ascii = 2;//ASCII
			else
				flag_bin_ascii = 1;//二进制
			break;
		}
		free(q->pointer);//由于文件末尾有一行字符”endsolid .....“，造成多创建了一个结点，该结点的数据是无用的，因此要释放
		q->pointer = NULL;//最后一个结点的数据释放完之后，将指向最后结点的指针置为NULL，方便遍历链表
	}
	fclose(fp);
	free(faces);
	return flag_bin_ascii;
}

//读取二进制格式的.stl文件
cv::Mat SQ_StlRead::BinaryStlPointInfo(char* path, int type)
{
	cv::Mat StlPoint3DZero(1, 3, CV_32FC1);
	Head head;
	FILE *fp;
	fopen_s(&fp, path, "rb");
	if (fp != NULL)
	{
		fread(head.partName, 80, 1, fp);//获取部件名
		fread(&head.faceNum, 4, 1, fp);//获取三角面片的数目
	}
	Face *face = (Face*)malloc(head.faceNum * sizeof(Face));//根据三角面片的数目，创建一个Face类型的数组

	//循环读取三角面片数据
	for (int i = 0; i < head.faceNum; i++)
	{
		fread(&face[i].normal, 12, 1, fp);//读取法线数据
		fread(&face[i].p1, 12, 1, fp);//读取顶点1的数据
		fread(&face[i].p2, 12, 1, fp);//读取顶点2的数据
		fread(&face[i].p3, 12, 1, fp);//读取顶点3的数据
		fread(&face[i].info, 2, 1, fp);//读取保留项数据，这一项一般没什么用，这里选择读取是为了移动文件指针
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

//读取ASCII格式的.stl文件
cv::Mat SQ_StlRead::AsciiStlPointInfo(char* path, int type)
{
	cv::Mat StlPoint3D(1, 3, CV_32FC1);
	FILE *fp;
	char fileName[64];
	Faces *faces = (Faces*)malloc(sizeof(Faces));//链表的表头
	Faces *p = faces;
	Faces *q;
	Head head;
	int i = 0;
	head.faceNum = 0;
	fp = fopen(path, "r");
	if (fp)
	{
		char str[24];
		fscanf_s(fp, "%s", str, 24);//该代码的作用仅是移动文件指针，使指针跳过标识符“solid”，将文件指针移到文件名称的位置
		fscanf_s(fp, "%s", head.partName, 80);//读入文件名称
		//循环读取三角片面的法线和顶点数据
		while (!feof(fp))
		{
			p->pointer = (Faces*)malloc(sizeof(Faces));//创建新结点，用于接收数据
			q = p;
			p = p->pointer;
			fscanf_s(fp, "%s", str, 24);//使文件指针跳过标识符“facetnormal”，指到法线数据部分
			fscanf_s(fp, "%f%f%f", &p->data.normal.i, &p->data.normal.j, &p->data.normal.k, 12);//读取法线数据
			fscanf_s(fp, "%s", str, 24);//使文件指针跳过标识符“facetloop”
			fscanf_s(fp, "%s", str, 24);//使文件指针跳过标识符“vertex”，指到顶点1的数据部分
			fscanf_s(fp, "%f%f%f", &p->data.vertex1.x, &p->data.vertex1.y, &p->data.vertex1.z, 12);
			fscanf_s(fp, "%s", str, 24);//使文件指针跳过标识符“vertex”，指到顶点2的数据部分
			fscanf_s(fp, "%f%f%f", &p->data.vertex2.x, &p->data.vertex2.y, &p->data.vertex2.z, 12);
			fscanf_s(fp, "%s", str, 24);//使文件指针跳过标识符“vertex”，指到顶点3的数据部分
			fscanf_s(fp, "%f%f%f", &p->data.vertex3.x, &p->data.vertex3.y, &p->data.vertex3.z, 12);
			fscanf_s(fp, "%s", str, 24);//使文件指针跳过标识符“endloop”
			fscanf_s(fp, "%s", str, 24);//使文件指针跳过标识符“endfacet“
			head.faceNum++;
		}
		free(q->pointer);//由于文件末尾有一行字符”endsolid .....“，造成多创建了一个结点，该结点的数据是无用的，因此要释放
		q->pointer = NULL;//最后一个结点的数据释放完之后，将指向最后结点的指针置为NULL，方便遍历链表
	}
	else
	{
		printf("打开文件失败！");
	}
	fclose(fp);
	p = faces->pointer;//获取链表第二个结点的指针

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

//点云去重--没有法向量数据
cv::Mat SQ_StlRead::PointCloudDeWeight(cv::Mat PointCloudOriginalMat)
{
	cv::Mat StlPoint3D(PointCloudOriginalMat.rows, PointCloudOriginalMat.cols, CV_32FC1);
	PointCloudOriginalMat.copyTo(StlPoint3D);
	//StlPoint3D = SortAscendingDeleteUUU(StlPoint3D);//删除相同的数据
	StlPoint3D = pointcloud->PCLDecreaseSampleToMat(StlPoint3D, 0.5);//降采样速度快
	return StlPoint3D;
}

//三列中前两列元素相等，对第三列进行排序并删除相同的数据
cv::Mat SQ_StlRead::SortAscendingDeleteEEU(cv::Mat PointOriginalMat)
{
	int row_result = 0;//存储最终结果中的行的个数
	cv::Mat StlPointThree3D = PointOriginalMat.col(2).clone();//获取矩阵第三列
	cv::Mat StlPointThreeIndex3D(StlPointThree3D.rows, StlPointThree3D.cols, CV_32FC1);//保存按照升序排列后的对应行的索引
	cv::sortIdx(StlPointThree3D, StlPointThreeIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//对矩阵第三列进行升序排列，保存对应行的索引
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//保存最后输出的结果

	for (int i = 0; i < PointOriginalMat.rows-1; i++)
	{
		if (abs(PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 2) - PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i + 1, 0), 2)) > error)
		{
			//保存不同的数据
			StlPoint3D.at<float>(row_result, 0) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 0);
			StlPoint3D.at<float>(row_result, 1) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 1);
			StlPoint3D.at<float>(row_result, 2) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 2);//第三列按升序排列
			row_result ++;
		}	
	}
	//保存最后一行数据
	StlPoint3D.at<float>(row_result, 0) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(PointOriginalMat.rows - 1, 0), 0);
	StlPoint3D.at<float>(row_result, 1) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(PointOriginalMat.rows - 1, 0), 1);
	StlPoint3D.at<float>(row_result, 2) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(PointOriginalMat.rows - 1, 0), 2);//第三列按升序排列
	
	StlPoint3D = StlPoint3D.rowRange(0, row_result + 1);

	return StlPoint3D;
}

//三列中前两列元素相等，对第三列进行排序
cv::Mat SQ_StlRead::SortAscendingEEU(cv::Mat PointOriginalMat)
{
	cv::Mat StlPointThree3D = PointOriginalMat.col(2).clone();//获取矩阵第三列
	cv::Mat StlPointThreeIndex3D(StlPointThree3D.rows, StlPointThree3D.cols, CV_32FC1);//保存按照升序排列后的对应行的索引
	cv::sortIdx(StlPointThree3D, StlPointThreeIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//对矩阵第三列进行升序排列，保存对应行的索引
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//保存最后输出的结果

	for (int i = 0; i < PointOriginalMat.rows; i++)
	{
		//保存升序排列后的矩阵
		StlPoint3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 0);
		StlPoint3D.at<float>(i, 1) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 1);
		StlPoint3D.at<float>(i, 2) = PointOriginalMat.at<float>(StlPointThreeIndex3D.at<int>(i, 0), 2);//第三列按升序排列
	}	

	return StlPoint3D;
}

//三列中前一列元素相等，对第二、三列进行排序并删除相同的数据
cv::Mat SQ_StlRead::SortAscendingDeleteEUU(cv::Mat PointOriginalMat)
{
	int row = 0;//存储第二列数值相同的行的个数
	int row_result = 0;//存储最终结果中的行的个数
	int flag_last_row = 0;//为1表示最后一行与前一行的第二列数据不等
	cv::Mat StlPointTwo3D = PointOriginalMat.colRange(1, 2);//获取矩阵第二列
	cv::Mat StlPointTwoThreeOk3D;
	cv::Mat StlPointTwoIndex3D(StlPointTwo3D.rows, StlPointTwo3D.cols, CV_32FC1);
	cv::sortIdx(StlPointTwo3D, StlPointTwoIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//对矩阵第二列进行升序排列，保存对应行的索引
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//存储最后的结果

	cv::Mat StlPointTwoOk3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//存储按照第二列升序排列后的数组
	for (int i = 0; i < PointOriginalMat.rows; i++)
	{
		StlPointTwoOk3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 0);
		StlPointTwoOk3D.at<float>(i, 1) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 1);//第二列按升序排列
		StlPointTwoOk3D.at<float>(i, 2) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 2);
	}

	cv::Mat StlPoint3DTemp(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//存储第二列相同的数组

	for (int i = 0; i < StlPointTwoOk3D.rows - 1; i++)
	{
		if (abs(StlPointTwoOk3D.at<float>(i, 1) - StlPointTwoOk3D.at<float>(i + 1, 1)) < error)//如果第i行和第i+1行的第二列数据相同，则进行暂存
		{
			StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i, 0);
			StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i, 1);
			StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i, 2);
			row++;

			if (i == StlPointTwoOk3D.rows - 2)//处理最后一行数据
			{
				//此时最后一行数据和上一行数据的第二列相同，因此进行存储
				StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i + 1, 0);
				StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i + 1, 1);
				StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i + 1, 2);

				StlPointTwoThreeOk3D = SortAscendingDeleteEEU(StlPoint3DTemp.rowRange(0, row + 1));//对第二列相同的数据进行删重操作

				//存储最终需要输出的结果
				for (int i = row_result; i < row_result + StlPointTwoThreeOk3D.rows; i++)
				{
					StlPoint3D.at<float>(i, 0) = StlPointTwoThreeOk3D.at<float>(i - row_result, 0);
					StlPoint3D.at<float>(i, 1) = StlPointTwoThreeOk3D.at<float>(i - row_result, 1);
					StlPoint3D.at<float>(i, 2) = StlPointTwoThreeOk3D.at<float>(i - row_result, 2);
				}

				row_result += StlPointTwoThreeOk3D.rows;//记录最终输出数组的行数
			}
		}
		else
		{
			//如果第i行和第i+1行的第二列数据不相同，则存储第i行数据，然后对第三列数据进行去重操作
			StlPoint3DTemp.at<float>(row, 0) = StlPointTwoOk3D.at<float>(i, 0);
			StlPoint3DTemp.at<float>(row, 1) = StlPointTwoOk3D.at<float>(i, 1);
			StlPoint3DTemp.at<float>(row, 2) = StlPointTwoOk3D.at<float>(i, 2);
			if (i == StlPointTwoOk3D.rows - 2)//处理最后一行数据
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

	//如果最后一行与上一行数据的第二列不同，则直接存在最终输出输出的矩阵中
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

//////////////////三列中前一列元素相等，对第二、三列进行排序
////////////////cv::Mat SQ_StlRead::SortAscendingEUU(cv::Mat PointOriginalMat)
////////////////{
////////////////	int row = 0;//存储第二列数值相同的行的个数
////////////////	int row_result = 0;//存储最终结果中的行的个数
////////////////	int flag_last_row = 0;//为1表示最后一行与前一行的第二列数据不等
////////////////	cv::Mat StlPointTwo3D = PointOriginalMat.colRange(1, 2);//获取矩阵第二列
////////////////
////////////////	cv::Mat StlPointTwoIndex3D(StlPointTwo3D.rows, StlPointTwo3D.cols, CV_32FC1);
////////////////	cv::sortIdx(StlPointTwo3D, StlPointTwoIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//对矩阵第二列进行升序排列，保存对应行的索引
////////////////
////////////////	cv::Mat StlPointTwoOk3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
////////////////	for (int i = 0; i < PointOriginalMat.rows; i++)
////////////////	{
////////////////		StlPointTwoOk3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 0);
////////////////		StlPointTwoOk3D.at<float>(i, 1) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 1);//第二列按升序排列
////////////////		StlPointTwoOk3D.at<float>(i, 2) = PointOriginalMat.at<float>(StlPointTwoIndex3D.at<int>(i, 0), 2);
////////////////	}
////////////////
////////////////	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//存储最后的结果
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
////////////////			if (i == StlPointTwoOk3D.rows - 2)//处理最后一行数据
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
////////////////			if (i == StlPointTwoOk3D.rows - 2)//处理最后一行数据
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
//////////////////三列中元素都不相等，对第一、二、三列进行排序并删除相同的数据
////////////////cv::Mat SQ_StlRead::SortAscendingDeleteUUU(cv::Mat PointOriginalMat)
////////////////{
////////////////	int row = 0;//存储第一列数值相同的行的个数
////////////////	int row_result = 0;//存储最终结果中的行的个数
////////////////	int flag_last_row = 0;//为1表示最后一行与前一行的第一列数据不等
////////////////	cv::Mat StlPointOneTwoThreeOk3D;
////////////////	cv::Mat StlPointOne3D = PointOriginalMat.col(0).clone();//获取矩阵第一列
////////////////	cv::Mat StlPointOneIndex3D(StlPointOne3D.rows, StlPointOne3D.cols, CV_32FC1);
////////////////	cv::sortIdx(StlPointOne3D, StlPointOneIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//对矩阵第一列进行升序排列，保存对应行的索引
////////////////
////////////////	cv::Mat StlPointOneOk3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
////////////////	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//存储最后的结果
////////////////
////////////////	cv::Mat StlPoint3DTemp(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
////////////////	for (int i = 0; i < PointOriginalMat.rows; i++)
////////////////	{
////////////////		StlPointOneOk3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 0);//第一列按升序排列
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
////////////////			if (i == StlPointOneOk3D.rows - 2)//处理最后一行数据
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
////////////////			if (i == StlPointOneOk3D.rows - 2)//处理最后一行数据
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

//三列中元素都不相等，对第一、二、三列进行排序
////////////////cv::Mat SQ_StlRead::SortAscendingUUU(cv::Mat PointOriginalMat)
////////////////{
////////////////	int row = 0;//存储第一列数值相同的行的个数
////////////////	int row_result = 0;//存储最终结果中的行的个数
////////////////	int flag_last_row = 0;//为1表示最后一行与前一行的第一列数据不等
////////////////
////////////////	cv::Mat StlPointOne3D = PointOriginalMat.col(0).clone();//获取矩阵第一列
////////////////	cv::Mat StlPointOneIndex3D(StlPointOne3D.rows, StlPointOne3D.cols, CV_32FC1);
////////////////	cv::sortIdx(StlPointOne3D, StlPointOneIndex3D, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);//对矩阵第一列进行升序排列，保存对应行的索引
////////////////
////////////////	cv::Mat StlPointOneOk3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
////////////////	for (int i = 0; i < PointOriginalMat.rows; i++)
////////////////	{
////////////////		StlPointOneOk3D.at<float>(i, 0) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 0);//第一列按升序排列
////////////////		StlPointOneOk3D.at<float>(i, 1) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 1);
////////////////		StlPointOneOk3D.at<float>(i, 2) = PointOriginalMat.at<float>(StlPointOneIndex3D.at<int>(i, 0), 2);
////////////////	}
////////////////
////////////////	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);//存储最后的结果
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
////////////////			if (i == StlPointOneOk3D.rows - 2)//处理最后一行数据
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
////////////////			if (i == StlPointOneOk3D.rows - 2)//处理最后一行数据
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

//获取中心点坐标和范围
CenterPoint_Range SQ_StlRead::GetCenterPoint(cv::Mat PointOriginalMat, int type)
{
	CenterPoint_Range centerPoint_Range;
	cv::Mat PointCloudMat;
	float max_x = 0, max_y = 0, max_z = 0;
	float min_x = 0, min_y = 0, min_z = 0;
	if (type == 2)
	{
		//PointCloudMat = PointCloudDeWeight(PointOriginalMat);//点云去重
		PointCloudMat = PointOriginalMat;//点云未去重
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
		//PointCloudMat = PointCloudDeWeight(TriNormalPointMat);//点云去重
		PointCloudMat = TriNormalPointMat;//点云未去重

	}
	if (type == 4)
	{
		PointCloudMat = PointOriginalMat;
	}

	//////centerPoint_Range.center_x = mean_mat(PointCloudMat.colRange(0, 1));//取第一列x均值
	//////centerPoint_Range.center_y = mean_mat(PointCloudMat.colRange(1, 2));//取第二列y均值
	//////centerPoint_Range.center_z = mean_mat(PointCloudMat.colRange(2, 3));//取第三列z均值
		
	max_x = max_mat(PointCloudMat.col(0).clone());//取第一列x最大值
	max_y = max_mat(PointCloudMat.colRange(1, 2));//取第二列y最大值
	max_z = max_mat(PointCloudMat.colRange(2, 3));//取第三列z最大值

	min_x = min_mat(PointCloudMat.colRange(0, 1));//取第一列x最小值
	min_y = min_mat(PointCloudMat.colRange(1, 2));//取第二列y最小值
	min_z = min_mat(PointCloudMat.colRange(2, 3));//取第三列z最小值

	centerPoint_Range.center_x = (max_x + min_x) / 2;
	centerPoint_Range.center_y = (max_y + min_y) / 2;
	centerPoint_Range.center_z = (max_z + min_z) / 2;
	
	centerPoint_Range.maxlength = max_four(0.01, max_x - min_x, max_y - min_y, max_z - min_z);//获取三轴的最大范围

	return centerPoint_Range;
}

//三维物体中心点坐标
CenterPoint SQ_StlRead::GetCenterPointOnly(cv::Mat PointOriginalMat, int type)
{
	CenterPoint centerPoint;
	cv::Mat PointCloudMat;
	float max_x = 0, max_y = 0, max_z = 0;
	float min_x = 0, min_y = 0, min_z = 0;
	if (type == 2)
	{
		//PointCloudMat = PointCloudDeWeight(PointOriginalMat);//点云去重
		PointCloudMat = PointOriginalMat;//点云未去重
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
		//PointCloudMat = PointCloudDeWeight(TriNormalPointMat);//点云去重
		PointCloudMat = TriNormalPointMat;//点云未去重

	}
	if (type == 4)
	{
		PointCloudMat = PointOriginalMat;
	}

	max_x = max_mat(PointCloudMat.colRange(0, 1));//取第一列x最大值
	max_y = max_mat(PointCloudMat.colRange(1, 2));//取第二列y最大值
	max_z = max_mat(PointCloudMat.colRange(2, 3));//取第三列z最大值

	min_x = min_mat(PointCloudMat.colRange(0, 1));//取第一列x最小值
	min_y = min_mat(PointCloudMat.colRange(1, 2));//取第二列y最小值
	min_z = min_mat(PointCloudMat.colRange(2, 3));//取第三列z最小值

	centerPoint.center_x = (max_x + min_x) / 2;
	centerPoint.center_y = (max_y + min_y) / 2;
	centerPoint.center_z = (max_z + min_z) / 2;
	
	return centerPoint;
}

//格式转换--改变中心点
cv::Mat SQ_StlRead::ChangeCenterRange(cv::Mat PointOriginalMat, CenterPoint_Range centerPoint_Range, int type)
{
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);

	if (type == 2 || type == 4)//没有法向量数据
	{
		for (int i = 0; i < PointOriginalMat.rows; i++)
		{
			StlPoint3D.at<float>(i, 0) = (PointOriginalMat.at<float>(i, 0) - centerPoint_Range.center_x) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i, 1) = (PointOriginalMat.at<float>(i, 1) - centerPoint_Range.center_y) / centerPoint_Range.maxlength;
			StlPoint3D.at<float>(i, 2) = (PointOriginalMat.at<float>(i, 2) - centerPoint_Range.center_z) / centerPoint_Range.maxlength;
		}
	}
	if (type == 3)//有法向量数据
	{
		for (int i = 0; i < PointOriginalMat.rows / 4; i++)
		{
			//法向量不变
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

//格式转换
//****************************
//问题：
//1.从.stl文件导入的原始图案大小不确定
//2.导入图案的坐标系与opengl坐标系不一致
//****************************
//格式转换--改变中心点
cv::Mat SQ_StlRead::ChangeCenterRange(cv::Mat PointOriginalMat, int type)
{
	cv::Mat StlPoint3D(PointOriginalMat.rows, PointOriginalMat.cols, CV_32FC1);
	CenterPoint_Range centerPoint_Range = GetCenterPoint(PointOriginalMat, type);//求中心坐标的最大范围
	StlPoint3D = ChangeCenterRange(PointOriginalMat, centerPoint_Range, type);
	return StlPoint3D;
}

//计算四个数中的最大值
float SQ_StlRead::max_four(float first, float second, float third, float fourth)
{
	return std::max(std::max(first, second), std::max(third, fourth));
}

//计算四个数中的最小值
float SQ_StlRead::min_four(float first, float second, float third, float fourth)
{
	return std::min(std::min(first, second), std::min(third, fourth));
}

//求单通道Mat均值
float SQ_StlRead::mean_mat(cv::Mat OriginalMat)
{
	return cv::mean(OriginalMat)[0];
}

//求Mat最大值
float SQ_StlRead::max_mat(cv::Mat OriginalMat)
{
	double max, min;
	cv::Point min_loc, max_loc;
	cv::minMaxLoc(OriginalMat, &min, &max, &min_loc, &max_loc);
	return max;
}

//求Mat最小值
float SQ_StlRead::min_mat(cv::Mat OriginalMat)
{
	double max, min;
	cv::Point min_loc, max_loc;
	cv::minMaxLoc(OriginalMat, &min, &max, &min_loc, &max_loc);
	return min;
}

//矩阵拼接-A=[A;B]
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