 /**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Register.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 *  The 'Register' class acts as the highest-level
 *  value type in Dargon. Equivelent to 'object' in other languages,
 *  however it cannot be accessed within the Dargon language itself.
 *
 */

#ifndef DARGON_HEADER_REGISTER
#define DARGON_HEADER_REGISTER

#include <string>

namespace dargon {

	/// @brief The top-level 'object' in the Dargon runtime.
	/// @author Kyle Morris
	/// @since v0.1
	class Register {
	public:
        enum class Type {
            INT,
            REAL,
            BOOL,
            STRING,
            USERDEF,
            UNDEFINED
        };

        Register() : _type(Type::UNDEFINED) {}

        Register(Type type) : _type(type) {}

    protected:
        Type _type;
	};

	/// @brief Template implementation of 'Registers'.
	/// @author Kyle Morris
	/// @since v0.1
	template<typename T>
	class Value : public Register {
	public:
        Value() : _value() {}
        Value(Type type, const char* name, T defaultVal)
            : Register(type), _name(name), _value(defaultVal), _mutable(true), _none(false) {}

        void Set(T v) { _value = v; }
        T Get() const { return _value; }
        int GUID() const { return -1; }
        const char* Name() const { return _name; }
        bool IsMutable() const { return _mutable; }
        bool IsNone() const { return _none; }

        operator T() const { return _value; }
        void operator = (const T& rhs) { _value = rhs; }

	protected:
        const char* _name;
        T _value;
        bool _mutable, _none;
	};

	/// @brief BUILT-IN CLASS: Integer
	/// @author Kyle Morris
	/// @since v0.1
	class Int : public Value<int> {
    public:
        using Value::operator=;
        Int() { _type = Type::INT; }
        Int(const char* name, int defaultVal)
            : Value(Type::INT, name, defaultVal) {}
	};

	/// @brief BUILT-IN CLASS: Real Number
	/// @author Kyle Morris
	/// @since v0.1
	class Real : public Value<float> {
    public:
        using Value::operator=;
        Real() { _type = Type::INT; }
        Real(const char* name, float defaultVal)
            : Value(Type::REAL, name, defaultVal) {}
	};

	/// @brief BUILT-IN CLASS: Boolean
	/// @author Kyle Morris
	/// @since v0.1
	class Boolean : public Value<bool> {
    public:
        using Value::operator=;
        Boolean() { _type = Type::BOOL; }
        Boolean(const char* name, bool defaultVal)
            : Value(Type::BOOL, name, defaultVal) {}
	};

	/// @brief BUILT-IN CLASS: String
	/// @author Kyle Morris
	/// @since v0.1
	class String : public Value<char*> {
    public:
        using Value::operator=;
        String() { _type = Type::STRING; }
        String(const char* name, char* defaultVal)
            : Value(Type::STRING, name, defaultVal) {}
	};

	/// @brief Represents the empty register.
	extern Register empty_t;

	/// @brief This macro returns the address of the empty register.
	#define DARGON_EMPTY_REG empty_t

};

#endif
