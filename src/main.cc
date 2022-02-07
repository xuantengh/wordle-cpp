#include <string>

#include "game.h"

int main(int argc, char **argv) {
  std::string word_list_path("./sgb-words.txt");
  if (argc == 2) {
    word_list_path = argv[1];
  }
  wordle::Wordle game(word_list_path);
  game.BeginGame();
  return 0;
}