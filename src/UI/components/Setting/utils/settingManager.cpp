//
// Created by DevAccount on 21/10/2025.
//

#include <UI/components/Setting/utils/settingManager.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>


SettingsManager& SettingsManager::Instance()
{
    static SettingsManager instance;
    return instance;
}

SettingsManager::SettingsManager() : m_autoSaveEnabled(true)
{
    m_settingsFilePath = getDefaultSettingsPath();

    // Setting up auto-save timer for 5 seconds
    m_autoSaveTimer = new QTimer(this);
    connect(m_autoSaveTimer, &QTimer::timeout, this, &SettingsManager::onAutoSaveTimeout);
    m_autoSaveTimer->setInterval(5000);
}

SettingsManager::~SettingsManager()
{
    // Save any pending cached changes
    if (!m_cachedSettings.isEmpty()) {
        commitCachedSettings();
        saveSettings();
    }
}

QString SettingsManager::getDefaultSettingsPath() const
{
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataPath);
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
    return dir.filePath("settings.json");
}

bool SettingsManager::loadSettings(const QString& filePath)
{
    QString path = filePath.isEmpty() ? m_settingsFilePath : filePath;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open settings file:" << path;
        return false;
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError)
    {
        qWarning() << "Failed to parse settings file:" << error.errorString();
        return false;
    }

    m_settings = doc.object().toVariantMap();
    emit settingLoaded();
    return true;
}


bool SettingsManager::saveSettings(const QString& filePath)
{
    QString path = filePath.isEmpty() ? m_settingsFilePath : filePath;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open settings file for writing:" << path;
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromVariant(m_settings);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    emit settingSaved();
    return true;
}


QVariantMap SettingsManager::getAllSettings() const
{
    return m_settings;
}

QVariant SettingsManager::getSetting(const QString& key, const QVariant& defaultValue) const
{
    return m_settings.value(key, defaultValue);
}

void SettingsManager::setSetting(const QString& key, const QVariant& value)
{
    m_settings[key] = value;
    emit settingsChanged();
}

QVariantMap SettingsManager::getTabSettings(const QString& tabId) const
{
    return m_settings.value(tabId).toMap();
}

void SettingsManager::setTabSettings(const QString& tabId, const QVariantMap& settings)
{
    m_settings[tabId] = settings;
    emit settingsChanged();
}

void SettingsManager::cancelCachedSettings()
{
    m_cachedSettings.clear();
}

bool SettingsManager::hasPendingChanges() const
{
    return !m_cachedSettings.isEmpty();
}


void SettingsManager::cacheTabSettings(const QString& tabId, const QVariantMap& settings)
{
    m_cachedSettings[tabId] = settings;
    emit tabSettingsCached(tabId);

    // Start auto-save timer if enabled
    if (m_autoSaveEnabled && !m_autoSaveTimer->isActive()) {
        m_autoSaveTimer->start();
    }
}

QVariantMap SettingsManager::getCachedTabSettings(const QString& tabId) const
{
    if (m_cachedSettings.contains(tabId)) {
        return m_cachedSettings.value(tabId).toMap();
    }
    return getTabSettings(tabId);
}

bool SettingsManager::hasCachedChanges(const QString& tabId) const
{
    return m_cachedSettings.contains(tabId);
}
void SettingsManager::commitCachedSettings()
{
    for (auto it = m_cachedSettings.begin(); it != m_cachedSettings.end(); ++it) {
        m_settings[it.key()] = it.value();
    }
    m_cachedSettings.clear();
    emit settingsChanged();
}

void SettingsManager::discardCachedSettings(const QString& tabId)
{
    m_cachedSettings.remove(tabId);
}

void SettingsManager::setAutoSaveEnabled(bool enabled)
{
    m_autoSaveEnabled = enabled;
    if (!enabled) {
        m_autoSaveTimer->stop();
    }
}
bool SettingsManager::isAutoSaveEnabled() const
{
    return m_autoSaveEnabled;
}

void SettingsManager::setAutoSaveInterval(int milliseconds)
{
    m_autoSaveTimer->setInterval(milliseconds);
}

QString SettingsManager::getSettingsFilePath() const
{
    return m_settingsFilePath;
}

void SettingsManager::setSettingsFilePath(const QString& filePath)
{
    m_settingsFilePath = filePath;
}

void SettingsManager::onAutoSaveTimeout()
{
    if (!m_cachedSettings.isEmpty()) {
        commitCachedSettings();
        saveSettings();
    }
    m_autoSaveTimer->stop();
}

void SettingsManager::loadDefaultSettings()
{
    // Define your application defaults here
    QVariantMap defaults;

    // Simulation defaults
    QVariantMap simulationDefaults;
    simulationDefaults["tickRate"] = 60;
    simulationDefaults["timeScale"] = 1.0;
    defaults["simulation"] = simulationDefaults;

    // Physics defaults
    QVariantMap physicsDefaults;
    physicsDefaults["gravity"] = 9.81;
    physicsDefaults["enabled"] = true;
    defaults["physics"] = physicsDefaults;

    // Store as default settings
    m_settings["_defaults"] = defaults;
}

QVariantMap SettingsManager::getDefaultSettings(const QString& tabId) const
{
    QVariantMap defaults = m_settings.value("_defaults").toMap();
    return defaults.value(tabId).toMap();
}

void SettingsManager::setDefaultSettings(const QString& tabId, const QVariantMap& settings)
{
    QVariantMap defaults = m_settings.value("_defaults").toMap();
    defaults[tabId] = settings;
    m_settings["_defaults"] = defaults;
}

void SettingsManager::applyCachedSettings()
{
    commitCachedSettings();
    saveSettings();
}


void SettingsManager::resetDefaultSettings(const QString& tabId)
{
    QVariantMap defaults = getDefaultSettings(tabId);
    if (!defaults.isEmpty()) {
        cacheTabSettings(tabId, defaults);
    }
}

void SettingsManager::resetAllToDefaultSettings()
{
    QVariantMap defaults = m_settings.value("_defaults").toMap();
    m_cachedSettings.clear();

    for (auto it = defaults.begin(); it != defaults.end(); ++it) {
        m_cachedSettings[it.key()] = it.value();
    }

    emit settingsChanged();
}


