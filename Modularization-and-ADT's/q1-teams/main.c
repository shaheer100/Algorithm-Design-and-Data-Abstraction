#include <stdio.h>
#include <assert.h>
#include "cs136-trace.h"
#include "team.h"

//////////////////////////////////////////////////////////////////////////////////////////
// These definitions are used to control testing.

// Used to turn on/off I/O-based testing
// You can turn this off while doing assertion_testing if you like
// BUT BE SURE TO MAKE THIS (io_testing) true BEFORE SUBMITTING
const bool io_testing = true;

// Used to turn off/on assertion-based testing
// Can be turned off when assertion testing has been completed.
const bool assertion_testing = true;

// -----------------------------------------------------------------------
// DO NOT CHANGE THIS REGION OF CODE

// print_reason(r) prints information about the reason for a failure
//    as indicated in the structure r.
// requires: r is a valid pointer to a reason
//           The reason code is either FAIL_INSUFFICIENT_FUNDS or FAIL_ROSTER_FULL
void print_reason(struct reason *r) {
  assert(r);
  assert(r->code == FAIL_INSUFFICIENT_FUNDS || r->code == FAIL_ROSTER_FULL);
  if (r->code == FAIL_INSUFFICIENT_FUNDS) {
    printf("Team %d doesn't have enough money\n", r->team_num);
  } else if (r->code == FAIL_ROSTER_FULL) {
    printf("Team %d has a full roster\n", r->team_num);
  }
}
// END OF DO NOT CHANGE REGION
//////////////////////////////////////////////////////////////////////////////////////////


void do_assertion_tests(void) {
  //barcelona
  struct player messi = {};
  player_setup(&messi, 10, 100);
  struct player neymar = {};
  player_setup(&neymar, 11, 90);
  
  struct team barcelona = {1, 150, messi, neymar};
  
  //bayern
  struct player lewandowski = {};
  player_setup(&lewandowski, 9, 90);
  struct player muller = {};
  player_setup(&muller, 25, 80);
  
  struct team bayern = {3, 50, lewandowski, muller};
  
  //madrid
  struct player ronaldo = {};
  player_setup(&ronaldo, 7, 95);
  struct player ramos = {};
  player_setup(&ramos, 4, 85);
  
  struct team madrid = {2, 300, ronaldo, ramos};
  
  //asserts
  assert(team_player_value(&barcelona) == 190);
  assert(team_player_value(&bayern) == 170);
  assert(team_player_value(&madrid) == 180);
  assert(team_value(&barcelona) == 340);
  assert(team_value(&bayern) == 220);
  assert(team_value(&madrid) == 480);
  assert(team_cash(&barcelona) == 150);
  assert(team_cash(&bayern) == 50);
  assert(team_cash(&madrid) == 300);
  
  struct team barca_copy = {};
  team_init_empty(&barca_copy);
  team_setup(&barca_copy, 1, 150);
  struct team bayern_copy = {};
  team_init_empty(&bayern_copy);
  team_setup(&bayern_copy, 3, 50);
  struct team madrid_copy = {};
  team_init_empty(&madrid_copy);
  team_setup(&madrid_copy, 2, 300);
  assert(team_cash(&barcelona) == team_cash(&barca_copy));
  assert(team_cash(&bayern) == team_cash(&bayern_copy));
  assert(team_cash(&madrid) == team_cash(&madrid_copy));
  
  assert(team_get_id(&barcelona) == 1);
  assert(team_get_id(&bayern) == 3);
  assert(team_get_id(&madrid) == 2);
  
  assert(team_is_player_on(&barcelona, 10) == true);
  assert(team_is_player_on(&barcelona, 7) == false);

  struct reason r = {};
  
  struct team psg = {};
  struct player gretzky = {};
  player_setup(&gretzky, 99, 99);
  team_init_empty(&psg);
  team_setup(&psg, 4, 100);
  assert(team_add_player(&psg, 10, 100, &r) == true);
  assert(team_add_player(&psg, 11, 90, &r) == false);
  assert(team_add_player(&barcelona, 99, 99, &r) == false);
  
  struct team all_star = {};
  team_init_empty(&all_star);
  team_setup(&all_star, 5, 500);
  assert(team_add_player(&all_star, 99, 99, &r) == true);
  assert(team_player_value(&all_star) == 99);
  assert(team_cash(&all_star) == 401);
  assert(team_value(&all_star) == 500);
  
  
  assert(team_sell_player(&barcelona, 10, &all_star, &r) == true);
  assert(team_sell_player(&all_star, 10, &bayern, &r) == false);
  assert(team_player_value(&all_star) == 199);
  assert(team_cash(&all_star) == 301);
  assert(team_value(&all_star) == 500);
  assert(team_is_player_on(&all_star, 10) == true);
  assert(team_is_player_on(&all_star, 7) == false);
  
  assert(team_trade_players(&all_star, 10, &madrid, 7, &r) == true);
//  printf("%d", team_cash(&all_star));
  assert(team_cash(&all_star) == 306); //sold messi (100) got ron (95) + 5
  assert(team_player_value(&all_star) == 194);
  assert(team_value(&all_star) == 500);
  assert(team_is_player_on(&all_star, 10) == false);
  assert(team_is_player_on(&all_star, 7) == true);
  
  struct team two = {};
  team_init_empty(&two);
  team_setup(&two, 2, 2000);
  struct player p222 = {};
  player_setup(&p222, 200, 1000);
  team_add_player(&two, 200, 1000, &r);
  assert(team_is_player_on(&two, 200) == true);
}

