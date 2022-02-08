#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace wordle {
class KeyBoardInfo {
 public:
  KeyBoardInfo();
  KeyBoardInfo(const KeyBoardInfo&) = delete;

  void ShowKeyBoard();

  void match(const char);
  void include(const char);
  void exclude(const char);

  static const std::vector<std::string> kKeyboard;

 private:
  std::set<char> matched_letters_;
  std::set<char> include_letters_;
  std::set<char> exclude_letters_;
  std::set<char> unknown_letters_;
};

class Wordle {
 public:
  Wordle(const std::string&);
  ~Wordle();
  Wordle(const Wordle&) = delete;

  int size();
  void BeginGame();

 private:
  static const int kGuessTime;
  static const int kWordLenth;
  static const int kWordTableWidth;
  static const int kWordTableHeight;
  static const int kWindowWidth;
  static const int kWindowHeight;
  std::vector<std::string> word_list_;
  std::string answer_;
  std::unordered_map<char, int> answer_letter_;
  std::vector<std::string> guessed_words_;
  KeyBoardInfo keyboard_info_;

  void ShowWordsTable();
  void UpdateKeyBoard(const std::string&);
};

};  // namespace wordle