#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import datetime

def get_type():
	return "BINARY"

def get_sub_type():
	return "SAMPLE"

def get_desc():
	return "e-xml sample"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return "authors.txt"

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_src_file([
		'sample/main.cpp',
		'sample/read.cpp',
		'sample/write.cpp'
		])
	my_module.add_depend(['exml', 'test-debug'])
	my_module.copy_path('sample/read.xml')
	return my_module

