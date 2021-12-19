#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QProcess>
#include <QLibrary>
#include <QPluginLoader>
#include <QTcpSocket>
#include "interface.h"
#include "interface_theme.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Player; }
QT_END_NAMESPACE

class Player : public QMainWindow {
    Q_OBJECT

public:
    Player(QWidget *parent = nullptr);
    ~Player();
    void load_mode_plugins();
    void load_interfase_plugins();


private slots:
    void add_playlist(QStringList list);
    void on_btn_add_clicked();
    void on_btn_play_clicked();
    void on_btn_previous_clicked();
    void on_btn_pause_clicked();
    void on_btn_stop_clicked();
    void on_btn_next_clicked();
    void on_playlistView_doubleClicked(const QModelIndex index);
    void on_Info_clicked();
    void on_reboot_clicked();
    void on_apply_clicked();
    void on_apply_2_clicked();
    void sockDisc();
    void sockReady();
    void on_check_update_clicked();

private:
    Ui::Player *ui;
    QList<Interface*> _mode;
    QList<Interface_theme*> _mode1;
    QStringList files_list;
    int count_tracks_num = 0;
    QStandardItemModel *playListModel;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    int Next, Back;
    bool isNext = true;
    QTcpSocket* socket;
    QByteArray Data;
};
#endif // PLAYER_H
