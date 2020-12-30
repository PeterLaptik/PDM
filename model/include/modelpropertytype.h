#ifndef MODELPROPERTYTYPE_H_INCLUDED
#define MODELPROPERTYTYPE_H_INCLUDED

#include <string>

enum ModelPropertyType
{
    // Integer
    DATA_TYPE_SMALL_INT,
    DATA_TYPE_INT,
    DATA_TYPE_LONG_INT,
    // Float numbers
    DATA_TYPE_FLOAT,
    DATA_TYPE_DOUBLE,
    // Varchars
    DATA_TYPE_STRING_16,
    DATA_TYPE_STRING_32,
    DATA_TYPE_STRING_64,
    DATA_TYPE_STRING_128,
    DATA_TYPE_STRING_256,
    DATA_TYPE_TEXT
};

namespace orm
{
    static std::string GetPropertyRealName(ModelPropertyType p_type)
    {
        switch(p_type)
        {
            case DATA_TYPE_SMALL_INT:
                return "SMALLINT";
            case DATA_TYPE_INT:
                return "INTEGER";
            case DATA_TYPE_LONG_INT:
                return "BIGINT";
            case DATA_TYPE_FLOAT:
                return "FLOAT";
            case DATA_TYPE_DOUBLE:
                return "DOUBLE";
            case DATA_TYPE_STRING_16:
                return "VARCHAR(16)";
            case DATA_TYPE_STRING_32:
                return "VARCHAR(32)";
            case DATA_TYPE_STRING_64:
                return "VARCHAR(64)";
            case DATA_TYPE_STRING_128:
                return "VARCHAR(128)";
            case DATA_TYPE_STRING_256:
                return "VARCHAR(256)";
            case DATA_TYPE_TEXT:
                return "TEXT";
        }
        return "UNDEFINED_TYPE";
    }


    static std::string GetPropertyName(ModelPropertyType p_type)
    {
        switch(p_type)
        {
            case DATA_TYPE_SMALL_INT:
                return "Short";
            case DATA_TYPE_INT:
                return "Integer";
            case DATA_TYPE_LONG_INT:
                return "Long";
            case DATA_TYPE_FLOAT:
                return "Float";
            case DATA_TYPE_DOUBLE:
                return "Double";
            case DATA_TYPE_STRING_16:
                return "String[16]";
            case DATA_TYPE_STRING_32:
                return "String[32]";
            case DATA_TYPE_STRING_64:
                return "String[64]";
            case DATA_TYPE_STRING_128:
                return "String[128]";
            case DATA_TYPE_STRING_256:
                return "String[256]";
            case DATA_TYPE_TEXT:
                return "Text";
        }
        return "UNDEFINED_TYPE";
    }
}

#endif // MODELPROPERTYTYPE_H_INCLUDED
