/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
 */
package main

import (
	"fmt"
)

var kmap = map[byte]string{
	'2' : "abc",
	'3' : "def",
	'4' : "ghi",
	'5' : "jkl",
	'6' : "mno",
	'7' : "pqrs",
	'8' : "tuv",
	'9' : "wxyz",
}

func letterCombinations(digits string) []string {
	rli := make([]string, 0, 6)
	if len(digits) <= 0 {
		return rli
	}

	for _, preload := range kmap[digits[0]] {
		rli = append(rli, string(preload))
	}

	i := 1
	for i < len(digits) {
		curlr := len(rli)
		curks := kmap[digits[i]]

		for _, prefix := range rli {
			for _, end := range curks {
				rli = append(rli, prefix + string(end))
			}
		}

		rli = rli[curlr:]
		i++
	}
	return rli;
}

func main() {
	fmt.Println(letterCombinations("23"))
	fmt.Println(letterCombinations(""))
	fmt.Println(letterCombinations("2"))
}
