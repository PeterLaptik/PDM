#ifndef MODELPROPERTY_H_INCLUDED
#define MODELPROPERTY_H_INCLUDED

#include "modelpropertytype.h"
#include <string>

class ModelProperty
{
    public:
        ModelProperty(const std::string &name, ModelPropertyType type, bool is_const_property = false):
            m_name(name), m_type(type), m_is_const(is_const_property)
        { }

        ~ModelProperty()
        { }

        const std::string& GetName(void) const {return m_name;}
        const ModelPropertyType& GetType(void) const {return m_type;}
        const bool& GetIsConstantProperty(void) const {return m_is_const;}

    private:
        std::string m_name;
        ModelPropertyType m_type;
        bool m_is_const;
};

#endif // MODELPROPERTY_H_INCLUDED
