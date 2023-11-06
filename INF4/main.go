/*
# Задание
Вариант 13. Статистика текста

Программа должна вычислять количество слов, общее количество
символов и количество символов, исключая пробелы, в текстовом
файле, содержащем текст на естественном английском языке. Слова в
таком файле состоят из подряд идущих больших и малых символов
латинского алфавита и разделяются любыми другими символами.

Входные данные: текстовый файл, заданный своим именем. Файл
должен содержать текст на естественном английском языке.
Выходные данные: количество слов в этом файле, общее
количество символов и количество символов, исключая пробелы.
*/

package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"path"
	"strings"
)

func main() {
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

func askForFile() *os.File {
	r := bufio.NewReader(os.Stdin)

	for {
		fmt.Printf("введите путь к файлу: ")

		p, err := r.ReadString('\n')
		if err != nil {
			fmt.Printf("не удалось прочитать ввод: %v\n", err)
			continue
		}

		p = strings.TrimSpace(p)

		if wd, err := os.Getwd(); err != nil {
			p = path.Join(wd, p)
		}

		f, err := os.Open(p)
		if err != nil {
			fmt.Printf("не удалось открыть файл %q\n", p)
			continue
		}

		stat, err := f.Stat()
		if err != nil {
			fmt.Printf("не удалось открыть файл %q\n", p)
			continue
		}

		if stat.IsDir() {
			fmt.Printf("%q является директорией\n", p)
			continue
		}

		return f

	}
}

type FileStats struct {
	Words              int
	NonSpaceCharacters int
	TotalCharacters    int
}

func readStats(r io.Reader) (FileStats, error) {
	stats := FileStats{}
	inWord := false

	var buf [1]byte
	var err error
	for err != io.EOF {
		_, err = r.Read(buf[:])
		if err != nil && err != io.EOF {
			return stats, err
		}

		stats.NonSpaceCharacters += 1
		stats.TotalCharacters += 1

		switch {
		case ('A' <= buf[0] && buf[0] <= 'Z') ||
			('a' <= buf[0] && buf[0] <= 'z'):
			if !inWord {
				stats.Words += 1
				inWord = true
			}

		case buf[0] == ' ', buf[0] == '\t', buf[0] == '\n':
			inWord = false
			stats.NonSpaceCharacters -= 1
		}
	}

	return stats, nil
}

func run() {
	f := askForFile()
	defer f.Close() // файл следует за собой закрыть

	s, err := readStats(f)
	if err != nil {
		fmt.Printf("произошла ошибка при чтении файла: %v\n", err)
		return
	}

	fmt.Printf("найдено слов латиницей: %d\n", s.Words)
	fmt.Printf("найдено видимых символов: %d\n", s.NonSpaceCharacters)
	fmt.Printf("найдено всего символов: %d\n", s.TotalCharacters)
}
