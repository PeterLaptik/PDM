#include "modelmanager.h"

ModelManager::ModelManager()
{ }

ModelManager::~ModelManager()
{
    for(std::vector<ModelTable*>::iterator it=m_tables.begin(); it!=m_tables.end(); ++it)
        delete (*it);
}


bool ModelManager::AppendTable(ModelTable *table)
{
    for(std::vector<ModelTable*>::iterator it=m_tables.begin(); it!=m_tables.end(); ++it)
    {
        if(((*it)->GetTableName()==table->GetTableName())||((*it)->GetTypeName()==table->GetTypeName()))
        {
            delete table;
            return false;
        }
    }
    m_tables.push_back(table);
    return true;
}

int ModelManager::GetTableCount() const
{
    return m_tables.size();
}

ModelTable* ModelManager::FindTableByName(const std::string &name)
{
    ModelTable *result = nullptr;
    for(std::vector<ModelTable*>::iterator it=m_tables.begin(); it!=m_tables.end(); ++it)
    {
        if((*it)->GetTableName()==name)
            result = *it;
    }
    return result;
}

const std::vector<ModelTable*>& ModelManager::GetTableList(void) const
{
    return m_tables;
}
