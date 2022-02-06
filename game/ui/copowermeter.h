#ifndef COPOWERMETER_H
#define COPOWERMETER_H

#include <QObject>

#include "3rd_party/oxygine-framework/oxygine-framework.h"

#include "game/co.h"

class CoPowermeter;
typedef oxygine::intrusive_ptr<CoPowermeter> spCoPowermeter;

class CoPowermeter : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit CoPowermeter(GameMap* pMap, CO* pCO);
    virtual ~CoPowermeter() = default;
    /**
     * @brief drawPowerMeter
     */
    void drawPowerMeter();
    /**
     * @brief getCO
     * @return
     */
    CO *getCO() const;
    /**
     * @brief setCO
     * @param pCO
     */
    void setCO(CO *pCO);
    /**
     * @brief setFlippedX
     * @param value
     */
    void setFlippedX(bool value);
    /**
     * @brief getFlippedX
     * @return
     */
    bool getFlippedX() const;
    GameMap *getMap() const;
    void setMap(GameMap *newPMap);

signals:

private:
    CO* m_pCO;
    bool m_flippedX{false};
    GameMap* m_pMap{nullptr};
};

#endif // COPOWERMETER_H
