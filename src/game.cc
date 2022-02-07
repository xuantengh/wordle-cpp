#include "game.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

#include "fmt/core.h"

namespace wordle {
Wordle::Wordle(const std::string& word_list_path) {
  try {
    std::ifstream ifs(word_list_path);
    if (ifs.fail()) {
      throw std::invalid_argument(
          fmt::format("Could not open file: {}", word_list_path));
    }

    std::string word;
    while (ifs >> word) {
      this->word_list.push_back(word);
    }
    fmt::print("Word list length: {}\n", this->word_list.size());
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Exit..." << std::endl;
    exit(EXIT_FAILURE);
  }
}

int Wordle::size() { return this->word_list.size(); }

void Wordle::begin() {
  srand(time(NULL));
  int answer_index = rand() % this->size();
  answer = word_list[answer_index];

  fmt::print("The answer word is: {}\n", answer);
}

};  // namespace wordle