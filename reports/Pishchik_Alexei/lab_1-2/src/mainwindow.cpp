#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool checked = true;
    on_processor_clicked(checked);
}

string *res = new string[100];
QStringList header, result_data, mass;
int size_str = 0;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::result_update(int size_cols, QStringList header, QStringList mass) {
    string result[size_cols];
    string s;
    ifstream f1;
    f1.open("test1.txt");
    int i = 0;
    while (!f1.eof()) {
        getline(f1, s);
        result[i] = s;
        i++;
    }
    f1.close();
    remove("test1.txt");
    for (int i = 0; i < size_cols; i++)
    {
        res[i] = result[i];
    }
    ui->tableWidget->setRowCount(size_cols); // Устанавливаем количество строк на size_cols
    ui->tableWidget->setColumnCount(1);
    for(int i = 0; i < size_cols; i++) {
        ui->tableWidget->verticalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->setVerticalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    for(int i = 0; i < size_cols; i++) {
        QString data = QString::fromStdString(res[i]);
        result_data.append(data);
    }

    int countt = 0;
    for (int i = countt; i <  ui->tableWidget->rowCount(); ++i) {
        QTableWidgetItem * item;
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            item = new QTableWidgetItem;
            for(int s = 0; s < size_str; s++) {
                if(i==s)
                   item->setText(result_data.value(mass[s].toInt()));
                ui->tableWidget->setItem(i, j, item);
            }
        }
    }
    countt++;

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}

void MainWindow::update_str(string s) {
    string new_str;
    bool flag = false;
    int flag1 = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '|') {
            flag = false;
            flag1++;
        }
        if (flag1 == 1) {
            new_str += '\n';
            flag1++;
        }
        if (flag == true) {
            new_str += s[i];
        }
        if (s[i] == '\n' || (s[i] == ' ' && s[++i] == ' ')) {
            flag = false;
        }
        if (s[i] == '=') {
            size_str++;
            flag = true;
        }
    }
    ofstream ff;
    ff.open("test1.txt");
    ff << new_str;
    ff.close();
}

void MainWindow::read_file_info() {
    ifstream f;
    string s;
    f.open("test.txt");
    while (!f.eof()) {
        char c = f.get();
        s += c;
    }
    f.close();
    remove("test.txt");
    update_str(s);
}

void MainWindow::on_processor_clicked(bool checked) {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    ui->switch_info->setText("Информация о процессоре");
    header.clear(), result_data.clear(), mass.clear();
    system("wmic CPU get Name, NumberOfCores, NumberOfLogicalProcessors, Maxclockspeed /format:list >> test.txt"); //proc
    read_file_info();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header<<"Частота на ядро"<<"Имя процессора"<<"Количество ядер"<<"Количество потоков", mass);
}

void MainWindow::on_mother_clicked() {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    header.clear(), result_data.clear(), mass.clear();
    ui->switch_info->setText("Информация о Материнской плате");
    system("wmic baseboard get manufacturer, product /format:list >> test.txt"); //mather
    read_file_info();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header<<"Производитель"<<"Модель", mass);
}

void MainWindow::on_os_clicked() {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    header.clear(), result_data.clear(), mass.clear();
    ui->switch_info->setText("Информация об Операционной системе");
    system("wmic OS get Manufacturer, Version /format:list >> test.txt"); //OS
    read_file_info();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header<<"Производитель OS"<<"Версия", mass);
}

void MainWindow::on_info_programm_clicked() {
    ui->tableWidget->setVisible(false);
    ui->switch_info->setText("Программу сделал студент группы ПО-5, Пищик Алексей");
}

void MainWindow::on_ram_clicked() {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    header.clear(), result_data.clear(), mass.clear();
    ui->switch_info->setText("Информация об Модулях оперативной памяти");
    system("wmic memorychip get speed, PartNumber /format:list >> test.txt"); //ram
    read_file_info();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    int r = size_str/2;
    for(int i = 0; i < r; i++) {
        header<<"Партийный номер"<<"Частота";
    }
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header, mass);
}

void MainWindow::on_hard_clicked() {
    size_str = 0;
    ui->tableWidget->setVisible(true);
    header.clear(), result_data.clear(), mass.clear();
    ui->switch_info->setText("Информация об Накопителях");
    system("wmic diskdrive get model, size /format:list >> test.txt"); //hard
    read_file_info();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    int r = size_str/2;
    for(int i = 0; i < r; i++) {
        header<<"Модель"<<"Размер";
    }
    for(int i = 0; i < size_str; i++) {
        QString m = QVariant(i).toString();
        mass.append(m);
    }
    result_update(size_str, header, mass);
}
