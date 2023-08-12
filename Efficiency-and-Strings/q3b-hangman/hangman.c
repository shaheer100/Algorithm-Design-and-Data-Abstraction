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
// Name: shaheer sheeraz.
// login ID: ssheeraz
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "words.h"
#include "hangman-io.h"

// in_word(word, len, letter) determines if a given [word] has a certain [letter] appear
//   in it at least one time, returns true if so, and false otherwise
// requires: word is a valid array with given len [not asserted]
//           letter is a valid letter [not asserted]
// time: O(n)
//       assume len = n (length of the array)
//       Loop: Sum[p=0..p=n-1]: O(1) = O(n)
static bool in_word(const char *word, int len, char letter) {
  assert(word);
  bool flag = 0;
  for (const char *p = word; p < word + len; ++p) {
    if (*p == letter) {
      flag = 1;
    }
  }
  return flag;
}

// return_caps(letter) returns the capatalized letter
// requires: letter is a valid letter [not asserted]
static char return_caps(char letter) {
  int interval = 32;
  char first_upper = 'A';
  char last_upper = 'Z';
  if (first_upper <= letter && letter <= last_upper) {
    return letter;
  } else {
    return letter - interval;
  }
}

int main(void) {
  while (1) {
    int game_num = 0;
    char board[51] = {};
    char visited[51] = {};
    int visited_len = 0;
    int strikes = 0;
    char first_lower = 'a';
    char last_lower = 'z';
    char first_upper = 'A';
    char last_upper = 'Z';
    char play = '0';
    bool flag = false;

    printf(enter_game_number, max_words); //prompt for game number
    scanf("%d", &game_num);

    if (!(1 <= game_num && game_num <= max_words)) { //checks for validity of number
      printf("%s", invalid_game_number);
      continue;
    }

    const char *secret_word = get_word(game_num); //pulls secret number and stores it
    int len = strlen(secret_word);

    for (int i = 0; i < len; ++i) { //adds asterisks/spaces to the secret board
      if (secret_word[i] == ' ') {
        board[i] = ' ';
      } else {
        board[i] = '*';
      }    
    }  

    print_hangman(strikes);

    while (1) { //reading in letters
      char letter = '0';
      
      printf("%s", letter_prompt);
      printf("%s\n", board);
      scanf(" %c", &letter);

      if (!((first_upper <= letter && letter <= last_upper) ||
          (first_lower <= letter && letter <= last_lower))) { //invalid letter?
        printf(not_a_letter, letter);
        print_hangman(strikes);
        continue;
      }

      letter = return_caps(letter); //make the letter CAPS

      if (in_word(visited, visited_len, letter) == true) { //if visited/guessed prior
        printf(already_guessed_letter, letter);
        print_hangman(strikes);
        continue;
      }

      if ((in_word(visited, visited_len, letter) == false) &&
          (in_word(secret_word, len, letter) == true)) { //not in visited but in word  
        for (int i = 0; i < len; ++i) {
          if (secret_word[i] == letter) {
            board[i] = letter;
          }
        }

        if (strcmp(board, secret_word) == 0) {
          printf(congratulations, secret_word);
          break;
        }

        visited[visited_len] = letter;
        ++visited_len;

        print_hangman(strikes);
        continue;
      }
        
      if ((in_word(visited, visited_len, letter) == false) &&
          (in_word(secret_word, len, letter) == false)) { //not in visited nor in word
        printf(not_in_word, letter);
        ++strikes;

        visited[visited_len] = letter;
        ++visited_len;

        if (strikes < max_strikes) {
          printf(not_last_guess, max_strikes - strikes);
          print_hangman(strikes);
          continue;
        }
        
        print_hangman(strikes);

        if (strikes == max_strikes) {
          printf(game_over, secret_word);
          break;
        }
      }
    }
    
    while (1) { //play again loop
      printf("%s", play_again);
      scanf(" %c", &play);

      if (play == 'y' || play == 'Y') {
        flag = true;
        break;
      } 
      else if (play == 'n' || play == 'N') {
        flag = false;
        break;
      } 
      else {
        printf("%s", invalid_play_again_response);
        continue;
      }
    }

    if (flag) { //if y, then continue, if n then break and end
      continue;
    } else {
      break;
    }

  }
}