void do_io_tests(void) {
  int TEAM = lookup_symbol("team");
  int ADD = lookup_symbol("add_player");
  int SELL = lookup_symbol("sell_player");
  int TRADE = lookup_symbol("trade_players");
  int IS_ON = lookup_symbol("is_on");
  int PRINT = lookup_symbol("print");
  struct team t1 = {};
  team_init_empty(&t1);
  struct team t2 = {};
  team_init_empty(&t2);

  struct reason r = {};

  while(1) {
    int cmd = read_symbol();
    if (cmd == TEAM) {
      int id = 0;
      int cash = 0;
      scanf("%d", &id);
      scanf("%d", &cash);
      if (t1.team_id == TEAM_INVALID_ID) {
        team_setup(&t1, id, cash);
        continue;
      } else if (t2.team_id == TEAM_INVALID_ID) {
        team_setup(&t2, id, cash);
        continue;
      } else {
        printf("Teams are all initialized\n"); 
        continue;
      }
// Possible messages for team command (nothing is printed if successful)
//   "Teams are all initialized\n"
    }
    
    else if (cmd == ADD) {
      int team_id = 0;
      int id = 0;
      int val = 0;
      scanf("%d", &team_id);
      scanf("%d", &id);
      scanf("%d", &val);

      if (t1.team_id == team_id) {
        int retval = team_add_player(&t1, id, val, &r);
        if (retval == 1) {
          continue;
        }
        else {
          printf("add_player failed : ");
          print_reason(&r);
          continue;
        }
      }
      if (t2.team_id == team_id) {
        int retval = team_add_player(&t2, id, val, &r);
        if (retval == 1) {
          continue;
        }
        else {
          printf("add_player failed : ");
          print_reason(&r);
          continue;
        }
      }
// Possible messages for add_player command (nothing is printed if successful)
//   "add_player failed : "
//    followed by calling print_reason to print the reason for the failure
    }
    
    else if (cmd == SELL) {
      int team1_id = 0;
      int player_id = 0;
      int team2_id = 0;
      scanf("%d", &team1_id);
      scanf("%d", &player_id);
      scanf("%d", &team2_id);
      if (team1_id == t1.team_id) {
        int retval = team_sell_player(&t1, player_id, &t2, &r);
        if (retval == 1) {
          continue;
        }
        else {
          printf("sell_player failed : ");
          print_reason(&r);
          continue;
        }
      }
      if (team1_id == t2.team_id) {
        int retval = team_sell_player(&t2, player_id, &t1, &r);
        if (retval == 1) {
          continue;
        }
        else {
          printf("sell_player failed : ");
          print_reason(&r);
          continue;
        }
      }
// Possible messages for sell_player command (nothing is printed if successful)
//   "sell_player failed : "
//    followed by calling print_reason to print the reason for the failure
    }
    
    else if (cmd == IS_ON) {
      int team_id = 0;
      int player_id = 0;
      scanf("%d", &team_id);
      scanf("%d", &player_id);
      if (team_id == t1.team_id) {
        if (team_is_player_on(&t1, player_id)) {
          printf("Player %d is on team %d\n", player_id, team_id);
          continue;
        } else {
          printf("Player %d is not on team %d\n", player_id, team_id);
          continue;
        }
      } 
      else if (team_id == t2.team_id) {
        if (team_is_player_on(&t2, player_id)) {
          printf("Player %d is on team %d\n", player_id, team_id);
          continue;
        } else {
          printf("Player %d is not on team %d\n", player_id, team_id);
          continue;
        }
      }
// Possible messages for is_on command
//   "Player %d is on team %d\n"
//   "Player %d is not on team %d\n" 
    }
    
    else if (cmd == TRADE) {
      int team_id1 = 0;
      int player_id1 = 0;
      int team_id2 = 0;
      int player_id2 = 0;
      scanf("%d", &team_id1);
      scanf("%d", &player_id1);
      scanf("%d", &team_id2);
      scanf("%d", &player_id2);
      
      if (team_id1 == t1.team_id) {
        if (team_trade_players(&t1, player_id1, &t2, player_id2, &r)) {
          continue;
        } 
        else {
          printf("trade_players failed : ");
          print_reason(&r);
        }
      }
      else if (team_id1 == t2.team_id) {
        if (team_trade_players(&t2, player_id1, &t1, player_id2, &r)) {
          continue;
        } 
        else {
          printf("trade_players failed : ");
          print_reason(&r);
        }
      }
      
// Possible messages for trade_players command (nothing is printed if successful)
//   "trade_players failed : "
//    followed by calling print_reason to print the reason for the failure
    }
    
    else if (cmd == PRINT) {
      int team = 0;
      scanf("%d", &team);
      if (team == t1.team_id) {
        team_print(&t1);
      } else if (team == t2.team_id) {
        team_print(&t2);
      }
      continue;
    }
    
    else {
      break;
    }
  }
}

int main(void) {
  // Uncomment if you want to turn tracing off
  // trace_off();

  // DO NOT CHANGE THE CODE BELOW THIS LINE
  if (assertion_testing) {
    do_assertion_tests();
  }

  if (io_testing) {
    do_io_tests();
  }
}
