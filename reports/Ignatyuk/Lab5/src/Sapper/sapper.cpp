#include "sapper.hpp"

#include <QApplication>
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFontDialog>
#include <QTimer>

#include <fstream>
#include <set>
#include <sstream>

#include "updater.hpp"

Sapper::Sapper(QWidget* const c_QWidgetPtr)
    : QWidget(c_QWidgetPtr,
              Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint) {
  m_HelperLibraryPtr = f_load_library("helper.dll");

  if (m_HelperLibraryPtr == nullptr) {
    return;
  }

  m_GetRandomNumberPtr =
      (f_get_random_number)m_HelperLibraryPtr->resolve("get_random_number");
  m_ReadLineFromFilePtr =
      (f_read_line_from_file)m_HelperLibraryPtr->resolve("read_line_from_file");
  m_WriteToFilePtr =
      (f_write_to_file)m_HelperLibraryPtr->resolve("write_to_file");

  m_MainWindowPtr = new QMainWindow{};

  constexpr std::uint64_t c_INFO_FIELD_LENGTH{3}, c_INFO_FIELD_SIZE{40};

  m_TimeInfoPtr = new QLCDNumber(c_INFO_FIELD_LENGTH);
  m_TimeInfoPtr->setMinimumHeight(c_INFO_FIELD_SIZE);

  m_BombsInfoPtr = new QLCDNumber(c_INFO_FIELD_LENGTH);
  m_BombsInfoPtr->setMinimumHeight(c_INFO_FIELD_SIZE);

  m_RestartButtonPtr = new QPushButton();
  m_RestartButtonPtr->setMinimumSize(c_INFO_FIELD_SIZE, c_INFO_FIELD_SIZE);
  m_RestartButtonPtr->setMaximumSize(c_INFO_FIELD_SIZE, c_INFO_FIELD_SIZE);
  connect(m_RestartButtonPtr, SIGNAL(clicked()), SLOT(sf_create_game()));

  m_GameTimerPtr = new QTimer(this);
  connect(m_GameTimerPtr, SIGNAL(timeout()), SLOT(sf_add_time()));

  m_AboutInfoPtr = new About{};
  m_WinnerInfoPtr = new QMessageBox(QMessageBox::Information, "You won!",
                                    "Your score: ", QMessageBox::Ok);

  m_ScoresInfoPtr = new QMessageBox(QMessageBox::Information, "Score Info",
                                    "Your score: ", QMessageBox::Ok);
  f_load_scores();

  m_GameMenuBarPtr = m_MainWindowPtr->menuBar();

  m_GameFileMenuPtr = m_GameMenuBarPtr->addMenu("File");
  m_GameFileMenuPtr->addAction("New game", this, SLOT(sf_create_game()),
                               Qt::CTRL | Qt::Key_N);
  m_GameFileMenuPtr->addSeparator();

  m_GameDifficultyMenuPtr = m_GameFileMenuPtr->addMenu("Difficulty");
  m_GameDifficultyMenuPtr->addAction("Easy", this, SLOT(sf_create_easy_game()));
  m_GameDifficultyMenuPtr->addAction("Medium", this,
                                     SLOT(sf_create_medium_game()));
  m_GameDifficultyMenuPtr->addAction("Hard", this, SLOT(sf_create_hard_game()));

  m_GameFileMenuPtr->addAction("Scores", this, SLOT(sf_show_scores()));
  m_GameFileMenuPtr->addSeparator();

  m_GameFileMenuPtr->addAction("Exit", this, SLOT(close()));

  m_GameHelpMenuPtr = m_GameMenuBarPtr->addMenu("Help");
  m_GameHelpMenuPtr->addAction("About", this, SLOT(sf_about()));

  m_GameChangeMenuPtr = m_GameMenuBarPtr->addMenu("Change");
  m_GameChangeMenuPtr->addAction("Change menu font", this,
                                 SLOT(sf_change_menu_font()));
  m_GameChangeMenuPtr->addAction("Change actions font", this,
                                 SLOT(sf_change_actions_font()));
  m_GameChangeMenuPtr->addAction("Change app color", this,
                                 SLOT(sf_change_color()));

  m_GameUpdateMenuPtr = m_GameMenuBarPtr->addMenu("Update");
  m_GameUpdateMenuPtr->addAction("Check for updates...", this,
                                 SLOT(sf_check_for_updates()));
  m_GameUpdateMenuPtr->addSeparator();

  m_GameUpdatePoliticsMenuPtr = m_GameUpdateMenuPtr->addMenu("Politics");
  m_GameUpdatePoliticsMenuPtr->addAction("Manual", this,
                                         SLOT(sf_manual_politic()));
  m_GameUpdatePoliticsMenuPtr->addAction("Auto with approval", this,
                                         SLOT(sf_auto_approval_politic()));
  m_GameUpdatePoliticsMenuPtr->addAction("Auto without approval", this,
                                         SLOT(sf_auto_politic()));

  for (auto& v_Action : m_GameUpdatePoliticsMenuPtr->actions()) {
    v_Action->setCheckable(true);
  }

  m_GameUpdatePoliticsMenuPtr->actions().first()->setChecked(true);

  m_GridLayoutPtr = new QGridLayout;
  m_GridLayoutPtr->setSpacing(0);

  m_HorizontLayoutPtr = new QHBoxLayout;
  m_HorizontLayoutPtr->addWidget(m_TimeInfoPtr);
  m_HorizontLayoutPtr->addWidget(m_RestartButtonPtr);
  m_HorizontLayoutPtr->addWidget(m_BombsInfoPtr);

  m_VerticalLayoutPtr = new QVBoxLayout;
  m_VerticalLayoutPtr->addWidget(m_GameMenuBarPtr);
  m_VerticalLayoutPtr->addLayout(m_HorizontLayoutPtr);
  m_VerticalLayoutPtr->addLayout(m_GridLayoutPtr);

  setLayout(m_VerticalLayoutPtr);

  f_load_version();
  f_load_difficulty();
}

