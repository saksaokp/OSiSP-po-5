#include "player.h"
#include "ui_player.h"
#include "about.h"
#include "helper.h"

typedef QString (*Helper_set_name_window)();
typedef QString (*Helper_set_first_name)();
typedef QString (*Helper_set_second_name)();

Player::Player(QWidget *parent) : QMainWindow(parent), ui(new Ui::Player) {
    ui->setupUi(this);

    // установка имени окна приложения
    QLibrary *helper_set = new QLibrary("Helper");
    Helper_set_name_window set_window_name_ = (Helper_set_name_window)helper_set->resolve("set_window_name");
    QString windowTitle = set_window_name_();
    delete helper_set;
    this->setWindowTitle(windowTitle);

    // установка имени первого заголовка playlistview
    QLibrary *helper_set_f_n = new QLibrary("Helper");
    Helper_set_first_name set_window_name_first = (Helper_set_first_name)helper_set_f_n->resolve("set_first_name_HeaderLabels");
    QString set_name_first = set_window_name_first();
    delete helper_set_f_n;


    // установка имени второго заголовка playlistview
    QLibrary *helper_set_s_n = new QLibrary("Helper");
    Helper_set_second_name set_window_name_second = (Helper_set_second_name)helper_set_s_n->resolve("set_second_name_HeaderLabels");
    QString set_name_second = set_window_name_second();
    delete helper_set_s_n;

    ui->just_playingTrack->setVisible(false);

    playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(playListModel);


    playListModel->setHorizontalHeaderLabels(QStringList()  << tr(set_name_first.toStdString().data())<< tr(set_name_second.toStdString().data()));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection); // Разрешаем выделять только одну строку
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Отключаем редактирование

    ui->playlistView->horizontalHeader()->setStretchLastSection(true); // по ширине строки

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    load_mode_plugins();
    load_interfase_plugins();

    connect(playlist, &QMediaPlaylist::currentIndexChanged, [this](int index) {
        int delLast = count_tracks_num;
        Next = index;
        Back = index;
        if(isNext) {
            ui->playlistView->model()->setData(ui->playlistView->model()->index(Next, 0),QColor(255, 125, 0), Qt::BackgroundRole);

            ui->playlistView->model()->setData(ui->playlistView->model()->index(--Back, 0),QColor(255, 255, 255), Qt::BackgroundRole);
        }
        else {
            ui->playlistView->model()->setData(ui->playlistView->model()->index(Next, 0),QColor(255, 125, 0), Qt::BackgroundRole);

            ui->playlistView->model()->setData(ui->playlistView->model()->index(++Back, 0),QColor(255, 255, 255), Qt::BackgroundRole);
        }
        ui->just_playingTrack->setText(playListModel->data(playListModel->index(index, 0)).toString());
        if(index == 0) ui->playlistView->model()->setData(ui->playlistView->model()->index(--delLast, 0),QColor(255, 255, 255), Qt::BackgroundRole);
        if(index == --delLast) ui->playlistView->model()->setData(ui->playlistView->model()->index(0, 0),QColor(255, 255, 255), Qt::BackgroundRole);
    });
}

void Player::load_mode_plugins()
{
    QDir dir(qApp->applicationDirPath());
    dir.cd("plugins");
    QStringList filter;
    filter << "*.dll";
    QPluginLoader loader;
    foreach(QFileInfo info, dir.entryInfoList(filter)) {
        loader.setFileName(info.absoluteFilePath());
        Interface* mode = qobject_cast<Interface*>(loader.instance());
        if(mode) {
            QString name = loader.metaData().value("MetaData").toObject().value("Mode_name").toString();
            ui->mode_list->addItem(name);
            _mode.append(mode);
        }
    }
}

void Player::load_interfase_plugins() { //загрузка интерфейса
    QDir dir(qApp->applicationDirPath());
    dir.cd("themes_interfases");
    QStringList filter_1;
    filter_1 << "*.dll";
    QPluginLoader loader_1;
    foreach(QFileInfo info, dir.entryInfoList(filter_1)) {
        loader_1.setFileName(info.absoluteFilePath());
        Interface_theme* mode1 = qobject_cast<Interface_theme*>(loader_1.instance());
        if(mode1) {
            QString name = loader_1.metaData().value("MetaData").toObject().value("interfas_name").toString();
            ui->mode_list_2->addItem(name);
            _mode1.append(mode1);
        }
    }
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
    ui->just_playingTrack->setVisible(true);
}

void Player::on_btn_previous_clicked() {
    isNext = false;
    playlist->previous();
}

void Player::on_btn_pause_clicked() {
    player->pause();
}

void Player::on_btn_stop_clicked() {
    player->stop();
    ui->just_playingTrack->setVisible(false);
}

void Player::on_btn_next_clicked() {
    isNext = true;
    playlist->next();
}

