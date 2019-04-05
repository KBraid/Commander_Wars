#include <QFileInfo>

#include <QDirIterator>

#include "weaponmanager.h"

#include "coreengine/mainapp.h"

WeaponManager* WeaponManager::m_pInstance = nullptr;

WeaponManager::WeaponManager()
{

}

WeaponManager* WeaponManager::getInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new WeaponManager();
    }
    return m_pInstance;
}

QString WeaponManager::getWeaponName(QString weaponID)
{
    Mainapp* pApp = Mainapp::getInstance();
    QString function1 = "getName";
    QJSValue ret = pApp->getInterpreter()->doFunction(weaponID, function1);
    if (ret.isString())
    {
        return ret.toString();
    }
    else
    {
        return "";
    }
}

void WeaponManager::reset()
{
    Mainapp* pMainapp = Mainapp::getInstance();
    for (qint32 i = 0; i < m_loadedWeapons.size(); i++)
    {
        pMainapp->getInterpreter()->deleteObject(m_loadedWeapons[i]);
    }
    m_loadedWeapons.clear();
}

void WeaponManager::loadAll()
{
    reset();
    Mainapp* pMainapp = Mainapp::getInstance();
    QStringList searchPaths;
    searchPaths.append("resources/scripts/weapons");
    // make sure to overwrite existing js stuff
    for (qint32 i = 0; i < pMainapp->getSettings()->getMods().size(); i++)
    {
        searchPaths.append(pMainapp->getSettings()->getMods().at(i) + "/scripts/weapons");
    }
    for (qint32 i = 0; i < searchPaths.size(); i++)
    {
        QString path =  QCoreApplication::applicationDirPath() + "/" + searchPaths[i];
        QStringList filter;
        filter << "*.js";
        QDirIterator* dirIter = new QDirIterator(path, filter, QDir::Files, QDirIterator::Subdirectories);
        while (dirIter->hasNext())
        {
            dirIter->next();
            QString file = dirIter->fileInfo().fileName().split(".").at(0);
            loadWeapon(file.toUpper());
        }
    }
}

bool WeaponManager::loadWeapon(const QString& weaponID)
{
    Mainapp* pMainapp = Mainapp::getInstance();

    QStringList searchPaths;
    for (qint32 i = 0; i < pMainapp->getSettings()->getMods().size(); i++)
    {
        searchPaths.append(pMainapp->getSettings()->getMods().at(i) + "/scripts/weapons");
    }
    searchPaths.append("resources/scripts/weapons");
    for (qint32 i = 0; i < searchPaths.size(); i++)
    {
        QString file = searchPaths[i] + "/" + weaponID + ".js";
        QFileInfo checkFile(file);
        if (checkFile.exists() && checkFile.isFile())
        {
            pMainapp->getInterpreter()->openScript(file);
            m_loadedWeapons.append(weaponID);
            return true;
        }
    }
    return false;
}
