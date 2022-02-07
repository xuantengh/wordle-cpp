#include <string>
#include <vector>

namespace wordle {
class Wordle {
 public:
  Wordle(const std::string&);

  int size();
  void BeginGame();

 private:
  static const int kGuessTime;
  static const int kWordLenth;
  static const int kWordTableWidth;
  std::vector<std::string> word_list_;
  std::string answer_;
  std::vector<std::string> guessed_words_;  

  void ShowWordsTable();
};
};  // namespace wordle