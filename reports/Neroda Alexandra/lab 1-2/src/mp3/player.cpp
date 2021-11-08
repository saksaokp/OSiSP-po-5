#include "player.h"
#include "ui_player.h"

Player::Player(QWidget *parent) : QMainWindow(parent), ui(new Ui::Player) {
    ui->setupUi(this);

    ui->just_plauingTrack->setVisible(false);

    playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(playListModel);

    playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track")<< tr("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection); // Разрешаем выделять только одну строку
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Отключаем редактирование

    ui->playlistView->horizontalHeader()->setStretchLastSection(true); // по ширине строки

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);


    connect(playlist, &QMediaPlaylist::currentIndexChanged, [this](int index) {
        ui->just_plauingTrack->setText(playListModel->data(playListModel->index(index, 0)).toString());
    });
}

Player::~Player() {
    delete ui;
    delete playListModel;
    delete playlist;
    delete player;
}

void Player::on_btn_add_clicked() {

    QStringList new_files = QFileDialog::getOpenFileNames(this, tr("Open files"), QString(), tr("Audio Files (*.mp3)"));

    if(!new_files.isEmpty()) {
        QStringList write_to_globallist;

        if(count_tracks_num != 0) {
            for(int i = 0; i < new_files.size(); i++) {
                bool flag = false;
                for(int j = 0; j < files_list.size(); j++) {
                    if(new_files[i] == files_list[j]) {
                         flag = true;
                    }
                }
                if(!flag) {
                    write_to_globallist.append(new_files[i]);
                }
            }
             add_playlist(write_to_globallist);
        }

        else add_playlist(new_files);
    }
}

void Player::add_playlist(QStringList list) {
    // устанавливаем данные по именам и пути к файлам
    // в плейлист и таблицу отображающую плейлист
    foreach (QString filePath, list) {
        files_list.append(list);
        count_tracks_num++;
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        playListModel->appendRow(items);
        playlist->addMedia(QUrl(filePath));
    }
    ui->count_tracks->setText(QString::number(count_tracks_num));
}

void Player::on_btn_play_clicked() {
    player->play();
    ui->just_plauingTrack->setVisible(true);
}

void Player::on_btn_previous_clicked() {
    playlist->previous();
}

void Player::on_btn_pause_clicked() {
    player->pause();
}

void Player::on_btn_stop_clicked() {
    player->stop();
    ui->just_plauingTrack->setVisible(false);
}

void Player::on_btn_next_clicked() {
    playlist->next();
}

void Player::on_playlistView_doubleClicked(const QModelIndex &index) {
    playlist->setCurrentIndex(index.row());
    on_btn_play_clicked();
}
