package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type Point struct {
	X, Y float64
}

func run() {
	p1, p2, p3 := askPoint(), askPoint(), askPoint()
	area := math.Abs(p1.X*(p2.Y-p3.Y)+p2.X*(p3.Y-p1.Y)+p3.X*(p1.Y-p2.Y)) / 2
	fmt.Printf("площадь треугольника: %.6f\n", area)
}

func askPoint() Point {
	r := bufio.NewReader(os.Stdin)

	for {
		fmt.Print("введите два целых числа через пробел: ")

		s, err := r.ReadString('\n')
		if err != nil {
			fmt.Println("произошла ошибка при чтении ввода")
			continue
		}

		// откидываем лишние символы вокруг ввода
		s = strings.TrimSpace(s)

		snum1, snum2, ok := strings.Cut(s, " ")
		if !ok {
			fmt.Println("пробел не найден")
			continue
		}

		num1, err := strconv.ParseFloat(snum1, 64)
		if err != nil {
			fmt.Println("неверное первое число")
			continue
		}

		num2, err := strconv.ParseFloat(snum2, 64)
		if err != nil {
			fmt.Println("неверное второе число")
			continue
		}

		return Point{num1, num2}
	}
}

func main() {
	fmt.Println("эта программа находит площадь треугольника на основе его точек")
	r := bufio.NewReader(os.Stdin)

	for {
		run()

		fmt.Print("снова? ('y'; любой иной ввод завершит программу): ")
		s, err := r.ReadString('\n')
		s = strings.TrimSpace(s)
		if err != nil || (s != "y" && s != "у") {
			//                         это русская у
			return
		}
	}
}