Sapper::~Sapper() {
  f_write_version();

  delete m_TimeInfoPtr;
  delete m_BombsInfoPtr;

  delete m_RestartButtonPtr;

  delete m_GameTimerPtr;
  delete m_UpdateTimerPtr;

  delete m_AboutInfoPtr;
  delete m_WinnerInfoPtr;
  delete m_ScoresInfoPtr;

  delete m_UpdateProgressPtr;

  delete m_GridLayoutPtr;
  delete m_HorizontLayoutPtr;
  delete m_VerticalLayoutPtr;

  if (m_HelperLibraryPtr->isLoaded()) {
    m_HelperLibraryPtr->unload();
  }

  delete m_HelperLibraryPtr;

  if (m_UpdaterThreadPtr != nullptr) {
    m_UpdaterThreadPtr->exit();
  }

  delete m_MainWindowPtr;
}

void Sapper::f_process_3x3(
    const std::uint64_t& c_Index,
    void (Sapper::*v_FunctionPtr)(const std::uint64_t&)) {
  std::uint64_t v_StartX{}, v_EndX{}, v_tartY{}, v_EndY{};

  v_EndX = v_StartX = c_Index / m_RowsCount;

  if (v_StartX > 0) {
    v_StartX--;
  }

  v_EndX += 2;

  if (v_EndX > m_RowsCount) {
    v_EndX--;
  }

  v_EndY = v_tartY = c_Index % m_RowsCount;

  if (v_tartY > 0) {
    v_tartY--;
  }

  v_EndY += 2;

  if (v_EndY > m_RowsCount) {
    v_EndY--;
  }

  for (std::uint64_t v_I{v_StartX}; v_I < v_EndX; ++v_I) {
    for (std::uint64_t v_J{v_tartY}; v_J < v_EndY; ++v_J) {
      (this->*v_FunctionPtr)(v_I * m_RowsCount + v_J);
    }
  }
}

