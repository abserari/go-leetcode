package main

import "fmt"

func main() {
	var m, n int
	fmt.Scanln(&m, &n)
	fmt.Println(fn(m, n))
}

func fn(m int, n int) int {
	if m == 1 {
		return n
	} else if n == 1 {
		return m
	} else {
		return fn(m-1, n) + fn(m, n-1)
	}
}
