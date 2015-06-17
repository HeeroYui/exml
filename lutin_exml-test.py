#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import datetime

def get_desc():
	return "e-xml test software"


def create(target):
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'exml-test', 'BINARY')
	
	# add the file to compile:
	myModule.add_src_file([
		'test/main.cpp'])
	
	myModule.add_module_depend(['exml', 'gtest'])
	
	now = datetime.datetime.now()
	versionID=str(now.year-2012)+"."+str(now.month)+"."+str(now.day)
	
	# set the package properties :
	myModule.pkg_set("VERSION", versionID)
	myModule.pkg_set("COMPAGNY_TYPE", "org")
	myModule.pkg_set("COMPAGNY_NAME", "Edouard DUPIN")
	myModule.pkg_set("MAINTAINER", ["Mr DUPIN Edouard <yui.heero@gmail.com>"])
	myModule.pkg_set("SECTION", ["Development"])
	myModule.pkg_set("PRIORITY", "optional")
	myModule.pkg_set("DESCRIPTION", "E_xml tester soft")
	myModule.pkg_set("NAME", "exml_tester")
	
	# add the currrent module at the 
	return myModule

