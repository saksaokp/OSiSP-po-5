#include "sapper.hpp"

#include <QRandomGenerator>
#include <QTimer>

#include <fstream>
#include <set>

Sapper::Sapper(QWidget* const c_QWidgetPtr)
  : QWidget(c_QWidgetPtr, Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint) {
  constexpr std::uint64_t c_INFO_FIELD_LENGTH{3}, c_INFO_FIELD_SIZE{40};

  m_TimeInfoPtr = new QLCDNumber(c_INFO_FIELD_LENGTH);
  m_TimeInfoPtr->setMinimumHeight(c_INFO_FIELD_SIZE);
  m_TimeInfoPtr->display(0);

  m_BombsInfoPtr = new QLCDNumber(c_INFO_FIELD_LENGTH);
  m_BombsInfoPtr->setMinimumHeight(c_INFO_FIELD_SIZE);
  m_BombsInfoPtr->display(static_cast<int>(m_GameDifficulty));

  m_RestartButtonPtr = new QPushButton();
  m_RestartButtonPtr->setMinimumSize(c_INFO_FIELD_SIZE, c_INFO_FIELD_SIZE);
  m_RestartButtonPtr->setMaximumSize(c_INFO_FIELD_SIZE, c_INFO_FIELD_SIZE);
  connect(m_RestartButtonPtr, SIGNAL(clicked()), SLOT(sf_create_game()));

  m_GameTimerPtr = new QTimer(this);
  connect(m_GameTimerPtr, SIGNAL(timeout()), SLOT(sf_add_time()));

  m_AboutInfoPtr = new QMessageBox(QMessageBox::Information, "About", "Sapper v1.0", QMessageBox::Ok);
  m_WinnerInfoPtr = new QMessageBox(QMessageBox::Information, "You won!", "Your score: ", QMessageBox::Ok);

  m_ScoresInfoPtr = new QMessageBox(QMessageBox::Information, "Score Info", "Your score: ", QMessageBox::Ok);
  f_load_scores();

  m_GameMenuBarPtr = m_MainWindow.menuBar();

  m_GameFileMenuPtr = m_GameMenuBarPtr->addMenu("File");
  m_GameFileMenuPtr->addAction("New game", this, SLOT(sf_create_game()), Qt::CTRL | Qt::Key_N);
  m_GameFileMenuPtr->addSeparator();

  m_GameDifficultyMenuPtr = m_GameFileMenuPtr->addMenu("Difficulty");
  m_GameDifficultyMenuPtr->addAction("Easy", this, SLOT(sf_create_easy_game()));
  m_GameDifficultyMenuPtr->addAction("Middle", this, SLOT(sf_create_middle_game()));
  m_GameDifficultyMenuPtr->addAction("Hard", this, SLOT(sf_create_hard_game()));

  m_GameFileMenuPtr->addAction("Scores", this, SLOT(sf_show_scores()));
  m_GameFileMenuPtr->addSeparator();

  m_GameFileMenuPtr->addAction("Exit", this, SLOT(close()));

  m_GameFileMenuPtr = m_GameMenuBarPtr->addMenu("Help");
  m_GameFileMenuPtr->addAction("About", this, SLOT(sf_about()));

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

  sf_create_game();
}

Sapper::~Sapper() {
  delete m_TimeInfoPtr;
  delete m_BombsInfoPtr;

  delete m_RestartButtonPtr;

  delete m_GameTimerPtr;

  delete m_AboutInfoPtr;
  delete m_WinnerInfoPtr;
  delete m_ScoresInfoPtr;

  delete m_GameFileMenuPtr;
  delete m_GameDifficultyMenuPtr;
  delete m_GameMenuBarPtr;

  delete m_GridLayoutPtr;
  delete m_HorizontLayoutPtr;
  delete m_VerticalLayoutPtr;
}

void Sapper::f_process_3x3(const std::uint64_t& c_Index, void (Sapper::* v_FunctionPtr)(const std::uint64_t&)) {
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

  connect(v_NewButtonPtr, SIGNAL(left_clicked(std::uint64_t)), SLOT(slotButtonClicked(std::uint64_t)));
  connect(v_NewButtonPtr, SIGNAL(right_clicked(std::uint64_t)), SLOT(rightButtonClicked(std::uint64_t)));
  connect(v_NewButtonPtr, SIGNAL(middle_clicked(std::uint64_t)), SLOT(middleButtonClicked(std::uint64_t)));

  m_GameMap.emplace(c_Index, v_NewButtonPtr);

  return v_NewButtonPtr;
}

void Sapper::f_load_scores() {
  std::ifstream v_Fin(mc_SCORES_FILENAME);

  if (v_Fin.is_open()) {
    v_Fin >> m_EasyBestScore >> m_MediumBestScore >> m_HardBestScore;
    v_Fin.close();
    return;
  }

  f_save_scores();
}

void Sapper::f_save_scores() {
  std::ofstream v_Fout(mc_SCORES_FILENAME);

  if (v_Fout.is_open()) {
    v_Fout << m_EasyBestScore << " " << m_MediumBestScore << " " << m_HardBestScore;
    v_Fout.close();
  }
}

void Sapper::sf_create_game() {
  m_GameOver = false;

  m_RestartButtonPtr->setIcon(QPixmap(":/icons/smile.png"));
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
    m_GridLayoutPtr->addWidget(f_create_button(v_I), v_I / m_RowsCount, v_I % m_RowsCount);
  }

  f_place_bombs();
}

