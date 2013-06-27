#!/usr/bin/python
import lutinModule
import lutinTools

def Create(target):
	myModule = lutinModule.module(__file__, 'exml', 'LIBRARY')
	
	myModule.AddModuleDepend(['etk'])
	
	myModule.AddSrcFile([
		'exml/debug.cpp',
		'exml/Attribute.cpp',
		'exml/AttributeList.cpp',
		'exml/Comment.cpp',
		'exml/Declaration.cpp',
		'exml/Document.cpp',
		'exml/Element.cpp',
		'exml/Node.cpp',
		'exml/Text.cpp'])
	
	myModule.AddExportPath(lutinTools.GetCurrentPath(__file__))
	
	# add the currrent module at the 
	return myModule


