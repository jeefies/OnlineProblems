/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/merge-sorted-array/
 */
package main

import (
	"fmt"
)

// func merge(nums1 []int, m int, nums2 []int, n int)  {
func merge(nums1 []int, m int, nums2 []int, n int)  []int {
	p := m + n - 1
	m, n = m - 1, n - 1

	for p >= 0 {
		if m < 0 {
			for n >= 0 {
				nums1[n] = nums2[n]
				n--
			}
			break
		} else if n < 0 {
			break
		}

		if nums1[m] > nums2[n] {
			nums1[p] = nums1[m]
			m--
		} else {
			nums1[p] = nums2[n]
			n--
		}
		p--
	}

	return nums1
}

func main() {
	fmt.Println(merge([]int{1,2,3,0,0,0}, 3, []int{2, 5, 6}, 3))
	fmt.Println(merge([]int{1}, 1, []int{}, 0))
	fmt.Println(merge([]int{0}, 0, []int{1}, 1))
}
