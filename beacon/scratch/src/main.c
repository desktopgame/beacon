#include <string.h>
#include <stdio.h>
#include <stdbool.h>
 
// 演算子
// 優先順位 : 演算子 : 結合性
// 4 :   !   : 右結合性
// 3 : * / % : 左結合性
// 2 :  + -  : 左結合性
// 1 :   =   : 右結合性
int op_preced(const char c)
{
	switch (c) {
		case '!':
			return 4;
		case '*':  case '/': case '%':
			return 3;
		case '+': case '-':
			return 2;
		case '=':
			return 1;
	}
	return 0;
}
 
bool op_left_assoc(const char c)
{
	switch (c) {
		// 左結合性
		case '*': case '/': case '%': case '+': case '-':
			return true;
		// 右結合性
		case '=': case '!':
			return false;
	}
	return false;
}
 
unsigned int op_arg_count(const char c)
{
	switch (c) {
		case '*': case '/': case '%': case '+': case '-': case '=':
			return 2;
		case '!':
			return 1;
		default: // 関数の場合、A()の引数は0個、B()の引数は1個、C()の引数は2個... と定義
			return c - 'A';
	}
	return 0;
}
 
#define is_operator(c)  (c == '+' || c == '-' || c == '/' || c == '*' || c == '!' || c == '%' || c == '=')
#define is_function(c)  (c >= 'A' && c <= 'Z')
#define is_ident(c)     ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))
 
bool shunting_yard(const char *input, char *output)
{
	const char *strpos = input, *strend = input + strlen(input);
	char c, *outpos = output;
 
	char stack[32];       // 演算子スタック
	unsigned int sl = 0;  // スタック長（深さ）
	char sc;              // スタック要素の記録用
 
	while (strpos < strend) {
		// 入力ストリームからトークンを1つ読み込む
		c = *strpos++;
		if (c == ' ') {
			continue;
		} else if (is_ident(c)) {
			// トークンが数値（識別子）なら、出力キューに追加する
			*outpos++ = c;
		} else if (is_function(c)) {
			// トークンが関数なら、スタックにプッシュする。
			stack[sl++] = c;
		} else if (c == ',') {
			// トークンが関数の引数のセパレータ（例えばカンマ）の場合
			bool pe = false;
			while (sl > 0) {
				sc = stack[sl - 1];
				if (sc == '(') {
					pe = true;
					break;
				} else {
					// スタックのトップのトークンが左括弧になるまで
					// スタック上の演算子を出力キューにポップし続ける
					*outpos++ = sc; 
					sl--;
				}
			}
			// 左括弧が出てこなかった場合、すなわちセパレータの位置が変だった場合
			// あるいは括弧が正しく対応していない場合
			if (!pe) {
				printf("エラー：セパレータか括弧の不一致\n");
				return false;
			}
		} else if (is_operator(c)) {
			// トークンが演算子 op1 の場合
			while (sl > 0) {
				sc = stack[sl - 1];
				// op1 が左結合性で優先順位が op2 と等しいか低い場合
				// あるいは op1 の優先順位が op2 より低い場合
				// 演算子トークン op2 がスタックのトップにある間ループする。
				// 1^2+3 のような式を正しく 12^3+ に変換するため
				// "+" と "^" は右結合性とする。
				// 演算子の優先順位の違いからポップするかプッシュするかを判断する。
				// 2つの演算子の優先順位が等しいなら、結合性から判断する。
				if (is_operator(sc) &&
						(
							(op_left_assoc(c) && (op_preced(c) <= op_preced(sc))) ||
							(op_preced(c) < op_preced(sc))
						)
					) {
					// Pop op2 off the stack, onto the output queue;
					*outpos++ = sc; 
					sl--;
				} else {
					break;
				}
			}
			// op1 をスタックにプッシュ
			stack[sl++] = c;
		} else if (c == '(') {
			// トークンが左括弧なら、スタックにプッシュ
			stack[sl++] = c;
		} else if (c == ')') {
			// トークンが右括弧の場合
			bool pe = false;
			// スタックのトップにあるトークンが左括弧になるまで
			// スタックから出力キューに演算子をポップし続ける
			while (sl > 0) {
				sc = stack[--sl];
				if (sc == '(') {
					// スタックから左括弧をポップするが、出力キューには置かない
					pe = true;
					break;
				} else {
					*outpos++ = sc; 
				}
			}
			// スタックを全部見ても左括弧に到達しなかった場合、左右の括弧の不一致があることになる
			if (!pe) {
				printf("エラー：括弧の不一致\n");
				return false;
			}
			// スタックのトップにあるトークンが関数トークンなら、それを出力キューにポップする
			if (sl > 0) {
				sc = stack[sl - 1];
				if (is_function(sc)) {
					*outpos++ = sc; 
					sl--;
				}
			}
		} else {
			printf("不明なトークン：%c\n", c);
			return false; // 不明なトークン
		}
	}
	// 読み込むべきトークンが尽きた際
	// スタック上に演算子トークンが残っていたら、それらを出力する
	while (sl > 0) {
		sc = stack[--sl];
		if (sc == '(' || sc == ')') {
			printf("エラー：括弧の不一致\n");
			return false;
		}
		*outpos++ = sc; 
	}
	*outpos = 0; // ヌルでターミネート
	return true;
}
 
