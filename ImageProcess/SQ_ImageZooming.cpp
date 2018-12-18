#include "SQ_ImageZooming.h"

SQ_ImageZooming::SQ_ImageZooming(QLabel *label, QWidget *parent) :QLabel(parent)
{
	
}

SQ_ImageZooming::~SQ_ImageZooming()
{

}

//显示二维深度图
void SQ_ImageZooming::ShowDepthImage2D(cv::Mat ImageDepth)
{
	double ImageScaleRatio_init_x = 0;
	double ImageScaleRatio_init_y = 0;
	
	ImageOriginalCv = ImageDepth;//读取图片为Mat格式
	cvtColor(ImageOriginalCv, ImageOriginalCv, CV_BGR2RGB);//图片的色域通道转换

	//ImageScaleRatio_init_x = double(ui->ImageShow->width()) / double(ImageOriginalCv.size().width);
	//ImageScaleRatio_init_y = double(ui->ImageShow->height()) / double(ImageOriginalCv.size().height);
	ImageScaleRatio_init_x = 1;
	ImageScaleRatio_init_y = 1;

	ImageScaleRatio_init = cv::min(ImageScaleRatio_init_x, ImageScaleRatio_init_y);
	ImageScaleRatio = ImageScaleRatio_init;//记录初始缩放比例

	cv::resize(ImageOriginalCv, ImageScaleCv, cv::Size(), ImageScaleRatio_init, ImageScaleRatio_init);//图片缩放

	ImageScaleQt = QImage((const unsigned char*)(ImageScaleCv.data), ImageScaleCv.cols, ImageScaleCv.rows, ImageScaleCv.step, QImage::Format_RGB888);//从Mat转QImage
	ui->ImageShow->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	ui->ImageShow->setPixmap(QPixmap::fromImage(ImageScaleQt));//显示图片

	flag_image = 1;
	ui->Message->setText(QString::fromLocal8Bit("显示图片成功！"));

}


//打开图片并显示
void SQ_ImageZooming::OpenImageEvent()
{
	double ImageScaleRatio_init_x = 0;
	double ImageScaleRatio_init_y = 0;
	QString ImageOpenPath = QFileDialog::getOpenFileName(this, tr("ImageOpenPath"), ".\\..\\Image", tr("(*.png *.bmp *.jpg *.tif *.gif *.jpeg)"));//获取图片路径信息
	//QString ImageOpenPath = "C:\\Users\\sq\\Desktop\\11.png";

	if (ImageOpenPath.isEmpty())//如果路径为空
	{
		ui->Message->setText(QString::fromLocal8Bit("路径为空！"));
	}
	else
	{
		ImageOriginalCv = cv::imread(ImageOpenPath.toLatin1().data(),1);//读取图片为Mat格式--彩色图
		cvtColor(ImageOriginalCv, ImageOriginalCv, CV_BGR2RGB);//图片的色域通道转换

		ImageScaleRatio_init_x = double(ui->ImageShow->width()) / double(ImageOriginalCv.size().width);
		ImageScaleRatio_init_y = double(ui->ImageShow->height()) / double(ImageOriginalCv.size().height);
		ImageScaleRatio_init = cv::min(ImageScaleRatio_init_x, ImageScaleRatio_init_y);
		ImageScaleRatio = ImageScaleRatio_init;//记录初始缩放比例

		cv::resize(ImageOriginalCv, ImageScaleCv, cv::Size(), ImageScaleRatio_init, ImageScaleRatio_init);//图片缩放

		ImageScaleQt = QImage((const unsigned char*)(ImageScaleCv.data), ImageScaleCv.cols, ImageScaleCv.rows, ImageScaleCv.step, QImage::Format_RGB888);//从Mat转QImage
		ui->ImageShow->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		ui->ImageShow->setPixmap(QPixmap::fromImage(ImageScaleQt));//显示图片

		flag_image = 1;
		ui->Message->setText(QString::fromLocal8Bit("打开图片成功！"));
	}
}


//图片恢复原始大小
void SQ_ImageZooming::ImageRecoverEvent()
{
	if (flag_image == 1)
	{
		cv::resize(ImageOriginalCv, ImageScaleCv, cv::Size(), ImageScaleRatio_init, ImageScaleRatio_init);
		ImageScaleQt = QImage((const unsigned char*)(ImageScaleCv.data), ImageScaleCv.cols, ImageScaleCv.rows, ImageScaleCv.step, QImage::Format_RGB888);//从Mat转QImage
		ui->ImageShow->setPixmap(QPixmap::fromImage(ImageScaleQt));
		mouse_image_X = 0, mouse_image_Y = 0;
		mouse_label_0_X = 0, mouse_label_0_Y = 0;
		ImageScaleRatio = 1.0;//记录图片缩放比例	
	}
}


//图片保存
void SQ_ImageZooming::SaveImageEvent()
{
	//QString ImageSavePath = QFileDialog::getExistingDirectory(this, "Save Path", ".\\..\\");
	//ImageScaleQt.save(ImageSavePath+"\\11177.jpg");
	if (flag_image == 1)
	{
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy-MM-dd hh-mm-ss");
		ImageScaleQt.save(QString(".\\..\\SaveImage\\Image-") + QString(current_date) + QString(".jpg"));
		ui->Message->setText(QString::fromLocal8Bit("保存图片成功！"));
		QMessageBox::information(NULL, "Save", "Success", QMessageBox::Yes, QMessageBox::Yes);
	}
}

