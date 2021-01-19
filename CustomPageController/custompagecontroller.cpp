#include "custompagecontroller.h"
#include "ui_custompagecontroller.h"
#include <QListView>

CustomPageController::CustomPageController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomPageController)
{
    ui->setupUi(this);
    InitUI();
    ConnectEvents();
    SetStyleSheet();
}

CustomPageController::~CustomPageController()
{
    delete ui;
}

void CustomPageController::SetNumberOfPage(QStringList numberList)
{
    ui->comboBox->clear();
    ui->comboBox->addItems(numberList);
    ui->comboBox->setCurrentText(numberList.at(0));
}

void CustomPageController::SetTotalNumber(int totalNum)
{
    m_totalNum = totalNum;
    int number = ui->comboBox->currentText().toInt();
    m_totalPage = m_totalNum / number;
	if (m_totalNum % number > 0)
	{
		m_totalPage += 1;
	}

	if (m_totalPage < 1)
	{
		m_totalPage = 1;
	}

	ui->lineEdit->setText("1");
    ui->label_total->setText(QStringLiteral("/%1页").arg(m_totalPage));
}

int CustomPageController::GetCurrentNumber()
{
    return ui->comboBox->currentText().toInt();
}

void CustomPageController::InitUI()
{
    QStringList numberList;
    numberList << "25" << "50" << "100";
    ui->comboBox->addItems(numberList);
    ui->lineEdit->setText("1");

    m_totalNum = 0;
    m_totalPage = 1;
}

void CustomPageController::ConnectEvents()
{
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCurrentNumberChanged(int)));
    connect(ui->Btn_home,SIGNAL(clicked(bool)),this,SLOT(slotBtnHomePageClicked()));
    connect(ui->Btn_last,SIGNAL(clicked(bool)),this,SLOT(slotBtnLastPageClicked()));
    connect(ui->Btn_previous,SIGNAL(clicked(bool)),this,SLOT(slotBtnPrevPageClicked()));
    connect(ui->Btn_next,SIGNAL(clicked(bool)),this,SLOT(slotBtnNextPageClicked()));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(slotCurrentPageChanged()));
}

void CustomPageController::SetStyleSheet()
{
    ui->comboBox->setView(new QListView());
    ui->comboBox->setStyleSheet("QComboBox QAbstractItemView::item { min-height:32px; }");
}

void CustomPageController::slotCurrentNumberChanged(int index)
{
    int number = ui->comboBox->currentText().toInt();
    if(number == 0)
    {
        return;
    }
    m_totalPage = m_totalNum / number;

	if (m_totalNum % number > 0)
	{
		m_totalPage += 1;
	}

	if (m_totalPage < 1)
	{
		m_totalPage = 1;
	}
    ui->label_total->setText(tr("/%1 page").arg(m_totalPage));
    ui->lineEdit->setText("1");
    emit sigPageChanged(1);
}

void CustomPageController::slotCurrentPageChanged()
{
    int currentPage = ui->lineEdit->text().toInt();
    if (currentPage < 1)
    {
        currentPage = 1;
    }

    if(currentPage > m_totalPage)
    {
        currentPage = m_totalPage;
    }

    emit sigPageChanged(currentPage);
}

void CustomPageController::slotBtnHomePageClicked()
{
    ui->lineEdit->setText("1");
    emit sigPageChanged(1);
}

void CustomPageController::slotBtnLastPageClicked()
{
    ui->lineEdit->setText(QString::number(m_totalPage));
    emit sigPageChanged(m_totalPage);
}

void CustomPageController::slotBtnPrevPageClicked()
{
    int currentPage = ui->lineEdit->text().toInt() - 1;
    if (currentPage < 1)
    {
        currentPage = 1;
    }

    ui->lineEdit->setText(QString::number(currentPage));
    emit sigPageChanged(currentPage);
}

void CustomPageController::slotBtnNextPageClicked()
{
    int currentPage = ui->lineEdit->text().toInt() + 1;
    if (currentPage > m_totalPage)
    {
        currentPage = m_totalPage;
    }

    ui->lineEdit->setText(QString::number(currentPage));
    emit sigPageChanged(currentPage);
}
