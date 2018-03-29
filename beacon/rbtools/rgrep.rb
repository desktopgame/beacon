#grepのためのモジュール
module RGrep
	#[行, 列] に変換して返します.
	#@param content: String
	#@param offs: Int
	def self.location(content, offs)
		row = 0
		col = 0
		ptr = 0
		content.chars do |x|
			ptr = ptr + 1
			if x.match(/\n/)
				row = row + 1
				col = 0
				next
			end
			if ptr >= offs then
				break
			end
			col = col + 1
		end
		return [row, col]
	end
end