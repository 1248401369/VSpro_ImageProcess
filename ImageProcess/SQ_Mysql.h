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

	Ui::ImageProcessClass* main_ui;//������UI

	bool Connect();//�������ݿ�
	bool InsertData();//�������
	bool DeleteData();//ɾ������
	bool UpdateData();//�޸�����
	bool QueryData();//��ѯ����
	bool CreateTable();//�½���

	void closeEvent(QCloseEvent *event);//�رմ���֮�䶯��
private:
	Ui::SQ_Mysql ui;

	void contextMenuEvent(QContextMenuEvent *event);//����Ҽ���ʾ�˵�--�һ�ɾ����������
	int row = -1;//��¼ѡ�е���
	int col = -1;//��¼ѡ�е���
	int sum_row = 0;//��¼���ݿ���������
	int flag_show = 0;
	studentinfo student_vec;
	QSqlDatabase db;

private slots:
	void on_QueryData_clicked();//��ʾ���ݿ��е�����
	void DeleteRows();//ɾ��ĳ�����ݲ��������ݿ�ͱ��
	void ItemChanged();//��������ݱ䶯
	void GetLocation();//��ȡλ��

};
#endif
//���ж�ȡ  ��ʾ
//str1 = textEdit->toPlainText();
//ui->textEdit->insertPlainText(str1);

//���ж�ȡ  ��ʾ
//str1 = ui->lineEdit->text();
//ui->lineEdit->setText(str1);