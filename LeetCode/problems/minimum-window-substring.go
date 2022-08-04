/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/minimum-window-substring/
 */
package main

import (
	"fmt"
)

func charToIndex(s byte) byte {
	if 'a' <= s && s <= 'z' {
		return s - 'a'
	}
	return s - 'A' + 26
}

func checkOk(bools []bool) bool {
	not_ok := false
	for _, b := range bools {
		not_ok = b || not_ok
	}
	return !not_ok
}

func minWindow(s string, t string) string {
	if len(t) > len(s) {
		return ""
	}

	nmap := make([]int8, 53) // 'z' is 122
	tmap := make([]bool, 53)
	cmap := make([]bool, 53) // not changed
	for i := range t {
		b := charToIndex(t[i])
		nmap[b] += 1
		tmap[b] = true
		cmap[b] = true
	}

	l, mlp, mlen := 0, 0, len(s) + 1
	for r := 0; r < len(s); r++ {
		bi := charToIndex(s[r])
		nmap[bi]--
		if cmap[bi] && nmap[bi] <= 0 {
			tmap[bi] = false
		}

		for checkOk(tmap) {
			lbi := charToIndex(s[l])
			nmap[lbi]++
			if cmap[lbi] && nmap[lbi] > 0 {
				tmap[lbi] = true
				slen := r - l + 1
				if slen < mlen {
					mlen = slen
					mlp = l
				}
				l++
				break
			}
			l++
		}
	}

	if mlen == len(s) + 1 {
		return ""
	}

	return s[mlp: mlp + mlen]
}

func main() {
	// fmt.Println(minWindow("ADOBECODEBANC", "ABC"))
	// fmt.Println(minWindow("a", "a"))
	// fmt.Println(minWindow("a", "aa"))
	// fmt.Println(minWindow("a", "b"))
	fmt.Println(minWindow("aaaaaaaaaaaabbbbbcdd", "abcdd"))
}
