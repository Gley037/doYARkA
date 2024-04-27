#include <stdio.h>
#include <yara.h>
#include <android.h>


const char* RULE_FOLDER = "./rules/android.yar";


typedef struct {
    char* result_buffer;
    size_t buffer_size;
} UserData;


int callback(YR_SCAN_CONTEXT* context, int message,	void *messageData, void *userData) 
{
    YR_RULE* rule = (YR_RULE*)messageData;
    UserData* user_data = (UserData*)userData;
    
    if (message == CALLBACK_MSG_RULE_MATCHING) 
    {
        printf("\tMatched rule: %s\n", rule->identifier);
        snprintf(user_data->result_buffer + strlen(user_data->result_buffer), 
                    user_data->buffer_size - strlen(user_data->result_buffer), 
                    "\tMatched rule: %s\n", rule->identifier);
    }
    else if (message == CALLBACK_MSG_RULE_NOT_MATCHING) 
    {
        printf("\tNo matches for rule: %s\n", rule->identifier);
        snprintf(user_data->result_buffer + strlen(user_data->result_buffer), 
                    user_data->buffer_size - strlen(user_data->result_buffer), 
                    "\tNo matches for rule: %s\n", rule->identifier);
    }
    else if (message == CALLBACK_MSG_SCAN_FINISHED) 
    {
        return CALLBACK_ABORT;
    }
    
    return CALLBACK_CONTINUE;
}


char* process_scan(char* analyse_folder) 
{
    UserData user_data;

    yr_initialize();

    YR_COMPILER* compiler;
    yr_compiler_create(&compiler);

    const char* rules_string = read_file(RULE_FOLDER);
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
            user_data.buffer_size = num_files * 128;
            user_data.result_buffer = (char*)malloc(user_data.buffer_size * sizeof(char));
            user_data.result_buffer[0] = '\0';

            for (int i = 0; i < num_files; i++)
            {
                printf("Scanning file %s:\n", files[i]);
                snprintf(user_data.result_buffer + strlen(user_data.result_buffer), 
                    user_data.buffer_size - strlen(user_data.result_buffer), 
                    "Scanning file %s:\n", files[i]);

                yr_rules_scan_file(rules, files[i], 0, callback, &user_data, 0);
            }
        }

        yr_scanner_destroy(scanner);
        yr_rules_destroy(rules);
        free(files);
    }
   
    yr_compiler_destroy(compiler);
    yr_finalize();

    return user_data.result_buffer;
}
