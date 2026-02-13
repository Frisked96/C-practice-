#include "input_handler.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/select.h>

InputHandler::InputHandler() : last_input_time(std::chrono::steady_clock::now()) {
  tcgetattr(STDIN_FILENO, &original_termios);
  struct termios raw = original_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

InputHandler::~InputHandler() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

std::unique_ptr<Action> InputHandler::handle_input() {
  // Since we are turn-based and want zero CPU, we don't need the timing check here anymore
  // because the OS will wake us up only when a key is pressed.

  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);

  // Passing NULL for timeout makes select block indefinitely
  if (select(STDIN_FILENO + 1, &fds, NULL, NULL, NULL) > 0) {
    char input;
    read(STDIN_FILENO, &input, 1);

    switch (input) {
      case 'w': return std::make_unique<MoveAction>(0, -1);
      case 's': return std::make_unique<MoveAction>(0, 1);
      case 'a': return std::make_unique<MoveAction>(-1, 0);
      case 'd': return std::make_unique<MoveAction>(1, 0);
      case 'q': return std::make_unique<QuitAction>();
    }
  }
  return nullptr;
}
