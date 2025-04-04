#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
  insert_at_tail(&(q->data), serialize(state));
}

struct game_state dequeue(struct queue *q) {
  return deserialize(remove_from_head(&(q->data)));
}

// Forward declaration for is_visited
bool is_visited(struct linked_list *visited, struct game_state state);

bool is_goal_state(struct game_state state) {
  int counter = 1;
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      if (state.tiles[row][col] != counter) {
        return false;
      }
      counter++;
      counter %= 16;
    }
  }
  return true;
}

int number_of_moves(struct game_state start) {
  struct queue q = {NULL};
  enqueue(&q, start);

  // Use a visited set to keep track of the states we've already encountered
  struct linked_list visited = {NULL};

  // Add the starting state to visited
  insert_at_head(&visited, serialize(start));

  while (q.data.head != NULL) {
    struct game_state current = dequeue(&q);

    // If the current state is the goal, return the number of moves
    if (is_goal_state(current)) {
      free_list(q.data);
      free_list(visited);
      return current.num_steps;
    }

    // Define the possible moves and the corresponding reverse operations
    struct game_state next_state;
    void (*moves[])(struct game_state*) = {move_up, move_down, move_left, move_right};

    for (int i = 0; i < 4; i++) {
      next_state = current;
      moves[i](&next_state);  // Apply the move

      // Only enqueue if this state has not been visited before
      if (!is_visited(&visited, next_state)) {
        next_state.num_steps = current.num_steps + 1;
        enqueue(&q, next_state);
        insert_at_head(&visited, serialize(next_state));
      }

      // Revert the move if it was applied
      if (i == 0) move_down(&next_state);  // Reverse move_up
      else if (i == 1) move_up(&next_state);  // Reverse move_down
      else if (i == 2) move_right(&next_state);  // Reverse move_left
      else if (i == 3) move_left(&next_state);  // Reverse move_right
    }
  }

  free_list(q.data);
  free_list(visited);
  return -1;
}

// Implementation of is_visited
bool is_visited(struct linked_list *visited, struct game_state state) {
  struct list_node *temp = visited->head;
  uint64_t serialized_state = serialize(state);
  while (temp != NULL) {
    if (temp->value == serialized_state) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}
