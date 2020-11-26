func rob(nums []int) int {

     if nums==nil || len(nums)==0 {
        return 0
    }
    if len(nums)==1 {
        return nums[0]
    }

    return max(dp(nums[1:]), dp(nums[:len(nums)-1]));
}
func dp(nums []int) int {
    if nums==nil || len(nums)==0 {
        return 0
    }
    if len(nums)==1 {
        return nums[0]
    }

    first := nums[0]
    second := max(nums[0], nums[1])
		// 空间复杂度压缩到O(1)
    for i:=2;i<len(nums);i++ {
        first, second = second, max(first + nums[i], second)
    }
    return second
}
// go没有 max(int,int) int 的库函数，我们手动实现一个
func max(a int , b int) int {
    if a>b {
        return a
    }
    return b
}
