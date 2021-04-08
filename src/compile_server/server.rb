require 'sinatra'
require 'sinatra/reloader' if development?
require 'open3'
require 'base64'
require 'byebug' if development?

port = ENV['PORT']

if port.nil? then
  port = 8080
end

set :port, port

get '/' do
  'This is the Arduino Program to Webassembly compile server for the 2D Robot Simulator!'
end

post '/compile' do
  response['Access-Control-Allow-Origin'] = '*'

  result = {:errors => '', :bin => ''}
  code = params['code']

  f = File.write('code.cpp', code)

  Open3.popen3('emcc code.cpp -I ../headers -s SIDE_MODULE=1 -o libcode.so') do |_, stdout, stderr, wait_tr|
    exit_code = wait_tr.value

    if exit_code != 0 then
      result[:errors] = stderr.read()
    elsif
      result[:bin] = Base64.encode64(File.read('libcode.so'))
    end
  end

  JSON(result)
end
