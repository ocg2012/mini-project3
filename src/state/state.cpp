#include <iostream>
#include <sstream>
#include <cstdint>

#include "./state.hpp"
#include "../config.hpp"

using namespace std;

/*static const int SafetyTable[100] = {
    0,  0,   1,   2,   3,   5,   7,   9,  12,  15,
  18,  22,  26,  30,  35,  39,  44,  50,  56,  62,
  68,  75,  82,  85,  89,  97, 105, 113, 122, 131,
 140, 150, 169, 180, 191, 202, 213, 225, 237, 248,
 260, 272, 283, 295, 307, 319, 330, 342, 354, 366,
 377, 389, 401, 412, 424, 436, 448, 459, 471, 483,
 494, 500, 500, 500, 500, 500, 500, 500, 500, 500,
 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
 500, 500, 500, 500, 500, 500, 500, 500, 500, 500
};*/

static const int SafetyTable[6][5] = {
  {0,0,1,2,3},
  {8,13,17,25,39},
  {55,62,75,82,97},
  {131,150,169,178},
  {224,260,279,288,300},
  {300,300,300,300,300},
};
 /*  private static final int[] PAWN_PST = {
             0,  0,   0,   0,   0,   0,  0,  0,
            50, 50,  50,  50,  50,  50, 50, 50,
            10, 10,  20,  30,  30,  20, 10, 10,
             5,  5,  10,  25,  25,  10,  5,  5,
             0,  0,   0,  20,  20,   0,  0,  0,
             5, -5, -10,   0,   0, -10, -5,  5,
             5, 10,  10, -20, -20,  10, 10,  5,
             0,  0,   0,   0,   0,   0,  0,  0
    };*/
static const int W_Pawntable[6][5]={
  {0,0,0,0,0},
  {50,50,50,50,50},
  {10,15,25,15,10},
  {0,0,20,0,0},
  {5,-15,0,-15,5},
  {0,0,0,0,0}
};

static const int W_Rooktable[6][5]={
  {0,0,0,0,0},
  {5,10,10,10,5},
  {-5,0,0,0,-5},
  {-5,0,0,0,-5},
  {-5,0,0,0,-5},
  {0,0,0,5,5}
};
static const int W_Bishoptable[6][5]={
  {-10,-10,-10,-10,-20},
  {-10,0,0,0,-10},
  {-10,5,10,10,-10},
  {-10,10,10,10,-10},
  {-10,5,0,0,0},
  {-20,-10,-10,-10,-10}
};
static const int W_Knighttable[6][5]={
  {-50,-40,-30,-40-50},
  {-40,-20,5,-20,-40},
  {-30,5,20,5,-30},
  {-10,5,20,5,-30},
  {-40,-20,5,-10,-40},
  {-50,-40,-30,-40,-50}
};
static const int W_Queentable[6][5]={
  {-10,0,-5,-5,-10},
  {-5,0,5,0,-10},
  {0,5,5,5,-10},
  {-10,5,5,5,-10},
  {-10,0,5,0,-10},
  {-10,-5,-5,0,-10}
};
static const int W_Kingtable[6][5]={
  {-30,-40,-50,-40,-30},
  {-30,-40,-50,-40,-30},
  {-30,-40,-50,-40,-30},
  {-10,-20,-30,-20,-30},
  {10,10,-5,10,10},
  {10,20,30,20,10}
};

static const int B_Pawntable[6][5]={
  {0,0,0,0,0},
  {5,-15,0,-15,5},
  {0,0,20,0,0},
  {10,15,25,15,10},
  {50,50,50,50,50},
  {0,0,0,0,0}
};

static const int B_Rooktable[6][5]={
  {5,5,0,0,0},
  {-5,0,0,0,-5},
  {-5,0,0,0,-5},
  {-5,0,0,0,-5},
  {-5,10,10,10,5},
  {0,0,0,0,0}
};
static const int B_Bishoptable[6][5]={
  {-10,-10,-10,-10,-20},
  {0,0,0,5,-10},
  {-10,10,10,10,-10},
  {-10,10,10,5,-10},
  {-10,0,0,0,-10},
  {-20,-10,-10,-10,-10}
};
static const int B_Knighttable[6][5]={
  {-50,-40,-30,-40-50},
  {-40,-10,5,-20,-40},
  {-30,5,20,5,-10},
  {-30,5,20,5,-30},
  {-40,-20,5,-20,-40},
  {-50,-40,-30,-40,-50}
};
static const int B_Queentable[6][5]={
  {-10,0,-5,-5,-10},
  {-10,0,5,0,-10},
  {-10,5,5,5,-10},
  {-10,5,5,5,0},
  {-10,0,5,0,-5},
  {-10,-5,-5,-0,-10}
};
static const int B_Kingtable[6][5]={
  {10,20,30,20,10},
  {10,10,-5,10,10},
  {-10,-20,-30,-20,-30},
  {-30,-40,-50,-40,-30},
  {-30,-40,-50,-40,-30},
  {-30,-40,-50,-40,-30}
};

static const int material_table[7] = {0, 2, 6, 7, 8, 20, 100};
/**
 * @brief evaluate the state
 * 
 * @return int 
 */
