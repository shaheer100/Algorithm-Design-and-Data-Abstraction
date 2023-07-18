/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// no one.
//
// Name: shaheer
// login ID: ssheeraz
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "team.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THIS REGION OF CODE
const int TEAM_INVALID_ID = -1;
const struct team team_empty = {TEAM_INVALID_ID}; // Doesn't set players to empty_player
                                                  // Must be done by team_init_empty

// DO NOT CHANGE THESE
// Reasons for failures
const int FAIL_INSUFFICIENT_FUNDS = -1;
const int FAIL_ROSTER_FULL = -2;

// DO NOT CHANGE THIS FUNCTION
void team_print(struct team *t) {
  assert(t);
  assert(team_player_value(t) + team_cash(t) == team_value(t));
  printf("Team %d : ", team_get_id(t));

  if ((t->p1.player_id != PLAYER_INVALID_ID) && (t->p2.player_id != PLAYER_INVALID_ID)) {
    if (t->p1.player_id < t->p2.player_id) {
      player_print(&t->p1);
      player_print(&t->p2);
    } else {
      player_print(&t->p2);
      player_print(&t->p1);
    }
  } else {
    if (t->p1.player_id != PLAYER_INVALID_ID) {
      player_print(&t->p1);
    }
    if (t->p2.player_id != PLAYER_INVALID_ID) {
      player_print(&t->p2);
    }
  }

  printf("player value = %d cash = %d", team_player_value(t), team_cash(t));
  printf("\n");
}
// END OF DO NOT CHANGE REGION
// -----------------------------------------------------------------------

// FOR DOCUMENTATION, see team.h

int team_player_value(struct team *t) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  return t->p1.value + t->p2.value;
}

int team_value(struct team *t) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  return team_player_value(t) + t->cash_available;
}

int team_cash(struct team *t) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  return t->cash_available;
}

void team_init_empty(struct team *t) {
  assert(t);
  t->team_id = TEAM_INVALID_ID;
  t->cash_available = 0;
  t->p1 = player_empty;
  t->p2 = player_empty;
}

void team_setup(struct team *t, int id, int cash) {
  assert(t);
  assert(t->team_id == TEAM_INVALID_ID);
  assert(t->p1.player_id == PLAYER_INVALID_ID);
  assert(t->p2.player_id == PLAYER_INVALID_ID);
  assert(id >= 0);
  assert(cash >= 0);
  t->team_id = id;
  t->cash_available = cash;
}

int team_get_id(struct team *t) {
  assert(t);
  return t->team_id;
}

bool team_is_player_on(struct team *t, int id) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  assert(id >= 0);
  return (t->p1.player_id == id) || (t->p2.player_id == id);
}

bool team_add_player(struct team *t, int id, int val, struct reason *r) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  assert(id >= 0);
  assert(val >= 0);
  assert(team_is_player_on(t, id) == false);
  assert(r);
  if ((t->p1.player_id != PLAYER_INVALID_ID) && 
      (t->p2.player_id != PLAYER_INVALID_ID)) {
    r->code = FAIL_ROSTER_FULL;
    r->team_num = t->team_id;
    return false;
  }
  else if (t->cash_available < val){
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t->team_id;
    return false;
  }
  else {
    if (t->p1.player_id == PLAYER_INVALID_ID){
      t->p1.player_id = id;
    }
    else if (t->p2.player_id == PLAYER_INVALID_ID) {
      t->p2.player_id = id;
      t->p2.value = val;
    }
    t->cash_available -= val; 
    return true; 
  }
}

//not done tests
bool team_sell_player(struct team *t1, int id, struct team *t2,
     struct reason *r) {
  assert(t1);
  assert(t2);
  assert(t1->team_id != TEAM_INVALID_ID);
  assert(t2->team_id != TEAM_INVALID_ID);
  assert(team_is_player_on(t1, id) == true);
  assert(team_is_player_on(t2, id) == false);
  assert(r);
  assert(id >= 0);
  assert(t1 != t2);
  
  //checking which player matches the id, and assigns that to val.
  int val = 0;
  if (t1->p1.player_id == id) {
    val = t1->p1.value;
  } else if (t1->p2.player_id == id) {
    val = t1->p2.value;
  }
  
  if ((t2->p1.player_id != PLAYER_INVALID_ID) && 
      (t2->p2.player_id != PLAYER_INVALID_ID)) {
    r->code = FAIL_ROSTER_FULL;
    r->team_num = t2->team_id;
    return false;
  }
  else if (t2->cash_available < val){
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t2->team_id;
    return false;
  }
  else {
    if (team_add_player(t2, id, val, r)){
      t1->cash_available += val;
      if (t1->p1.player_id == id) {
        t1->p1 = player_empty;
      } else {
        t1->p2 = player_empty;
      }
      return true; 
    }
    else {
      return false;
    }
  }
}

bool team_trade_players(struct team *t1, int id1, struct team *t2, int id2,
     struct reason *r) {
  assert(t1);
  assert(t2);
  assert(t1->team_id != TEAM_INVALID_ID);   
  assert(t2->team_id != TEAM_INVALID_ID); 
  assert(team_is_player_on(t1, id1) == true); 
  assert(team_is_player_on(t2, id2) == true); 
  assert(r); 
  assert(id1 >= 0); 
  assert(id2 >= 0);  
  assert(t1 != t2); 
  assert(t1->team_id != -1);
  assert(t2->team_id != -1);
  assert(t1->team_id != t2->team_id);
  bool is_p1_t1 = 0; 
  bool is_p1_t2 = 0; 
  int val_t1 = 0;  
  int val_t2 = 0;   
  
  // figuring out which player (1 or 2) will be swapped from each team
  if (t1->p1.player_id == id1) { 
    val_t1 = t1->p1.value;    
    is_p1_t1 = 1;  
  } else if (t1->p2.player_id == id1) {  
    val_t1 = t1->p2.value;   
    is_p1_t1 = 0;  
  }
  if (t2->p1.player_id == id2) {    
    val_t2 = t2->p1.value; 
    is_p1_t2 = 1;  
  } else if (t2->p2.player_id == id2) {    
    val_t2 = t2->p2.value;    
    is_p1_t2 = 0;  
  }    

  // cash requirements
  if (!(t1->cash_available - (val_t2 - val_t1) >= 0)) { 
    r->team_num = t1->team_id; 
    r->code = FAIL_INSUFFICIENT_FUNDS;     
    return false; 
  }  
  if (!(t2->cash_available - (val_t1 - val_t2) >= 0)) {  
    r->team_num = t2->team_id;    
    r->code = FAIL_INSUFFICIENT_FUNDS; 
    return false;   
  }  
  
  // assigning a temp struct for the 2 players to be swapped
  struct player temp1 = {}; 
  struct player temp2 = {};    
  if (is_p1_t1) {  
    temp1 = t1->p1;
    t1->p1 = player_empty; 
    t1->cash_available += temp1.value;
  } 
  else {  
    temp1 = t1->p2; 
    t1->p2 = player_empty;
    t1->cash_available += temp1.value;
  }   
  if (is_p1_t2) {   
    temp2 = t2->p1;
    t2->p1 = player_empty;  
    t2->cash_available += temp2.value;
  } 
  else {  
    temp2 = t2->p2;
    t2->p2 = player_empty;
    t2->cash_available += temp2.value;
  }
  
  // if possible to add return true
  team_add_player(t1, id2, temp2.value, r);
  team_add_player(t2, id1, temp1.value, r);
  return true;
}
