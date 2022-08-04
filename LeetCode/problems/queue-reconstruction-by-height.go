/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/queue-reconstruction-by-height/
 */
package main

import (
	"fmt"
	"sort"
)

func reconstructQueue(people [][]int) [][]int {
	rli := make([][]int, len(people))
	for i := range rli {
		rli[i] = []int{-1, -1}
	}

	if len(people) == 0 {
		return rli
	}

	sort.Slice(people, func (i, j int) bool { return people[i][0] < people[j][0] })

	// fmt.Println(people)

	for i := 0; i < len(people); i++ {
		height, ignore := people[i][0], people[i][1]
		j := 0
		// fmt.Println("Ignore number, insert p:", ignore, people[i])
		for ;j < len(people); j++ {
			if rli[j][0] == -1 || rli[j][0] == height {
				ignore--
			}

			if (ignore < 0) {
				break
			}
		}
		rli[j] = people[i]
		// fmt.Println("i, j, rli :", i, j, rli)
	}

	return rli
}

func main() {
	fmt.Println(reconstructQueue([][]int{[]int{7, 0}, []int{4, 4}, []int{7, 1}, []int{5, 0}, []int{6, 1}, []int{5, 2}}))
}
