class Solution:
    def findLength(self, A: List[int], B: List[int]) -> int:
        ans = 0
        for i in range(len(A)):
            for j in range(len(B)):
                k = 0
                while i+k < len(A) and j+k< len(B) and A[i+k] is B[j+k]:
                    k +=1
                ans = ans if(ans > k) else k
        return ans
