# property
**property** は属性を定義する文です。

## 実装例
Locale.bc より抜粋
````
中略...
public:
	property String decimalPoint { private defset; defget; }
	property String thousandsSep { private defset; defget; }
	property String intCurrSymbol { private defset; defget; }
	property String currencySymbol { private defset; defget; }
	property String monDecimalPoint { private defset; defget; }
	property String monThousandsSep { private defset; defget; }
	property String positiveSign { private defset; defget; }
	property String negativeSign { private defset; defget; }
	property Int intFracDigits { private defset; defget; }
	property Int fracDigits { private defset; defget; }

````

## 利用例
private なので decimalPoint には書き込めない
````
require "beacon/unsafe/Locale"
beacon::unsafe::Locale.setLocale(beacon::unsafe::LocaleCategory.All, "ja_JP");

var locale = beacon::unsafe::Locale.getLocale();
print("decimal_point: ");
printLine(locale.decimalPoint);

locale.decimalPoint = "aaa";
print("decimal_point: ");
printLine(locale.decimalPoint);
````