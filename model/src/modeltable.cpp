#include "modeltable.h"
#include <iostream>

static const std::string UNDEFINED_PROPERTY = "null";
static const int DEFAULT_ID = 1000;


ModelTable::ModelTable(std::string table_name, std::string type_name):
    id(DEFAULT_ID), parent(nullptr), m_table_name(table_name), m_type_name(type_name),
    m_is_hidden_table(false), m_implements_inheritance(false)
{ }

ModelTable::~ModelTable()
{ }


bool ModelTable::AddProperty(const ModelProperty &prop)
{
    for(std::vector<ModelProperty>::iterator it=m_properties.begin(); it!=m_properties.end(); ++it)
        if((*it).GetName()==prop.GetName())
            return false;

    m_properties.push_back(prop);
    return true;
}

void ModelTable::GetPropertyList(std::vector<ModelProperty> &vec) const
{
    for(std::vector<ModelProperty>::const_iterator it=m_properties.begin(); it!=m_properties.end(); ++it)
        vec.push_back(*it);
}

void ModelTable::SetId(int val)
{
    id = val;
}

void ModelTable::SetInheritance(const bool &val)
{
    m_implements_inheritance = val;
}

void ModelTable::SetVisibility(const bool &val)
{
    m_is_hidden_table = val;
}


void ModelTable::AddForeignKey(ModelTable* outer_table, const std::string &outer_prop_name, const std::string &inner_prop_name)
{
    std::pair<ModelTable*, std::string> outer_pair(outer_table, outer_prop_name);
    std::pair<std::pair<ModelTable*, std::string>, std::string> connection(outer_pair, inner_prop_name);
    m_foreign_keys.insert(connection);
}

bool ModelTable::GetInheritance() const
{
    return m_implements_inheritance;
}

bool ModelTable::GetVisibility() const
{
    return m_is_hidden_table;
}

int ModelTable::GetId() const
{
    return id;
}

const std::string& ModelTable::GetTableName(void) const
{
    return m_table_name;
}

const std::string& ModelTable::GetTypeName(void) const
{
    return m_type_name;
}

 ModelProperty ModelTable::GetPropertyByName(const std::string &name) const
 {
     for(std::vector<ModelProperty>::const_iterator it=m_properties.begin(); it!=m_properties.end(); ++it)
        if((*it).GetName()==name)
            return (*it);

     return ModelProperty(UNDEFINED_PROPERTY, DATA_TYPE_SMALL_INT);
 }

 std::string ModelTable::GetCreateQuery(void) const
 {
     std::string create_query;
     create_query.append("CREATE TABLE ").append(m_table_name).append(" (\n");
     // Insert fields
     int fields_size = m_properties.size();
     // Properties list
     for(std::vector<ModelProperty>::const_iterator it=m_properties.begin(); it!=m_properties.end(); ++it)
        create_query.append("\t")
        .append((*it).GetName()).append(" ")
        .append(orm::GetPropertyRealName((*it).GetType()))
        .append(--fields_size==0 ? "\n" : ",\n");
    // Foreign keys
    int keys_size = m_foreign_keys.size();
    for(std::map<std::pair<ModelTable*, std::string>, std::string>::const_iterator it=m_foreign_keys.begin(); it!=m_foreign_keys.end(); ++it)
        create_query.append("\tFOREIGN KEY (").append((*it).second)
        .append(") REFERENCES ")
        .append((*it).first.first->GetTableName())
        .append("(").append((*it).first.second)
        .append(--keys_size==0 ? ")\n" : "),\n");

     create_query.append(");\n");
     std::cout<<create_query;
     return create_query;
 }
