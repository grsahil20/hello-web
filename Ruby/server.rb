require 'bundler'
Bundler.require

set :port, 8080


get '/' do
  'Hello, web!'
end
