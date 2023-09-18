package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func run() {
	fmt.Println("эта программа решает проблему 196")
	num := readInput()
	i := 0

	for {
		if i >= 10000 {
			fmt.Printf("не удалось найти ответ за %d итераций; вероятно, его не найти; сворачиваемся", i)
			os.Exit(1)
		}

		fnum := num.Flip()
		if num.Equals(fnum) {
			break
		}

		i += 1
		num = num.Add(fnum)
	}

	fmt.Printf("понадобилось %d итераций чтобы получить %s\n", i, num)
}

func readInput() DynamicUint {
	r := bufio.NewReader(os.Stdin)

	for {
		fmt.Print("введите целое неотрицательное число: ")

		s, err := r.ReadString('\n')
		if err != nil {
			fmt.Println("произошла ошибка при чтении ввода")
			continue
		}

		// откидываем лишние символы вокруг ввода
		s = strings.TrimSpace(s)

		v, err := ParseDynamicUint(s)
		if err != nil {
			fmt.Println("это число не подходит")
			continue
		}

		return v
	}
}

type DynamicUint []byte

func ParseDynamicUint(s string) (DynamicUint, error) {
	v := make(DynamicUint, len(s))
	for i, b := range []byte(s) {
		b -= '0'
		if b > 9 {
			return nil, fmt.Errorf("not a number")
		}
		v[i] = b
	}
	return v.Flip(), nil
}

func (a DynamicUint) String() string {
	s := make([]byte, len(a))
	for i := range a {
		s[len(a)-i-1] = a[i] + '0'
	}
	return string(s)
}

func (a DynamicUint) Flip() DynamicUint {
	b := make(DynamicUint, len(a))
	for i := range a {
		b[len(a)-i-1] = a[i]
	}
	return b
}

func (a DynamicUint) Equals(b DynamicUint) bool {
	if len(a) != len(b) {
		return false
	}

	for i := range a {
		if a[i] != b[i] {
			return false
		}
	}

	return true
}

func (a DynamicUint) Add(b DynamicUint) DynamicUint {
	alen, blen := len(a), len(b)
	if blen > alen {
		a, b = b, a
	}

	c := make(DynamicUint, alen, alen+1)

	carry := false
	for i := range c {
		if i >= blen {
			c[i] = a[i]
			if carry {
				c[i] += 1
				carry = false
			}
			continue
		}

		c[i] = a[i] + b[i]
		if carry {
			c[i] += 1
		}

		carry = c[i] >= 10
		c[i] %= 10
	}

	if carry {
		c = append(c, 1)
	}

	return c
}

func main() {
	r := bufio.NewReader(os.Stdin)

	for {
		run()

		fmt.Print("снова? ('y'; любой иной ввод завершит программу): ")
		s, err := r.ReadString('\n')
		s = strings.TrimSpace(s)
		if err != nil || !(s == "y" || s == "у") {
			//                         это русская у
			return
		}
	}
}
