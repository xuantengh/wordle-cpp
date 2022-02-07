#include "game.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "fmt/color.h"
#include "fmt/core.h"

namespace wordle {
const int Wordle::kGuessTime = 6;
const int Wordle::kWordLenth = 5;
const int Wordle::kWordTableWidth = 11;

const std::vector<std::string> KeyBoardInfo::kKeyboard = {
    "qwertyuiop", "asdfghjkl", "zxcvbnm"};

Wordle::Wordle(const std::string& word_list_path) {
  try {
    std::ifstream ifs(word_list_path);
    if (ifs.fail()) {
      throw std::invalid_argument(
          fmt::format("Could not open file: {}", word_list_path));
    }

    std::string word;
    while (ifs >> word) {
      word_list_.push_back(word);
    }
#ifdef DEBUG
    fmt::print("Word list length: {}\n", word_list_.size());
#endif
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Exit..." << std::endl;
    exit(EXIT_FAILURE);
  }
}

int Wordle::size() { return word_list_.size(); }

void Wordle::BeginGame() {
  srand(time(NULL));
  int answer_index = rand() % size();
  answer_ = word_list_[answer_index];
  for (const char c : answer_) {
    answer_letter_[c]++;
  }

#ifdef DEBUG
  fmt::print("The answer word is: {}\n", answer_);
#endif

  std::string input;
  bool hit = false;
  for (int i = 0; i < kGuessTime; ++i) {
    ShowWordsTable();
    ShowKeyBoard();
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
    auto answer_letter(answer_letter_);
    for (int i = 0; i < word.size(); ++i) {
      fmt::detail::color_type color;
      if (word[i] == answer_[i]) {
        color = fmt::color::green;
        answer_letter[word[i]]--;
        keyboard_info_.matched_letters.insert(word[i]);
        keyboard_info_.unknown_letters.erase(word[i]);
        keyboard_info_.include_letters.erase(word[i]);
      } else {
        if (answer_letter.find(word[i]) != answer_letter.end() &&
            answer_letter[word[i]] > 0) {  // answer contains word[i]
          color = fmt::color::orange;
          answer_letter[word[i]]--;
          if (keyboard_info_.matched_letters.find(word[i]) ==
              keyboard_info_.matched_letters.end()) {
            keyboard_info_.include_letters.insert(word[i]);
          }
          keyboard_info_.unknown_letters.erase(word[i]);
        } else {
          color = fmt::color::gray;
          if (keyboard_info_.include_letters.find(word[i]) ==
                  keyboard_info_.include_letters.end() &&
              keyboard_info_.matched_letters.find(word[i]) ==
                  keyboard_info_.matched_letters.end()) {
            keyboard_info_.exclude_letters.insert(word[i]);
          }
          keyboard_info_.unknown_letters.erase(word[i]);
        }
      }
      fmt::print(fmt::fg(color), "{} ", word[i]);
    }
    fmt::print("\n");
  }
}

KeyBoardInfo::KeyBoardInfo() {
  for (const std::string& row : kKeyboard) {
    for (const char c : row) {
      unknown_letters.insert(c);
    }
  }
}

void Wordle::ShowKeyBoard() {
  fmt::print("{:-^25}\n", "");
  for (const std::string& row : keyboard_info_.kKeyboard) {
    for (const char c : row) {
      fmt::detail::color_type color = fmt::color::black;
      if (keyboard_info_.exclude_letters.find(c) !=
          keyboard_info_.exclude_letters.end()) {
        color = fmt::color::gray;
      } else if (keyboard_info_.include_letters.find(c) !=
                 keyboard_info_.include_letters.end()) {
        color = fmt::color::orange;
      } else if (keyboard_info_.matched_letters.find(c) !=
                 keyboard_info_.matched_letters.end()) {
        color = fmt::color::green;
      }
      fmt::print(fmt::fg(color), "{} ", c);
    }
    fmt::print("\n");
  }
}

};  // namespace wordle