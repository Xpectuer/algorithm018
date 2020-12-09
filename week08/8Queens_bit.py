class Solution:
    def totalNQueens(self, n: int) -> int:
        if n < 1: return []
        self.count = 0
        self.DFS(n,0,0,0,0)
        return self.count
    def DFS(self, n, row, cols, pie, na):
        # recursion terminator
        if row >= n:
            self.count +=1
            return
         '''
        假设当前 n = 4,
        1层：
        row, col , pie, na = 0,0,0,0
        bits = 0b1111
        进入循环：
            p = 1 , 最低1位在第1位
            bits = bits & (bit -1)
            bits = 0b1110, 在最低位试探一个皇后
        ----drill down----
        2层：
        row = 1, col = 0b0001, pie = 0b0010, na = 0b0000
        bits = (~(0011)) & (1111)  # num&mask
             = 1100
        得到此时的可用位置
        循环：
            p=0100
            bit = 1000 # 打掉p位的Q
        ----drill down----
        以此类推
        ...
        
        '''
        bits = (~(cols | pie | na)) & ((1 << n)-1 ) # 得到本层的空位
    while bits:
        p = bits & -bits # 取得最低位的1的位置
        bits = bits & (bit - 1) # 在最低的1位放上皇后，即p位
        # 下探一层，往可行的位置放上皇后
        self.DFS(n, row + 1, cols | p, (pie | p) << 1, (na | p)>>1)