int State::evaluate(){
  // [TODO] design your own evaluation function
  int sum=0,sum1=0,materialval;

  for(int i=0;i<BOARD_H;i++)
  {
    for(int j=0;j<BOARD_W;j++)
    {
      sum+=material_table[this->board.board[0/*this->player*/][i][j]]*100 ;
      
    }
  }
  for(int i=0;i<BOARD_H;i++)
  {
    for(int j=0;j<BOARD_W;j++)
    {
      sum1+=material_table[this->board.board[1/*-this->player*/][i][j]]*100 ;
      
    }
  }
  //cout<<this->player<<endl;
  materialval=sum-sum1;
  /*for(int i=0;i<BOARD_H;i++)
  {
    for(int j=0;j<BOARD_W;j++)
    {
      if(this->board.board[0][i][j]==1)
      {
        w_posval+=material_table[1]*W_Pawntable[i][j];
      }
      else if(this->board.board[0][i][j]==2)
      {
        
        w_posval+=material_table[2]*W_Rooktable[i][j];
      }
      else if(this->board.board[0][i][j]==3)
      {
        w_posval+=material_table[3]*W_Knighttable[i][j];
        
      }
      else if(this->board.board[0][i][j]==4)
      {
        w_posval+=material_table[4]*W_Bishoptable[i][j];
        
      }
      else if(this->board.board[0][i][j]==5)
      {
        w_posval+=material_table[5]*W_Queentable[i][j]; 
      }
      else if(this->board.board[0][i][j]==6)
      {
        w_posval+=material_table[5]*W_Kingtable[i][j];
      }

      if(this->board.board[1][i][j]==1)
      {
        b_posval+=material_table[1]*B_Pawntable[i][j];
      }
      else if(this->board.board[1][i][j]==2)
      {
        
        b_posval+=material_table[2]*B_Rooktable[i][j];
      }
      else if(this->board.board[1][i][j]==3)
      {
        b_posval+=material_table[3]*B_Knighttable[i][j];
        
      }
      else if(this->board.board[1][i][j]==4)
      {
        b_posval+=material_table[4]*B_Bishoptable[i][j];
        
      }
      else if(this->board.board[1][i][j]==5)
      {
        b_posval+=material_table[5]*B_Queentable[i][j]; 
      }
      else if(this->board.board[1][i][j]==6)
      {
        b_posval+=material_table[5]*B_Kingtable[i][j];
      }
    }
  }
  posval=w_posval-b_posval;*/

  return materialval/*+posval*/;
  
}

int State::evaluate2(){
  // [TODO] design your own evaluation function
  int sum=0,sum1=0,materialval,posval,w_posval=0,b_posval=0;

  for(int i=0;i<BOARD_H;i++)
  {
    for(int j=0;j<BOARD_W;j++)
    {
      sum+=material_table[this->board.board[0/*this->player*/][i][j]]*50 ;
      
    }
  }
  for(int i=0;i<BOARD_H;i++)
  {
    for(int j=0;j<BOARD_W;j++)
    {
      sum1+=material_table[this->board.board[1/*-this->player*/][i][j]]*50 ;
      
    }
  }
  //cout<<this->player<<endl;
  materialval=sum-sum1;
  for(int i=0;i<BOARD_H;i++)
  {
    for(int j=0;j<BOARD_W;j++)
    {
      if(this->board.board[0][i][j]==1)
      {
        w_posval+=material_table[1]*W_Pawntable[i][j];
      }
      /*else if(this->board.board[0][i][j]==2)
      {
        
        w_posval+=material_table[2]*W_Rooktable[i][j];
      }
      else if(this->board.board[0][i][j]==3)
      {
        w_posval+=material_table[3]*W_Knighttable[i][j];
        
      }
      else if(this->board.board[0][i][j]==4)
      {
        w_posval+=material_table[4]*W_Bishoptable[i][j];
        
      }
      else if(this->board.board[0][i][j]==5)
      {
        w_posval+=material_table[5]*W_Queentable[i][j]; 
      }*/
      else if(this->board.board[0][i][j]==6)
      {
        w_posval+=material_table[5]*W_Kingtable[i][j];
      }

      if(this->board.board[1][i][j]==1)
      {
        b_posval+=material_table[1]*B_Pawntable[i][j];
      }
      /*else if(this->board.board[1][i][j]==2)
      {
        
        b_posval+=material_table[2]*B_Rooktable[i][j];
      }
      else if(this->board.board[1][i][j]==3)
      {
        b_posval+=material_table[3]*B_Knighttable[i][j];
        
      }
      else if(this->board.board[1][i][j]==4)
      {
        b_posval+=material_table[4]*B_Bishoptable[i][j];
        
      }
      else if(this->board.board[1][i][j]==5)
      {
        b_posval+=material_table[5]*B_Queentable[i][j]; 
      }*/
      else if(this->board.board[1][i][j]==6)
      {
        b_posval+=material_table[5]*B_Kingtable[i][j];
      }
    }
  }
  posval=w_posval-b_posval;

  return materialval+posval;
  
}

/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}