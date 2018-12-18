#ifndef SQ_ABOUT_H
#define SQ_ABOUT_H

#include <QWidget>
#include "ui_SQ_About.h"
#include <qDebug.h>

class SQ_About : public QWidget
{
	Q_OBJECT

public:
	SQ_About(QWidget *parent = Q_NULLPTR);
	~SQ_About();

private:
	Ui::SQ_About ui;

private slots:
	void on_AboutClose_clicked();

}; 
#endif
