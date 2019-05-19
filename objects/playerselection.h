#ifndef PLAYERSELECTION_H
#define PLAYERSELECTION_H

#include <QObject>

#include "oxygine-framework.h"

#include "objects/panel.h"

#include "objects/spinbox.h"

#include "objects/dropdownmenu.h"
#include "objects/dropdownmenucolor.h"

#include "network/NetworkInterface.h"

#include "gameinput/basegameinputif.h"

class PlayerSelection;
typedef oxygine::intrusive_ptr<PlayerSelection> spPlayerSelection;

class PlayerSelection : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit PlayerSelection(qint32 width, qint32 heigth);
    virtual ~PlayerSelection() = default;

    void showPlayerSelection();
    void resetPlayerSelection();
    void attachNetworkInterface(spNetworkInterface pNetworkInterface);
    bool isOpenPlayer(qint32 player);
    bool hasOpenPlayer();
    QString getPlayerAiName(qint32 player);
    void setPlayerAiName(qint32 player, QString name);
    BaseGameInputIF::AiTypes getPlayerAiType(qint32 player);
    /**
     * @brief sendPlayerRequest sends a request to play as a human player
     * @param socketID
     * @param player -1 for any player
     */
    void sendPlayerRequest(quint64 socketID, qint32 player);
    void playerDataChanged();
    void updateCOData(qint32 playerIdx);
signals:
    void buttonAllCOsRandom();
    void sigShowSelectCO(qint32 player, quint8 co);
    void buttonShowAllBuildList();
    void buttonShowPlayerBuildList(qint32 player);
    void sigAiChanged(qint32 player);
public slots:
    // slots for changing player data
    void allPlayerIncomeChanged(float value);
    void playerIncomeChanged(float value, qint32 playerIdx);
    void allPlayerStartFondsChanged(float value);
    void playerStartFondsChanged(float value, qint32 playerIdx);
    void playerTeamChanged(qint32 value, qint32 playerIdx);
    void playerColorChanged(QColor value, qint32 playerIdx);
    void showSelectCO(qint32 player, quint8 co);
    void playerCO1Changed(QString coid, qint32 playerIdx);
    void updateCO1Sprite(QString coid, qint32 playerIdx);
    void playerCO2Changed(QString coid, qint32 playerIdx);
    void updateCO2Sprite(QString coid, qint32 playerIdx);
    void playerCOCanceled();
    void slotAllCOsRandom();
    void slotShowAllBuildList();
    void slotShowPlayerBuildList(qint32 player);
    void slotChangeAllBuildList(qint32, QStringList buildList);
    void slotChangePlayerBuildList(qint32 player, QStringList buildList);
    void selectAI(qint32 player);

    // network stuff
    void recieveData(quint64 socketID, QByteArray data, NetworkInterface::NetworkSerives service);
    void disconnected(quint64 socketID);
    /**
     * @brief updatePlayerData updates the visual player data when data has been changed via network
     * @param player the player that has changed
     */
    void updatePlayerData(qint32 player);
protected:
    /**
     * @brief requestPlayer a client requested to get control of a player. We check the request and execute it if it's valid
     * @param socketID
     * @param stream
     */
    void requestPlayer(quint64 socketID, QDataStream& stream);
    /**
     * @brief changePlayer changes the player data on client sites
     * @param socketID
     * @param stream
     */
    void changePlayer(quint64 socketID, QDataStream& stream);
    /**
     * @brief recievedPlayerData
     * @param socketID
     * @param stream
     */
    void recievedPlayerData(quint64 socketID, QDataStream& stream);
    /**
     * @brief PlayerSelection::recievedCOData
     * @param stream
     */
    void recievedCOData(quint64, QDataStream& stream);
private:
    // player selection
    spPanel m_pPlayerSelection;

    QVector<oxygine::spSprite> m_playerCO1;
    QVector<oxygine::spSprite> m_playerCO2;
    QVector<spDropDownmenuColor> m_playerColors;
    QVector<spSpinBox> m_playerIncomes;
    QVector<spSpinBox> m_playerStartFonds;
    QVector<spDropDownmenu> m_playerAIs;
    /**
     * @brief m_PlayerSockets holds which socket owns which player
     * For clients and local games this always contains 0
     * For the host this contains 0 for owned by the server or the socket id for client owned
     */
    QVector<quint64> m_PlayerSockets;
    QVector<spDropDownmenu> m_playerTeams;
    QVector<oxygine::spButton> m_playerBuildlist;

    spNetworkInterface m_pNetworkInterface{nullptr};
};

#endif // PLAYERSELECTION_H
