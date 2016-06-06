#ifndef INCPTOOLBUTTON_H
#define INCPTOOLBUTTON_H

#include <QToolButton>
#include <QIcon>

class IncpToolButton : public QToolButton
{
    Q_OBJECT
public:
    enum Mode { Normal, Hover, Checked };

    explicit IncpToolButton(QWidget *parent = 0);

    void setIcons(QIcon iconNormal, QIcon iconHover, QIcon iconChecked);

    ~IncpToolButton(){}

signals:
    void hoverIn();
    void hoverOut();

public slots:
    void slotHoverIn();
    void slotHoverOut();
    void slotToggled(bool checked);

protected:
    QIcon icons[3];

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // INCPTOOLBUTTON_H
