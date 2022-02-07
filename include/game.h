#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace wordle {
class KeyBoardInfo {
 public:
  KeyBoardInfo();
  KeyBoardInfo(const KeyBoardInfo&) = delete;

  static const std::vector<std::string> kKeyboard;

  std::set<char> matched_letters;
  std::set<char> include_letters;
  std::set<char> exclude_letters;
  std::set<char> unknown_letters;
};

class Wordle {
 public:
  Wordle(const std::string&);
  Wordle(const Wordle&) = delete;

  int size();
  void BeginGame();

 private:
  static const int kGuessTime;
  static const int kWordLenth;
  static const int kWordTableWidth;
  std::vector<std::string> word_list_;
  std::string answer_;
  std::unordered_map<char, int> answer_letter_;
  std::vector<std::string> guessed_words_;
  KeyBoardInfo keyboard_info_;

  void ShowWordsTable();
  void ShowKeyBoard();
  void UpdateKeyBoard(const std::string&);
};

};  // namespace wordle