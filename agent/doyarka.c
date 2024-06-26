#include <argp.h>
#include <string.h>
#include <stdlib.h>
#include <connection.h>
#include <yara_analyzer.h>


const char *argp_program_version = "doYARkA 0.1";
static char doc[] = "Remote Android YARA analyzer";
static char args_doc[] = "-i [IP] -p [PORT] -s [DIR] -r [FILE]";
static struct argp_option options[] = { 
    { "ip", 'i', "IP", 0, "doYARka server IP for sending scan data"},
    { "port", 'p', "PORT", 0, "doYARka server PORT for socket connection"},
    { "scan", 's', "SCAN", 0, "Android directory for YARA scanning"},
    { "rule", 'r', "RULE", 0, "YARA rules for scanning"},
    { 0 } 
};


struct arguments 
{
    char *server_ip;
    int server_port;
    char *scan_path;
    char *rule_file;
};


error_t parse_opt(int key, char *arg, struct argp_state *state) 
{
    struct arguments *arguments = state->input;

    switch (key) 
    {
        case 'i':
            arguments->server_ip = arg;
            break;
        case 'p':
            arguments->server_port = atoi(arg);
            break;
        case 's':
            arguments->scan_path = arg;
            break;
        case 'r':
            arguments->rule_file = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}


static struct argp argp = { options, parse_opt, args_doc, doc };


int main(int argc, char *args[])
{
    struct arguments arguments;

    arguments.server_ip = "127.0.0.1";
    arguments.server_port = 31337;
    arguments.scan_path = "/storage/emulated/0/Download";
    arguments.rule_file = "./rules/android.yar";

    argp_parse(&argp, argc, args, 0, 0, &arguments);

    int server_sockfd = initialize_socket(arguments.server_ip, arguments.server_port);
    if (server_sockfd == -1)
    {
        return 1;
    }

    process_scan(arguments.rule_file, arguments.scan_path, server_sockfd);
    
    close_socket(server_sockfd);
    return 0;
}