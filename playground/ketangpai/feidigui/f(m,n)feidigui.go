package main

import "fmt"

func main() {
	var m, n int
	fmt.Scanln(&m, &n)
	var sl [][]int

	for i := 0; i < m; i++ {
		sli := make([]int, 0, n)
		for j := 0; j < n; j++ {
			sli = append(sli, 0)
		}
		sl = append(sl, sli)
	}

	for i := 0; i < m; i++ {
		sl[i][0] = i + 1
	}
	for j := 1; j < n; j++ {
		sl[0][j] = j + 1
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			sl[i][j] = sl[i-1][j] + sl[i][j-1]
		}
	}

	fmt.Println(sl[m-1][n-1])
}
