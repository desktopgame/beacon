#https://qiita.com/fetaro/items/6a1ad6bf3c14470c949b
require 'fileutils'
require 'tempfile'
require 'tmpdir'
require 'timeout'

class Cmd
  @@timeout = 0
  def Cmd.timeout=(sec) ; @@timeout = sec ; end
  def Cmd.run(*cmd_array)
    raise(Exception,"Command string is nil") if cmd_array.size == 0
    stdout_file = Tempfile::new("#{$$}_light_cmd_tmpout",Dir.tmpdir)
    stderr_file = Tempfile::new("#{$$}_light_cmd_tmperr",Dir.tmpdir)
    pid = spawn(*cmd_array, :out => [stdout_file,"w"],:err => [stderr_file,"w"])
    status = nil
    if @@timeout != 0
      begin
        timeout(@@timeout) do
          status = Process.waitpid2(pid)[1] >> 8
        end
      rescue Timeout::Error => e
        begin
          Process.kill('SIGINT', pid)
          raise(Exception,"Timeout #{@@timeout.to_s} sec. Kill process : PID=#{pid}" )
        rescue
          raise(Exception,"Timeout #{@@timeout.to_s} sec. Fail to kill process : PID=#{pid}" )
        end
      end
    else
      status = Process.waitpid2(pid)[1] >> 8
    end
    return  Result.new(stdout_file,stderr_file,status,cmd_array)
  end

  class Result
    attr_reader :stdout_file, :stderr_file, :status, :cmd_array
    def initialize(stdout_file, stderr_file, status, cmd_array)
      @stdout_file = stdout_file
      @stderr_file = stderr_file
      @status = status
      @cmd_array = cmd_array
    end
    def stdout  ; File.read(@stdout_file) ; end
    def stderr  ; File.read(@stderr_file) ; end
    def to_h    ; {:cmd_str => cmd_str,:stdout => stdout, :stderr => stderr, :status => status} ; end
    def cmd_str ; @cmd_array.join(" ") ; end
    def to_s    ;to_h.to_s ; end
  end
  class Exception < StandardError ; end
end