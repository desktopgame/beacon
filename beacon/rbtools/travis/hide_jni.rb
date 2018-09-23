require "open3"
require "fileutils"
require "date"

Dir.glob("beacon/src/beacon/shared/jni/*") do |file|
    next if !file.end_with?(".h") && !file.end_with?(".c")
    File.open(file, "w") do |fp|
        fp.puts("/* JNIのテストは実行されません */")
    end
end