//滚轮定点缩放
void SQ_ImageZooming::wheelEvent(QWheelEvent*event)
{
	int image_x_start = 0;
	int image_x_end = 0;
	int image_y_start = 0;
	int image_y_end = 0;

	//判断光标是否在框内
	if (flag_image == 1 && mouse_X - ImageShow_0_X >= 0 && mouse_X - ImageShow_0_X <= ui->ImageShow->width() && mouse_Y - ImageShow_0_Y >= 0 && mouse_Y - ImageShow_0_Y <= ui->ImageShow->height()
		&& mouse_X - ImageShow_0_X <= ImageScaleCv.size().width && mouse_Y - ImageShow_0_Y <= ImageScaleCv.size().height)
	{
		mouse_image_X = mouse_label_0_X + floor((mouse_X - ImageShow_0_X) / ImageScaleRatio + 0.5);
		mouse_image_Y = mouse_label_0_Y + floor((mouse_Y - ImageShow_0_Y) / ImageScaleRatio + 0.5);

		//如果滚轮往上滚 ,图片变大
		if (event->delta() > 0)
		{
			ImageScaleRatio *= 1.1;
			if (ImageScaleRatio > 200)
				ImageScaleRatio = 200;
			mouse_label_0_X = mouse_image_X - floor((mouse_X - ImageShow_0_X) / ImageScaleRatio + 0.5);
			mouse_label_0_Y = mouse_image_Y - floor((mouse_Y - ImageShow_0_Y) / ImageScaleRatio + 0.5);

		}
		else//如果滚轮往下滚 ,图片变小
		{
			ImageScaleRatio /= 1.1;
			if (ImageScaleRatio < 0.1)
				ImageScaleRatio = 0.1;
			mouse_label_0_X = mouse_image_X - floor((mouse_X - ImageShow_0_X) / ImageScaleRatio + 0.5);
			mouse_label_0_Y = mouse_image_Y - floor((mouse_Y - ImageShow_0_Y) / ImageScaleRatio + 0.5);

			if (mouse_label_0_X < 0)
				mouse_label_0_X = 0;
			if (mouse_label_0_Y < 0)
				mouse_label_0_Y = 0;
		}

		//计算切割范围
		image_x_start = cv::max(0, mouse_label_0_X);
		image_x_end = cv::min(ImageOriginalCv.size().width, int(mouse_label_0_X + floor(ui->ImageShow->width() / ImageScaleRatio + 0.5)));
		image_y_start = cv::max(0, mouse_label_0_Y);
		image_y_end = cv::min(ImageOriginalCv.size().height, int(mouse_label_0_Y + floor(ui->ImageShow->height() / ImageScaleRatio + 0.5)));

		if (image_x_start > image_x_end && image_y_start > image_y_end)
			return;

		ImageScaleCv = ImageOriginalCv(cv::Range(image_y_start, image_y_end), cv::Range(image_x_start, image_x_end));//图片切割

		cv::resize(ImageScaleCv, ImageScaleCv, cv::Size(), ImageScaleRatio, ImageScaleRatio);//图片缩放

		ImageScaleQt = QImage((const unsigned char*)(ImageScaleCv.data), ImageScaleCv.cols, ImageScaleCv.rows, ImageScaleCv.step, QImage::Format_RGB888);//图片转换
		ui->ImageShow->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		ui->ImageShow->setPixmap(QPixmap::fromImage(ImageScaleQt));//图片显示

		//ui.ImageInfo->setText(QString::number(int(ImageScaleQt.width() / ImageScaleRatio), 10) + ",,," + QString::number(int(ImageScaleQt.height() / ImageScaleRatio), 10));//显示
	}
}

//光标移动
void SQ_ImageZooming::mouseMoveEvent(QMouseEvent *event)
{
	mouse_X = event->pos().x();//是光标在重载的Label中的位置，而不是在UI界面中自己放置的Label中的位置
	mouse_Y = event->pos().y();

	if (flag_image == 1)
	{
		mouse_image_X = mouse_label_0_X + floor((mouse_X - ImageShow_0_X) / ImageScaleRatio + 0.5);
		mouse_image_Y = mouse_label_0_Y + floor((mouse_Y - ImageShow_0_Y) / ImageScaleRatio + 0.5);
		if (mouse_image_X >= 0 && mouse_image_X < ImageScaleCv.size().width && mouse_image_X < ui->ImageShow->width() &&
			mouse_image_Y >= 0 && mouse_image_Y < ImageScaleCv.size().height && mouse_image_Y < ui->ImageShow->height())
		{
			R_Value = QString::number(int(ImageScaleCv.at<cv::Vec3b>(mouse_image_Y, mouse_image_X)[0]), 10);
			G_Value = QString::number(int(ImageScaleCv.at<cv::Vec3b>(mouse_image_Y, mouse_image_X)[1]), 10);
			B_Value = QString::number(int(ImageScaleCv.at<cv::Vec3b>(mouse_image_Y, mouse_image_X)[2]), 10);
		}
		if (mouse_image_X < ui->ImageShow->width() && mouse_image_Y < ui->ImageShow->height() && mouse_image_X <= ImageOriginalCv.size().width&&mouse_image_Y <= ImageOriginalCv.size().height)
			ui->ImageInfo->setText("X:" + QString::number(int(mouse_image_X), 10) + "," 
			+ "Y:" + QString::number(int(mouse_image_Y), 10)+ "," 
			+ "R:" + R_Value + "," 
			+ "G:" + G_Value + "," 
			+ "B:" + B_Value);//显示
	}
}

//鼠标点击事件
void SQ_ImageZooming::mousePressEvent(QMouseEvent *event)
{
	switch (event->button())
	{
		case Qt::LeftButton:{

			break; }
		case Qt::RightButton:{
			break; }
		case Qt::MidButton:{
			break; }
		default:break;
	}
}