#include "SQ_Mysql.h"


SQ_Mysql::SQ_Mysql(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//������
	connect(ui.tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(GetLocation()));

	//�޸ı����ĳ�е�����
	connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(ItemChanged()));
}

SQ_Mysql::~SQ_Mysql()
{
	
}

//�رմ���֮�䶯��
void SQ_Mysql::closeEvent(QCloseEvent *event)
{
	db.close();//�ر����ݿ� 
	ui.tableWidget->setRowCount(20);//���ñ�������
	ui.tableWidget->setColumnCount(3);//���ñ�������
	ui.tableWidget->clear();//��ձ����������
}


//�������ݿ�
//mysql -u root -p 123456
bool SQ_Mysql::Connect()
{
	bool state;
	//addDatabase����������һ�����ӣ������������ʱ�����ǿ��Դ�������Ҫ�����������͵����ݿ�
	db = QSqlDatabase::addDatabase("QMYSQL");     //���� 

	db.setHostName("localhost");			//���ݿ��ַ��һ�㶼�Ǳ��أ�����localhost�Ϳ��� 
	db.setDatabaseName("sq_test");			//���ݿ�����������Mysql��������ݿ���������д��������Mysql�����и����ݿ��test��������Navicat������Լ������ݿ�����
	db.setUserName("root");					//�û�����һ���Ǳ����û�������root�Ϳ���
	db.setPassword("123456");				//���룬��д���Լ���Mysql��½���룬Ϊ�˱�����������*�����ҵ�����
	db.setPort(3306);						//�˿�Ĭ�ϵ���3306�����Բ���д 

	if (db.open())
	{
		//QMessageBox::warning(NULL, QStringLiteral("��ʾ"), "open ok", QMessageBox::Yes);
		main_ui->Message->setText(QString::fromLocal8Bit("���ݿ�򿪳ɹ���"));
		state = true;
	}
	else
	{
		//QMessageBox::warning(NULL, QStringLiteral("��ʾ"), "open failed", QMessageBox::Yes);
		main_ui->Message->setText(QString::fromLocal8Bit("���ݿ��ʧ�ܣ�"));
		state = false;
	}
	//db.close();//�ر����ݿ� 
	return state;
}

//�½���
bool SQ_Mysql::CreateTable()
{
	QSqlQuery query;
	bool state;
	state = query.exec("create table if not exists teacher (id int,name varchar(20))");

	if (state)
	{
		main_ui->Message->setText(QString::fromLocal8Bit("������ɹ���"));
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("������ʧ�ܣ�"));
	}
	return state;
}

//�������
bool SQ_Mysql::InsertData()
{

	QSqlQuery query;
	bool state;

	int id = 11;
	QString name = "mz";
	int score = 98;

	QString str_query = "insert into student values (" + QString::number(id, 10) + ",'" + name + "'," + QString::number(score, 10) + ")";
	//qDebug() << str_query;
	state = query.exec(str_query);

	//query.prepare("insert into student values(?,?,?)");
	//query.bindValue(0, 11);
	//query.bindValue(1, "qw");
	//query.bindValue(2, 100);
	//state = query.exec();

	if (state)
	{
		main_ui->Message->setText(QString::fromLocal8Bit("������ӳɹ���"));
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("�������ʧ�ܣ�"));
	}
	return state;
}

//ɾ������
bool SQ_Mysql::DeleteData()
{
	QSqlQuery query;
	bool state;
	state = query.exec("delete from student where id = 11");
	if (state)
	{
		main_ui->Message->setText(QString::fromLocal8Bit("����ɾ���ɹ���"));
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("����ɾ��ʧ�ܣ�"));
	}
	return state;
}

//�޸�����
bool SQ_Mysql::UpdateData()
{
	QSqlQuery query;
	bool state;
	state = query.exec("update student set id = 88 where name = 'zc' ");
	if (state)
	{
		main_ui->Message->setText(QString::fromLocal8Bit("�����޸ĳɹ���"));
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("�����޸�ʧ�ܣ�"));
	}
	return state;
}

//��ѯ����
bool SQ_Mysql::QueryData()
{
	QSqlQuery query;
	bool state;
	state = query.exec("select *  from student");
	if (state)
	{
		while (query.next())
		{
			main_ui->Message->setText(QString::fromLocal8Bit("���ݲ�ѯ�ɹ���"));
			qDebug() << query.value(0).toInt() << query.value(1).toString();
		}
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("���ݲ�ѯʧ�ܣ�"));
	}
	return state;
}

