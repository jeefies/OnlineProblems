package main

import (
	"fmt"
	"time"
)

const (
	UP = iota
	DOWN
	EVEN
)

func gainStatus(x, y int) int {
	if x > y {
		return DOWN
	} else if x < y{
		return UP
	} else {
		return EVEN
	}

	// should not reach here
	return 0
}

func wiggleMaxLength(nums []int) int {
	fmt.Println(nums)
	seql := 1
	ln := len(nums)

	if ln == 1 {
		return 1
	}

	prevStatus := gainStatus(nums[0], nums[1])
	
	if ln == 2 {
		if prevStatus == EVEN {
			return 1
		}
		return 2
	}

	if prevStatus == EVEN {
		seql = 0
	}

	for i := 1; i < ln - 1; i++ {
		curStatus := gainStatus(nums[i], nums[i + 1])
		fmt.Printf("\ti := %d, prevStatus %d to curStatus %d\n", i, prevStatus, curStatus)
		if curStatus != EVEN && curStatus != prevStatus {
			seql++
			prevStatus = curStatus
		}

		fmt.Printf("\t\tSeql is %d\n", seql)
		time.Sleep(time.Second / 2)
	}

	if prevStatus != EVEN {
		seql += 1
	}
	return seql
}

func main() {
	time.Sleep(0)
	fmt.Println(wiggleMaxLength([]int{1, 7, 4, 9, 2, 5}))
	fmt.Println(wiggleMaxLength([]int{1, 17, 5, 10, 13, 15, 10, 5, 16, 8}))
	fmt.Println(wiggleMaxLength([]int{1, 2, 3, 4, 5, 6, 7, 8, 9}))
	fmt.Println(wiggleMaxLength([]int{5, 4, 3, 2, 1}))
	fmt.Println(wiggleMaxLength([]int{0}))
	fmt.Println(wiggleMaxLength([]int{7, 1, 9, 4, 5, 2}))
	fmt.Println(wiggleMaxLength([]int{0, 0}))
	fmt.Println(wiggleMaxLength([]int{3, 3, 3, 2, 5}))
	fmt.Println(wiggleMaxLength([]int{3, 3, 2, 5}))
}
