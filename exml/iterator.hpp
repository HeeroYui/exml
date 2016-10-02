/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <ememory/memory.hpp>
#include <etk/types.hpp>

namespace exml {
	/**
	 * iterator on elements.
	 */
	template<class EXML_BASE_T, class EXML_RETURN_T>
	class iterator {
		private:
			EXML_BASE_T& m_data; //!< Reference on the exml::Element
			size_t m_id; //!< Id of the element that we are parsing
		public:
			/**
			 * @brief Constructor of the generic object class
			 * @param[in] _obj Reference on the object to go threw
			 * @param[in] _pos Position in the object
			 */
			iterator(EXML_BASE_T& _obj, size_t _pos);
			/**
			 * @brief Const constructor of the generic const object class
			 * @param[in] _obj Reference on the object to go threw
			 * @param[in] _pos Position in the object
			 */
			iterator(const EXML_BASE_T& _obj, size_t _pos);
			/**
			 * @brief Copy iterator
			 * @param[in] _obj Iterator to copy
			 */
			iterator(const iterator& _obj);
			/**
			 * @brief Operator= Asignement iterator
			 * @param[in] _obj Iterator to copy
			 * @return Local reference of the iterator assigned
			 */
			iterator& operator= (const iterator& _obj);
			/**
			 * @brief Operator+= Addition value
			 * @param[in] _val Value to addition
			 * @return Local reference of the iterator additionned
			 */
			iterator& operator+= (int32_t _val);
			/**
			 * @brief Operator+ Addition a value
			 * @param[in] _val Value to addition
			 * @return New iterator containing the value
			 */
			iterator operator+ (int32_t _val) const;
			/**
			 * @brief Operator-= Decrement a value
			 * @param[in] _val Value to addition
			 * @return Local reference of the iterator decremented
			 */
			iterator& operator-= (int32_t _val);
			/**
			 * @brief Operator- Decrement a value
			 * @param[in] _val Value to addition
			 * @return New iterator containing the value
			 */
			iterator operator- (int32_t _val) const;
			/**
			 * @brief Operator++ Pre-incrementation of this iterator
			 * @return Local reference of the iterator incremented
			 */
			iterator& operator++();
			/**
			 * @brief Operator++ Post-incrementation of this iterator
			 * @return New iterator containing the last value
			 */
			iterator operator++(int);
			/**
			 * @brief Operator++ Pre-decrementation of this iterator
			 * @return Local reference of the iterator incremented
			 */
			iterator& operator--();
			/**
			 * @brief Operator++ Post-decrementation of this iterator
			 * @return New iterator containing the last value
			 */
			iterator operator--(int);
			/**
			 * @brief Equality compare operator with an other iterator.
			 * @param[in] _obj Reference on the comparing iterator
			 * @return true The iterators are identical
			 * @return false The iterators are NOT identical
			 */
			bool operator== (const iterator& _obj) const;
			/**
			 * @brief In-Equality compare operator with an other iterator.
			 * @param[in] _obj Reference on the comparing iterator
			 * @return true The iterators are NOT identical
			 * @return false The iterators are identical
			 */
			bool operator!= (const iterator& _obj) const;
			/**
			 * @brief Get the property Value
			 * @return Const reference on the value.
			 */
			const EXML_RETURN_T operator *() const noexcept;
			/**
			 * @brief Get the property Value
			 * @return Const reference on the value.
			 */
			EXML_RETURN_T operator *() noexcept;
	};
}
