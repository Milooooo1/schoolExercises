#include "ai.hpp"

#include "messages.hpp"

#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <unistd.h>

struct GameStatus
{
    unsigned int currentRoomNum;
    bool smellWumpus, smellBats;
    unsigned int possibleDirections[3];

    char currentState;
};


static int readPipe[2];
static int writePipe[2];
static const char* wumpusExecutable;
static int maxNumberOfMatches;
static char* buffer;

static GameStatus status;

// Static helper functions
static inline void read_line_from_pipe_into_buffer()
{
    for(unsigned int i = 0; i < BUFFER_SIZE; i++)
    {
        if(read(readPipe[0], &buffer[i], 1) != 1 || buffer[i] == '\n')
        { 
            buffer[i] = 0x00;
            break;
        }
    }
}

static char room_handler(void)
{
    if(!strstr(buffer, CURRENT_ROOM_MSG))
        return FSM_HAS_ROOM;
    
    status.currentRoomNum = atoi(buffer+strlen(CURRENT_ROOM_MSG));
    return FSM_HAS_SMELL;
}

static char idle_handler(void)
{
    if(strstr(buffer, CURRENT_ROOM_MSG))
        return room_handler();

    return FSM_IDLE;
}

static char directions_handler(void)
{
    if(!strstr(buffer, POSSIBLE_DIRECTIONS_MSG))
        return FSM_HAS_DIRECTIONS;
    
    // TODO write helper func for increasing endOfString
    char *endOfString = buffer+strlen(POSSIBLE_DIRECTIONS_MSG);
    status.possibleDirections[0] = atoi(endOfString);

    endOfString += (status.possibleDirections[0] >= 10) ? (3) : (2);
    status.possibleDirections[1] = atoi(endOfString);

    endOfString += (status.possibleDirections[1] >= 10) ? (3) : (2);
    status.possibleDirections[2] = atoi(endOfString);
    
    return FSM_ACTION_PROMPT;
}

static char smell_handler(void)
{
    // No smell data provided, process directions data
    if(strstr(buffer, POSSIBLE_DIRECTIONS_MSG))
        return directions_handler();

    // Else parse smell data
    if(strstr(buffer, SMELL_WUMPUS_MSG))
        status.smellWumpus = true;

    if(strstr(buffer, SMELL_BATS_MSG))
        status.smellBats = true;

    return FSM_HAS_SMELL;
}

static char choose_action_handler(void)
{
    write(writePipe[1], "M\n", 2);
    write(STDOUT_FILENO, "M\n", 3);
    return FSM_ROOM_PROMPT;
}

static char choose_room_handler(void)
{
    char tmp[5] = {0};
    int direction = status.possibleDirections[(rand() % 3)];
    sprintf(tmp, "%d", direction);
    tmp[strlen(tmp)] = '\n'; 

    write(writePipe[1], tmp, strlen(tmp));
    return FSM_IDLE;
}


static void start_game(void)
{
    dup2(readPipe[1], STDOUT_FILENO);
    dup2(writePipe[0], STDIN_FILENO);
    
    close(readPipe[0]);
    close(writePipe[1]);

    char * const args[] = {(char*)wumpusExecutable, NULL};
    execve(wumpusExecutable, args, {NULL});
}


static bool ai_play_game_loop(void)
{
    read_line_from_pipe_into_buffer();
    printf("%s\n", buffer);

    switch(status.currentState)
    {
        case FSM_IDLE: { status.currentState = idle_handler(); break;}
        case FSM_HAS_ROOM:  { status.currentState = room_handler(); break;}
        case FSM_HAS_SMELL: { status.currentState = smell_handler(); break;}
        case FSM_HAS_DIRECTIONS: { status.currentState = directions_handler(); break;}
        case FSM_ACTION_PROMPT: { status.currentState = choose_action_handler(); break;}
        case FSM_ROOM_PROMPT: { status.currentState = choose_room_handler(); break;}
        default: {break;}
    }

    return 1;
}


// Namespace, functions accessible to other modules
namespace AI
{
    void init(const char* arguments[])
    {
        wumpusExecutable = arguments[1];
        maxNumberOfMatches = atoi(arguments[2]);

        buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
        status.currentState = FSM_IDLE; 
    }


    void start()
    {
        pipe(readPipe);
        pipe(writePipe);

        if( fork() == 0 )
            start_game();
        
        else
        {
            close(readPipe[1]);
            close(writePipe[0]);

            srand((int)(NULL));
            for(int i = 0; i < 100; i++)
            {
            (ai_play_game_loop());

            }
        }
    }


    void cleanup()
    {
        free(buffer);
    }

}