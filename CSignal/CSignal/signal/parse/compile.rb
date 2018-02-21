# coding: utf-8
require_relative 'ruby_lib/make'
require_relative 'ruby_lib/build'

Make.lex()
Make.yy()
Build.compile()