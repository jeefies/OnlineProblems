/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/sum-of-square-numbers/
 */
package main

import (
	"fmt"
	"math"
	_ "time"
)

/*
var squares [65540]int64
var inited bool = false

func min(x, y int64) int64 {
	if x < y {
		return x
	}
	return y
}

func judgeSquareSum(c int) bool {
	if c <= 2 {
		return true
	}

	if !inited {
		inited = true
		var i int64
		l := int64(len(squares))
		for i = 0; i < l; i++ {
			squares[i] = i * i
		}
	}

	var t int64 = int64(c)
	var l, r int64 = 0, min((t + 1) / 2, 65539)

	for l < r {
		for l < r && squares[l] + squares[r] < t {
			l++
		}

		for l < r &&  squares[l] + squares[r] > t {
			r--
		}

		if squares[l] + squares[r] == t {
			return true
		}
	}

	return false
}
*/

func judgeSquareSum(c int) bool {
	l, r := 0, int(math.Sqrt(float64(c))) + 1

	for l <= r {
		l2 := l * l
		for l <= r && l2 + r * r > c {
			r--
		}

		r2 := r * r
		for l <= r && r2 + l * l < c {
			l++
		}

		if r2 + l * l == c {
			return true
		}
	}
	return false
}

func main() {
	fmt.Println(judgeSquareSum(5))
	fmt.Println(judgeSquareSum(3))
	fmt.Println(judgeSquareSum(1))
	fmt.Println(judgeSquareSum(4))
	fmt.Println(judgeSquareSum(8))
	fmt.Println(judgeSquareSum(13))
	fmt.Println(judgeSquareSum(2147483646))
	fmt.Println(judgeSquareSum(2147483642))
}
