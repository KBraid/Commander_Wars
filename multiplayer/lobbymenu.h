#ifndef LOBBYMENU_H
#define LOBBYMENU_H

#include <QObject>

#include "3rd_party/oxygine-framework/oxygine/actor/Button.h"

#include "objects/tableView/complextableview.h"

#include "network/networkgamedata.h"
#include "network/NetworkInterface.h"

#include "multiplayer/networkcommands.h"
#include "multiplayer/password.h"

#include "menue/basemenu.h"

class LobbyMenu;
using spLobbyMenu = oxygine::intrusive_ptr<LobbyMenu>;

class LobbyMenu final : public Basemenu
{
    Q_OBJECT
    static constexpr qint32 REQUEST_COUNT = 50;
public:
    enum class GameViewMode
    {
        OpenGames,
        OwnGames,
        ObserveGames,
    };

    explicit LobbyMenu();
    ~LobbyMenu() = default;
signals:
    void sigExitMenue();
    void sigHostServer();
    void sigHostLocal();
    void sigJoinGame();
    void sigJoinAdress();
    void sigObserveGame();
    void sigObserveAdress();
    void sigUpdateGamesView();
    void sigRequestUpdateGames();
    void sigServerResponded();
    void sigOther();

    void sigShowNextStep();
    void sigShowPreviousStep();
    void sigShowStart();
    void sigShowEnd();

public slots:
    bool getServerRequestNewPassword() const;
    void setServerRequestNewPassword(bool newServerRequestNewPassword);
    void exitMenue();    
    void hostLocal();
    void hostServer();
    void joinGame();
    void joinGamePassword(QString password);
    void join(QString adress, QString password);
    void joinAdress();
    void recieveData(quint64 socketID, QByteArray data, NetworkInterface::NetworkSerives service);
    void updateGamesView();
    void selectGame();
    void observe(QString adress, QString password);
    void observeAdress();
    void observeGame();
    void observeGamePassword(QString password);
    void connected(quint64 socket);
    void onLogin();
    bool isValidEmailAdress(const QString & emailAdress);
    bool isValidPassword(const QString & password);
    void leaveServer();
    void createServerAccount(const QString & password, const QString & emailAdress);
    void deleteServerAccount(const QString & password, const QString & emailAdress);
    void loginToServerAccount(const QString & password);
    void resetPasswordOnServerAccount(const QString & emailAdress);
    void changePasswordOnServerAccount(const QString & oldEmailAdress, const QString & newEmailAdress);
    void enableServerButtons(bool enable);
    void requestUpdateGames();
    void requestObserverUpdateGames();
    void showContactingServer();
    void cancelWaitingForServer();
    void showNextStep();
    void showPreviousStep();
    void showStart();
    void showEnd();
    void showOther();
protected slots:
    virtual void onEnter() override;
private:
    void updateGameData(const QJsonObject & objData);
    void joinSlaveGame(const QJsonObject & objData);
    void checkVersionAndShowInfo(const QJsonObject & objData);
    void onPublicKeyDeleteAccount(quint64 socketID, const QJsonObject & objData, NetworkCommands::PublicKeyActions action);
    void onPublicKeyCreateAccount(quint64 socketID, const QJsonObject & objData, NetworkCommands::PublicKeyActions action);
    void onPublicKeyLoginAccount(quint64 socketID, const QJsonObject & objData, NetworkCommands::PublicKeyActions action);
    void onPublicKeyResetAccount(quint64 socketID, const QJsonObject & objData, NetworkCommands::PublicKeyActions action);
    void onPublicKeyChangePassword(quint64 socketID, const QJsonObject & objData, NetworkCommands::PublicKeyActions action);
    void handleAccountMessage(quint64 socketID, const QJsonObject & objData);
    void requestServerGames();
    void requestUserUpdateGames();    /**
     * @brief getMinimapImage
     * @param img
     * @param data
     */
    void getMinimapImage(QImage & img, NetworkGameData & data);
    /**
     * @brief showNetworkGameData
     * @param data
     */
    void showNetworkGameData(NetworkGameData & data);
private:
    spNetworkInterface m_pTCPClient{nullptr};
    QVector<NetworkGameData> m_games;
    NetworkGameData m_currentGame;
    oxygine::spButton m_pButtonHostOnServer;
    oxygine::spButton m_pButtonGameObserve;    
    oxygine::spButton m_pButtonGameJoin;
    oxygine::spButton m_pButtonSwapOpenGamesMode;
    oxygine::spButton m_pButtonSwapOwnGamesMode;
    oxygine::spButton m_pButtonSwapObserveGamesMode;
    oxygine::spButton m_pButtonUpdateGamesMode;
    oxygine::spButton m_pEndStepButton;
    oxygine::spButton m_pNextStepButton;
    oxygine::spButton m_pPreviousStepButton;
    oxygine::spButton m_pStartStepButton;
    oxygine::spButton m_pOtherButton;
    spLabel m_matchViewInfo;
    spComplexTableView m_gamesview;
    QString m_password;
    bool m_loggedIn{false};

    Password m_serverPassword;
    Password m_oldServerPassword;
    QString m_serverEmailAdress;
    bool m_serverRequestNewPassword;
    GameViewMode m_mode{GameViewMode::OpenGames};
    qint32 m_lastSelectedItem{-1};
    qint32 m_gameIndex{0};
    qint32 m_serverCurrentMatchCount{0};
};

#endif // LOBBYMENU_H
