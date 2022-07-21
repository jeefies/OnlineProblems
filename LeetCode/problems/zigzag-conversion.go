/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * Origin URL: leetcode.cn/problems/zigzag-conversion
 */
package main

import (
	"fmt"
)

func IMin(x, y int) int {
	if x > y {
		return y
	}
	return x
}

/* Bad Solution 1
func convert(s string, numRows int) string {
	b := []byte(s)
	bl := len(b)
	if bl == 1 {
		return s
	}
	rows := make([][]byte, numRows)
	index := 0
	for index < bl {
		for i := 0; i < numRows - 1 && index < bl; i++ {
			rows[i] = append(rows[i], b[index])
			index++
			fmt.Println(i)
		}
		for i := numRows - 1; i > 0 && index < bl; i-- {
			rows[i] = append(rows[i], b[index])
			index++
			fmt.Println(i)
		}
	}
	r := ""
	for _, v := range rows {
		r += string(v)
	}
	return r
}
*/
func convert(s string, numRows int) string {
    n, r := len(s), numRows
    if r == 1 || r >= n {
        return s
    }
    t := r*2 - 2
    ans := make([]byte, 0, n)
    for i := 0; i < r; i++ { // 枚举矩阵的行
        for j := 0; j+i < n; j += t { // 枚举每个周期的起始下标
            ans = append(ans, s[j+i]) // 当前周期的第一个字符
            if 0 < i && i < r-1 && j+t-i < n {
                ans = append(ans, s[j+t-i]) // 当前周期的第二个字符
            }
        }
    }
    return string(ans)
}


func main() {
	fmt.Print(convert("PAYPALISHIRING", 3))
}
