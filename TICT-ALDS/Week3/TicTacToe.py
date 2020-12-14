import copy
import random
import warnings
warnings.simplefilter(action='ignore', category=SyntaxWarning)

state = (1, [[2,2,1],[1,0,2],[0,0,1]]) #A possible game state after three moves (=6 plies) 

def prettyPrintTTT(game_state):
    result = "\n"
    for i in range(3):
        result+="           "
        for j in range(3):
            if game_state[1][i][j] is 1:
                result+="x "
            elif game_state[1][i][j] is 2: 
                result+="o "
            else: 
                result+="- "
        result+="\n"
    result+="\n"
    if game_state[0] is 2:
        result+="   naughts (\'o\') to move"
    else: 
        result+="   crosses (\'x\') to move"
    print(result)
    
# prettyPrintTTT(state) #Now lets have a look at this state

def checkFinishedAndWhoWon(game_state):
    open_fields = False
    who_won = 0 #default: no one
    board = game_state[1]
    #check lines
    for i in [0,1,2]:
        player = board[i][0]
        line = True
        for j in [0,1,2]:
            if(board[i][j] is 0):
                open_fields = True
                line = False
                break
            if(board[i][j] is not player):
                line = False
                break
        if line:
            return (True, player)
    #check columns
    for i in [0,1,2]:
        player = board[0][i]
        line = True
        for j in [0,1,2]:
            if(board[j][i] is not player):
                line = False
                break
        if line:
            return (True, player)
    #check diagonals
    player = board[1][1] #the middle
    if(player is 0):
        return (False,0)
    if((board[0][0] is player) and (board[2][2] is player)):
        return (True,player)
    if((board[2][0] is player) and (board[0][2] is player)):
        return (True,player)
    return (not open_fields, 0)

# class GameTreeNode: 
#     def __init__(self, gstate, parentNode=None, last_move=None):
#         self.state=gstate
#         self.finished, self.won = checkFinishedAndWhoWon(self.state)
#         self.parent=parentNode
#         self.children=[]
#         self.previous_move = last_move
        
#     def printNode(self):
#         #print("Node:\n")
#         print("  has_parent: "+str(self.parent is not None))
#         print("  no. of children: "+str(len(self.children)))
#         print("  result: "+(("player "+str(self.won)+" won" if self.won is not 0 else "draw") if self.finished else "not yet finished"))
#         print("  game state:")
#         prettyPrintTTT(self.state)
        
#     def calcValue(self):
#         self.finished, self.won = checkFinishedAndWhoWon(self.state)
#         if self.finished:
#             if self.won == 1: #We won
#                 return +1
#             elif self.won == 2: #We lost
#                 return -1
#             elif self.won == 0: #Draw
#                 return 0
#         else:
#             if self.state[0] == 1: #Our turn
#                 value = -2
#                 for ch in self.children:
#                     value = max(ch.calcValue(), value)
#             if self.state[0] == 2: #Opponents turn
#                 value = 2
#                 for ch in self.children:
#                     value = min(ch.calcValue(), value)
#             return value
        
### Uw antwoord hier: 
# class GameTreeNode2: 
#     def __init__(self, gstate, parentNode=None, last_move=None):
#         self.state=gstate
#         self.finished, self.won = checkFinishedAndWhoWon(self.state)
#         self.parent=parentNode
#         self.children=[]
#         self.move = last_move
#         self.value = None
    
#     ### please implement some way to compute the values for each node in the tree
#     ### such that this next function gives us the right answer
#     def calcValue(self):
#         if self.value != None:
#             return self.value
        
#         self.finished, self.won = checkFinishedAndWhoWon(self.state)
#         if self.finished:
#             if self.won == 1: #We won
#                 value = 1
#             elif self.won == 2: #We lost
#                 value = -1
#             elif self.won == 0: #Draw
#                 value =  0
#         else:
#             if self.state[0] == 1: #Our turn
#                 value = -2
#                 for ch in self.children:
#                     value = max(ch.calcValue(), value)
#             if self.state[0] == 2: #Opponents turn
#                 value = 2
#                 for ch in self.children:
#                     value = min(ch.calcValue(), value)
#         self.value = value
#         return value    
    
#     def best_move(self):
#         best_value=self.value
#         for ch in self.children:
#             if ch.value is best_value:
#                 return ch.move
#         return None ##if this node does not have children
    
#     def printNode(self):
#         print("Node:\n")
#         print("  has_parent: "+str(self.parent is not None))
#         print("  no. of children: "+str(len(self.children)))
#         print("  result: "+(("player "+str(self.won)+" won" if self.won is not 0 else "draw") if self.finished else "not yet finished"))
#         print("  game state:")
#         prettyPrintTTT(self.state)    

