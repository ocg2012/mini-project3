#include <cstdlib>
#include<iostream>
#include <algorithm>
#include <cmath>
#include "../state/state.hpp"
#include "./minimax.hpp"
using namespace std;
Move m;
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
    //auto actions = state->legal_actions;
  Move ans;
  /*Node* root=new Node;
  root->state=*state;
  root->state.get_legal_actions();*/
  //buildtree(root,0);
  state->get_legal_actions();
  minimax2(state,depth,true,1);
  /*vector<State*> child;
  state->get_legal_actions();
  for(auto it:state->legal_actions)
  {
    State* nextstate=state->next_state(it);
    child.push_back(nextstate);
  }*/
  //cout<<val<<endl;
  /*for(auto it:child)
  {
    //cout<<it->val<<endl;
    if(it->val==val)
    {
        ans=it->move;
        //cout<<it->val<<endl;
        break;
    }
  }*/
  ans=m;
  return ans;
}
/*
void buildtree(Node* root,int depth)
{
    if(depth==1)
        return ;
    for(int i=0;i<(int)root->state.legal_actions.size();i++)
    {
        //cout<<root->state.legal_actions.size()<<endl;
        Node* tmp=new Node;
        tmp->state=*(root->state.next_state(root->state.legal_actions[i]));
        tmp->state.get_legal_actions();
        tmp->move=root->state.legal_actions[i]
        root->child.push_back(tmp);
        buildtree(tmp,depth+1);
    }
    
    return;
}

int Minimax::minimax(Node* root, int depth, bool maxplayer)
{
    //cout<<depth;
    if(depth==1)
    {
        if((depth%2==0&&root->state.player==0)||(depth%2==1&&root->state.player==1))
        {
            root->val=root->state.evaluate();
            //cout<<"AA"<<endl;
        }     
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
}*/

int Minimax::minimax2(State* state, int depth, bool maxplayer, int flag)
{
    if(depth==0)
    {
        if((maxplayer&&state->player==0)||(!maxplayer&&state->player==1))
        {
            state->val=state->evaluate2();
            //cout<<"AA"<<endl;
        }     
        else
            state->val=-state->evaluate2();
        /*if((depth%2==0&&state->player==0)||(depth%2==1&&state->player==1))
        {
            state->val=state->evaluate2();
            //cout<<"AA"<<endl;
        }     
        else
            state->val=-state->evaluate2();*/
        //cout<<root->val<<endl;
        return state->val;
    }  
    /*if(state->game_state==WIN)
    {
        if(maxplayer)
        {
            state->val=10000000state->evaluate();
            //cout<<"AA"<<endl;
        }     
        else
            state->val=-10000000state->evaluate();
        //cout<<root->val<<endl;
        cout<<"AA"<<endl;
        return state->val;
    }*/
    if(maxplayer)
    {
        state->val=-10000000;
        //state->get_legal_actions();
        for(auto it:state->legal_actions)
        {
            State* nextstate=state->next_state(it);
            //state->val=max(state->val,minimax2(nextstate,depth+1,false));
            nextstate->get_legal_actions();
            int nextval=minimax2(nextstate,depth-1,false,0);
            if(nextval>state->val)
            {
                state->val=nextval;
                if(flag==1)
                    m=it;
            }
        }
        return state->val;
    }
    else 
    {
        state->val=10000000;
        //state->get_legal_actions();
        for(auto it:state->legal_actions)
        {
            State* nextstate=state->next_state(it);
            nextstate->get_legal_actions();
            state->val=min(state->val,minimax2(nextstate,depth-1,true,0));
        }
        return state->val;
    }
}