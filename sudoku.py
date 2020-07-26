from time import time
class Solution:
    def solveSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        def check(x, y, s):
            for i in range(9):
                if board[i][y] == s or board[x][i] == s:
                    return False
            for i in [0, 1, 2]:
                for j in [0, 1, 2]:
                    if board[x//3*3+i][y//3*3+j] == s:
                        return False
            return True
        
        def bt(cur):
            if cur == 81:
                return True
            x, y = cur // 9, cur % 9
            if board[x][y] != '.':
                return bt(cur + 1)
            for i in range(1, 10):
                s = str(i)
                if check(x, y, s):
                    board[x][y] = s
                    if bt(cur + 1):
                        return True
                    board[x][y] = '.'
            return False
        
        bt(0)
board=[[".","9","4",".",".","5",".",".",".",],["3",".",".",".",".","9",".","6",".",],["1",".",".",".","8",".","9",".",".",],[".",".",".","7",".","6",".","1","2",],[".",".","3",".",".",".","4",".",".",],["2","1",".","9",".","8",".",".",".",],[".",".","1",".","7",".",".",".","3",],[".","4",".","8",".",".",".",".","9",],[".",".",".","5",".",".","6","2",".",]]
start = time()
Solution().solveSudoku(board)
for i in range(9):
    print(board[i])
    print("\n")
print(time()-start)
