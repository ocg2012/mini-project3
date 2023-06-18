#pragma once
#include "../state/state.hpp"
#include <vector>
using namespace std;

struct Node{
    State state;
    Move move;
    int val;
    vector<Node*> child;
};
void buildtree(Node* root,int depth);
/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Minimax{
public:
  static Move get_move(State *state, int depth);
  static int minimax(Node* node, int depth, bool maxplayer);
};



