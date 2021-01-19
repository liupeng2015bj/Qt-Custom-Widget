#ifndef CUSTOMPAGECONTROLLER_H
#define CUSTOMPAGECONTROLLER_H

#include <QWidget>

namespace Ui {
class CustomPageController;
}

class CustomPageController : public QWidget
{
    Q_OBJECT

public:
    explicit CustomPageController(QWidget *parent = 0);
    ~CustomPageController();
    void SetNumberOfPage(QStringList numberList);
    void SetTotalNumber(int totalNum);
    int GetCurrentNumber();

private:
    void InitUI();
    void ConnectEvents();
    void SetStyleSheet();

private slots:
    void slotCurrentNumberChanged(int index);
    void slotCurrentPageChanged();
    void slotBtnHomePageClicked();
    void slotBtnLastPageClicked();
    void slotBtnPrevPageClicked();
    void slotBtnNextPageClicked();

signals:
    void sigPageChanged(int currentPage);

private:
    Ui::CustomPageController *ui;
    int m_totalNum;
    int m_totalPage;
};

#endif // CUSTOMPAGECONTROLLER_H
