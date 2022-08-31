package main

import (
	"fmt"
	"time"
	// "strings"
)

func PositiveOrZero(i int) int {
	if i < 0 {
		return 0
	}
	return i
}

type V struct {
	v []int
}

func (v * V) PopF() (r int) {
	r = v.v[0]
	v.v = v.v[1:]
	return
}

func (v * V) PopB() (r int) {
	ri := len(v.v) - 1
	r = v.v[ri]
	v.v = v.v[:ri]
	return
}

func (v * V) Push(x int) {
	v.v = append(v.v, x)
}

func (v * V) Empty() bool {
	return len(v.v) == 0
}

func RKD(num []byte, k int) []byte {
	// fmt.Printf("%v, k %d\n", num, k)
	nl := len(num)
	nk := k

	if nl == k {
		return []byte{'0'}
	}

	tags := make([]byte, nl - 1)
	for i := 0; i < nl - 1; i++ {
		ni, ni1 := num[i], num[i+1]
		if ni < ni1 {
			tags[i] = 'U'
		} else if ni > ni1 {
			tags[i] = 'D'
		} else {
			tags[i] = 'E'
		}
	}

	// shift status
	for i := nl - 1 - 1 - 1; i >= 0; i-- {
		if tags[i] == 'E' {
			tags[i] = tags[i + 1]
		}
	}
	// make sure last Es are replaced
	for i := 1; i < nl - 1; i++ {
		if tags[i] == 'E' {
			tags[i] = tags[i - 1]
		}
	}

	// That means all elements in nums are the same
	if tags[0] == 'E' {
		return nums[:k]
	}

	// delete D from start to end
	// delete U from end to start
	for i := 0; i < nl - 1 && k > 0; i++ {
		if tags[i] == 'D' {
			k--
			num[i] = 0
		}
	}

	for i := nl - 2; i >= 0 && k > 0; i-- {
		if tags[i] == 'U' {
			k--
			num[i + 1] = 0
		}
	}

	tags = tags[:0]

	wi, ri := 0, 0
	for ri < nl && (num[ri] == 0 || num[ri] == '0') {
		ri++
	}

	for ; ri < nl; ri++ {
		if num[ri] != 0 {
			num[wi] = num[ri]
			wi++
		}
	}

	if wi == 0 {
		return []byte{'0'}
	}

	num = num[:wi]
	// fmt.Printf("\tFor one loop, num = %+v, k rest %d\n", num, k)
	// time.Sleep(time.Second / 2)
	if k > 0 || wi + nk > nl {
		return RKD(num, wi + nk - nl)
	}

	return num
}

func removeKdigits(num string, k int) string {
	return string(RKD([]byte(num), k))
}

func main() {
	time.Sleep(0)
	// fmt.Println(removeKdigits("1432219", 3))
	// fmt.Println(removeKdigits("10200", 1))
	// fmt.Println(removeKdigits("10", 2))
	// fmt.Println(removeKdigits("112", 1))
	// fmt.Println(removeKdigits("10001", 4))
	// fmt.Println(removeKdigits("1111", 2))
	fmt.Println(removeKdigits("1173", 2))
	fmt.Println(removeKdigits("5337", 2))
	fmt.Println(removeKdigits("12345", 2))
}
