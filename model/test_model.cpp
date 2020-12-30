#include <iostream>
#include <assert.h>
#include "include/modelmanager.h"

ModelTable* CreateTableUsers(void);
ModelTable* CreateTableOffice(void);
ModelTable* CreateTableDepartment(void);
ModelTable* CreateTableGroups();
ModelTable* CreateTableGroupMembers();
ModelTable* CreateDummyTable(std::string name, std::string type);


int main(int argc, char**argv)
{
    ModelManager manager;
    ModelTable *table_to_add;
    ModelTable *error_table;

    std::cout<<"Model testing..."<<std::endl;

    // User table add
    table_to_add = CreateTableUsers();
    manager.AppendTable(table_to_add);

    // Error check: duplicate names and types
    error_table = CreateDummyTable("abc", "User");
    manager.AppendTable(error_table);
    error_table = CreateDummyTable("users", "abc");
    manager.AppendTable(error_table);
    assert("Table duplicate (by name) added to model manager" && manager.GetTableCount()==1);

    // Office table add
    table_to_add = CreateTableOffice();
    manager.AppendTable(table_to_add);
    //
    table_to_add = CreateTableDepartment();
    manager.AppendTable(table_to_add);
    //
    table_to_add = CreateTableGroups();
    manager.AppendTable(table_to_add);
    //
    table_to_add = CreateTableGroupMembers();
    manager.AppendTable(table_to_add);
    //
    ModelTable *table = manager.FindTableByName("group_members");
    ModelTable *outer_table = manager.FindTableByName("users");
    assert("Table found" && table!=nullptr);
    assert("Table found" && outer_table!=nullptr);

    table->AddForeignKey(outer_table, "user_id", "user_id");
    table->GetCreateQuery();

    std::cout<<"Manager table count:"<<manager.GetTableCount()<<std::endl;
    return 0;
}


ModelTable* CreateDummyTable(std::string name, std::string type)
{
    ModelTable *table = new ModelTable(name, type);
    return table;
}


ModelTable* CreateTableUsers()
{
    std::vector<ModelProperty> result_prop_list;

    ModelTable *test_table = new ModelTable("users", "User");
    test_table->AddProperty(ModelProperty("user_id", DATA_TYPE_INT));
    test_table->AddProperty(ModelProperty("user_name", DATA_TYPE_STRING_16));
    test_table->AddProperty(ModelProperty("user_password", DATA_TYPE_STRING_16));
    test_table->AddProperty(ModelProperty("user_name", DATA_TYPE_LONG_INT));    // error: duplicate
    test_table->AddProperty(ModelProperty("user_surname", DATA_TYPE_STRING_16));
    test_table->AddProperty(ModelProperty("department_id", DATA_TYPE_SMALL_INT));
    test_table->AddProperty(ModelProperty("user_position", DATA_TYPE_STRING_16));
    test_table->GetPropertyList(result_prop_list);
    std::cout<<"Added props: "<<result_prop_list.size()<<std::endl;

    assert("Property duplicate added in the table" && result_prop_list.size()==6);

    return test_table;
}

ModelTable* CreateTableOffice()
{
    ModelTable *table_office = new ModelTable("offices", "Office");
    table_office->AddProperty(ModelProperty("office_id", DATA_TYPE_SMALL_INT));
    table_office->AddProperty(ModelProperty("office_name", DATA_TYPE_STRING_256));
    table_office->AddProperty(ModelProperty("office_description", DATA_TYPE_TEXT));
    return table_office;
}

ModelTable* CreateTableDepartment()
{
    ModelTable *table_office = new ModelTable("departments", "Department");
    table_office->AddProperty(ModelProperty("department_id", DATA_TYPE_SMALL_INT));
    table_office->AddProperty(ModelProperty("department_name", DATA_TYPE_STRING_64));
    table_office->AddProperty(ModelProperty("department_description", DATA_TYPE_STRING_256));
    table_office->AddProperty(ModelProperty("parent_office", DATA_TYPE_SMALL_INT));
    return table_office;
}

ModelTable* CreateTableGroups()
{
    ModelTable *table_office = new ModelTable("user_groups", "Group");
    table_office->AddProperty(ModelProperty("group_id", DATA_TYPE_SMALL_INT));
    table_office->AddProperty(ModelProperty("group_name", DATA_TYPE_STRING_16));
    table_office->AddProperty(ModelProperty("group_description", DATA_TYPE_STRING_256));
    return table_office;
}

ModelTable* CreateTableGroupMembers()
{
    ModelTable *table_office = new ModelTable("group_members", "GroupMember");
    table_office->SetVisibility(false);
    table_office->AddProperty(ModelProperty("group_id", DATA_TYPE_SMALL_INT));
    table_office->AddProperty(ModelProperty("user_id", DATA_TYPE_STRING_16));
    return table_office;
}