QPushButton* Sapper::f_create_button(const std::uint64_t& c_Index) {
  PushButton* v_NewButtonPtr = new PushButton(c_Index);

  if (m_CellStyleSheet.size() > 0) {
    v_NewButtonPtr->setStyleSheet(m_CellStyleSheet);
  }

  connect(v_NewButtonPtr, SIGNAL(left_clicked(std::uint64_t)),
          SLOT(leftButtonClicked(std::uint64_t)));
  connect(v_NewButtonPtr, SIGNAL(right_clicked(std::uint64_t)),
          SLOT(rightButtonClicked(std::uint64_t)));

  m_GameMap.emplace(c_Index, v_NewButtonPtr);

  return v_NewButtonPtr;
}

void Sapper::f_load_scores() {
  std::string v_ScoresLine{};
  m_ReadLineFromFilePtr(mc_SCORES_FILENAME, v_ScoresLine);

  std::stringstream v_Stream{v_ScoresLine};
  v_Stream >> m_EasyBestScore >> m_MediumBestScore >> m_HardBestScore;

  f_save_scores();
}

void Sapper::f_save_scores() {
  m_WriteToFilePtr(mc_SCORES_FILENAME, (QString::number(m_EasyBestScore) + " " +
                                        QString::number(m_MediumBestScore) +
                                        " " + QString::number(m_HardBestScore))
                                           .toStdString());
}

void Sapper::f_load_difficulty() {
  QFile v_File(QDir::currentPath() + "/files/difficulty.conf");

  if (!v_File.open(QIODevice::ReadOnly | QIODevice::ExistingOnly)) {
    sf_create_game();
    return;
  }

  const QString c_Data{v_File.readLine()};
  v_File.close();

  if (c_Data == "Easy") {
    sf_create_easy_game();
    return;
  }

  if (c_Data == "Medium") {
    sf_create_medium_game();
    return;
  }

  if (c_Data == "Hard") {
    sf_create_hard_game();
    return;
  }

  if (c_Data.startsWith("New")) {
    const QStringList c_Values{c_Data.split(' ')};
    m_BombsCount.insert("New", c_Values[1].toULongLong());
    m_NewGameRowsCount = c_Values[2].toULongLong();

    if (m_BombsCount["New"] > m_NewGameRowsCount * m_NewGameRowsCount) {
      m_BombsCount["New"] = m_NewGameRowsCount * m_NewGameRowsCount;
    }

    m_GameDifficultyMenuPtr->addAction("New", this, SLOT(sf_create_new_game()));

    sf_create_new_game();
    return;
  }

  sf_create_game();
}

void Sapper::f_load_version() {
  QFile v_File(QDir::currentPath() + "/version.conf");

  if (!v_File.open(QIODevice::ReadOnly | QIODevice::ExistingOnly)) {
    return;
  }

  const QString c_Data{v_File.readLine()};
  v_File.close();

  m_Version = c_Data;
}

void Sapper::f_write_version() {
  QFile v_File(QDir::currentPath() + "/version.conf");

  if (!v_File.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    return;
  }

  v_File.write(m_Version.toStdString().c_str(), m_Version.size());
  v_File.close();
}

