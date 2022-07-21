/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/integer-to-roman/
 */
package main

import (
	"fmt"
	"strings"
)

func intToRoman(num int) string {
	var r strings.Builder
	nmap := []int{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}
	cmap := []string{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"}

	for i := range nmap {
		for num >= nmap[i] {
			num -= nmap[i]
			r.WriteString(cmap[i])
		}
	}
	return r.String()
}

func main() {
	fmt.Println(intToRoman(3)) // III
	fmt.Println(intToRoman(4)) // IV
	fmt.Println(intToRoman(9)) // IX
	fmt.Println(intToRoman(58)) // LVIII
	fmt.Println(intToRoman(1994)) // MCMXCIV
}
