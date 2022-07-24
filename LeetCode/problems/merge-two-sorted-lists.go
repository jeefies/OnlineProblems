/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL : https://leetcode.cn/problems/merge-two-sorted-lists/
 */
package main

import (
	"fmt"
)


type ListNode struct {
    Val int
    Next *ListNode
}

func Append(li * ListNode, val int) *ListNode {
	if li == nil {
		return &ListNode{val, nil}
	}

	li.Next = &ListNode{val, nil}
	return li.Next
}

func mergeTwoLists(list1 *ListNode, list2 *ListNode) *ListNode {
	// Avoid empty list
	if list1 == nil {
		return list2
	}

	if list2 == nil {
		return list1
	}

	var rli * ListNode = nil
	curp := rli
	for list1 != nil || list2 != nil {
		if list1 == nil {
			curp = Append(curp, list2.Val)
			list2 = list2.Next
			continue
		}
		if list2 == nil {
			curp = Append(curp, list1.Val)
			list1 = list1.Next
			continue
		}

		for list1 != nil && list2 != nil && list1.Val < list2.Val {
			if rli == nil {
				rli = Append(rli, list1.Val)
				curp = rli
			} else {
				curp = Append(curp, list1.Val)
			}
			list1 = list1.Next
		}

		if list2 == nil {
			continue
		}

		if rli == nil {
			rli = Append(rli, list2.Val)
			curp = rli
		} else {
			curp = Append(curp, list2.Val)
		}

		if list2 != nil {
			list2 = list2.Next
		}
	}
	return rli
}

func PrintList(p *ListNode) {
	for p != nil {
		fmt.Print(p.Val, " ")
		p = p.Next
	}
	fmt.Print("\n")
}

func main() {
	PrintList(mergeTwoLists(&ListNode{1, &ListNode{2, &ListNode{3, nil}}}, &ListNode{1, &ListNode{2, &ListNode{4, nil}}}))
	PrintList(mergeTwoLists(nil, nil))
	PrintList(mergeTwoLists(nil, &ListNode{0, nil}))
}
