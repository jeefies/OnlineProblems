package main

import (
	"fmt"
	"time"
)

func canCompleteCircuit(gas []int, cost []int) int {
	stepn := len(gas)
	restAneed := make([]int, stepn)

	for i := 0; i < stepn; i++ {
		restAneed[i] = gas[i] - cost[i]
	}

	// fmt.Println(restAneed)

	start_index := -1
	for i := 0; i < stepn; i++ {
		if restAneed[i] >= 0 {
			// 测试循环
			restGas := restAneed[i]
			ok := true

			// fmt.Printf("Start test at %d\n", i)

			s := i
			for {
				s++
				if s >= stepn { s = 0 }
				if s == i { break }

				if restAneed[s] == 0 {
					continue
				}

				restGas += restAneed[s]
				if restGas < 0 {
					// 不能
					ok = false
					break
				}
				
				// fmt.Printf("\tTest Loop at %d\n", s)
				// time.Sleep(time.Second / 2)
			}
			
			if ok {
				start_index = i
				break
			}
		}
	}

	return start_index
}

func main() {
	time.Sleep(0)
	fmt.Println(canCompleteCircuit([]int{1, 2, 3, 4, 5}, []int{3, 4, 5, 1, 2}))
	fmt.Println(canCompleteCircuit([]int{2, 3, 4}, []int{3, 4, 3}))
	fmt.Println(canCompleteCircuit([]int{3, 1, 1}, []int{1, 2, 2}))
}
