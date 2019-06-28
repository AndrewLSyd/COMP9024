// boardADT.h - interface

#define INITIAL_SIZE 1000000  // size block for realloc
#define BLANK 99999999  // special value to represent BLANK tile
#define TOLERANCE  0.000001  // tolerance for machine error
#define USAGE "Usage: enter only digits and 'b' separated by spaces\n"
#define BOARD_ERROR_INPUT "Board Input Error.\n"
#define BOARD_ERROR_N "Board Error. Start and Goal board must have same size N.\n"
#define MEMORY_ERROR "Memory Error.\n"

// function prototypes and typedefs
void print_array(int * array_p, int length);
int read_into_board(int ** A);
int check_board(int * A, int n);
int calc_disorder(int * B, int n);
typedef int *board_t;
board_t create_board(void);
