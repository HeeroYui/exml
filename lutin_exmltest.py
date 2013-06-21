#!/usr/bin/python
import lutinModule
import lutinTools
import datetime

def Create(target):
	# module name is 'edn' and type binary.
	myModule = lutinModule.module(__file__, 'exmltest', 'PACKAGE')
	
	# add the file to compile:
	myModule.AddSrcFile([
		'exml/EXmlTest.cpp'])
	
	myModule.AddModuleDepend('exml')
	
	now = datetime.datetime.now()
	versionID=str(now.year-2012)+"."+str(now.month)+"."+str(now.day)
	
	# set the package properties :
	myModule.pkgSet("VERSION", versionID)
	myModule.pkgSet("COMPAGNY_TYPE", "org")
	myModule.pkgSet("COMPAGNY_NAME", "Edouard DUPIN")
	myModule.pkgSet("MAINTAINER", ["Mr DUPIN Edouard <yui.heero@gmail.com>"])
	myModule.pkgSet("SECTION", ["Development"])
	myModule.pkgSet("PRIORITY", "optional")
	myModule.pkgSet("DESCRIPTION", "E_xml tester soft")
	myModule.pkgSet("NAME", "exml_tester")
	
	myModule.pkgAddRight("WRITE_EXTERNAL_STORAGE")
	myModule.pkgAddRight("SET_ORIENTATION")
	
	# add the currrent module at the 
	return myModule

