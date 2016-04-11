#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "XML parser and generator"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def get_version():
	return [0,4,"dev"]

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_module_depend(['elog', 'etk', 'ememory'])
	my_module.add_extra_compile_flags()
	my_module.add_src_file([
		'exml/debug.cpp',
		'exml/FilePos.cpp',
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
		'exml/FilePos.h',
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
	return my_module


