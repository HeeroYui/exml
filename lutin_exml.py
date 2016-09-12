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
	return [0,5,"dev"]

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_depend(['elog', 'etk', 'ememory'])
	my_module.add_extra_flags()
	my_module.add_src_file([
		'exml/debug.cpp',
		'exml/FilePos.cpp',
		'exml/nodeType.cpp',
		'exml/Attribute.cpp',
		'exml/AttributeList.cpp',
		'exml/Comment.cpp',
		'exml/Declaration.cpp',
		'exml/Document.cpp',
		'exml/Element.cpp',
		'exml/Node.cpp',
		'exml/Text.cpp',
		])
	my_module.add_src_file([
		'exml/internal/Attribute.cpp',
		'exml/internal/AttributeList.cpp',
		'exml/internal/Comment.cpp',
		'exml/internal/Declaration.cpp',
		'exml/internal/Document.cpp',
		'exml/internal/Element.cpp',
		'exml/internal/Node.cpp',
		'exml/internal/Text.cpp'
		])
	my_module.add_header_file([
		'exml/FilePos.h',
		'exml/nodeType.h',
		'exml/exml.h',
		'exml/iterator.h',
		'exml/Attribute.h',
		'exml/AttributeList.h',
		'exml/Comment.h',
		'exml/Declaration.h',
		'exml/Document.h',
		'exml/Element.h',
		'exml/Node.h',
		'exml/Text.h',
		'exml/internal/Attribute.h',
		'exml/internal/AttributeList.h',
		'exml/internal/Comment.h',
		'exml/internal/Declaration.h',
		'exml/internal/Document.h',
		'exml/internal/Element.h',
		'exml/internal/Node.h',
		'exml/internal/Text.h'
		])
	my_module.add_path(tools.get_current_path(__file__))
	return my_module