void Sapper::f_place_bombs() {
  std::set<std::uint64_t> v_BobmIndexes;

  while (v_BobmIndexes.size() < m_GameDifficulty) {
    std::uint64_t v_Index{QRandomGenerator::global()->generate() % (m_GameButtonsCount + 1)};

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
    if (m_FieldValuesArray[c_Index] < m_GameButtonsCount) {
      ++m_FieldValuesArray[c_Index];
    }
  }
}

void Sapper::f_show_unckecked_fields(const std::uint64_t& c_Index) {
  if (!m_GameMap.at(c_Index)->f_is_flag()) {
    slotButtonClicked(c_Index);
  }
}

void Sapper::f_flags_count(const std::uint64_t& c_Index) {
  if (m_GameMap.at(c_Index)->f_is_flag()) {
    ++m_CheckedFields3x3Count;
  }
}

void Sapper::f_win() {
  m_GameTimerPtr->stop();
  std::uint64_t value = m_TimeInfoPtr->intValue();

  bool newValue = false;

  m_WinnerInfoPtr->setText("You won! Your score: " + QString().number(m_TimeInfoPtr->intValue()));

  switch (m_GameDifficulty) {
    case EASY: {
      if (m_EasyBestScore == 0 || value < m_EasyBestScore) {
        m_EasyBestScore = value;
        newValue = true;
      }

      break;
    }
    case MEDIUM: {
      if (m_MediumBestScore == 0 || value < m_MediumBestScore) {
        m_MediumBestScore = value;
        newValue = true;
      }

      break;
    }
    case HARD: {
      if (m_HardBestScore == 0 || value < m_HardBestScore) {
        m_HardBestScore = value;
        newValue = true;
      }

      break;
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

      m_GameMap.at(v_Index)->setFlat(true);
      m_GameMap.at(v_Index)->setIcon(QPixmap(":/icons/bomb.png"));
    } else if (m_GameMap.at(v_Index)->f_is_flag()) {
      m_GameMap.at(v_Index)->setFlat(true);
      m_GameMap.at(v_Index)->setIcon(QPixmap(":/icons/bad_check.png"));
    }
  }
}

void Sapper::sf_add_time() { m_TimeInfoPtr->display(m_TimeInfoPtr->intValue() + 1); }

void Sapper::sf_create_easy_game() {
  m_CheckedFieldsCount = m_GameDifficulty = BombsCount::EASY;
  setFixedSize(10 * PushButton::c_BUTTON_SIZE, 325);
  m_RowsCount = 8;
  m_GameButtonsCount = m_RowsCount * m_RowsCount;
  sf_create_game();
}

void Sapper::sf_create_middle_game() {
  m_CheckedFieldsCount = m_GameDifficulty = BombsCount::MEDIUM;
  setFixedSize(12 * PushButton::c_BUTTON_SIZE, 350);
  m_RowsCount = 10;
  m_GameButtonsCount = m_RowsCount * m_RowsCount;
  sf_create_game();
}

void Sapper::sf_create_hard_game() {
  m_CheckedFieldsCount = m_GameDifficulty = BombsCount::HARD;
  setFixedSize(18 * PushButton::c_BUTTON_SIZE, 420);
  m_RowsCount = 15;
  m_GameButtonsCount = m_RowsCount * m_RowsCount;
  sf_create_game();
}

void Sapper::sf_show_scores() {
  m_ScoresInfoPtr->setText(
    "<table><tr><td><b/>Difficulty</td><td>  |  </td><td><b/>Time</td></tr>"
    "<tr><td>Easy</td><td>  |  </td><td>" + QString().number(m_EasyBestScore) + "</td></tr>"
    "<tr><td>Medium</td><td>  |  </td><td>" + QString().number(m_MediumBestScore) + "</td></tr>"
    "<tr><td>Hard</td><td>  |  </td><td>" + QString().number(m_HardBestScore) + "</td><tr></table>");

  m_ScoresInfoPtr->show();
}

void Sapper::sf_about() { m_AboutInfoPtr->show(); }

void Sapper::slotButtonClicked(const std::uint64_t& c_Index) {
  if (m_GameOver || (c_Index > m_GameButtonsCount)
      || m_GameMap.at(c_Index)->isFlat() || (m_GameMap.at(c_Index)->f_get_icon_index() != 0)) {
    return;
  }

  if (!m_GameTimerPtr->isActive()) {
    m_GameTimerPtr->start(1000);
  }

  if (m_FieldValuesArray[c_Index] < m_GameButtonsCount) {
    m_GameMap.at(c_Index)->setFlat(true);

    ++m_VisibleCellsCount;

    if (m_FieldValuesArray[c_Index] > 0) {
      m_GameMap.at(c_Index)->setIcon(QPixmap(":/icons/" + QString().number(m_FieldValuesArray[c_Index]) + ".png"));
    }

    if (m_FieldValuesArray[c_Index] == 0) {
      f_process_3x3(c_Index, &Sapper::slotButtonClicked);
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
      m_GameMap.at(c_Index)->setIcon(QPixmap());
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

void Sapper::middleButtonClicked(const std::uint64_t& c_Index) {
  if (m_GameOver) {
    return;
  }

  if (m_FieldValuesArray[c_Index] == 0) {
    return;
  }

  m_CheckedFields3x3Count = 0;

  f_process_3x3(c_Index, &Sapper::f_flags_count);

  if (m_CheckedFields3x3Count == m_FieldValuesArray[c_Index]) {
    f_process_3x3(c_Index, &Sapper::f_show_unckecked_fields);
  }
}
