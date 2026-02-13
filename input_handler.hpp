#pragma once
#include <memory>
#include <termios.h>
#include <chrono>
#include "actions.hpp"

class InputHandler {
public:
  InputHandler();
  ~InputHandler();
  std::unique_ptr<Action> handle_input();

private:
  struct termios original_termios;
  std::chrono::steady_clock::time_point last_input_time;
  const std::chrono::milliseconds input_delay{100}; // 100ms delay between moves
};
