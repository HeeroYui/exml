#!/usr/bin/python
import monkModule as module
import monkTools as tools

def get_desc():
	return "e-xml XML parser and generator"

def create():
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'exml', 'LIBRARY')
	# enable doculentation :
	myModule.set_website("http://heeroyui.github.io/exml/")
	myModule.set_website_sources("http://github.com/heeroyui/exml/")
	myModule.set_path(tools.get_current_path(__file__) + "/exml/")
	# add the currrent module at the 
	return myModule

