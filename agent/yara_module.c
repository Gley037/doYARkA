#include <stdio.h>
#include <yara.h>

#include "android_module.h"


int callback(YR_SCAN_CONTEXT* context, int message,	void *messageData, void *userData) 
{
    YR_RULE* rule = (YR_RULE*)messageData;

    if (message == CALLBACK_MSG_RULE_MATCHING) 
    {
        printf("Matched rule: %s\n", rule->identifier);
    }
    else if (message == CALLBACK_MSG_RULE_NOT_MATCHING)
    {
        printf("No matches with message: %d\n", message);
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

    const char* rule_string = "rule ExampleRule { strings: $ = \"example\" condition: all of them }";

    yr_compiler_add_string(compiler, rule_string, NULL);

    YR_RULES* rules;
    yr_compiler_get_rules(compiler, &rules);

    YR_SCANNER* scanner;
    yr_scanner_create(rules, &scanner);

    yr_scanner_set_callback(scanner, callback, NULL);

    int num_files;
    char* dir_path = "."; //"/storage/emulated/0/Download";
    char** files = read_directory(dir_path, &num_files);

    if (files != NULL) 
    {
        for (int i = 0; i < num_files; i++) 
        {
            printf("Scan - %s:\n", files[i]);
            yr_rules_scan_file(rules, files[i], 0, callback, NULL, 0);
        }
    }

    yr_scanner_destroy(scanner);
    yr_rules_destroy(rules);
    yr_compiler_destroy(compiler);
    yr_finalize();
    free(files);

    return 0;
}
