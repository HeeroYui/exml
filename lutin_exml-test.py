#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import datetime


def get_type():
	return "BINARY"

def get_name():
	return "exml_tester"

def get_sub_type():
	return "TEST"

def get_desc():
	return "e-xml test software"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_src_file([
		'test/main.cpp',
		'test/exmlTestAll.cpp',
		'test/exmlTestComment.cpp',
		'test/exmlTestElement.cpp',
		'test/exmlTestAttribute.cpp',
		'test/exmlTestCommon.cpp',
		'test/exmlTestDeclaration.cpp',
		'test/exmlTestDeclarationXML.cpp',
		'test/exmlTestParseComment.cpp',
		'test/exmlTestParseElement.cpp',
		'test/exmlTestParseAttribute.cpp',
		'test/exmlTestParseDeclaration.cpp'
		])
	my_module.add_depend(['exml', 'gtest', 'test-debug'])
	return my_module

