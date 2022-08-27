package main

import (
	"fmt"
)

var dx = []int{1, 0, -1, 0};
var dy = []int{0, 1, 0, -1};

func insearch(board [][]byte, x, y int, word []byte, n int) bool {
	if n == len(word) { return true }

	if (x < 0 || y < 0 || x >= len(board) || y >= len(board[0]) || board[x][y] != word[n]) { return false }

	b := word[n]
	word[n] = 0

	n += 1
	ok := false
	for i := range dx {
		ok = ok || insearch(board, x + dx[i], y + dy[i], word, n)
	}

	word[n - 1] = b
	return ok
}

func exist(board [][]byte, word_ string) bool {
	word := []byte(word_)
	for i := range board {
		for j := range board[i] {
			if (insearch(board, i, j, word, 0)) {
				return true;
			}
		}
	}
	return false;
}

func main() {
	fmt.Println(exist([][]byte{[]byte("ABCE"), []byte("SFCS"), []byte("ADEE")}, "SEE"))
	fmt.Println(exist([][]byte{[]byte("ABCE"), []byte("SFCS"), []byte("ADEE")}, "ABCCED"))
	fmt.Println(exist([][]byte{[]byte("ABCE"), []byte("SFCS"), []byte("ADEE")}, "ABCB"))
}
