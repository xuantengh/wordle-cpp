#include "game.h"

int main() {
  wordle::Wordle game("./sgb-words.txt");
  game.begin();
  return 0;
}