void Player::on_playlistView_doubleClicked(const QModelIndex index) {

    for (int ind = 0; ind < count_tracks_num; ++ind) {
        ui->playlistView->model()->setData(ui->playlistView->model()->index(ind, 0),QColor(255, 255, 255), Qt::BackgroundRole);
    }
    playlist->setCurrentIndex(index.row());
    on_btn_play_clicked();
}

void Player::on_Info_clicked() {

    typedef void (*About)();
    QLibrary *aboutLib = new QLibrary("About");
    About showWindowAboutProgramm = (About)aboutLib->resolve("about");
    showWindowAboutProgramm();
    delete aboutLib;
}

void Player::on_reboot_clicked() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void Player::on_apply_clicked() {//применить для первой темы
    QApplication::setFont(_mode.at(ui->mode_list->currentIndex())->changeView());
}

void Player::on_apply_2_clicked() {//применить для второй темы
    QApplication::setPalette(_mode1.at(ui->mode_list_2->currentIndex())->changeInterfase());
}

void Player::sockDisc() { //отключение от сервера
    socket->disconnected();
}

void Player::sockReady() { //получение данных от сервера
    if(socket->waitForConnected(100)) {
        socket->waitForReadyRead(100);
        Data = socket->readAll();

         QDir dir_client(QDir::currentPath() + "/themes_interfases");

        if(Data == "Actuale") {
            QMessageBox::information(this, "Информация", "Соединение установлено\nУ вас актуальная версия программы!");
            socket->disconnected();
        }

        else if(Data == "Need update") { //если сервер отправляет обновление
            Data.clear();
            QStringList find_filter;

            bool ok = dir_client.exists();
            if (ok) {
                dir_client.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
                dir_client.setSorting(QDir::Name);
                QFileInfoList list = dir_client.entryInfoList();

                for (int i = 0; i < list.size(); ++i) {
                    QFileInfo fileInfo = list.at(i);
                    find_filter.append(fileInfo.fileName());
                }
                qDebug() << find_filter << endl;
            }
            foreach (const QString &str, find_filter) {
                Data.append(str);
                if(&str != find_filter.last()) {
                    Data.append(" ");
                }
            }
            qDebug() << Data << endl; //получение списка тем текущих, которые есть у клиента


            socket->write(Data);
            socket->waitForBytesWritten(100);
        }
        else { //когда сервер уже отправляет файлы
            QStringList rec_data_update;
            QString new_version;

            rec_data_update.append(QString(Data).split(" "));
            new_version.append(rec_data_update.last());

            QDir new_client_version(qApp->applicationDirPath());
            QStringList filter;
            filter << "*.json";
            foreach(QFileInfo info, new_client_version.entryInfoList(filter)) { //обновляет версию
                filter.clear();
                filter << info.absoluteFilePath();
            }

            QFile file(filter.back());
            if (!file.open(QIODevice::WriteOnly)) //получает путь
                return;
            file.write(new_version.toStdString().data());

            for(int i = 1; i < rec_data_update.size()-1; i++) {
                QFile::copy(rec_data_update.front()+'/'+rec_data_update[i], dir_client.path()+'/'+rec_data_update[i]); //копирывание из сервера
            }

            _mode1.clear();
            ui->mode_list_2->clear();
            load_interfase_plugins();
            QMessageBox::information(this, "Информация", "Обновление завершено!");

            //create log

            QDir write_log(QDir::currentPath() + "/logs"); //создание логирования
            QStringList formatFile;
            formatFile << "*.txt";
            foreach(QFileInfo info, write_log.entryInfoList(formatFile)) {
                formatFile.clear();
                formatFile << info.absoluteFilePath();
            }

            QFile log(formatFile.front());
            if (!log.open(QIODevice::WriteOnly))
                return;
            QString text = "Update Modules and version "+ rec_data_update.back();
            log.write(text.toStdString().data());
        }
    }
}

void Player::on_check_update_clicked() { //создание соединения с сервером
    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));

    Data.clear();

    QDir client_version(qApp->applicationDirPath());
    QStringList filter;
    filter << "*.json";
    foreach(QFileInfo info, client_version.entryInfoList(filter)) { //помещение в перменную версию клиента
        filter.clear();
        filter << info.absoluteFilePath();
    }
    QFile file(filter.back());
    if (!file.open(QIODevice::ReadOnly))
        return;
    Data = file.readAll();
    socket->connectToHost("127.0.0.1", 5555); //подключение к серверу
    socket->waitForConnected(1);
    if(socket->state() == QTcpSocket::ConnectedState) {
        if(socket->isOpen()) { //если соединение было открыто, то отправляет текущую версию программы
            socket->write(Data);

            socket->waitForBytesWritten(100);
        }
    }
    else {
        QMessageBox::information(this, "Информация", "Соединение не установлено");
    }
}
