#ifndef SQ_NYSQL_H
#define SQ_MYSQL_H

#include <QWidget>
#include "ui_SQ_Mysql.h"
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QDebug>  
#include <QMessageBox>
#include "ui_ImageProcess.h"
#include <QContextMenuEvent>
#include <QCloseEvent>
struct studentinfo
{
	int id;
	QString name;
	int grade;
};
class SQ_Mysql : public QWidget
{
	Q_OBJECT

public:
	SQ_Mysql(QWidget *parent = Q_NULLPTR);
	~SQ_Mysql();

	Ui::ImageProcessClass* main_ui;//主界面UI

	bool Connect();//连接数据库
	bool InsertData();//添加数据
	bool DeleteData();//删除数据
	bool UpdateData();//修改数据
	bool QueryData();//查询数据
	bool CreateTable();//新建表

	void closeEvent(QCloseEvent *event);//关闭窗口之间动作
private:
	Ui::SQ_Mysql ui;

	void contextMenuEvent(QContextMenuEvent *event);//鼠标右键显示菜单--右击删除整行数据
	int row = -1;//记录选中的行
	int col = -1;//记录选中的列
	int sum_row = 0;//记录数据库中总行数
	int flag_show = 0;
	studentinfo student_vec;
	QSqlDatabase db;

private slots:
	void on_QueryData_clicked();//显示数据库中的数据
	void DeleteRows();//删除某行数据并更新数据库和表格
	void ItemChanged();//表格中数据变动
	void GetLocation();//获取位置

};
#endif
//多行读取  显示
//str1 = textEdit->toPlainText();
//ui->textEdit->insertPlainText(str1);

//单行读取  显示
//str1 = ui->lineEdit->text();
//ui->lineEdit->setText(str1);