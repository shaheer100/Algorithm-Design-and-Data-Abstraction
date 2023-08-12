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
// Name: shaheer sheeraz
// login ID: ssheeraz
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "team.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THIS REGION OF CODE
const int MAX_PLAYERS = 5;
const int TEAM_INVALID_ID = -1;
const struct team team_empty = {TEAM_INVALID_ID, 0}; // Doesn't set players to empty_player
                                                     // Must be done by team_init_empty

// DO NOT CHANGE THESE
// Reasons for failures
const int FAIL_INSUFFICIENT_FUNDS = -1;
const int FAIL_ROSTER_FULL = -2;
// END OF DO NOT CHANGE REGION

// YOU MUST COMPLETE THIS FUNCTION
void team_print(const struct team* const t) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  assert(team_player_value(t) + team_cash(t) == team_value(t));
  printf("Team %d : ", team_get_id(t));
  //makes an array that is mutable
  struct player players_array[5] = {};
  for (int k = 0; k < MAX_PLAYERS; ++k) {
    players_array[k] = t->players[k];
  }
  //sort the players in terms of value
  for (int i = 1; i < MAX_PLAYERS; ++i) {
    for (int j = i; j > 0 && players_array[j - 1].player_id > players_array[j].player_id; --j) {
      struct player temp = players_array[j];
      players_array[j] = players_array[j - 1];
      players_array[j - 1] = temp;
    }
  }
  for (int m = 0; m < MAX_PLAYERS; ++m) {
    if (players_array[m].player_id != PLAYER_INVALID_ID) {
      player_print(&players_array[m]);
    }
  }
  // INSERT CODE HERE FOR PRINTING PLAYERS
  // Players must be printed from the lowest player_id to highest player_id.
  // You must NOT print players with player_id == PLAYER_INVALID_ID
  // The function you use to print the player is 
  //    player_print(player_ptr);  See player.h
  // player_print will take care of proper spacing.
  // See team_print in team.c of A5 if you need a better idea of what to do.

  printf("player value = %d cash = %d", team_player_value(t), team_cash(t));
  printf("\n");
}
// -----------------------------------------------------------------------

// FOR DOCUMENTATION, see team.h

int team_player_value(const struct team* const t) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  int team_player_value = 0;
  for (int i = 0; i < MAX_PLAYERS; ++i) {
    if (t->players[i].player_id != PLAYER_INVALID_ID) {
      team_player_value += t->players[i].value;
    }
  }
  return team_player_value;
}

int team_value(const struct team* const t) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  return team_player_value(t) + t->cash_available;
}

int team_cash(const struct team* const t) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  return t->cash_available;
}

void team_init_empty(struct team* const t) {
  assert(t);
  t->team_id = TEAM_INVALID_ID;
  t->cash_available = 0;
  t->num_players = 0;
  for (int i = 0; i < MAX_PLAYERS; ++i) {
    t->players[i] = player_empty;
  }
}

void team_setup(struct team* const t, const int id, const int cash) {
  assert(t);
  assert(t->team_id == TEAM_INVALID_ID);
  assert(t->num_players == 0);
  assert(t->players[0].player_id == PLAYER_INVALID_ID);
  assert(t->players[1].player_id == PLAYER_INVALID_ID);
  assert(t->players[2].player_id == PLAYER_INVALID_ID);
  assert(t->players[3].player_id == PLAYER_INVALID_ID);
  assert(t->players[4].player_id == PLAYER_INVALID_ID);
  assert(id >= 0);
  assert(cash >= 0);
  t->team_id = id;
  t->cash_available = cash;
}

int team_get_id(const struct team* const t) {
  assert(t);
  return t->team_id;
}

bool team_is_player_on(const struct team* const t, const int id) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  bool player_exist = false;
  for (int i = 0; i < MAX_PLAYERS; ++i) {
    if (t->players[i].player_id == id) {
      player_exist = true;
      break;
    }
  }
  return player_exist;
}

bool team_add_player(struct team* const t, const int id, const int val,
   struct reason *r) {
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  assert(id >= 0);
  assert(val >= 0);
  assert(team_is_player_on(t, id) == false);
  assert(r);

  if (t->num_players == MAX_PLAYERS) {
    r->code = FAIL_ROSTER_FULL;
    r->team_num = t->team_id;
    return false;
  }

  if (t->cash_available < val) {
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t->team_id;
    return false;
  }

  for (int i = 0; i < MAX_PLAYERS; ++i) {
    if (t->players[i].player_id == PLAYER_INVALID_ID) {
      t->players[i].player_id = id;
      t->players[i].value = val;
      t->num_players += 1;
      t->cash_available -= val;
      break;
    }
  }
  return true;
}

bool team_sell_player(struct team* const t1, const int id,
     struct team* const t2, struct reason *r) {
  assert(t1);
  assert(t2);
  assert(t1->team_id != TEAM_INVALID_ID);
  assert(t2->team_id != TEAM_INVALID_ID);
  assert(team_is_player_on(t1, id) == true);
  assert(team_is_player_on(t2, id) == false);
  assert(r);
  assert(id >= 0);
  assert(t1 != t2); 
  assert(t1->team_id != t2->team_id);
  int val = 0;
  int player_num = 0;

  for (int i = 0; i < MAX_PLAYERS; ++i) {
    if (t1->players[i].player_id == id) {
      val = t1->players[i].value;
      player_num = i;
      break;
    }
  }

  if (team_add_player(t2, id, val, r)) {
    t1->cash_available += val;
    t1->num_players -= 1;
    t1->players[player_num] = player_empty;
    return true;
  } else {
    return false;
  }
}

bool team_trade_players(struct team* const t1, const int id1,
     struct team* const t2, const int id2, struct reason *r) {
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
  assert(t1->team_id != t2->team_id);
  int val1 = 0;
  int val2 = 0;

  for (int i = 0; i < MAX_PLAYERS; ++i) {
    if (t1->players[i].player_id == id1) {
      val1 = t1->players[i].value;
    }
     if (t2->players[i].player_id == id2) {
      val2 = t2->players[i].value;
    }
  }

  if (!(t1->cash_available + val1 - val2 >= 0)) {
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t1->team_id;
    return false;
  }
  if (!(t2->cash_available + val2 - val1 >= 0)) {
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t2->team_id;
    return false;
  }
  
  t1->cash_available += val1;
  t2->cash_available += val2; 
  
  for (int j = 0; j < MAX_PLAYERS; ++j) {
    if (t1->players[j].player_id == id1) {
      t1->players[j] = player_empty;
      t1->num_players -= 1;
    } 
    if (t2->players[j].player_id == id2) {
      t2->players[j] = player_empty;
      t2->num_players -= 1;
    }
  }

  team_add_player(t1, id2, val2, r);
  team_add_player(t2, id1, val1, r);
  return true;
}
