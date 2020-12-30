#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <modeltable.h>

class ModelManager
{
    public:
        ModelManager();
        virtual ~ModelManager();

        // Returns: false if table or type name exists / true if all is OK
        // The table object is handled by the ModelManager-class, so it has not be deleted outside
        // (calls delete-operator on table-pointer if table or type name exists)
        bool AppendTable(ModelTable *table);

        // Return null-pointer if a table does not exist
        ModelTable* FindTableByName(const std::string &name);
//        ModelTable* FindTableByType(const std::string &type);

        int GetTableCount(void) const;
        const std::vector<ModelTable*>& GetTableList(void) const;

    protected:

    private:
        std::vector<ModelTable*> m_tables;
};

#endif // MODELMANAGER_H
