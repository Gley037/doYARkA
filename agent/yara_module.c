#include <stdio.h>
#include <yara.h>

#include "android_module.h"


const char* RULE_FOLDER = "./rules/android.yar";
const char* ANALYSE_FOLDER = "/storage/emulated/0/Download/";


int callback(YR_SCAN_CONTEXT* context, int message,	void *messageData, void *userData) 
{
    YR_RULE* rule = (YR_RULE*)messageData;

    if (message == CALLBACK_MSG_RULE_MATCHING) 
    {
        printf("Matched rule: %s\n", rule->identifier);
    }
    else if (message == CALLBACK_MSG_RULE_NOT_MATCHING)
    {
        printf("No matches for rule: %s\n", rule->identifier);
    }
    else if(message == CALLBACK_MSG_SCAN_FINISHED)
	{
		return CALLBACK_ABORT;
	}
    
    return CALLBACK_CONTINUE;
}


int main() 
{
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
        const char* analyse_folder = ANALYSE_FOLDER;
        char** files = read_directory(analyse_folder, &num_files);

        if (files != NULL) 
        {
            for (int i = 0; i < num_files; i++) 
            {
                printf("Scanning file %s:\n", files[i]);
                yr_rules_scan_file(rules, files[i], 0, callback, NULL, 0);
            }
        }

        yr_scanner_destroy(scanner);
        yr_rules_destroy(rules);
        free(files);
    }
   
    yr_compiler_destroy(compiler);
    yr_finalize();
    
    return 0;
}
