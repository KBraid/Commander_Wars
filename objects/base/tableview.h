#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QObject>
#include <QVector>
#include <QStringList>

#include "3rd_party/oxygine-framework/oxygine/actor/ColorRectSprite.h"
#include "objects/base/label.h"

class TableView;
using spTableView = oxygine::intrusive_ptr<TableView>;

class TableView final : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit TableView(const QVector<qint32> & widths, const QVector<QStringList> & data, const QVector<QStringList> & tooltips, const QStringList & header, bool selectable = false);
    ~TableView() = default;
    const QStringList & getItem(qint32 i) const;
signals:
    void sigItemClicked();
public slots:
    void setCurrentItem(qint32 i);
    qint32 getCurrentItem() const;
private:
    void addRow(qint32 i, qint32 i2, qint32 x, bool selectable, const QVector<QStringList> & tooltips);
private:
    QStringList m_Header;
    QVector<QStringList> m_data;
    QVector<oxygine::spColorRectSprite> m_VLines;
    QVector<oxygine::spColorRectSprite> m_HLines;
    QVector<spLabel> m_Labels;
    QVector<qint32> m_widths;
    qint32 m_currentItem{-1};
};

Q_DECLARE_INTERFACE(TableView, "TableView");

#endif // TABLEVIEW_H
