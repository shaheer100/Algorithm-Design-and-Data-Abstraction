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
#include "cs136-trace.h"
#include "team.h"

//////////////////////////////////////////////////////////////////////////////////////////
// These definitions are used to control testing.
const int MAX_TEAMS = 4;

// -----------------------------------------------------------------------
// DO NOT CHANGE THIS REGION OF CODE

// print_reason(r) prints information about the reason for a failure
//    as indicated in the structure r.
// requires: r is a valid pointer to a reason
//           The reason code is either FAIL_INSUFFICIENT_FUNDS or FAIL_ROSTER_FULL
// effects: produces output

void print_reason(const struct reason* const r) {
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


void do_io_tests(void) {
  //defining symbols
  int TEAM = lookup_symbol("team");
  int ADD = lookup_symbol("add_player");
  int IS_ON = lookup_symbol("is_on");
  int SELL = lookup_symbol("sell_player");
  int TRADE = lookup_symbol("trade_players");
  int PRINT = lookup_symbol("print");

  //created an array of structs to store all 4 teams
  //initialized them to empty teams [team_init_empty]
  struct team teams[4] = {};
  for (int i = 0; i < MAX_TEAMS; ++i) {
    team_init_empty(&teams[i]);
  }

  //defined reason struct
  struct reason r = {};
  
  while(1) {
    int cmd = read_symbol(); //read in a symbol -> command

    if (cmd == TEAM) {
      //initializing and reading in variables
      int id = 0;
      int cash = 0;
      scanf("%d", &id);
      scanf("%d", &cash);
      bool flag = 0;

      //uses [team_setup] to set teams up
      for (int i = 0; i < MAX_TEAMS; ++i) {
        if (teams[i].team_id == TEAM_INVALID_ID) {
          team_setup(&teams[i], id, cash);
          flag = 1;
          break;
        }       
      }

      //if all teams are full, then flag = 0 and all teams are initialized
      if (flag == 0) {
        printf("Teams are all initialized\n");
      }
    }

    else if (cmd == ADD) {
      //initializing and reading in variables
      int team_id = 0;
      int player_id = 0;
      int value = 0;
      scanf("%d", &team_id);
      scanf("%d", &player_id);
      scanf("%d", &value);

      //finds team in array using team_id then
      //uses [team_add_player] to add players
      for (int i = 0; i < MAX_TEAMS; ++i) {
        if (teams[i].team_id == team_id) {
          if (!team_add_player(&teams[i], player_id, value, &r)) {
            printf("add_player failed : ");
            print_reason(&r);
          }
          break; //ensures that we exit the loop, reduces chances of bugs
        }
      }
    }

    else if (cmd == IS_ON) {
      //initializing and reading in variables
      int team_id = 0;
      int player_id = 0;
      scanf("%d", &team_id);
      scanf("%d", &player_id);
      bool status = 0;
      
      //finds team in array using team_id then
      //uses [team_is_player_on] to check if player is on team [team_id]
      for (int i = 0; i < MAX_TEAMS; ++i) {
        if (teams[i].team_id == team_id) {
          if (team_is_player_on(&teams[i], player_id)) {
            status = 1;
            break;
          } else {
            break;
          }
        }
      }

      //if player was found status = true, and player is on team
      //otherwise player is "not" on team
      if (status) {
        printf("Player %d is on team %d\n", player_id, team_id);
      } else {
        printf("Player %d is not on team %d\n", player_id, team_id);
      }
    }

    else if (cmd == SELL) {
      //initializing and reading in variables
      int team1_id = 0;
      int player_id = 0;
      int team2_id = 0;
      scanf("%d", &team1_id);
      scanf("%d", &player_id);
      scanf("%d", &team2_id);
      struct team *team1;
      struct team *team2;

      //searches for teams (to sell and to sell to) in array 
      //using [team_id] then assings structs team1 and team2 to them
      for (int i = 0; i < MAX_TEAMS; ++i) {
        if (teams[i].team_id == team1_id) {
          team1 = &teams[i];
        }
        if (teams[i].team_id == team2_id) {
          team2 = &teams[i];
        }
      }

      //runs team_sell_player, if false it prints reason
      if (!team_sell_player(team1, player_id, team2, &r)) {
        printf("sell_player failed : ");
        print_reason(&r);
      }
    }

    else if (cmd == TRADE) {
      //initializing and reading in variables
      int team1_id = 0;
      int player1_id = 0;
      int team2_id = 0;
      int player2_id = 0;
      scanf("%d", &team1_id);
      scanf("%d", &player1_id);
      scanf("%d", &team2_id);
      scanf("%d", &player2_id);
      struct team *team1;
      struct team *team2;

      //searches for teams (to trade) in array using [team_id]
      //then assigns structs to team1 and team2 to them
      for (int i = 0; i < MAX_TEAMS; ++i) {
        if (teams[i].team_id == team1_id) {
          team1 = &teams[i];
        }
        if (teams[i].team_id == team2_id) {
          team2 = &teams[i];
        }
      }
      
      //runs team_trade_players, if false it prints reason
      if (!team_trade_players(team1, player1_id, team2, player2_id, &r)) {
        printf("trade_players failed : ");
        print_reason(&r);
        continue;
      } 
    }

    else if (cmd == PRINT) {
      //initializing and reading in variables
      int team_id = 0;
      scanf("%d", &team_id);

      //finds team to print using [team_id] and
      //calls team_print to print that team
      for (int i = 0; i < MAX_TEAMS; ++i) {
        if (teams[i].team_id == team_id) {
          team_print(&teams[i]);
          break; //break out, reduces chances of bugs
        }
      }
    }

    else {
      break; //invalid symbol, breaks out
    }
  }
}

int main(void) {
  // DO NOT CHANGE THE CODE BELOW THIS LINE
  do_io_tests(); 
}
