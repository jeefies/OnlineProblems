package main

import (
	"fmt"
)


func calcSum(matrix [][]int, a, b, x, y int) (r int) {
	r = matrix[x][y]
	if a > 0 {
		r -= matrix[a - 1][y]
	}

	if b > 0 {
		r -= matrix[x][b - 1]
	}

	if a > 0 && b > 0 {
		r += matrix[a - 1][b - 1]
	}
	// if a, b == 0, do nothing
	// fmt.Printf("Calc (%d,%d) and (%d, %d) is %d\n", a, b, x, y, r)
	return r
}

func max(x, y int) int {
	if x > y { return x }
	return y
}

func sumMatrix(matrix [][]int) [][]int {
    w := len(matrix)
    h := len(matrix[0])
	r := make([][]int, w + 1)
	for i:= 0; i < w + 1; i++ {
		r[i] = make([]int, h + 1)
	}

    for j := 0; j < h; j++ {
        for i := 1; i < w + 1; i++ {
            r[i][j + 1] = matrix[i - 1][j] + r[i - 1][j + 1]
        }
    }

	return r
}

func getMaxMatrix(matrix [][]int) []int {
	// fmt.Println(matrix)
	matrix = sumMatrix(matrix)
	// fmt.Println(matrix)

	w, h := len(matrix), len(matrix[0])
	// dp := make([]int, h)

	maxn := -(1 << 32)
	maxp := make([]int, 4)

	for x := 1; x < w; x++ {
		for a := 0; a < x; a++ {
			b, y, sum := 1, 1, 0

			for i := 1; i < h; i++ {
				xa := matrix[x][i] - matrix[a][i]
				if sum < 0 {
					b, y = i, i
					sum = 0
				} else if sum + xa > sum {
					y = i
				}
				sum += xa

				if sum > maxn {
					maxn = sum
					maxp[0], maxp[1], maxp[2], maxp[3] = a, b - 1, x - 1, y - 1
				}
			}
		}
	}

	return maxp
}

func main() {
	fmt.Println(getMaxMatrix([][]int{[]int{-1, 0}, []int{0, -1}}))
	fmt.Println(getMaxMatrix([][]int{[]int{9, -8, 1, 3, -2}, []int{-3, 7, 6, -2, 4}, []int{6, -4, -4, 8, -7}}))
}