void Sapper::sf_create_game() {
  setFixedSize(m_RowsCount * PushButton::c_BUTTON_SIZE,
               m_RowsCount * PushButton::c_BUTTON_SIZE + 100 + m_RowsCount);

  m_GameOver = false;
  m_RestartButtonPtr->setIcon(QPixmap(":/icons/smile.png"));
  m_CheckedFieldsCount = m_GameDifficulty;

  m_TimeInfoPtr->display(0);
  m_BombsInfoPtr->display(static_cast<int>(m_GameDifficulty));

  m_GameMap.clear();
  m_FieldValuesArray.clear();

  m_VisibleCellsCount = 0;
  m_FieldValuesArray.resize(m_GameButtonsCount, std::uint64_t{});

  for (std::uint64_t v_I{}, size = m_GameMap.size(); v_I < size; ++v_I) {
    m_GameMap.at(v_I)->f_clear();
  }

  for (std::uint64_t v_I{m_GameMap.size()}; v_I < m_GameButtonsCount; ++v_I) {
    m_GridLayoutPtr->addWidget(f_create_button(v_I), v_I / m_RowsCount,
                               v_I % m_RowsCount);
  }

  f_place_bombs();
}

void Sapper::f_place_bombs() {
  std::set<std::uint64_t> v_BobmIndexes;

  while (v_BobmIndexes.size() < m_GameDifficulty) {
    std::int64_t v_Index{m_GetRandomNumberPtr(0, m_GameButtonsCount)};

    // If we already do not have bomb here
    if (m_FieldValuesArray[v_Index] < m_GameButtonsCount) {
      v_BobmIndexes.insert(v_Index);
    }
  }

  std::uint64_t v_BombsPlaced{};

  for (const std::uint64_t& c_Index : v_BobmIndexes) {
    m_FieldValuesArray[c_Index] = m_GameButtonsCount + v_BombsPlaced++;
    f_process_3x3(c_Index, &Sapper::f_add_bomb);
  }
}

void Sapper::f_add_bomb(const std::uint64_t& c_Index) {
  if (c_Index < m_GameButtonsCount) {
    ++m_FieldValuesArray[c_Index];
  }
}

void Sapper::f_win() {
  m_GameTimerPtr->stop();
  std::uint64_t value = m_TimeInfoPtr->intValue();

  bool newValue = false;

  m_WinnerInfoPtr->setText("You won! Your score: " +
                           QString().number(m_TimeInfoPtr->intValue()));

  if (m_GameDifficulty == m_BombsCount["Easy"]) {
    if (m_EasyBestScore == 0 || value < m_EasyBestScore) {
      m_EasyBestScore = value;
      newValue = true;
    }
  } else if (m_GameDifficulty == m_BombsCount["Medium"]) {
    if (m_MediumBestScore == 0 || value < m_MediumBestScore) {
      m_MediumBestScore = value;
      newValue = true;
    }
  } else if (m_GameDifficulty == m_BombsCount["Hard"]) {
    if (m_HardBestScore == 0 || value < m_HardBestScore) {
      m_HardBestScore = value;
      newValue = true;
    }
  }

  if (newValue) {
    f_save_scores();
  }

  m_WinnerInfoPtr->show();
}

void Sapper::f_show_all_bombs() {
  for (std::uint64_t v_Index{}; v_Index < m_GameButtonsCount; ++v_Index) {
    if (m_FieldValuesArray[v_Index] >= m_GameButtonsCount) {
      if (m_GameMap.at(v_Index)->f_is_flag()) {
        continue;
      }

      m_GameMap.at(v_Index)->setIcon(QPixmap(":/icons/bomb.png"));
    } else if (m_GameMap.at(v_Index)->f_is_flag()) {
      m_GameMap.at(v_Index)->setIcon(QPixmap(":/icons/bad_check.png"));
    } else {
      continue;
    }

    m_GameMap.at(v_Index)->setFlat(true);
  }
}

QLibrary* Sapper::f_load_library(const QString& c_LibPath) const {
  QLibrary* v_LibraryPtr = new QLibrary(c_LibPath);

  if (!v_LibraryPtr->load()) {
    qWarning() << QString("Can't load plugin lib \"%1\"").arg(c_LibPath)
               << v_LibraryPtr->errorString();
    delete v_LibraryPtr;
    v_LibraryPtr = nullptr;
    return nullptr;
  }

  return v_LibraryPtr;
}

