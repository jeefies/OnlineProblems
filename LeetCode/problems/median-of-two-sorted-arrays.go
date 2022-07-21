/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: leetcode.cn/problems/median-of-two-sorted-arrays/
 */
package main

import (
	"fmt"
)

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	nums := append(nums1, nums2...)
	nl := len(nums)
	qsort(nums, 0, nl - 1)
	fmt.Println(nums)
	return float64(nums[nl / 2] + nums[(nl - 1) / 2]) / 2
}

func qsort(vals []int, l, r int) {
	if (l >= r) {
		return
	}

	front, back := l, r
	temp := vals[l]
	for front < back {
		for front < back && vals[back] >= temp {
			back--
		}
		vals[front] = vals[back]
		for front < back && vals[front] <= temp {
			front++
		}
		vals[back] = vals[front]
	}
	vals[front] = temp
	qsort(vals, l, front)
	qsort(vals, front + 1, r)
}

func main() {
	fmt.Println(findMedianSortedArrays([]int{1, 3}, []int{2}))
}
