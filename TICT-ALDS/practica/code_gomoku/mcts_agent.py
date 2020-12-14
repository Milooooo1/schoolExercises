# -*- coding: utf-8 -*-

import random
import gomoku
from gomoku import Move, GameState
import time
import math
import copy
import numpy as np
import itertools


SIZE = 19

class gomokuTree2:
    
    def __init__(self, player, gstate, last_move=None, valid_move_list=None, parentNode=None):
        self.state = gstate
        self.move = None
        self.fin = False
        self.children = []

        self.N = 0
        self.Q = 0
        self.val = self.val()

        self.player = player
        self.parent = parentNode
        self.last_move = last_move
        self.validMoves = valid_move_list
        
    def val(self):
        return self.N / self.Q if self.N != 0 else 0 
        
    #De runtime complexiteit van deze functie is in the worst case O(b^2) 
    #waar b de breedte van het bord is.
    def findSpotToExpand(self, node, validMoves):
        # Check if expanded spot is the end of the game
                    
        if node.state[1] > 5 and gomoku.check_win(node.state[0], self.last_move) == True:
            return 1
        
        self.validMoves = validMoves
        movesToTry = copy.deepcopy(self.validMoves)        
        if len(self.children) <= len(movesToTry):
            pickedMove = random.choice(movesToTry)
            valid, fin, new_state = gomoku.move(self.state, pickedMove)
            movesToTry.remove(pickedMove)
            child = gomokuTree2(self.player, new_state, self.last_move, movesToTry, self) 
            node.children.append(child)
            return child
        
        highest_UCT_child = self.getHighestValuedNode(True)
        return highest_UCT_child
    
    #De runtime complexitieit van deze functie is het langste (worst case)
    #wanneer het bord leeg is en je super veel zetten kan zetten (for move in moves).
    #De big Oh notatie is in dit geval O(m), m is hier het aantal moves wat je kan zetten
    def rollout(self, node, state):
        if(self.fin):
            if(self.player == 1):
                return 1
            elif(self.player == 2):
                return -1
            else:
                return 0

        moves = copy.deepcopy(self.validMoves)
        random.shuffle(moves)
        new_state = copy.deepcopy(self.state)

        while len(moves) > 0:
            node.move = moves.pop()
            valid, node.fin, new_state = gomoku.move(new_state, node.move)
            if(type(new_state) != type((1,1))):
                print("Error")
                
            if(node.fin or len(moves) == 0):
                if(self.player == 1):
                    return 1
                elif(self.player == 2):
                    return -1
                else:
                    return 0

    #De tijd complexiteit van deze functie is het slechtste als je bij een 
    #leaf node zit, je moet dan helemaal terug de big Oh notatie is in dit geval
    #O(d) waar d de diepte (depth) is van de boom 
    def backupValue( self, n, val ):
        # print(val)
        while n is not None:
            n.N += 1
            if n.player == 1:       #Player 1 (Black)
                n.Q = n.Q - val
            else:                   #Player 2 (White)
                n.Q = n.Q + val
            n = n.parent
    
    #De runtime complexitieit van deze functie is het langste (worst case)
    #wanneer een move het grootste aantal kinderen heeft die hij kan hebben. 
    #De big Oh notatie is in dit geval O(c), c is hier het aantal children die 
    #de node heeft. 
    def getHighestValuedNode(self, exploration):
        bestChildScore = 0
        childWithBestMove = self.children[0]
        for child in self.children:
            if exploration:
                #In the below formula 2 is a constant which can be fiddled with. 
                childScore = child.Q/child.N + 1.5 * math.sqrt((math.log(child.parent.N)) / child.N)   

            else:
                childScore = child.Q/child.N
            
            if self.player == 1:                    #Player = White
                if childScore >= bestChildScore:
                    bestChildScore = childScore
                    childWithBestMove = child
            else:                                   #Player = Black
                if childScore <= bestChildScore:
                    bestChildScore = childScore
                    childWithBestMove = child
        return childWithBestMove          

