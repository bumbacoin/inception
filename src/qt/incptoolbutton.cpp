#include "incptoolbutton.h"

#include "QStylePainter"
#include "QStyleOptionToolButton"

IncpToolButton::IncpToolButton(QWidget *parent) :
    QToolButton(parent)
{
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    connect(this, SIGNAL(hoverIn()), this, SLOT(slotHoverIn()));
    connect(this, SIGNAL(hoverOut()), this, SLOT(slotHoverOut()));
    connect(this, SIGNAL(toggled(bool)), this, SLOT(slotToggled(bool)));
}

void IncpToolButton::setIcons(QIcon iconNormal, QIcon iconHover, QIcon iconChecked)
{
    icons[Normal] = iconNormal;
    icons[Hover] = iconHover;
    icons[Checked] = iconChecked;

    if (isChecked())
        this->setIcon(icons[Checked]);
    else
        this->setIcon(icons[Normal]);
}

void IncpToolButton::slotHoverIn()
{
    if (isChecked() && isChecked())
        this->setIcon(icons[Checked]);
    else
        this->setIcon(icons[Hover]);
}

void IncpToolButton::slotHoverOut()
{
    if (isChecked())
        this->setIcon(icons[Checked]);
    else
        this->setIcon(icons[Normal]);
}

void IncpToolButton::slotToggled(bool checked)
{
    if (checked)
        this->setIcon(icons[Checked]);
    else
        this->setIcon(icons[Normal]);
}

void IncpToolButton::enterEvent(QEvent *event)
{
    emit hoverIn();
}

void IncpToolButton::leaveEvent(QEvent *event)
{
    emit hoverOut();
}
