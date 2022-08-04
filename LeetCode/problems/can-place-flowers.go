/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/can-place-flowers/
 */
package main

import (
	"fmt"
)

func canPlaceFlowers(flowerbed []int, n int) bool {
	for i := 0; i < len(flowerbed) && n > 0; i++ {
		// 保证上一个不会是1
		if (flowerbed[i] == 1) {
			i += 1
			continue
		}

		if flowerbed[i] == 0 {
			// 确保不会越界
			// 确定下一个不会是1
			if i + 1 < len(flowerbed) && flowerbed[i + 1] == 1 {
				continue
			}

			if n > 0 {
				n -= 1
				flowerbed[i] = 1
				i += 1
			}
		}
	}

	if n == 0 {
		return true
	}

	return false
}

func main() {
	fmt.Println(canPlaceFlowers([]int{0, 0, 1, 0, 0, 1}, 2))
	fmt.Println(canPlaceFlowers([]int{1, 0, 0, 0, 0, 1}, 2))
}
