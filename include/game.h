#include <string>
#include <vector>

namespace wordle {
class Wordle {
 public:
  Wordle(const std::string&);

  int size();
  void begin();

 private:
  std::vector<std::string> word_list;
  std::string answer;
};
};  // namespace wordle