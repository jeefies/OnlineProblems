/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/roman-to-integer/
 * 		This solution is too bad, it costs too much
 */
package main

import (
	"fmt"
)

func romanToInt(s string) int {
	// nmap := []int{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}
	// cmap := []string{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"}
	imap := map[string]int{
		"M" : 1000,
		"CM": 900,
		"D" : 500,
		"CD": 400,
		"C" : 100,
		"XC": 90,
		"L" : 50,
		"XL": 40,
		"X" : 10,
		"IX": 9,
		"V" : 5,
		"IV": 4,
		"I" : 1,
	}
	r := 0
	i, sl := 0, len(s)
	for i < sl {
		if i + 1 >= sl {
			r += imap[s[i:i+1]]
			return r
		}
		if val, ok := imap[s[i:i+2]]; ok {
			r += val
			i += 2
			continue
		}
		r += imap[s[i:i+1]]
		i++
	}
	return r
}

func main() {
	fmt.Println(romanToInt("III"))
	fmt.Println(romanToInt("IV"))
	fmt.Println(romanToInt("IX"))
	fmt.Println(romanToInt("LVIII"))
	fmt.Println(romanToInt("MCMXCIV"))
}
