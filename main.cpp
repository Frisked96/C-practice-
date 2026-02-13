#include "engine.hpp"
#include <unistd.h>

int main() {
  Engine engine;
  engine.init();

  while (engine.is_running()) {
    engine.render();
    engine.update();
  }

  return 0;
}
