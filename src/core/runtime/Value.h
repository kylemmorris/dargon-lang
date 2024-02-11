 /**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Register.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 *  The 'Value' class acts as the highest-level value type in Dargon.
 *  Equivelent to 'object' in other languages, however it cannot be
 *  accessed within the Dargon language itself.
 *
 */

#ifndef DARGON_HEADER_VALUE
#define DARGON_HEADER_VALUE

#include <string>

namespace dargon {

	/// @brief Abstract class representing a Dargon runtime value.
	/// @author Kyle Morris
	/// @since v0.1
	class ValueBase {
	public:
        enum class Type {
            UNDEFINED,
            INT,
            REAL,
            BOOL,
            STRING,
            USERDEF
        };

        ValueBase() : _type(Type::UNDEFINED) {}

        ValueBase(Type type) : _type(type) {}

        Type GetType() const { return _type; }

        std::string ToString() const {
            switch(_type) {
                case Type::INT: return "INT";
                case Type::REAL: return "REAL";
                case Type::BOOL: return "BOOL";
                case Type::STRING: return "STRING";
                case Type::USERDEF: return "USERDEF";
                case Type::UNDEFINED: return "UNDEFINED";
                default: return "";
            }
        }

        bool operator==(const ValueBase& rhs) const noexcept {
            return _type == rhs._type;
        }

    protected:
        Type _type;
	};

	/// @brief Template implementation of 'Registers'.
	/// @author Kyle Morris
	/// @since v0.1
	template<typename T>
	class Value : public ValueBase {
	public:
        Value() : _value() {}
        Value(Type type, const std::string& name, T defaultVal)
            : ValueBase(type), _name(name), _value(defaultVal), _mutable(true), _none(false) {}

        void Set(T v) { _value = v; }
        T Get() const { return _value; }
        int GUID() const { return -1; }
        const std::string Name() const { return _name; }
        bool IsMutable() const { return _mutable; }
        bool IsNone() const { return _none; }

        operator T() const { return _value; }
        void operator = (const T& rhs) { _value = rhs; }

	protected:
        const std::string _name;
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
	class String : public Value<std::string> {
    public:
        using Value::operator=;
        String() { _type = Type::STRING; }
        String(const std::string& name, std::string& defaultVal)
            : Value(Type::STRING, name, defaultVal) {}
	};

	/// @brief Represents the empty value.
	extern ValueBase NONE_VALUE;

};

#endif
