#include "SQ_Mysql.h"


SQ_Mysql::SQ_Mysql(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//点击表格
	connect(ui.tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(GetLocation()));

	//修改表格中某行的数据
	connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(ItemChanged()));
}

SQ_Mysql::~SQ_Mysql()
{
	
}

//关闭窗口之间动作
void SQ_Mysql::closeEvent(QCloseEvent *event)
{
	db.close();//关闭数据库 
	ui.tableWidget->setRowCount(20);//设置表格的行数
	ui.tableWidget->setColumnCount(3);//设置表格的列数
	ui.tableWidget->clear();//清空表格所有内容
}


//连接数据库
//mysql -u root -p 123456
bool SQ_Mysql::Connect()
{
	bool state;
	//addDatabase（）来创建一个连接，调用这个函数时，我们可以传递我们要访问哪种类型的数据库
	db = QSqlDatabase::addDatabase("QMYSQL");     //驱动 

	db.setHostName("localhost");			//数据库地址，一般都是本地，就填localhost就可以 
	db.setDatabaseName("sq_test");			//数据库名，根据你Mysql里面的数据库名称来填写，比如我Mysql里面有个数据库叫test，可以用Navicat软件看自己的数据库名字
	db.setUserName("root");					//用户名，一般是本地用户，就填root就可以
	db.setPassword("123456");				//密码，填写你自己的Mysql登陆密码，为了保密我这里用*代替我的密码
	db.setPort(3306);						//端口默认的是3306，可以不用写 

	if (db.open())
	{
		//QMessageBox::warning(NULL, QStringLiteral("提示"), "open ok", QMessageBox::Yes);
		main_ui->Message->setText(QString::fromLocal8Bit("数据库打开成功！"));
		state = true;
	}
	else
	{
		//QMessageBox::warning(NULL, QStringLiteral("提示"), "open failed", QMessageBox::Yes);
		main_ui->Message->setText(QString::fromLocal8Bit("数据库打开失败！"));
		state = false;
	}
	//db.close();//关闭数据库 
	return state;
}

//新建表
bool SQ_Mysql::CreateTable()
{
	QSqlQuery query;
	bool state;
	state = query.exec("create table if not exists teacher (id int,name varchar(20))");

	if (state)
	{
		main_ui->Message->setText(QString::fromLocal8Bit("创建表成功！"));
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("创建表失败！"));
	}
	return state;
}

//添加数据
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
		main_ui->Message->setText(QString::fromLocal8Bit("数据添加成功！"));
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("数据添加失败！"));
	}
	return state;
}

//删除数据
bool SQ_Mysql::DeleteData()
{
	QSqlQuery query;
	bool state;
	state = query.exec("delete from student where id = 11");
	if (state)
	{
		main_ui->Message->setText(QString::fromLocal8Bit("数据删除成功！"));
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("数据删除失败！"));
	}
	return state;
}

//修改数据
bool SQ_Mysql::UpdateData()
{
	QSqlQuery query;
	bool state;
	state = query.exec("update student set id = 88 where name = 'zc' ");
	if (state)
	{
		main_ui->Message->setText(QString::fromLocal8Bit("数据修改成功！"));
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("数据修改失败！"));
	}
	return state;
}

//查询数据
bool SQ_Mysql::QueryData()
{
	QSqlQuery query;
	bool state;
	state = query.exec("select *  from student");
	if (state)
	{
		while (query.next())
		{
			main_ui->Message->setText(QString::fromLocal8Bit("数据查询成功！"));
			qDebug() << query.value(0).toInt() << query.value(1).toString();
		}
	}
	else
	{
		main_ui->Message->setText(QString::fromLocal8Bit("数据查询失败！"));
	}
	return state;
}

//显示数据
void SQ_Mysql::on_QueryData_clicked()
{
	flag_show = 0;
	int i = 0;
	sum_row = 0;
	ui.tableWidget->setRowCount(20);//设置表格的行数
	ui.tableWidget->setColumnCount(3);//设置表格的列数
	ui.tableWidget->clear();//清空表格所有内容
	ui.tableWidget->setWindowTitle("QTableWidget");
	//ui.tableWidget->resize(400, 300);  //设置表格大小
	QStringList header;
	header << "ID" << "Name" << "Grade";   
	ui.tableWidget->setHorizontalHeaderLabels(header);//表头
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

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


//右击删除整行数据
void SQ_Mysql::contextMenuEvent(QContextMenuEvent *event)
{
	row = ui.tableWidget->currentIndex().row();
	col = ui.tableWidget->currentIndex().column();
	//qDebug() << row << col;

	QMenu *menu = new QMenu();
	QAction *deleterows = new QAction(QString::fromLocal8Bit("删除"));
	menu->addAction(deleterows);	
	connect(deleterows, SIGNAL(triggered(bool)), this, SLOT(DeleteRows()));
	menu->exec(QCursor::pos());
}

//删除某行数据
void SQ_Mysql::DeleteRows()
{
	int i = 0;
	if (row >= 0 && row <= sum_row-1)
	{
		QSqlQuery query;
		QString str_query = "delete from student where id = " + ui.tableWidget->item(row, 0)->text();
		qDebug() << str_query;
		query.exec(str_query);//删除数据库中对应行
		sum_row--;
		ui.tableWidget->clearContents();//清空表格数据
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

//表格中数据变动，会自动更新至数据库中
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

//获取位置
void SQ_Mysql::GetLocation()
{
	row = ui.tableWidget->currentIndex().row();
	col = ui.tableWidget->currentIndex().column();
	//qDebug() << row << col;
}
