####
# Copyright by Philipp Dunkel
#
# See license text in LICENSE file
####

import Options, Utils
from os import unlink, symlink, chdir
from os.path import exists

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  
  # Node.js and debug flags
  conf.env.append_unique('CPPFLAGS', ["-D_FILE_OFFSET_BITS=64","-D_LARGEFILE_SOURCE"])
  conf.env.append_unique('CXXFLAGS', ["-Wall"])
    
def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.target = "multicast-bindings"
  obj.source = "./src/multicast-bindings.cc"

def test(tst):

def lint(lnt):
  # Bindings C++ source code
  print("Run CPPLint:")
  Utils.exec_command('cpplint ./src/*.h ./src/*.cc')
  # Bindings javascript code, tools and tests
  print("Run Nodeint:")
  Utils.exec_command('nodelint ./package.json ./udp-multicast.js')

def doc(doc):
  description = (
	'--desc "UDP-Multicast Sockets for NodeJS\n\n' +
	'Check out the [Github repo](http://github.com/phidelta/NodeJS-UDP-Multicast) for the source and installation guide.\n\n' +
	'Extra information:'
  )

  ribbon = '--ribbon "http://github.com/phidelta/NodeJS-UDP-Multicast" '
  
  print("Parse README.markdown:")
  Utils.exec_command(
	'dox --title "NodeJS UDP-Multicast" ' +
	'[Homepage](./index.html), [ChangeLog](./changelog.html), [API](./api.html)' +
    description +
	ribbon + 
    './README.markdown > ./doc/index.html'
  )

  print("Parse CHANGELOG.markdown:")
  Utils.exec_command(
	'dox --title "NodeJS UDP-Multicast ChangeLog" ' +
	'[Homepage](./index.html), [ChangeLog](./changelog.html), [API](./api.html)' +
    description +
	ribbon +
    './CHANGELOG.markdown > ./doc/changelog.html'
  )

  print("Parse API.markdown:")
  Utils.exec_command(
	'dox --title "NodeJS UDP-Multicast API" ' +
	'[Homepage](./index.html), [ChangeLog](./changelog.html), [API](./api.html)' +
    description +
	ribbon +
    './CHANGELOG.markdown > ./doc/changelog.html'
  )

def shutdown():
  # HACK to get bindings.node out of build directory.
  # better way to do this?
  t = 'multicast-bindings.node'
  if Options.commands['clean']:
    if exists(t): unlink(t)
  else:
    if exists('build/default/' + t) and not exists(t):
      symlink('build/default/' + t, t)

