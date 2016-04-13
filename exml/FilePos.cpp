/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#include <exml/FilePos.h>

exml::FilePos::FilePos() :
  m_col(0),
  m_line(0) {
	
}

exml::FilePos::FilePos(size_t _line, size_t _col) :
  m_col(_col),
  m_line(_line) {
	
}

exml::FilePos& exml::FilePos::operator ++() {
	m_col++;
	return *this;
}

exml::FilePos& exml::FilePos::operator --() {
	if(m_col>0) {
		m_col--;
	}
	return *this;
}

exml::FilePos& exml::FilePos::operator +=(const exml::FilePos& _obj) {
	if (_obj.m_line == 0) {
		m_col += _obj.m_col;
	} else {
		m_col = _obj.m_col;
		m_line += _obj.m_line;
	}
	return *this;
}

exml::FilePos& exml::FilePos::operator +=(size_t _col) {
	m_col += _col;
	return *this;
}

exml::FilePos& exml::FilePos::operator= (const exml::FilePos& _obj ) {
	m_col = _obj.m_col;
	m_line = _obj.m_line;
	return *this;
}

void exml::FilePos::newLine() {
	m_col=0;
	m_line++;
}

bool exml::FilePos::check(char32_t _val) {
	m_col++;
	if (_val == '\n') {
		newLine();
		return true;
	}
	return false;
}

void exml::FilePos::set(size_t _line, size_t _col) {
	m_col = _col;
	m_line = _line;
}

void exml::FilePos::clear() {
	m_col = 0;
	m_line = 0;
}

size_t exml::FilePos::getCol() const {
	return m_col;
}

size_t exml::FilePos::getLine() const {
	return m_line;
}

std::ostream& exml::operator <<(std::ostream& _os, const exml::FilePos& _obj) {
	_os << "(l=";
	_os << _obj.getLine();
	_os << ",c=";
	_os << _obj.getCol();
	_os << ")";
	return _os;
}
