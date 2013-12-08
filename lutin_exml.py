#!/usr/bin/python
import lutinModule
import lutinTools

def Create(target):
	myModule = lutinModule.module(__file__, 'exml', 'LIBRARY')
	# enable doculentation :
	myModule.doc_enable()
	myModule.documentation.set_website("http://HeeroYui.github.io/exml/")
	myModule.documentation.set_path(lutinTools.GetCurrentPath(__file__) + "/exml/")
	myModule.documentation.set_external_link(['etk'])
	
	myModule.AddModuleDepend(['etk'])
	
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	# add sources files
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


