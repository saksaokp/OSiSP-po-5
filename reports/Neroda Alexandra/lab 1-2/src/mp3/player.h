#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Player; }
QT_END_NAMESPACE

class Player : public QMainWindow {
    Q_OBJECT

public:
    Player(QWidget *parent = nullptr);
    ~Player();

private slots:
    void add_playlist(QStringList list);
    void on_btn_add_clicked();
    void on_btn_play_clicked();
    void on_btn_previous_clicked();
    void on_btn_pause_clicked();
    void on_btn_stop_clicked();
    void on_btn_next_clicked();
    void on_playlistView_doubleClicked(const QModelIndex &index);

private:
    Ui::Player *ui;
    QStringList files_list;
    int count_tracks_num = 0;
    QStandardItemModel *playListModel;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
};
#endif // PLAYER_H
