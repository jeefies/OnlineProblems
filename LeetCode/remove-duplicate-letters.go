package main

import (
	"fmt"
)

// invalid!
func removeDuplicateLetters(s string) string {
	ls := len(s)
	n := make([]int, ls)
	for i := 0; i < ls; i++ {
		n[i] = int(s[i] - 'a')
	}

	prti := make([]int, ls)
	dp := make([]int, ls)

	maxn := 0
	lasti := 0
	for i := 0; i < ls; i++ {
		dp[i] = 0

		for j := 0; j < i; j++ {
			if s[j] < s[i] {
				if dp[i] < dp[j] + 1 {
					dp[i] = dp[j] + 1
					prti[i] = j
				}
			}
		}

		if dp[i] > maxn {
			lasti = i
			maxn = dp[i]
		}
	}

	res := make([]byte, maxn)
	for a := maxn - 1; a >= 0; a-- {
		res[a] = s[lasti]
		lasti = prti[lasti]
	}

	return string(res)
}

func main() {
	fmt.Println(removeDuplicateLetters("bcabc"))
	fmt.Println(removeDuplicateLetters("cbacdcbc"))
}
