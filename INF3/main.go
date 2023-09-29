package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func run() {
	nums := readNumbers()
	res := gcd(nums...)
	fmt.Printf("наибольший общий делитель: %v\n", res)
}

func readNumbers() []int {
	fmt.Print("введите целые положительные числа через пробел или в разных строках; ")
	fmt.Print("0 завершает последовательность\n")

	var nums []int
	r := bufio.NewReader(os.Stdin)

	for {
		fmt.Print("> ")
		line, err := r.ReadString('\n')
		if err != nil {
			fmt.Print("произошла ошибка при чтении строки, попробуйте ещё раз\n")
			continue
		}

		line = strings.TrimSpace(line)

		newNums, err := extractNumbers(line)
		if err != nil {
			fmt.Printf("ошибка парсинга: %s\n", err)
			continue
		}

		if len(newNums) == 0 {
			continue
		}

		for _, num := range newNums {
			if num == 0 {
				return nums
			}

			if num < 0 {
				num *= -1
			}

			nums = append(nums, num)
		}

		fmt.Printf("добавлено: %v\n", newNums)
	}
}

func extractNumbers(s string) ([]int, error) {
	words := strings.Split(s, " ")
	nums := make([]int, 0, len(words))
	for _, word := range words {
		if word == "" {
			continue
		}

		num, err := strconv.Atoi(word)
		if err != nil {
			return nil, fmt.Errorf("строка содержит нечисловые значения: %q", word)
		}

		nums = append(nums, num)
	}
	return nums, nil
}

func gcd(nums ...int) int {
	switch len(nums) {
	case 2: // стандартный рекурсивный алгоритм для двух чисел
		if nums[0] == 0 {
			return nums[1]
		}
		return gcd(nums[1]%nums[0], nums[0])

	case 1: // одно число является своим наибольшим делителем
		return nums[0]

	case 0: // тупой вход = тупой выход
		return 0

	default:
		res := nums[0]
		for _, num := range nums[1:] {
			res = gcd(res, num)
		}
		return res
	}
}

func main() {
	fmt.Println("эта программа находит наибольший общий делитель конечной последовательности целых чисел")
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
