/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/generate-parentheses/
 */
package main

import (
	"fmt"
)

func gP(prefix string, needLeft, needRight int) []string {
	if needRight + needLeft == 0 {
		return []string{prefix}
	}

	rli := make([]string, 0, 2)

	if needLeft > 0 {
		rli = append(rli, gP(prefix + "(", needLeft - 1, needRight + 1)...)
	}

	if needRight > 0 {
		rli = append(rli, gP(prefix + ")", needLeft, needRight - 1)...)
	}

	return rli
}

func generateParenthesis(n int) []string {
	return gP("", n, 0)
}

func main() {
	fmt.Println(generateParenthesis(3))
	fmt.Println(generateParenthesis(1))
}
