/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/Document.hpp>
#include <exml/debug.hpp>
#include <exml/internal/Document.hpp>
#include <etk/path/fileSystem.hpp>
#include <etk/uri/uri.hpp>

exml::Document::Document(ememory::SharedPtr<exml::internal::Node> _internalNode) :
  exml::Element(_internalNode) {
	if (m_data == null) {
		return;
	}
	if (m_data->isDocument() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = null;
	}
}

exml::Document::Document(const exml::Document& _obj) :
  exml::Element(_obj.m_data) {
	
}

exml::Document::Document() :
  exml::Element() {
	m_data = exml::internal::Document::create();
}

exml::Document& exml::Document::operator= (const exml::Document& _obj) {
	m_data = _obj.m_data;
	return *this;
}

bool exml::Document::parse(const etk::String& _data) {
	if (m_data == null) {
		EXML_DEBUG("Can not parse (null) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->parse(_data);
}

bool exml::Document::generate(etk::String& _data) {
	if (m_data == null) {
		EXML_DEBUG("Can not generate (null) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->generate(_data);
}

bool exml::Document::load(const etk::Path& _path) {
	if (m_data == null) {
		EXML_DEBUG("Can not load (null) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->load(_path);
}

bool exml::Document::load(const etk::Uri& _uri) {
	if (m_data == null) {
		EXML_DEBUG("Can not load (null) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->load(_uri);
}

bool exml::Document::store(const etk::Path& _path) {
	if (m_data == null) {
		EXML_DEBUG("Can not store (null) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->store(_path);
}

bool exml::Document::store(const etk::Uri& _uri) {
	if (m_data == null) {
		EXML_DEBUG("Can not store (null) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->store(_uri);
}

bool exml::Document::storeSafe(const etk::Path& _path) {
	if (m_data == null) {
		EXML_DEBUG("Can not store (null) ...");
		return false;
	}
	bool done = static_cast<exml::internal::Document*>(m_data.get())->store(_path+".tmp");
	if (done == false) {
		return false;
	}
	return etk::path::move(_path+".tmp", _path);
}

bool exml::Document::storeSafe(const etk::Uri& _uri) {
	if (m_data == null) {
		EXML_DEBUG("Can not store (null) ...");
		return false;
	}
	if (etk::uri::canMove(_uri) == false) {
		return static_cast<exml::internal::Document*>(m_data.get())->store(_uri);
	}
	etk::Uri uriTmp = _uri;
	uriTmp.setPath(uriTmp.getPath() + ".tmp");
	bool done = static_cast<exml::internal::Document*>(m_data.get())->store(uriTmp);
	if (done == false) {
		return false;
	}
	return etk::uri::move(uriTmp, _uri);
}

void exml::Document::display() {
	if (m_data == null) {
		EXML_DEBUG("Can not display (null) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->display();
}

void exml::Document::setCaseSensitive(bool _val) {
	if (m_data == null) {
		EXML_DEBUG("Can not setCaseSensitive (null) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->setCaseSensitive(_val);
}

bool exml::Document::getCaseSensitive() const {
	if (m_data == null) {
		EXML_DEBUG("Can not getCaseSensitive (null) ...");
		return false;
	}
	return static_cast<const exml::internal::Document*>(m_data.get())->getCaseSensitive();
}

void exml::Document::setDisplayError(bool _value){
	if (m_data == null) {
		EXML_DEBUG("Can not setDisplayError (null) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->setDisplayError(_value);
}

bool exml::Document::getDisplayError() {
	if (m_data == null) {
		EXML_DEBUG("Can not getDisplayError (null) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->getDisplayError();
}

void exml::Document::displayError() {
	if (m_data == null) {
		EXML_DEBUG("Can not displayError (null) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->displayError();
}
