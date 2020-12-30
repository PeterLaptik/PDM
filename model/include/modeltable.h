#ifndef MODELTABLE_H
#define MODELTABLE_H

#include"modelproperty.h"
#include <string>
#include <vector>
#include <map>


class ModelTable
{
    public:
        ModelTable(std::string table_name, std::string type_name);
        virtual ~ModelTable();

        bool AddProperty(const ModelProperty &prop);

        // Sets whether the table have sub-tables
        void SetInheritance(const bool &val);

        // Sets whether the table is visible in dbWizard application
        void SetVisibility(const bool &val);

        // The property can be used for sorting tables in list
        void SetId(int val);

        // Add table foreign key
        void AddForeignKey(ModelTable* outer_table, const std::string &outer_prop_name, const std::string &inner_prop_name);

        // Build create-table query for a database
        std::string GetCreateQuery(void) const;

        ModelProperty GetPropertyByName(const std::string &name) const;
        void GetPropertyList(std::vector<ModelProperty> &vec) const;

        bool GetInheritance(void) const;
        bool GetVisibility(void) const;
        int GetId(void) const;
        const std::string& GetTableName(void) const;
        const std::string& GetTypeName(void) const;

    protected:

    private:
        int id;
        ModelTable *parent;
        std::string m_table_name;
        std::string m_type_name;
        // Behavior properties
        bool m_is_hidden_table;
        bool m_implements_inheritance;
        // Properties
        std::vector<ModelProperty> m_properties;
        std::map <std::pair<ModelTable*, std::string>, std::string> m_foreign_keys;  // table,field -> m_field
};

#endif // MODELTABLE_H
