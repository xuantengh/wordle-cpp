# wordle-cpp
Terminal-based [WORDLE](https://www.powerlanguage.co.uk/wordle/) game written in cpp.

## Build

This project depends on `fmt` library and for colorful text output C++11 supported compiler.

```bash
# compiler
make
# run
./wordle ./wordle-answers-alphabetical.txt
```

## Screenshots

![](./assets/wordle.png)

## TODO

- Use `ncurses` TUI
- Refactor and simplify code