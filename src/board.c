#include "includes/board.h"

void board_update(Board **board, Snake **snake) {
  Board *b = *board;

  char tile = TILE_SNAKE_HEAD_CHAR;
  if (snake != NULL) {
    Snake *s = *snake;

    // pop snake end
    SnakeBody *current = s->body;
    while (current != NULL) {
      if (current->next != NULL) {
        current = current->next;
        continue;
      }

      if (current->prev != NULL) {
        current->prev->next = NULL;
        b->lines[current->y][current->x] = TILE_EMPTY_CHAR;
        free(current);
      }

      break;
    }

    SnakeBody *new_head = malloc(sizeof(SnakeBody));
    SnakeBody *head = s->body;
    new_head->x = head->x;
    new_head->y = head->y;

    s->body->prev = new_head;
    new_head->next = &*s->body;

    switch (s->direction) {
    case SNAKE_LEFT: {
      if (head->x == 0) {
        Panic("Game over! snake hit left wall\n");
      }

      new_head->x = head->x - 1;
    } break;
    case SNAKE_RIGHT: {
      if (head->x == b->cols - 1) {
        Panic("Game over! snake hit right wall\n");
      }

      new_head->x = head->x + 1;
    } break;
    case SNAKE_UP: {
      if (head->y == 0) {
        Panic("Game over! snake hit top wall\n");
      }

      new_head->y = head->y - 1;
    } break;
    case SNAKE_DOWN: {
      if (head->y == b->rows - 1) {
        Panic("Game over! snake hit bottom wall\n");
      }

      new_head->y = head->y + 1;
    } break;
    }

    current = new_head->next;
    while (current != NULL) {
      unsigned int current_x = current->x;
      unsigned int head_x = new_head->x;
      if (new_head->x == current->x) {
        if (new_head->y == current->y) {
          Panic("Game over! snake hit self {x: %d, y: %d}\n", head_x,
                current_x);
        }
      }

      current = current->next;
    }

    s->body = new_head;

    current = s->body;
    while (current != NULL) {
      b->lines[current->y][current->x] = tile;
      current = current->next;
      tile = TILE_SNAKE_BODY_CHAR;
    }
  }

  // draw fruits
}

Board *board_init(unsigned int cols, unsigned int rows) {
  Board *board = malloc(sizeof(Board));
  board->rows = rows;
  board->cols = cols;

  board->lines = malloc(sizeof(char *));

  for (unsigned int row = 0; row < rows; ++row) {
    unsigned int size = cols + 1;
    board->lines[row] = malloc(sizeof(char) * size);

    for (unsigned int col = 0; col < board->cols; ++col) {
      board->lines[row][col] = TILE_EMPTY_CHAR;
    }
    board->lines[row][cols] = '\n';
  }

  board_update(&board, NULL);

  return board;
}
