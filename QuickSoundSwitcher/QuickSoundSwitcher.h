#ifndef QUICKSOUNDSWITCHER_H
#define QUICKSOUNDSWITCHER_H

#include "SoundPanel.h"
#include <QMainWindow>
#include <QSystemTrayIcon>

class QuickSoundSwitcher : public QMainWindow
{
    Q_OBJECT

public:
    QuickSoundSwitcher(QWidget *parent = nullptr);
    ~QuickSoundSwitcher();
    static QuickSoundSwitcher* instance;
    void adjustOutputVolume(bool up);
    void toggleMuteWithKey();

private slots:
    void onRunAtStartupStateChanged();
    void onOutputMuteChanged();
    void onSoundPanelClosed();

private:
    QSystemTrayIcon *trayIcon;
    SoundPanel* soundPanel;
    void createTrayIcon();
    void togglePanel();
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    static HHOOK mouseHook;
    static HHOOK keyboardHook;
    void installGlobalMouseHook();
    void uninstallGlobalMouseHook();
    void installKeyboardHook();
    void uninstallKeyboardHook();
    static const int HOTKEY_ID = 1;

signals:
    void outputMuteStateChanged(int volumeIcon);
    void volumeChangedWithTray(int volume);
};

#endif // QUICKSOUNDSWITCHER_H
