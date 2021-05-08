#ifndef BASEMENU_H
#define BASEMENU_H

#include <QObject>
#include "3rd_party/oxygine-framework/oxygine-framework.h"

class Basemenu;
using spBasemenu = oxygine::intrusive_ptr<Basemenu>;

class Basemenu : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit Basemenu();

signals:
    void sigOnUpdate();
public slots:
    bool getFocused() const;
    virtual void setFocused(bool Focused);
protected:
    bool m_Focused{true};
};

#endif // BASEMENU_H