bool execution_order(const char *input)
{
	const char *strpos = input, *strend = input + strlen(input);
	char c, res[4];
	unsigned int sl = 0, sc, stack[32], rn = 0;
	printf("【実行順序】\n");
	// 入力トークンがある間ループする
	while (strpos < strend) {
		// 入力から次のトークンを読み込む
		c = *strpos++;
		if (is_ident(c)) {
			// トークンが値か識別子の場合
			// それをスタックにプッシュする。
			stack[sl++] = c;
		} else if (is_operator(c) || is_function(c)) {
			// さもなくば、トークンは演算子である（ここでは関数も演算子に含める）
			sprintf(res, "$%d", rn++);
			printf("%s = ", res);
			// 演算子が n 個の引数をとることは事前にわかっている。
			unsigned int nargs = op_arg_count(c);
			if (sl < nargs) {
				// スタックに n 個未満の値しかない場合
				// ユーザーの入力した式に値（引数）が足りないのでエラーを返す
				return false;
			}
			// そうでない場合、スタックから n 個の値をポップする
			// それらの値を引数として、演算子を評価する
			if (is_function(c)) {
				printf("%c(", c);
				while (nargs > 0) {
					sc = stack[sl - nargs]; // 逆順の引数を削除
					if (nargs > 1) {
						printf("%s, ", (char*) &sc);
					} else {
						printf("%s);\n", (char*) &sc);
					}
					--nargs;
				}
				sl -= op_arg_count(c);
			} else {
				if (nargs == 1) {
					sc = stack[--sl];
					printf("%c %s;\n", c, (char*) &sc);
				} else {
					sc = stack[sl - 2];
					printf("%s %c ", (char*) &sc, c);
					sc = stack[sl - 1];
					sl -= 2;
					printf("%s;\n", (char*) &sc);
				}
			}
			// 返ってきた結果がもしあれば、スタックにプッシュ
			stack[sl++] = *(unsigned int*) res;
		}
	}
	// スタックに1つの値しかない場合、
	// その値が計算結果である。
	if (sl == 1) {
		sc = stack[--sl];
		printf("実行結果は %s\n", (char*) &sc);
		return true;
	}
	// スタックにさらに値がある場合
	// ユーザ入力に値が多すぎるので、エラーとする。
	return false;
}
 
int main()
{
	// 関数: A() B(a) C(a, b), D(a, b, c) ...
	// 識別子: 0 1 2 3 ... および a b c d e ...
	// 演算子: = - + / * % !
	const char *input = "a = D(f - b * c + d, !e, g)";
	char output[128];
	printf("【入力】\n%s\n\n", input);
	if (shunting_yard(input, output)) {
		printf("【出力】\n%s\n\n", output);
		if (!execution_order(output)) {
			printf("\n不正な入力\n");
		}
	}
	return 0;
}