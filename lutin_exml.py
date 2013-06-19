#!/usr/bin/python
import lutinModule
import lutinTools

def Create(target):
	myModule = lutinModule.module(__file__, 'exml', 'LIBRARY')
	
	myModule.AddModuleDepend(['etk'])
	
	myModule.AddSrcFile([
		'exml/debug.cpp',
		'exml/EXmlAttribute.cpp',
		'exml/EXmlComment.cpp',
		'exml/EXmlDeclaration.cpp',
		'exml/EXmlDocument.cpp',
		'exml/EXmlElement.cpp',
		'exml/EXmlNode.cpp',
		'exml/EXmlText.cpp'])
	
	myModule.AddExportPath(lutinTools.GetCurrentPath(__file__))
	
	# add the currrent module at the 
	return myModule


