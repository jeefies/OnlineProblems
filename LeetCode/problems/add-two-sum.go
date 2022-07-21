/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/add-two-sum
 */
package main

import (
	"fmt"
)

type ListNode struct {
	Val int
	Next *ListNode
}

func getVal(l *ListNode) int {
	if l == nil {
		return 0
	}
	return l.Val
}

func next(l *ListNode) *ListNode {
	if l == nil {
		return nil
	}
	return l.Next
}


func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	rl := []int{}
	c := 0
	for l1 != nil || l2 != nil || c != 0 {
		x := getVal(l1) + getVal(l2)
		l1, l2 = next(l1), next(l2)
		x += c
		rl = append(rl, x % 10)
		c = x / 10
	}
	rln := &ListNode{rl[0], nil}

	index := rln
	for i := 1; i < len(rl); i++ {
		index.Next = &ListNode{rl[i], nil}
		index = index.Next
	}
	return rln
}

func main() {
	li1 := &ListNode{9, &ListNode{9, &ListNode{9, &ListNode{9, &ListNode{9, nil}}}}}
	li2 := &ListNode{9, &ListNode{9, &ListNode{9, nil}}}
	// li1 := &ListNode{2, &ListNode{4, &ListNode{3, nil}}}
	// li2 := &ListNode{5, &ListNode{6, &ListNode{4, nil}}}

	rli := addTwoNumbers(li1, li2)
	for rli != nil {
		fmt.Printf("%d", rli.Val)
		rli = rli.Next
	}
	fmt.Println("")
}
