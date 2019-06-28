// puzzle.c - client

#include "boardADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(int argc, char ** argv){
    int n, num_elems_start, num_elems_goal, disorder_start, disorder_goal, parity_even_start
        , parity_even_goal, solvable, validity_start, validity_goal;

    board_t start_board;
    board_t goal_board;
    
    start_board = create_board();
    goal_board = create_board();

    // read in values
    fputs("enter values, ^D to end\n", stdout);

    num_elems_start = read_into_board(&start_board);
    num_elems_goal = read_into_board(&goal_board);

    // printout of board
    if (!(argc == 2 && *(*(argv + 1)) == 'q')){  // if option 'q' (quiet) then do not print
        fputs("start:", stdout);
        print_array(start_board, num_elems_start);
        fputs("goal:", stdout);
        print_array(goal_board, num_elems_goal);
    }

    // input validity e.g. only numbers and 'b'
    if (num_elems_start == EXIT_FAILURE || num_elems_goal == EXIT_FAILURE){
        fputs(USAGE, stderr);
        // free memory and clear dangling pointers
        free(start_board);
        start_board = NULL;
        free(goal_board);
        goal_board = NULL;
        return EXIT_FAILURE;
    }

    // size of start and goal board must be the same
    if (num_elems_start != num_elems_goal){
        fputs(BOARD_ERROR_N, stderr);
        // free memory and clear dangling pointers
        free(start_board);
        start_board = NULL;
        free(goal_board);
        goal_board = NULL;
        return EXIT_FAILURE;
    }
    
    // board validity, must have exactly one of 1, 2, ... N and B
    validity_start = check_board(start_board, num_elems_start);
    validity_goal = check_board(goal_board, num_elems_goal);
    if (validity_start == EXIT_FAILURE || validity_goal == EXIT_FAILURE){
        fputs(BOARD_ERROR_INPUT, stderr);
        // free memory and clear dangling pointers
        free(start_board);
        start_board = NULL;
        free(goal_board);
        goal_board = NULL;
        return EXIT_FAILURE;
    }

    // calculating disorder and parity
    n = sqrt(num_elems_start);
    disorder_start = calc_disorder(start_board, n);
    disorder_goal = calc_disorder(goal_board, n);
    parity_even_start = (disorder_start + 1) % 2;
    parity_even_goal = (disorder_goal + 1) % 2;
    solvable = parity_even_start == parity_even_goal;

    if (argc == 2 && *(*(argv + 1)) == 'v'){  // if verbose the print this extra output
    printf("num_elems: %d, n: %d, disorder_start: %d, disorder_goal: %d\n", num_elems_start, n
        , disorder_start, disorder_goal);
    printf("parity_even_start: %d, parity_end: %d, solvable: %d\n", parity_even_start
        , parity_even_goal, solvable);
    }

    // final output
    if (solvable){
        fputs("solvable\n", stdout);
    }
    else{
        fputs("unsolvable\n", stdout);
    }

    // free memory and clear dangling pointers
    free(start_board);
    start_board = NULL;
    free(goal_board);
    goal_board = NULL;

    return EXIT_SUCCESS;
}

