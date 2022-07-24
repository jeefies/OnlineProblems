/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * https://leetcode.cn/problems/swap-nodes-in-pairs/
 */
package main

import (
	"fmt"
)

type ListNode struct {
    Val int
    Next *ListNode
}

func PrintList(p *ListNode) {
	for p != nil {
		fmt.Print(p.Val, " ")
		p = p.Next
	}
	fmt.Print("\n")
}

func swapPairs(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	// get first node
	rli := head.Next
	head.Next = rli.Next
	rli.Next = head
	
	parent := head
	for {
		if parent.Next == nil || parent.Next.Next == nil {
			break
		}

		c := parent.Next
		d := c.Next
		c.Next = d.Next
		parent.Next = d
		d.Next = c

		parent = c
	}
	return rli
}

func main() {
	PrintList(swapPairs(&ListNode{1, &ListNode{2, &ListNode{3, &ListNode{4, nil}}}}))
	PrintList(swapPairs(&ListNode{1, &ListNode{2, &ListNode{3, nil}}}))
}
