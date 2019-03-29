package main

import (
	"fmt"
	"math"
)

type point struct {
	x float64
	y float64
}

func main() {
	var points [4]point
	points[0] = point{
		x: 4,
		y: 12,
	}
	points[1] = point{
		x: 5,
		y: 6,
	}
	points[2] = point{
		x: 3,
		y: 14,
	}
	points[3] = point{
		x: 8,
		y: 18,
	}

	var minD, d float64
	minD = 10000000
	for m, p := range points {
		for n, q := range points {
			if m == n {
				continue
			}
			d = D(p, q)
			if minD > d {
				minD = d
			}
		}
	}

	fmt.Println(minD)
	return
}

func D(m, n point) float64 {
	return math.Sqrt((m.x-n.x)*(m.x-n.x) + (m.y-n.y)*(m.y-n.y))
}
