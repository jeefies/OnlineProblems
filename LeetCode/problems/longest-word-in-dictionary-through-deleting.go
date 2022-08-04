/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/longest-word-in-dictionary-through-deleting/
 */
package main

import (
	"fmt"
	"sort"
)

func findLongestWord(s string, dictionary []string) string {
	sort.Slice(dictionary, func (i, j int) bool {
		il, jl := len(dictionary[i]), len(dictionary[j])
		if il == jl {
			return dictionary[i] < dictionary[j]
		}
		return il > jl
	})

	sl := len(s)
	for _, w := range dictionary {
		sp, wp := 0, 0
		ok := true
		for wp = 0; wp < len(w); wp++ {
			for sp < sl {
				if s[sp] == w[wp] {
					sp++
					break
				}
				sp++
			}
			if sp == sl && wp + 1 != len(w) {
				ok = false
				break
			}
		}

		if ok {
			return w
		}
	}

	return ""
}

func main() {
	// fmt.Println(findLongestWord("abpcplea", []string{"ale","apple","monkey","plea"}))
	// fmt.Println(findLongestWord("abpcplea", []string{"c", "b", "a"}))
	fmt.Println(findLongestWord("aaa", []string{"aaa", "aa", "a"}))
}
