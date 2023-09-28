package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
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

		path, err := r.ReadString('\n')
		if err != nil {
			fmt.Printf("не удалось прочитать ввод: %v\n", err)
			continue
		}

		path = strings.TrimSpace(path)

		f, err := os.Open(path)
		if err != nil {
			fmt.Printf("не удалось открыть файл %s\n", path)
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