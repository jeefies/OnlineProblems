/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/
 */
package main

import (
	"fmt"
	"sort"
	// "time"
)

func qsort(points [][]int, al, ar int) {
	if (al + 1 > ar) {
		return
	}

	l, r := al, ar
	tmp := points[l]

	for l < r {
		for l < r && points[r][1] >= tmp[1] {
			r--
		}
		points[l] = points[r]
		for l < r && points[l][1] <= tmp[1] {
			l++
		}
		points[r] = points[l]
	}
	points[l] = tmp;
	qsort(points, al, l)
	qsort(points, l + 1, ar)
}

func findMinArrowShots(points [][]int) int {
	if len(points) == 0 {
		return 0
	}

	// sort(points, 0, len(points) - 1)
	// fmt.Println(points)
	sort.Slice(points, func(i, j int) bool { return points[i][1] < points[j][1] })

	shots := 0
	i := 0
	for i < len(points) {
		aim := points[i][1]
		for i++; i < len(points); i++ {
			if points[i][0] > aim {
				break
			}
		}
		shots += 1
	}


	return shots
}

func main() {
	fmt.Println(findMinArrowShots([][]int{[]int{10, 16}, []int{2, 8}, []int{1, 6}, []int{7, 12}}))
	fmt.Println(findMinArrowShots([][]int{[]int{2, 3}, []int{2, 3}}))
	fmt.Println(findMinArrowShots([][]int{[]int{-1, 1}, []int{0, 1}, []int{2, 3}, []int{1, 2}}))
}