void Sapper::sf_add_time() {
  m_TimeInfoPtr->display(m_TimeInfoPtr->intValue() + 1);
}

void Sapper::sf_create_easy_game() {
  m_CheckedFieldsCount = m_GameDifficulty = m_BombsCount["Easy"];
  m_RowsCount = 8;
  m_GameButtonsCount = m_RowsCount * m_RowsCount;
  sf_create_game();
}

void Sapper::sf_create_medium_game() {
  m_CheckedFieldsCount = m_GameDifficulty = m_BombsCount["Medium"];
  m_RowsCount = 10;
  m_GameButtonsCount = m_RowsCount * m_RowsCount;
  sf_create_game();
}

void Sapper::sf_create_hard_game() {
  m_CheckedFieldsCount = m_GameDifficulty = m_BombsCount["Hard"];
  m_RowsCount = 15;
  m_GameButtonsCount = m_RowsCount * m_RowsCount;
  sf_create_game();
}

void Sapper::sf_create_new_game() {
  m_CheckedFieldsCount = m_GameDifficulty = m_BombsCount["New"];
  m_RowsCount = m_NewGameRowsCount;
  m_GameButtonsCount = m_RowsCount * m_RowsCount;
  sf_create_game();
}

void Sapper::sf_show_scores() {
  m_ScoresInfoPtr->setText(
      "<table><tr><td><b/>Difficulty</td><td>  |  </td><td><b/>Time</td></tr>"
      "<tr><td>Easy</td><td>  |  </td><td>" +
      QString().number(m_EasyBestScore) +
      "</td></tr>"
      "<tr><td>Medium</td><td>  |  </td><td>" +
      QString().number(m_MediumBestScore) +
      "</td></tr>"
      "<tr><td>Hard</td><td>  |  </td><td>" +
      QString().number(m_HardBestScore) + "</td><tr></table>");

  m_ScoresInfoPtr->show();
}

void Sapper::sf_about() { m_AboutInfoPtr->f_show(); }

void Sapper::sf_change_menu_font() {
  bool v_Ok{false};

  QFont v_Font{QFontDialog::getFont(&v_Ok)};

  if (v_Ok) {
    m_GameMenuBarPtr->setFont(v_Font);
  }
}

void Sapper::sf_change_actions_font() {
  bool v_Ok{false};

  QFont v_Font{QFontDialog::getFont(&v_Ok)};

  if (v_Ok) {
    m_GameFileMenuPtr->setFont(v_Font);
    m_GameDifficultyMenuPtr->setFont(v_Font);
    m_GameHelpMenuPtr->setFont(v_Font);
    m_GameChangeMenuPtr->setFont(v_Font);
  }
}

void Sapper::sf_change_color() {
  QColor v_Color{QColorDialog::getColor()};

  m_GameMenuBarPtr->setStyleSheet("QMenuBar { background-color : rgb(" +
                                  QString::number(v_Color.red()) + ", " +
                                  QString::number(v_Color.green()) + ", " +
                                  QString::number(v_Color.blue()) + "); }");

  m_CellStyleSheet = "QPushButton { background-color : rgb(" +
                     QString::number(v_Color.red()) + ", " +
                     QString::number(v_Color.green()) + ", " +
                     QString::number(v_Color.blue()) + "); }";

  for (auto& v_Cell : m_GameMap) {
    v_Cell.second->setStyleSheet(m_CellStyleSheet);
  }
}