class random_dummy_player2:
    """This class specifies a player that just does random moves.
    The use of this class is two-fold: 1) You can use it as a base random roll-out policy.
    2) it specifies the required methods that will be used by the competition to run
    your player
    """
    def __init__(self, black_: bool = True):
        """Constructor for the player."""
        self.black = black_
        self.validMoves = None

    def new_game(self, black_: bool):
        """At the start of each new game you will be notified by the competition.
        this method has a boolean parameter that informs your agent whether you
        will play black or white.
        """
        self.boardSize = SIZE #TODO: De grootte van de starting state is nu hardcoded 9
        if(black_ == False):
            self.player = (2, "White")
            firstMove = (int(self.boardSize / 2), int(self.boardSize / 2))
        else:
            self.player = (1, "Black")
            firstMove = ()
            
        self.lastMove = ()
        self.state = np.zeros((self.boardSize, self.boardSize), dtype=np.int8), 1
        self.validMoves = gomoku.valid_moves(self.state)
        self.root = gomokuTree2(self.player[0], self.state, firstMove, self.validMoves) 
            
        self.black = black_

    
    def getBestMove(self):
        bestChildScore = 0
        bestMove = None
        bestChild = None
        for child in self.root.children:
            childScore = child.val
            if self.root.player == 1:
                if childScore >= bestChildScore:
                    bestChildScore = childScore
                    bestMove = child.move
                    bestChild = child
            else:
                if childScore <= bestChildScore:
                    bestChildScore = childScore
                    bestMove = child.move
                    bestChild = child
                    
        return bestMove, bestChildScore, bestChild
    

    def move(self, state: GameState, last_move: Move, max_time_to_move: int = 1000) -> Move:
        """This is the most important method: the agent will get:
        1) the current state of the game
        2) the last move by the opponent
        3) the available moves you can play (this is a special service we provide ;-) )
        4) the maximum time until the agent is required to make a move in milliseconds 
           [diverging from this will lead to disqualification].
        """       
        
        startTime = time.time_ns()
        buffer = 7 #This buffer is substracted from the max time to move to ensure you don't go over it
        
        if self.validMoves == None or state[1] <= 5: #Only generate the field on first 3 moves
            self.validMoves = gomoku.valid_moves(state)
        elif last_move != ():
            self.validMoves.remove(last_move)

        counter = 0
        while(((time.time_ns() - startTime)/ 1000000) < max_time_to_move - buffer): #Time remaining
            counter += 1
            child = self.root.findSpotToExpand(self.root, self.validMoves)
            val = self.root.rollout(child, child.state)
            self.root.backupValue(child, val )

        print("Default algorithm has time for "+str(counter)+" amount of loops")


        move, bestScore, child = self.getBestMove()
        # print("Out of loop and chose move: "+str(move))
        # print("This move had a score of: "+str(bestScore))
        # print("Remaining time: "+str(round( 1000 - ((time.time_ns() - startTime)/ 1000000), 4)))

        try:
            self.validMoves.remove(move)
        except:
            print("Error")
        self.root = child
        self.root.parent = None
        self.root.last_move = move
        return move


    def id(self) -> str:
        """Please return a string here that uniquely identifies your submission e.g., "name (student_id)" """
        return "DEFAULT Milo Beliën Color: "+ str(self.player[1]) + " ID: 1758427"

class gomokuTree3:
    
    def __init__(self, player, gstate, last_move=None, valid_move_list=None, parentNode=None):
        self.state = gstate
        self.move = None
        self.fin = False
        self.children = []

        self.N = 0
        self.Q = 0
        self.val = self.val()

        self.player = player
        self.parent = parentNode
        self.last_move = last_move
        self.validMoves = valid_move_list
        
    def val(self):
        return self.N / self.Q if self.N != 0 else 0 
        
    #De runtime complexiteit van deze functie is in the worst case O(b^2) 
    #waar b de breedte van het bord is.
    def findSpotToExpand(self, node, validMoves):
        # Check if expanded spot is the end of the game
                    
        if node.state[1] > 5 and gomoku.check_win(node.state[0], self.last_move) == True:
            return 1
        
        self.validMoves = validMoves
        movesToTry = copy.deepcopy(self.validMoves)        
        if len(self.children) <= len(movesToTry):
            pickedMove = random.choice(movesToTry)
            valid, fin, new_state = gomoku.move(self.state, pickedMove)
            movesToTry.remove(pickedMove)
            child = gomokuTree3(self.player, new_state, self.last_move, movesToTry, self) 
            node.children.append(child)
            return child
        
        highest_UCT_child = self.getHighestValuedNode(True)
        return highest_UCT_child
    
    #De runtime complexitieit van deze functie is het langste (worst case)
    #wanneer het bord leeg is en je super veel zetten kan zetten (for move in moves).
    #De big Oh notatie is in dit geval O(m), m is hier het aantal moves wat je kan zetten
    def rollout(self, node, state):
        if(self.fin):
            if(self.player == 1):
                return 1
            elif(self.player == 2):
                return -1
            else:
                return 0

        moves = copy.deepcopy(self.validMoves)
        random.shuffle(moves)
        new_state = copy.deepcopy(self.state)

        while len(moves) > 0:
            node.move = moves.pop()
            valid, node.fin, new_state = gomoku.move(new_state, node.move)
            if(type(new_state) != type((1,1))):
                print("Error")
                
            if(node.fin or len(moves) == 0):
                if(self.player == 1):
                    return 1
                elif(self.player == 2):
                    return -1
                else:
                    return 0

    #De tijd complexiteit van deze functie is het slechtste als je bij een 
    #leaf node zit, je moet dan helemaal terug de big Oh notatie is in dit geval
    #O(d) waar d de diepte (depth) is van de boom 
    def backupValue( self, n, val ):
        # print(val)
        while n is not None:
            n.N += 1
            if n.player == 1:       #Player 1 (Black)
                n.Q = n.Q - val
            else:                   #Player 2 (White)
                n.Q = n.Q + val
            n = n.parent
    
    #De runtime complexitieit van deze functie is het langste (worst case)
    #wanneer een move het grootste aantal kinderen heeft die hij kan hebben. 
    #De big Oh notatie is in dit geval O(c), c is hier het aantal children die 
    #de node heeft. 
    def getHighestValuedNode(self, exploration):
        bestChildScore = 0
        childWithBestMove = self.children[0]
        for child in self.children:
            if exploration:
                #In the below formula c is a constant which can be fiddled with. 
                childScore = child.Q/child.N + 32 * math.sqrt((math.log(child.parent.N)) / child.N)
            else:
                childScore = child.Q/child.N            
                
            if self.player == 1:                    #Player = White
                if childScore >= bestChildScore:
                    bestChildScore = childScore
                    childWithBestMove = child
            else:                                   #Player = Black
                if childScore <= bestChildScore:
                    bestChildScore = childScore
                    childWithBestMove = child
        return childWithBestMove     

