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
    auto actions = state->legal_actions;
  Move ans;
  Node* root=new Node;
  root->state=*state;
  root->state.get_legal_actions();
  buildtree(root,0);
  int val=minimax(root,0,true);
  //cout<<val<<endl;
  for(auto it:root->child)
  {
    //cout<<it->val<<endl;
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
    if(depth==4)
        return ;
    for(int i=0;i<(int)root->state.legal_actions.size();i++)
    {
        //cout<<root->state.legal_actions.size()<<endl;
        Node* tmp=new Node;
        tmp->state=*(root->state.next_state(root->state.legal_actions[i]));
        tmp->state.get_legal_actions();
        tmp->move=root->state.legal_actions[i];
        /*if(depth==2)
            tmp->val=tmp->state.evaluate();*/
        root->child.push_back(tmp);
        buildtree(tmp,depth+1);
    }
    
    return;
}

int Minimax::minimax(Node* root, int depth, bool maxplayer)
{
    //cout<<depth;
    if(depth==4)
    {
        if(depth%2==0)
            root->val=root->state.evaluate(); 
        else
            root->val=-root->state.evaluate();
        //cout<<root->val<<endl;
        return root->val;
    }
        
    if(maxplayer)
    {
        root->val=-10000000;
        for(auto it:root->child)
        {
            root->val=max(root->val,minimax(it,depth+1,false));
        }
        return root->val;
    }
    else 
    {
        root->val=10000000;
        for(auto it:root->child)
        {
            root->val=min(root->val,minimax(it,depth+1,true));
        }
        return root->val;
    }
}