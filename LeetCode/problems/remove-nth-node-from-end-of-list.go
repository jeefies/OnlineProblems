/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
 */
package main

import (
	"fmt"
)


type ListNode struct {
    Val int
    Next *ListNode
}

func removeNthFromEnd(head *ListNode, n int) *ListNode {
	curN := head
	dstN := head

	for i := 0; i < n; i++ {
		curN = curN.Next
	}

	if curN == nil {
		return head.Next
	}
	curN = curN.Next

	for curN != nil {
		curN = curN.Next
		dstN = dstN.Next
	}

	if dstN.Next != nil {
		dstN.Next = dstN.Next.Next
	}
	return head
}

func PrintList(p *ListNode) {
	for p != nil {
		fmt.Print(p.Val, " ")
		p = p.Next
	}
	fmt.Print("\n")
}

func main() {
	PrintList(removeNthFromEnd(&ListNode{1, &ListNode{2, &ListNode{3, &ListNode{4, &ListNode{5, nil}}}}}, 2))
	PrintList(removeNthFromEnd(&ListNode{1, nil}, 1))
	PrintList(removeNthFromEnd(&ListNode{1, &ListNode{2, nil}}, 1))
}
