#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "e-xml XML parser and generator"


def create(target):
	my_module = module.Module(__file__, 'exml', 'LIBRARY')
	
	my_module.add_module_depend(['etk'])
	
	# add extra compilation flags :
	my_module.add_extra_compile_flags()
	# add sources files
	my_module.add_src_file([
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
	
	my_module.add_header_file([
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
	
	my_module.add_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return my_module


