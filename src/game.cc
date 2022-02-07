#include "game.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "fmt/core.h"
#include "fmt/color.h"


namespace wordle {
const int Wordle::kGuessTime = 6;
const int Wordle::kWordLenth = 5;
const int Wordle::kWordTableWidth = 11;

Wordle::Wordle(const std::string& word_list_path) {
  try {
    std::ifstream ifs(word_list_path);
    if (ifs.fail()) {
      throw std::invalid_argument(
          fmt::format("Could not open file: {}", word_list_path));
    }

    std::string word;
    while (ifs >> word) {
      this->word_list_.push_back(word);
    }
    fmt::print("Word list length: {}\n", this->word_list_.size());
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Exit..." << std::endl;
    exit(EXIT_FAILURE);
  }
}

int Wordle::size() { return this->word_list_.size(); }

void Wordle::BeginGame() {
  srand(time(NULL));
  int answer_index = rand() % this->size();
  answer_ = word_list_[answer_index];

#ifdef DEBUG
  fmt::print("The answer word is: {}\n", answer_);
#endif

  std::string input;
  bool hit = false;
  for (int i = 0; i < kGuessTime; ++i) {
    ShowWordsTable();
    while (true) {
      fmt::print("[{}] Please type the word you guessed: ", i + 1);
      std::cin >> input;
      if (input.size() != kWordLenth) {
        fmt::print("[-] Invalid input, please type again.\n");
      } else {
        break;
      }
    }
    guessed_words_.push_back(input);
    if (input == answer_) {
      fmt::print("[+] Hit! The answer is: {}\n", answer_);
      hit = true;
      break;
    }
  }
  if (hit == false) {
    fmt::print("[-] You failed to figure out the target. The answer is: {}\n",
               answer_);
  }
}

void Wordle::ShowWordsTable() {
  for (const std::string& word : guessed_words_) {
    fmt::print("{:^{}}\n", word, kWordTableWidth);
  }
}

};  // namespace wordle