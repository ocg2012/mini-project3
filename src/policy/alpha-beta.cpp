#include <cstdlib>
#include<iostream>
#include <algorithm>
#include <cmath>
#include "../state/state.hpp"
#include "./alpha-beta.hpp"
using namespace std;
Move m1;
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBeta::get_move(State *state, int depth){
   //auto actions = state->legal_actions;
   Move ans;
  /*Node* root=new Node;
  root->state=*state;
  root->state.get_legal_actions();
  Buildtree(root,0);
  
  //cout<<val<<endl;
  for(auto it:root->child)
  {
    //cout<<it->val<<endl;
    if(it->val==val)
    {
        ans.push_back(it->move);
        //cout<<it->val<<endl;
        break;
    }
  }*/
  alpha_beta2(state,0,-10000000,10000000,true,1);
  ans=m1;
  return ans;//ans[rand()%ans.size()];
}

void Buildtree(Node* root,int depth)
{
    if(depth==3)
        return ;
    for(int i=0;i<(int)root->state.legal_actions.size();i++)
    {
        //cout<<root->state.legal_actions.size()<<endl;
        Node* tmp=new Node;
        tmp->state=*(root->state.next_state(root->state.legal_actions[i]));
        tmp->state.get_legal_actions();
        tmp->move=root->state.legal_actions[i];
        root->child.push_back(tmp);
        Buildtree(tmp,depth+1);
    }
    
    return;
}

int AlphaBeta::alpha_beta(Node* root, int depth, int alpha, int beta, bool maxplayer)
{
    //cout<<depth;
    if(depth==3)
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
        root->val=-100000000;
        for(auto it:root->child)
        {
            root->val=max(root->val,alpha_beta(it,depth+1,alpha,beta,false));
            alpha=max(alpha,root->val);
            if(alpha>=beta)
            {
                //cout<<"BB"<<endl;
                break;
            }
                
        }
        return root->val;
    }
    else 
    {
        root->val=100000000;
        for(auto it:root->child)
        {
            root->val=min(root->val,alpha_beta(it,depth+1,alpha,beta,true));
            beta=min(beta,root->val);
            if(beta<=alpha)
            {
                //cout<<"AA"<<endl;
                break;
            }
                
        }
        return root->val;
    }
}

int AlphaBeta::alpha_beta2(State* state, int depth, int alpha, int beta, bool maxplayer, int flag)
{
    if(depth==6)
    {
        if((depth%2==0&&state->player==0)||(depth%2==1&&state->player==1))
        {
            state->val=state->evaluate();
            //cout<<"AA"<<endl;
        }     
        else
            state->val=-state->evaluate();
        //cout<<root->val<<endl;
        return state->val;
    }  
    /*if(state->game_state==WIN)
    {
        if((depth%2==0&&state->player==0)||(depth%2==1&&state->player==1))
        {
            state->val=state->evaluate();
            //cout<<"AA"<<endl;
        }     
        else
            state->val=-state->evaluate();
        //cout<<root->val<<endl;
        //cout<<"AA"<<endl;
        return state->val;
    }*/
    if(maxplayer)
    {
        state->val=-10000000;
        //state->get_legal_actions();
        for(auto it:state->legal_actions)
        {
            State* nextstate=state->next_state(it);
            int nextval=alpha_beta2(nextstate,depth+1, alpha, beta,false,0);
            if(nextval>state->val)
            {
                state->val=nextval;
                if(flag==1)
                    m1=it;
            }
            alpha=max(alpha,state->val);
            if(alpha>=beta)
            {
                //cout<<"BB"<<endl;
                break;
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
            state->val=min(state->val,alpha_beta2(nextstate,depth+1, alpha, beta,true,0));
            beta=min(beta,state->val);
            if(beta<=alpha)
            {
                //cout<<"AA"<<endl;
                break;
            }
        }
        return state->val;
    }
}