void Sapper::leftButtonClicked(const std::uint64_t& c_Index) {
  if (m_GameOver || (c_Index > m_GameButtonsCount) ||
      m_GameMap.at(c_Index)->isFlat() ||
      (m_GameMap.at(c_Index)->f_get_icon_index() != 0)) {
    return;
  }

  if (!m_GameTimerPtr->isActive()) {
    m_GameTimerPtr->start(1000);
  }

  if (m_FieldValuesArray[c_Index] < m_GameButtonsCount) {
    m_GameMap.at(c_Index)->setFlat(true);

    ++m_VisibleCellsCount;

    if (m_FieldValuesArray[c_Index] > 0) {
      m_GameMap.at(c_Index)->setIcon(QPixmap(
          ":/icons/" + QString().number(m_FieldValuesArray[c_Index]) + ".png"));
    }

    if (m_FieldValuesArray[c_Index] == 0) {
      f_process_3x3(c_Index, &Sapper::leftButtonClicked);
    }
  }

  if (m_FieldValuesArray[c_Index] >= m_GameButtonsCount) {
    m_GameOver = true;
    m_RestartButtonPtr->setIcon(QPixmap(":/icons/bad.png"));
    m_GameTimerPtr->stop();
    f_show_all_bombs();
    return;
  }

  if (m_VisibleCellsCount >= (m_GameButtonsCount - m_GameDifficulty)) {
    f_win();
  }
}

void Sapper::rightButtonClicked(const std::uint64_t& c_Index) {
  if (m_GameOver) {
    return;
  }

  switch (m_GameMap.at(c_Index)->f_get_icon_index()) {
    case 0: {
      m_GameMap.at(c_Index)->setIcon(QPixmap(""));
      ++m_CheckedFieldsCount;
      break;
    }
    case 1: {
      m_GameMap.at(c_Index)->setIcon(QPixmap(":/icons/check.png"));
      --m_CheckedFieldsCount;
      break;
    }
    case 2: {
      m_GameMap.at(c_Index)->setIcon(QPixmap(":/icons/query.png"));
      break;
    }
  }

  m_BombsInfoPtr->display(static_cast<int>(m_CheckedFieldsCount));
}

void Sapper::sf_check_for_updates() {
  if (m_UpdaterThreadPtr) {
    m_UpdaterThreadPtr->exit();
  }

  m_UpdaterThreadPtr = new QThread{};
  Updater* v_UpdaterPtr{new Updater{m_Version}};

  v_UpdaterPtr->moveToThread(m_UpdaterThreadPtr);

  connect(m_UpdaterThreadPtr, SIGNAL(started()), v_UpdaterPtr,
          SLOT(sf_process()));

  connect(v_UpdaterPtr, SIGNAL(s_connecting()), this, SLOT(sf_connecting()));
  connect(v_UpdaterPtr, SIGNAL(s_can_not_connect()), this,
          SLOT(sf_can_not_connect()));
  connect(v_UpdaterPtr, SIGNAL(s_up_to_date()), this, SLOT(sf_up_to_date()));
  connect(v_UpdaterPtr, SIGNAL(s_updated()), this, SLOT(sf_updated()));

  connect(v_UpdaterPtr, SIGNAL(s_add_progress()), this,
          SLOT(sf_add_progress()));
  connect(v_UpdaterPtr, SIGNAL(s_end_progress()), this,
          SLOT(sf_end_progress()));

  connect(v_UpdaterPtr, SIGNAL(s_finished()), m_UpdaterThreadPtr, SLOT(quit()));
  connect(v_UpdaterPtr, SIGNAL(s_finished()), v_UpdaterPtr,
          SLOT(deleteLater()));
  connect(m_UpdaterThreadPtr, SIGNAL(finished()), m_UpdaterThreadPtr,
          SLOT(deleteLater()));

  if (m_UpdateProgressPtr != nullptr) {
    delete m_UpdateProgressPtr;
    m_UpdateProgressPtr = nullptr;
  }

  m_UpdateProgressPtr = new QProgressDialog{this};
  m_UpdateProgressPtr->setLabelText("Update progress");
  m_UpdateProgressPtr->setRange(0, 100);
  m_UpdateProgressPtr->setValue(10);
  m_UpdateProgressPtr->setAutoClose(false);
  m_UpdateProgressPtr->setAutoReset(false);
  m_UpdateProgressPtr->setCancelButtonText("OK");
  m_UpdateProgressPtr->show();

  m_UpdaterThreadPtr->start();
}

