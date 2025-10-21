//
// Created by DevAccount on 21/10/2025.
//

#ifndef AETHER_ENGINE_SETTINGMANAGER_H
#define AETHER_ENGINE_SETTINGMANAGER_H
#pragma once
#include <QObject>
#include <QVariantMap>
#include <QString>
#include <QTimer>

class SettingsManager : public QObject
{
    Q_OBJECT


public:
    static SettingsManager& Instance();

    bool loadSettings(const QString& filePath = QString());
    bool saveSettings(const QString& filePath = QString());

    QVariantMap getAllSettings() const;
    QVariant getSetting(const QString& key, const QVariant& defaultValue = QVariant()) const;
    void setSetting(const QString& key, const QVariant& value);

    QVariantMap getTabSettings(const QString& tabId) const;
    void setTabSettings(const QString& tabId, const QVariantMap& settings);

    //Cache management
    void cacheTabSettings(const QString& tabId, const QVariantMap& settings);
    QVariantMap getCachedTabSettings(const QString& tabId) const;
    bool hasCachedChanges(const QString& tabId) const;
    void commitCachedSettings();
    void discardCachedSettings(const QString& tabId);

    // Auto-save configuration
    void setAutoSaveEnabled(bool enabled);
    bool isAutoSaveEnabled() const;
    void setAutoSaveInterval(int milliseconds);

    QString getSettingsFilePath() const;
    void setSettingsFilePath(const QString& filePath);

    void loadDefaultSettings();
    QVariantMap getDefaultSettings(const QString& tabId) const;

    void setDefaultSettings(const QString& tabId, const QVariantMap& settings);
    void resetDefaultSettings(const QString& tabId);
    void resetAllToDefaultSettings();

    void applyCachedSettings();
    void cancelCachedSettings();
    bool hasPendingChanges() const;

signals:
    void settingsChanged();
    void settingLoaded();
    void settingSaved();
    void tabSettingsCached(const QString& tabId);

private:
    SettingsManager();
    ~SettingsManager() override;
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    QString m_settingsFilePath;
    QVariantMap m_settings;
    QVariantMap m_cachedSettings;  // Temporary cache for unsaved changes

    QTimer* m_autoSaveTimer;
    bool m_autoSaveEnabled;

    QString getDefaultSettingsPath() const;
    void onAutoSaveTimeout();
};


#endif //AETHER_ENGINE_SETTINGMANAGER_H