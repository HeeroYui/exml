/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#include <exml/iterator.hpp>

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T>::iterator(EXML_BASE_T& _obj, size_t _pos) :
  m_data(_obj),
  m_id(_pos) {
	m_id = std::avg(size_t(0), m_id, m_data.size());
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T>::iterator(const EXML_BASE_T& _obj, size_t _pos) :
  m_data(const_cast<EXML_BASE_T&>(_obj)),
  m_id(_pos) {
	m_id = std::avg(size_t(0), m_id, m_data.size());
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T>::iterator(const exml::iterator<EXML_BASE_T,EXML_RETURN_T>& _obj) :
  m_data(_obj.m_data),
  m_id(_obj.m_id) {
	m_id = std::avg(size_t(0), m_id, m_data.size());
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T>& exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator= (const exml::iterator<EXML_BASE_T,EXML_RETURN_T>& _obj) {
	m_data = _obj.m_data;
	m_id = _obj.m_id;
	m_id = std::avg(size_t(0), m_id, m_data.size());
	return *this;
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T>& exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator+= (int32_t _val) {
	int64_t val = m_id;
	val += _val;
	m_id = std::avg(int64_t(0), val, int64_t(m_data.size()));
	return *this;
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T> exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator+ (int32_t _val) const {
	exml::iterator<EXML_BASE_T,EXML_RETURN_T> result(*this);
	result += _val;
	return result;
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T>& exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator-= (int32_t _val) {
	int64_t val = m_id;
	val -= _val;
	m_id = std::avg(int64_t(0), val, int64_t(m_data.size()));
	return *this;
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T> exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator- (int32_t _val) const {
	exml::iterator<EXML_BASE_T,EXML_RETURN_T> result = *this;
	result -= _val;
	return result;
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T>& exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator++() {
	int64_t val = m_id;
	++val;
	m_id = std::avg(int64_t(0), val, int64_t(m_data.size()));
	return *this;
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T> exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator++(int) {
	exml::iterator<EXML_BASE_T,EXML_RETURN_T> result = *this;
	++(*this);
	return result;
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T>& exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator--() {
	int64_t val = m_id;
	--val;
	m_id = std::avg(int64_t(0), val, int64_t(m_data.size()));
	return *this;
}

template<class EXML_BASE_T, class EXML_RETURN_T>
exml::iterator<EXML_BASE_T,EXML_RETURN_T> exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator--(int) {
	exml::iterator<EXML_BASE_T,EXML_RETURN_T> result = *this;
	--(*this);
	return result;
}

template<class EXML_BASE_T, class EXML_RETURN_T>
bool exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator== (const exml::iterator<EXML_BASE_T,EXML_RETURN_T>& _obj) const {
	//EXML_WARNING("compare : " << _obj.m_id << " == " << m_id );
	return (    _obj.m_id == m_id
	         && &_obj.m_data == &m_data);
}

template<class EXML_BASE_T, class EXML_RETURN_T>
bool exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator!= (const exml::iterator<EXML_BASE_T,EXML_RETURN_T>& _obj) const {
	//EXML_WARNING("compare : " << _obj.m_id << " != " << m_id );
	return (    _obj.m_id != m_id
	         || &_obj.m_data != &m_data);
}

template<class EXML_BASE_T, class EXML_RETURN_T>
const EXML_RETURN_T exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator *() const noexcept {
	return m_data[m_id];
}

template<class EXML_BASE_T, class EXML_RETURN_T>
EXML_RETURN_T exml::iterator<EXML_BASE_T,EXML_RETURN_T>::operator *() noexcept {
	return m_data[m_id];
}