void Sapper::sf_connecting() {
  QMessageBox::information(this, "Update Checker",
                           "Getting data from the server...");
}

void Sapper::sf_can_not_connect() {
  QMessageBox::information(this, "Update Checker",
                           "Can not connect to server!");
}

void Sapper::sf_up_to_date() {
  QMessageBox::information(this, "Update Checker", "You are up to date!");
}

void Sapper::sf_updated() {
  QMessageBox::information(
      this, "Update Checker",
      "Updated successfully!\nPlease restart the program!");
}

void Sapper::sf_manual_politic() {
  m_UpdatePolitic = "Manual";
  m_GameUpdatePoliticsMenuPtr->actions().at(0)->setChecked(true);
  m_GameUpdatePoliticsMenuPtr->actions().at(1)->setChecked(false);
  m_GameUpdatePoliticsMenuPtr->actions().at(2)->setChecked(false);

  m_UpdateTimerPtr->stop();
  delete m_UpdateTimerPtr;
  m_UpdateTimerPtr = nullptr;
}

void Sapper::sf_auto_approval_politic() {
  m_UpdatePolitic = "Auto approval";
  m_GameUpdatePoliticsMenuPtr->actions().at(0)->setChecked(false);
  m_GameUpdatePoliticsMenuPtr->actions().at(1)->setChecked(true);
  m_GameUpdatePoliticsMenuPtr->actions().at(2)->setChecked(false);

  if (m_UpdateTimerPtr != nullptr) {
    m_UpdateTimerPtr->stop();
    delete m_UpdateTimerPtr;
    m_UpdateTimerPtr = nullptr;
  }

  m_UpdateTimerPtr = new QTimer(this);
  connect(m_UpdateTimerPtr, &QTimer::timeout, [this]() {

    bool v_Answer = QMessageBox::warning(this, "Update Checker",
                                         "Want to start the update now?", "No",
                                         "Yes", QString(), 1, 1);

    if (v_Answer) {
      sf_check_for_updates();
    }

    if (m_UpdateTimerPtr != nullptr) {
      m_UpdateTimerPtr->start(10'000);
    }
  });

  m_UpdateTimerPtr->start(10'000);
}

void Sapper::sf_auto_politic() {
  m_UpdatePolitic = "Auto";
  m_GameUpdatePoliticsMenuPtr->actions().at(0)->setChecked(false);
  m_GameUpdatePoliticsMenuPtr->actions().at(1)->setChecked(false);
  m_GameUpdatePoliticsMenuPtr->actions().at(2)->setChecked(true);

  if (m_UpdateTimerPtr != nullptr) {
    m_UpdateTimerPtr->stop();
    delete m_UpdateTimerPtr;
    m_UpdateTimerPtr = nullptr;
  }

  m_UpdateTimerPtr = new QTimer(this);
  connect(m_UpdateTimerPtr, &QTimer::timeout, [this]() {
    sf_check_for_updates();

    if (m_UpdateTimerPtr != nullptr) {
      m_UpdateTimerPtr->start(10'000);
    }
  });

  m_UpdateTimerPtr->start(10'000);
}

void Sapper::sf_add_progress() {
  if (m_UpdateProgressPtr == nullptr) {
    return;
  }

  constexpr int c_INC{10}, c_MAX{90};

  if (m_UpdateProgressPtr->value() < c_MAX) {
    m_UpdateProgressPtr->setValue(m_UpdateProgressPtr->value() + c_INC);
  }
}

void Sapper::sf_end_progress() {
  if (m_UpdateProgressPtr == nullptr) {
    return;
  }

  constexpr int c_MAX{100};
  m_UpdateProgressPtr->setValue(c_MAX);
}