class GameTreeNode3: 
    def __init__(self, gstate, parentNode=None, last_move=None, valid_move_list=None):
        self.state=gstate
        self.finished, self.won = checkFinishedAndWhoWon(self.state)
        self.parent=parentNode
        self.children=[]
        self.move = last_move
        self.Q = 0 #number of wins
        self.N = 0 #number of visits
        self.valid_moves = valid_move_list
        
    def fully_expanded(self):
        return len(self.children) is len(self.valid_moves)
    
    def expand(self,move,n_rollouts):
        #when expanding a node with a new child node, we are not also going to perform a number of roll-outs.
        #first, we create the new node:
        new_state = play(self.state, move)
        if(new_state is None):
            return
        new_valid_moves = copy.deepcopy(self.valid_moves)
        new_valid_moves.remove(move)
        new_node = GameTreeNode3(new_state, parentNode=self, last_move=move,valid_move_list=new_valid_moves)
        #add it to the children:
        self.children.append(new_node)
        #and then perform a number of random roll-outs: random plays until the game finishes
        for i in range(n_rollouts):
            score = new_node.roll_out()
            #and process the result (score) we get from this rollout
            new_node.process_result(score)
    
    def roll_out(self):
        #rollouts are quite simple
        #when the node respresents a game state of a game that's finished, we immediately return the result
        if(self.finished):
            if(self.won is 1):
                return 1
            elif(self.won is 2):
                return -1
            else:
                return 0
        #else we play moves in on the remaining open fields
        moves = copy.deepcopy(self.valid_moves)
        random.shuffle(moves)
        new_state = self.state
        for move in moves:
            new_state = play(new_state, move)
            fin, whowon = checkFinishedAndWhoWon(new_state)
            #until the game finishes, and return the score:
            if(fin):
                if(whowon is 1):
                    return 1
                elif(whowon is 2):
                    return -1
                else:
                    return 0
        
    def process_result(self,rollout_result):
        #then we increase Q by the score, and N by 1
        self.Q+=rollout_result
        self.N+=1
        #and do the same, recursively, for its ancestors
        if(self.parent is not None):
            self.parent.process_result(rollout_result)
            

def tree2StringWithValues(game_tree_node3, prefix=""):
    result=""
    if(game_tree_node3 is not None):
        result+=prefix+str(int(len(prefix)/2))+": "+str(game_tree_node3.state)+"\n"
        result+=prefix+"value: "+str(game_tree_node3.Q/game_tree_node3.N)+"\n"
        result+=prefix+"{\n"
        cprefix=(prefix+"  ")
        for child in game_tree_node3.children:
            result+=tree2StringWithValues(child,cprefix)
        result+=prefix+"}\n"
    return result

#when we do this, with a 100 roll-outs for each child node, we get value estimates (not exact values, just estimates)
#for each child node:
root = GameTreeNode3(state, valid_move_list=[(1,1),(2,0),(2,1)])
for mv in root.valid_moves:
    root.expand(mv, 100)
print(tree2StringWithValues(root))
            

                
###A: check all valid moves
def validMoves(game_state):
    validMoves = [] #validMoves is a list of (row, col) tuples of available moves
    for i in range(0, 3):                                   # (0,0), (0,1), (0, 2)
        for j in range(0, 3):                               # (1,0), (1,1), (1, 2)
            if game_state[1][i][j] == 0:                    # (2,0), (2,1), (2, 2)
                validMoves.append((i, j))
    return validMoves
       
###B: getting a new game state
def play(game_state, move): ##move is a tuple indicating where the player to move is going to place a stone
    new_game_state = ( (1 if (game_state[0] is 2) else 2), copy.deepcopy(game_state[1]))
    if(new_game_state[1][move[0]][move[1]] is 0):
        new_game_state[1][move[0]][move[1]]=game_state[0]
    else:
        return None #invalid move
    return new_game_state

###C: adding new nodes to the tree
def expandAllByOnePly(game_tree_node, valid_moves):
    if(game_tree_node.finished):
        return False ##Nothing to do here, the game is finished
    for move in valid_moves: 
        new_state = play(game_tree_node.state, move)
        game_tree_node.children.append(GameTreeNode3(new_state, parentNode=game_tree_node, last_move=move))
    return True

def expandFully(game_tree_node):
    valid_moves = validMoves(game_tree_node.state)
    res = expandAllByOnePly(game_tree_node, valid_moves)
    if res == False:
        return
    else:
        for child in game_tree_node.children:
            # child.value = child.calcValue()
            expandFully(child)
            
    
#Now let us define a function that "pretty" prints a tree (starting from a root node) 
def tree2String(game_tree_node, prefix=""):
    result=""
    if(game_tree_node is not None):
        result+=prefix+str(int(len(prefix)/2))+": "+str(game_tree_node.value)+": "+str(game_tree_node.state)+"\n"
        result+=prefix+"{\n"
        cprefix=(prefix+"  ")
        for child in game_tree_node.children:
            result+=tree2String(child,cprefix)
        result+=prefix+"}\n"
    return result

#reinitialising the root node (because that's easier than re-evaluating the previous cells)
root = GameTreeNode3(state)    

#I'm cheating here, please replace this by your own function from Assignment 1: 
# valid_moves = [(2,0), (2,1), (1,1)]
valid_moves = validMoves(state)

# expandAllByOnePly(root,valid_moves)
expandFully(root)
root.calcValue()
print(tree2String(root))
print("Best move: "+ str(root.best_move()))

# root = GameTreeNode(state)
root.printNode()