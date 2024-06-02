#include <stdio.h>
#include <yara.h>
#include <android.h>
#include <cjson/cJSON.h> 


typedef struct 
{
    char* filename;
    cJSON* result_json;
} UserData;


int callback(YR_SCAN_CONTEXT* context, int message,	void *message_data, void *user_data) 
{
    YR_RULE* rule = (YR_RULE*)message_data;
    UserData* userdata = (UserData*)user_data;
    
    if (message == CALLBACK_MSG_RULE_MATCHING) 
    {
        printf("\tMatched rule: %s\n", rule->identifier);

        cJSON* rule_obj = cJSON_CreateObject();
        cJSON_AddItemToObject(rule_obj, "filename", cJSON_CreateString(userdata->filename));
        cJSON_AddItemToObject(rule_obj, "rulename", cJSON_CreateString(rule->identifier));

        YR_META* meta;
        yr_rule_metas_foreach(rule, meta) 
        {
            if (meta->type == META_TYPE_STRING) 
            {
                cJSON_AddItemToObject(rule_obj, meta->identifier, cJSON_CreateString(meta->string));
            }
        }

        cJSON_AddItemToArray(userdata->result_json, rule_obj);
    }
    else if (message == CALLBACK_MSG_RULE_NOT_MATCHING) 
    {
        printf("\tNo matches for rule: %s\n", rule->identifier);
    }
    else if (message == CALLBACK_MSG_SCAN_FINISHED) 
    {
        return CALLBACK_ABORT;
    }
    
    return CALLBACK_CONTINUE;
}


char* process_scan(char* rule_folder, char* analyse_folder) 
{
    UserData user_data;
    char *json_result = NULL;

    yr_initialize();

    YR_COMPILER* compiler;
    yr_compiler_create(&compiler);

    const char* rules_string = read_rules_file(rule_folder);
    if (rules_string != NULL) 
    {
        yr_compiler_add_string(compiler, rules_string, NULL);

        YR_RULES* rules;
        yr_compiler_get_rules(compiler, &rules);

        YR_SCANNER* scanner;
        yr_scanner_create(rules, &scanner);

        yr_scanner_set_callback(scanner, callback, NULL);

        int num_files;
        char** files = read_directory(analyse_folder, &num_files);

        if (files != NULL) 
        {
            user_data.result_json = cJSON_CreateArray();

            for (int i = 0; i < num_files; i++)
            {
                printf("Scanning file %s:\n", files[i]);
                user_data.filename = files[i];
                yr_rules_scan_file(rules, files[i], 0, callback, &user_data, 0);
            }

            json_result = cJSON_Print(user_data.result_json);
        }
        
        cJSON_Delete(user_data.result_json);
        yr_scanner_destroy(scanner);
        yr_rules_destroy(rules);
        free(files);
    }
    
    yr_compiler_destroy(compiler);
    yr_finalize();

    return json_result;
}
