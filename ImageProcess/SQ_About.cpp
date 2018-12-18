#include "SQ_About.h"

SQ_About::SQ_About(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("About"));
}

SQ_About::~SQ_About()
{
}

void SQ_About::on_AboutClose_clicked()
{
	this->close();
}