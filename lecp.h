#ifndef LECP_H
#define LECP_H

#include <QtWidgets/QMainWindow>
#include "ui_lecp.h"

class LECP : public QMainWindow
{
	Q_OBJECT

	
public:
	LECP(QWidget *parent = 0);
	~LECP();

private:
	Ui::LECPClass ui;
};

#endif // LECP_H
