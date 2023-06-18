#include <cstdlib>
#include<iostream>
#include <algorithm>
#include <cmath>
#include "../state/state.hpp"
#include "./minimax.hpp"
using namespace std;

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  Move ans;
  Node* root=new Node;
  root->state=*state;
  buildtree(root,depth);
  int val=minimax(root,depth,true);
  for(auto it:root->child)
  {
    if(it->val==val)
    {
        ans=it->move;
        //cout<<it->val<<endl;
        break;
    }
        
  }
  return ans;
}

void buildtree(Node* root,int depth)
{
    depth++;
    if(depth==3)
        return ;
    for(int i=0;i<root->state.legal_actions.size();i++)
    {
        //cout<<i<<endl;
        Node* tmp=new Node;
        tmp->state=*(root->state.next_state(root->state.legal_actions[i]));
        tmp->move=root->state.legal_actions[i];
        tmp->val=tmp->state.evaluate();
        root->child.push_back(tmp);
        buildtree(tmp,depth);
    }
}

int Minimax::minimax(Node* root, int depth, bool maxplayer)
{
    if(depth==3)
        return root->val;
    if(maxplayer)
    {
        int val=-10000000;
        for(auto it:root->child)
        {
            val=max(val,minimax(it,++depth,false));
        }
        return val;
    }
    else
    {
        int val=10000000;
        for(auto it:root->child)
        {
            val=min(val,minimax(it,++depth,true));
        }
        return val;
    }
}