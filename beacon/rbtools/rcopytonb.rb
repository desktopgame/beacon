require 'fileutils'

copy_from = "/Users/koya/Work/VSCode/beacon/beacon/bin/a.out"
copy_to = "/Users/koya/Work/Netbeans/Jet/JBeacon_test/beacon.so"
FileUtils.cp(copy_from, copy_to)
FileUtils.cp_r('../bin/script-lib', '/Users/koya/Work/Netbeans/Jet/JBeacon_test')