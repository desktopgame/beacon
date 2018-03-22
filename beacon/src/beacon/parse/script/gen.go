package main

import (
	"bytes"
	"flag"
	"fmt"
	"io/ioutil"
	"os/exec"
	"regexp"
	"strings"
)

//
//insert
//
func insert(fileName string, entries ...string) error {
	var buff bytes.Buffer
	var all bytes.Buffer
	for _, line := range entries {
		buff.WriteString(line)
		buff.WriteString("\n")
	}
	//読み込み
	content, err := ioutil.ReadFile(fileName)
	if err != nil {
		fmt.Println("insert :     error")
		return err
	}
	text := string(content)
	prepend := buff.String()
	if !strings.Contains(text, prepend) {
		all.WriteString(prepend)
		all.WriteString(text)
		ioutil.WriteFile(fileName, all.Bytes(), 0600)
		fmt.Println("insert :     complete")
		return nil
	}
	fmt.Println("insert :     already")
	return nil
}

//
//make
//
func replace(source string, m map[string]string) string {
	ret := source
	for k, v := range m {
		ret = regexp.MustCompile(k).ReplaceAllString(ret, v)
	}
	return ret
}

func addReplace(prefix string, line string, buff *bytes.Buffer, m map[string]string) {
	//words := strings.Split(line, " ")
	fixedLine := strings.TrimLeft(line[strings.Index(line, prefix)+len(prefix):len(line)], " \t")
	buff.WriteString(replace(fixedLine, m))
	buff.WriteByte('\n')
}

func preprocess(source string, m map[string]string, isTest bool) string {
	var buff bytes.Buffer
	inMultiLineComment := false
	exp := 0
	for _, line := range regexp.MustCompile("\r\n|\n\r|\n|\r").Split(source, -1) {
		styledLine := strings.TrimSpace(line)
		//単一行コメント
		if strings.HasPrefix(styledLine, ";;") {
			continue
		}
		//コメントに入っている間は無視
		if !inMultiLineComment && strings.HasPrefix(styledLine, "$$-") {
			inMultiLineComment = true
			continue
		} else if inMultiLineComment && strings.HasPrefix(styledLine, "-$$") {
			inMultiLineComment = false
			continue
		}
		if inMultiLineComment {
			continue
		}
		//マクロ定義
		if strings.HasPrefix(styledLine, "$$SET") {
			words := strings.Split(line, " ")
			m[words[1]] = strings.Join(words[2:len(words)], " ")
			//fmt.Printf(words[1])
			//fmt.Printf(" : ")
			//fmt.Println(m[words[1]])
		} else if strings.HasPrefix(styledLine, "$$REM") {
			words := strings.Split(line, " ")
			for _, word := range words {
				delete(m, word)
			}
		} else if strings.HasPrefix(styledLine, "$$ENV") {
			words := strings.Split(line, " ")
			for _, word := range words {
				delete(m, word)
			}
			buff.WriteString(strings.Join(words[1:len(words)-1], " "))
			buff.WriteByte('\n')
			exp++
			//テスト時のみ有効になるコードは $$TOK で開始する
		} else if strings.HasPrefix(styledLine, "$$TOK") {
			if isTest {
				buff.WriteString("//Test Only")
				buff.WriteByte('\n')
				addReplace("$$TOK", line, &buff, m)
			}
			//テスト時のみ無効になるコードは $$TOK で開始する
		} else if strings.HasPrefix(styledLine, "$$TNO") {
			if !isTest {
				buff.WriteString("//Release Only")
				buff.WriteByte('\n')
				addReplace("$$TNO", line, &buff, m)
			}
		} else {
			buff.WriteString(replace(line, m))
			buff.WriteByte('\n')
		}
	}
	if exp > 0 {
		return preprocess(buff.String(), m, isTest)
	}
	return buff.String()
}

func make(config string, targetFile string, isTest bool) error {
	//ディレクトリをひらけなかった場合
	content, err := ioutil.ReadFile(config)
	if err != nil {
		fmt.Println("make :     error")
		return err
	}
	//一行づつ読み込んで files へ
	text := string(content)
	var buff bytes.Buffer
	for _, line := range regexp.MustCompile("\r\n|\n\r|\n|\r").Split(text, -1) {
		//ログに出力
		content, err := ioutil.ReadFile(line)
		if err != nil {
			fmt.Println("make : error2")
			fmt.Printf("     : ")
			fmt.Println(line)
			return nil
		}
		fmt.Println("make : opened")
		fmt.Printf("     : ")
		fmt.Println(line)
		fmt.Println()
		//プリプロセッサで加工
		text := string(content)
		buff.WriteString(preprocess(text, map[string]string{}, isTest))
	}
	ioutil.WriteFile(targetFile, buff.Bytes(), 0600)
	fmt.Println("make : complete")
	return nil
}

//
//main
//
func execp(name string, args ...string) {
	//実行するコマンドを表示する
	fmt.Printf(name)
	fmt.Printf(" : ")
	for _, e := range args {
		fmt.Printf(" %s", e)
	}
	fmt.Println()
	//実行する
	out, err := exec.Command(name, args...).Output()
	if err != nil {
		fmt.Println("    error")
	}
	fmt.Println(string(out))
	fmt.Println()
}

//global
var (
	isTest = flag.Bool("test", false, "test flag")
)

func main() {
	//実行時引数を解析する
	flag.Parse()
	//args := flag.Args()
	//fmt.Println(args)

	make("lex.makeconfig", "signal.l", *isTest)
	make("yy.makeconfig", "signal.y", *isTest)
	execp("flex", "signal.l")
	execp("bison", "-d", "signal.y")
	insert("signal.tab.h",
		"#include \"../ast/ast.h\"",
		"#include \"../ast/ast_new_factor.h\"",
		"#include \"../ast/constructor_chain_type.h\"",
		"#include \"../ast/assign_operator_type.h\"",
		"#include \"../ast/modifier_type.h\"",
		"#include \"../ast/access_level.h\"",
		"#include \"../util/mem.h\"")
}
