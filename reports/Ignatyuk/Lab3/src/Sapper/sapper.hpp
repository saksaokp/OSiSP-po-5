#pragma once

#ifndef SAPPER_HPP
#define SAPPER_HPP

#include <QLibrary>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>

#include <qlayout.h>
#include <qlcdnumber.h>

#include "about.hpp"
#include "helperclass.hpp"

typedef std::int64_t (*f_get_random_number)(const std::int64_t&,
                                            const std::int64_t&);
typedef void (*f_read_line_from_file)(const std::string&, const std::string&);
typedef void (*f_write_to_file)(const std::string&, const std::string&);

class Sapper : public QWidget {
  Q_OBJECT

 public:
  Sapper(QWidget* const c_QWidgetPtr = nullptr);
  ~Sapper();

 private:
  enum BombsCount { EASY = 10, MEDIUM = 25, HARD = 70 };

  QLCDNumber* m_TimeInfoPtr{nullptr};
  QLCDNumber* m_BombsInfoPtr{nullptr};

  QPushButton* m_RestartButtonPtr{nullptr};

  QTimer* m_GameTimerPtr{nullptr};

  About* m_AboutInfoPtr{nullptr};
  QMessageBox* m_WinnerInfoPtr{nullptr};
  QMessageBox* m_ScoresInfoPtr{nullptr};

  QMenuBar* m_GameMenuBarPtr{nullptr};
  QMenu* m_GameFileMenuPtr{nullptr};
  QMenu* m_GameDifficultyMenuPtr{nullptr};
  QMenu* m_GameHelpMenuPtr{nullptr};
  QMenu* m_GameChangeMenuPtr{nullptr};

  QGridLayout* m_GridLayoutPtr{nullptr};
  QHBoxLayout* m_HorizontLayoutPtr{nullptr};
  QVBoxLayout* m_VerticalLayoutPtr{nullptr};

  QLibrary* m_HelperLibraryPtr{nullptr};

  f_get_random_number m_GetRandomNumberPtr{nullptr};
  f_read_line_from_file m_ReadLineFromFilePtr{nullptr};
  f_write_to_file m_WriteToFilePtr{nullptr};

  bool m_GameOver{false};

  BombsCount m_GameDifficulty{BombsCount::EASY};

  std::uint64_t m_CheckedFieldsCount{m_GameDifficulty};
  std::uint64_t m_CheckedFields3x3Count{};
  std::uint64_t m_VisibleCellsCount{};

  static constexpr std::uint64_t c_ROWS_COUNT{8};

  std::uint64_t m_RowsCount{c_ROWS_COUNT};
  std::uint64_t m_GameButtonsCount{m_RowsCount * m_RowsCount};

  std::uint64_t m_EasyBestScore{}, m_MediumBestScore{}, m_HardBestScore{};

  const std::string mc_SCORES_FILENAME{"scores.txt"};

  QMainWindow m_MainWindow;

  std::vector<std::uint64_t> m_FieldValuesArray;
  std::map<std::uint64_t, std::unique_ptr<PushButton>> m_GameMap;

  void f_process_3x3(const std::uint64_t& c_Index,
                     void (Sapper::*v_FunctionPtr)(const std::uint64_t&));

  QPushButton* f_create_button(const std::uint64_t& c_Index);

  void f_load_scores();
  void f_save_scores();

  void f_place_bombs();
  void f_add_bomb(const std::uint64_t& c_Index);

  void f_show_unckecked_fields(const std::uint64_t& c_Index);

  void f_win();
  void f_show_all_bombs();

  QLibrary* f_load_library(const QString& c_LibPath) const;

 public slots:
  void sf_create_game();

  void sf_add_time();

  void sf_create_easy_game();
  void sf_create_middle_game();
  void sf_create_hard_game();

  void sf_show_scores();
  void sf_about();
  void sf_change_menu_font();
  void sf_change_actions_font();
  void sf_change_color();

  void leftButtonClicked(const std::uint64_t& c_Index);
  void rightButtonClicked(const std::uint64_t& c_Index);
};

#endif  // SAPPER_HPP