//��ʾ����
void SQ_Mysql::on_QueryData_clicked()
{
	flag_show = 0;
	int i = 0;
	sum_row = 0;
	ui.tableWidget->setRowCount(20);//���ñ�������
	ui.tableWidget->setColumnCount(3);//���ñ�������
	ui.tableWidget->clear();//��ձ����������
	ui.tableWidget->setWindowTitle("QTableWidget");
	//ui.tableWidget->resize(400, 300);  //���ñ���С
	QStringList header;
	header << "ID" << "Name" << "Grade";   
	ui.tableWidget->setHorizontalHeaderLabels(header);//��ͷ
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true); //���ó�������

	QSqlQuery query;
	query.exec("select *  from student");
	while (query.next())
	{
		sum_row++;
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(query.value(0).toInt(),10)));
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(query.value(2).toInt(), 10)));
		i++;
	}
	ui.tableWidget->show();
	flag_show = 1;
}


//�һ�ɾ����������
void SQ_Mysql::contextMenuEvent(QContextMenuEvent *event)
{
	row = ui.tableWidget->currentIndex().row();
	col = ui.tableWidget->currentIndex().column();
	//qDebug() << row << col;

	QMenu *menu = new QMenu();
	QAction *deleterows = new QAction(QString::fromLocal8Bit("ɾ��"));
	menu->addAction(deleterows);	
	connect(deleterows, SIGNAL(triggered(bool)), this, SLOT(DeleteRows()));
	menu->exec(QCursor::pos());
}

//ɾ��ĳ������
void SQ_Mysql::DeleteRows()
{
	int i = 0;
	if (row >= 0 && row <= sum_row-1)
	{
		QSqlQuery query;
		QString str_query = "delete from student where id = " + ui.tableWidget->item(row, 0)->text();
		qDebug() << str_query;
		query.exec(str_query);//ɾ�����ݿ��ж�Ӧ��
		sum_row--;
		ui.tableWidget->clearContents();//��ձ������
		query.exec("select *  from student");
		while (query.next())
		{
			ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(query.value(0).toInt(), 10)));
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
			ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(query.value(2).toInt(), 10)));
			i++;
		}
		ui.tableWidget->show();
	}
}

//��������ݱ䶯�����Զ����������ݿ���
void SQ_Mysql::ItemChanged()
{
	row = ui.tableWidget->currentIndex().row();
	col = ui.tableWidget->currentIndex().column();
	//qDebug() << row << col;
	if (row >= 0 && row <= sum_row - 1 && col >= 0 && col <= 2 && flag_show==1)
	{
		QSqlQuery query;
		QString str_query;
		switch (col)
		{
			case 0:{					  
					   str_query = "update student set id=" + ui.tableWidget->item(row, col)->text() + " where name='" + ui.tableWidget->item(row, 1)->text() + "'";
					   break; }
			case 1:{
					   str_query = "update student set name='" + ui.tableWidget->item(row, col)->text() + "' where id=" + ui.tableWidget->item(row, 0)->text();
					   break; }
			case 2:{
					   str_query = "update student set grade=" + ui.tableWidget->item(row, col)->text() + " where name='" + ui.tableWidget->item(row, 1)->text() + "'";
					   break; }
			default:break;
		}
		qDebug() << str_query;
		query.exec(str_query);
		//qDebug() << ui.tableWidget->item(row, col)->text().toInt();
	}
	else
	{
		if (row >= sum_row)
		{
			if (col == 0)
				student_vec.id = ui.tableWidget->item(row, col)->text().toInt();
			if (col == 1)
				student_vec.name = ui.tableWidget->item(row, col)->text();
			if (col == 2)
			{
				student_vec.grade = ui.tableWidget->item(row, col)->text().toInt();
				QString str_query = "insert into student values (" + QString::number(student_vec.id, 10) + ",'" + student_vec.name + "'," + QString::number(student_vec.grade, 10) + ")";
				qDebug() << str_query;
				QSqlQuery query;
				query.exec(str_query);
			}
		}
	}

	//qDebug() << item->data(Qt::DisplayRole).toString();
}

//��ȡλ��
void SQ_Mysql::GetLocation()
{
	row = ui.tableWidget->currentIndex().row();
	col = ui.tableWidget->currentIndex().column();
	//qDebug() << row << col;
}
