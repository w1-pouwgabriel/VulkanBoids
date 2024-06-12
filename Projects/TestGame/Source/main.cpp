#include <stdio.h>
#include <string.h>
#include <chrono>

#include "./Engine.h"

const int width = 120, height = 44; // Width and height of the terminal window
char buffer[width * 44]; // Buffer for storing ASCII characters
int backgroundASCIICode = ' '; // ASCII character for the background

int main() 
{
  printf("\x1b[2J"); // Clear the screen

  foo f;

  auto previous = std::chrono::system_clock::now();
  std::time_t t_p = std::chrono::system_clock::to_time_t(previous);

  while (1) {
    printf("\x1b[2J"); // Clear the screen

    printf("\x1b[H"); // Move the cursor to (0, 0)

    printf("Hello");
  }

  glm::vec3 a = {0,0,0};

  return 0;
}