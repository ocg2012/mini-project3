#pragma once
#include "../state/state.hpp"
#include <vector>
using namespace std;

/*struct Node{
    State state;
    Move move;
    int val;
    vector<Node*> child;
};*/
//void Buildtree(Node* root,int depth);
/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class AlphaBeta3{
public:
  static Move get_move(State *state, int depth);
 // static int alpha_beta(Node* node, int depth, int alpha, int beta, bool maxplayer);
  static int alpha_beta2(State* state, int depth, int alpha, int beta, bool maxplayer, int flag);
};



