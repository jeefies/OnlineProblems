package main

import (
	"fmt"
	"time"
)

func integerReplacement(n int) int {
	t := 0
	for n != 1 {
		t++
		if n & 1 == 1 {
			if n & 2 == 2 && n >= 4 {
				n += 1
			} else {
				n -= 1
			}
		} else {
			n = n >> 1
		}
	}

	return t
}

func main() {
	time.Sleep(0)
	fmt.Println(integerReplacement(8))
	fmt.Println(integerReplacement(7))
	fmt.Println(integerReplacement(4))
	fmt.Println(integerReplacement(3))
}
