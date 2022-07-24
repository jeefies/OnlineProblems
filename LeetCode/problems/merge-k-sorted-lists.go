/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */
package main

import (
	"fmt"
	"sort"
)

type ListNode struct {
    Val int
    Next *ListNode
}

// Too bad solution
// func mergeTwoLists(list1 *ListNode, list2 *ListNode) *ListNode {
// 	// Avoid empty list
// 	if list1 == nil {
// 		return list2
// 	}
// 
// 	if list2 == nil {
// 		return list1
// 	}
// 
// 	var rli * ListNode = nil
// 	curp := rli
// 	for list1 != nil || list2 != nil {
// 		if list1 == nil {
// 			curp = Append(curp, list2.Val)
// 			list2 = list2.Next
// 			continue
// 		}
// 		if list2 == nil {
// 			curp = Append(curp, list1.Val)
// 			list1 = list1.Next
// 			continue
// 		}
// 
// 		for list1 != nil && list2 != nil && list1.Val < list2.Val {
// 			if rli == nil {
// 				rli = Append(rli, list1.Val)
// 				curp = rli
// 			} else {
// 				curp = Append(curp, list1.Val)
// 			}
// 			list1 = list1.Next
// 		}
// 
// 		if list2 == nil {
// 			continue
// 		}
// 
// 		if rli == nil {
// 			rli = Append(rli, list2.Val)
// 			curp = rli
// 		} else {
// 			curp = Append(curp, list2.Val)
// 		}
// 
// 		if list2 != nil {
// 			list2 = list2.Next
// 		}
// 	}
// 	return rli
// }
// 
// func mergeKLists(lists []*ListNode) *ListNode {
// 	if len(lists) == 0 {
// 		return nil
// 	}
// 
// 	if len(lists) == 1 {
// 		return lists[0]
// 	}
// 
// 	rli := mergeTwoLists(lists[0], lists[1])
// 	for i := 2; i < len(lists); i++ {
// 		rli = mergeTwoLists(rli, lists[i])
// 	}
// 	return rli
// }


// No a best solution, but a ordinary one
func Append(li * ListNode, val int) *ListNode {
	if li == nil {
		return &ListNode{val, nil}
	}

	li.Next = &ListNode{val, nil}
	return li.Next
}


func mergeKLists(lists []*ListNode) *ListNode {
	if len(lists) == 0 {
		return nil
	}

	if len(lists) == 1 {
		return lists[0]
	}

	rslice := make([]int, 0, 50)
	for _, li := range lists {
		for li != nil {
			rslice = append(rslice, li.Val)
			li = li.Next
		}
	}

	sort.Ints(rslice)

	if len(rslice) == 0 {
		return nil
	}

	if len(rslice) == 1 {
		return Append(nil, rslice[0])
	}

	rli := Append(nil, rslice[0])
	curp := rli
	for i := 1; i < len(rslice); i++ {
		curp = Append(curp, rslice[i])
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