class random_dummy_player3:
    """This class specifies a player that just does random moves.
    The use of this class is two-fold: 1) You can use it as a base random roll-out policy.
    2) it specifies the required methods that will be used by the competition to run
    your player
    """
    def __init__(self, black_: bool = True):
        """Constructor for the player."""
        self.black = black_
        self.validMoves = None

    def new_game(self, black_: bool):
        """At the start of each new game you will be notified by the competition.
        this method has a boolean parameter that informs your agent whether you
        will play black or white.
        """
        self.boardSize = SIZE #TODO: De grootte van de starting state is nu hardcoded 9
        if(black_ == False):
            self.player = (2, "White")
            firstMove = (int(self.boardSize / 2), int(self.boardSize / 2))
        else:
            self.player = (1, "Black")
            firstMove = ()
            
        self.lastMove = ()
        self.state = np.zeros((self.boardSize, self.boardSize), dtype=np.int8), 1
        self.validMoves = gomoku.valid_moves(self.state)
        self.root = gomokuTree3(self.player[0], self.state, firstMove, self.validMoves) 
            
        self.black = black_

    
    def getBestMove(self):
        bestChildScore = 0
        bestMove = None
        bestChild = None
        for child in self.root.children:
            childScore = child.val #+ 2 * math.sqrt((math.log2(child.parent.N)) / child.N) 
            if self.root.player == 1:
                if childScore >= bestChildScore:
                    bestChildScore = childScore
                    bestMove = child.move
                    bestChild = child
            else:
                if childScore <= bestChildScore:
                    bestChildScore = childScore
                    bestMove = child.move
                    bestChild = child
                    
        return bestMove, bestChildScore, bestChild
    
    # This function makes a list of all moves adjecent to all stones already on
    # the board and in a range of 5 from the last move. 
    def getSmartValidMoves(self, state, lastmove):
        #Rij = i Colom = j
        #TODO: Houden aan regels als je beginnende speler bent op ply 1 (midden) en 3 (niet in de buurt van het midden)
        
        # smartMoves = set(self.validMoves)
        smartMoves = set()
        board = state[0]
        ply = state[1]
        
        if(self.player[0] == 1 and ply == 1):
            middle = np.array(np.shape(board))//2
            return [tuple(middle)]
        
        #Third move of the player can be anywhere
        if(self.player[0] == 1 and ply == 3): 
            middle = np.shape(board)[0] // 2
            rclist = list(range(middle - 2, middle + 3))
            all_list = list(range(np.shape(board)[0]))
            centre = set(itertools.product(rclist, rclist))
            boardlist = set(itertools.product(all_list, all_list))
            return list(boardlist-centre)
        
        #Check around all the existing pieces for possible spots
        for i in range(0, self.boardSize):
            for j in range(0, self.boardSize):
                if(board[i][j] == 0):
                    continue #skip all empty positions.
                    
                if(i != self.boardSize-1 and j != self.boardSize-1 and board[i+1][j+1] == 0):       #Check rechts onder
                    smartMoves.add((i+1, j+1))
                if(i != 0 and j != self.boardSize-1 and board[i-1][j+1] == 0):                      #Check rechts boven
                    smartMoves.add((i-1, j+1))
                if(i != self.boardSize-1 and j != 0 and board[i+1][j-1] == 0):                      #Check links onder 
                    smartMoves.add((i+1, j-1))
                if(i != 0 and j != 0 and board[i-1][j-1] == 0):                                     #Check links boven 
                    smartMoves.add((i-1, j-1))
                if(j != self.boardSize-1 and board[i][j+1] == 0):                                   #Check rechts
                    smartMoves.add((i, j+1))
                if(j != 0 and board[i][j-1] == 0):                                                  #Check links
                    smartMoves.add((i, j-1))
                if(i != self.boardSize-1 and board[i+1][j] == 0):                                   #Check onder
                    smartMoves.add((i+1, j))
                if(i != 0 and board[i-1][j] == 0):                                                  #Check boven
                    smartMoves.add((i-1, j))
        
        #Check in a radius of 5 around the last move 
        lm = self.root.last_move #lm = (4,4) boardSize = 8
        for i in range(0, 5):
            for j in range(0, 5):
                if((lm[0]+i) < self.boardSize-1 and (lm[1]+j) < self.boardSize-1 and board[lm[0]+i][lm[1]+j] == 0): 
                    smartMoves.add((lm[0]+i, lm[1]+j))                                              #Check rechts onder 
                if((lm[0]-i) > 0 and (j+lm[1]) < self.boardSize-1 and board[lm[0]-i][lm[1]+j] == 0):                  
                    smartMoves.add((lm[0]-i, lm[1]+j))                                              #Check rechts boven
                if((lm[0]+i) < self.boardSize-1 and (lm[1]-j) > 0 and board[lm[0]+i][lm[1]-j] == 0):                  
                    smartMoves.add((lm[0]+i, lm[1]-j))                                              #Check links onder 
                if((lm[0]-i) > 0 and (lm[1]-j) > 0 and board[lm[0]-i][lm[1]-j] == 0):                                 
                    smartMoves.add((lm[0]-i, lm[1]-j))                                              #Check links boven 
                if((lm[1]+j) < self.boardSize-1 and board[lm[0]][lm[1]+j] == 0):                               
                    smartMoves.add((lm[0], lm[1]+j))                                                #Check rechts
                if((lm[1]-j) > 0 and board[lm[0]][lm[1]-j] == 0):                                              
                    smartMoves.add((lm[0], lm[1]-j))                                                #Check links
                if((lm[0]+i) < self.boardSize-1 and board[lm[0]+i][lm[1]] == 0):                               
                    smartMoves.add((lm[0]+i, lm[1]))                                                #Check onder                         
                if((lm[0]-i) > 0 and board[lm[0]-i][lm[1]] == 0):                                              
                    smartMoves.add((lm[0]-i, lm[1]))                                                #Check boven
                    
                    
        return list(smartMoves)
            
    

    def move(self, state: GameState, last_move: Move, max_time_to_move: int = 1000) -> Move:
        """This is the most important method: the agent will get:
        1) the current state of the game
        2) the last move by the opponent
        3) the available moves you can play (this is a special service we provide ;-) )
        4) the maximum time until the agent is required to make a move in milliseconds 
           [diverging from this will lead to disqualification].
        """       
        
        startTime = time.time_ns()
        buffer = 7 #This buffer is substracted from the max time to move to ensure you don't go over it
    
        self.validMoves = self.getSmartValidMoves(state, last_move)
        # print(self.validMoves)    
        
        counter = 0 
        while(((time.time_ns() - startTime)/ 1000000) < max_time_to_move - buffer): #Time remaining
            counter += 1
            child = self.root.findSpotToExpand(self.root, self.validMoves)
            val = self.root.rollout(child, child.state)
            self.root.backupValue(child, val )
            
        print("Heuristic algorithm has time for "+str(counter)+" amount of loops on ply:"+str(state[1]))

        move, bestScore, child = self.getBestMove()
        # print("Player "+str(self.player[0])+" picked move:"+str(move))
            
        # self.validMoves.remove(move)
        self.root = child
        self.root.parent = None
        self.root.last_move = move
        return move


    def id(self) -> str:
        """Please return a string here that uniquely identifies your submission e.g., "name (student_id)" """
        return "HEURISTIC Milo Beliën Color: "+ str(self.player[1]) + " ID: 1758427"



'''
    TODO: Dont generate all the moves every turn but do it only once and remove 
    the move you'r opponent did and your own. Do generate the radius of 5 around 
    your own last_move. 
'''