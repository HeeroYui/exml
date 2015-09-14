#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "e-xml XML parser and generator"


def create(target):
	myModule = module.Module(__file__, 'exml', 'LIBRARY')
	
	myModule.add_module_depend(['etk'])
	
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	# add sources files
	myModule.add_src_file([
		'exml/debug.cpp',
		'exml/Attribute.cpp',
		'exml/AttributeList.cpp',
		'exml/Comment.cpp',
		'exml/Declaration.cpp',
		'exml/Document.cpp',
		'exml/Element.cpp',
		'exml/Node.cpp',
		'exml/Text.cpp'
		])
	
	myModule.add_header_file([
		'exml/exml.h',
		'exml/Attribute.h',
		'exml/AttributeList.h',
		'exml/Comment.h',
		'exml/Declaration.h',
		'exml/Document.h',
		'exml/Element.h',
		'exml/Node.h',
		'exml/Text.h'
		])
	
	myModule.add_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return myModule


