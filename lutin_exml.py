#!/usr/bin/python
import realog.debug as debug
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "XML parser and generator"

def get_licence():
	return "MPL-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return "authors.txt"

def get_version():
	return "version.txt"

def configure(target, my_module):
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
	    'exml/FilePos.hpp',
	    'exml/nodeType.hpp',
	    'exml/exml.hpp',
	    'exml/iterator.hpp',
	    'exml/Attribute.hpp',
	    'exml/AttributeList.hpp',
	    'exml/Comment.hpp',
	    'exml/Declaration.hpp',
	    'exml/Document.hpp',
	    'exml/Element.hpp',
	    'exml/Node.hpp',
	    'exml/Text.hpp',
	    'exml/internal/Attribute.hpp',
	    'exml/internal/AttributeList.hpp',
	    'exml/internal/Comment.hpp',
	    'exml/internal/Declaration.hpp',
	    'exml/internal/Document.hpp',
	    'exml/internal/Element.hpp',
	    'exml/internal/Node.hpp',
	    'exml/internal/Text.hpp'
	    ])
	my_module.add_path(".")
	return True


