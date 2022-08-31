package main

import (
	"fmt"
	"strconv"
	"sort"
	"strings"
)

func largestNumber(nums []int) string {
	nl := len(nums)
	ns := make([]string, nl)
	for i, v := range nums {
		ns[i] = strconv.Itoa(v)
	}
	sort.Slice(ns, func(i, j int) bool {
		return ns[i] + ns[j] > ns[j] + ns[i]
	})

	if ns[0] == "0" {
		return "0"
	}

	// fmt.Println(ns)
	var b strings.Builder

	for i := 0; i < nl; i++ {
		b.WriteString(ns[i])
	}

	return b.String()
}

func main() {
	fmt.Println(largestNumber([]int{10, 2}))
	fmt.Println(largestNumber([]int{3, 30, 34, 5, 9}))
}
