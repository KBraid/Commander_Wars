#ifndef PROXYAI_H
#define PROXYAI_H

#include <QObject>
#include <QList>
#include <QMutex>

#include "game/gameaction.h"
#include "ai/coreai.h"

#include "network/NetworkInterface.h"

class ProxyAi;
using spProxyAi = oxygine::intrusive_ptr<ProxyAi>;

class ProxyAi final : public CoreAI
{
    Q_OBJECT
public:
    explicit ProxyAi(GameMap* pMap);
    ~ProxyAi() = default;
    /**
     * @brief serialize stores the object
     * @param pStream
     */
    virtual void serializeObject(QDataStream& pStream) const override;
    /**
     * @brief deserialize restores the object
     * @param pStream
     */
    virtual void deserializeObject(QDataStream& pStream) override;
    /**
     * @brief getVersion version of the file
     * @return
     */
    virtual qint32 getVersion() const override
    {
        return 4;
    }
    /**
     * @brief process empty impl
     */
    virtual void process() override {}
    /**
     * @brief setInterface
     * @param pNetworkInterface
     */
    void connectInterface(NetworkInterface* pNetworkInterface);
    void disconnectInterface();
    /**
     * @brief init
     */
    virtual void init(GameMenue* pMenu) override;
public slots:
    virtual void nextAction() override;
    void recieveData(quint64 socket, QByteArray data, NetworkInterface::NetworkSerives service);
    /**
     * @brief readIni
     * @param name
     */
    virtual void readIni(QString name) override;
    /**
     * @brief verifyActionStack
     */
    bool verifyActionStack();
private:
    void onInvalidStack();
    void doNextAction();
private:
    QList<spGameAction> m_ActionBuffer;
    QMutex m_ActionMutex;
};

#endif // PROXYAI_H
