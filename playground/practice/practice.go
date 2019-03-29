package main

import (
	"fmt"
	"time"
)

func main() {
	i := 0
	go func() {
		for true {
			i++
		}
	}()

	for true {
		//隔一秒打印i
		time.Sleep(1000000000)
		fmt.Println(i)
	}
}
