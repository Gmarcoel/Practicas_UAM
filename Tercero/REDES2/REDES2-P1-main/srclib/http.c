#include "http.h"
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <sys/wait.h>

/* Define errors */
#define RequestIsTooLongError -2
#define ParseError -3
//#define EINTR 0
#define IOError -4
#define BAD_REQUEST 400
#define NOT_FOUND 404
#define INTERNAL_SERVER 500

/*Define extensions and types*/
typedef struct
{
    const char *ext;
    const char *type;
} exttype;

enum rw_type
{
    READ,
    WRITE
};

exttype et[] = {
    {".txt", "text/plain"},
    {".htm", "text/html"},
    {".html", "text/html"},
    {".gif", "image/gif"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".mpg", "video/mpeg"},
    {".mpeg", "video/mpeg"},
    {".doc", "application/msword"},
    {".docx", "application/msword"},
    {".pdf", "application/pdf"},

    {".py", "text/html"},
    {".php", "text/html"},
};

/* Private functions */
void get(int sock, char *path, char *name, char *args);
void post(int sock, char *path, char *name, char *args);
void options(int sock, char *name);
int get_date(char *date);
void error(int socketfd, int error, char *server);
int CGIScript(char *command, char *arg, char *route);
int MakeArguments(char *args, char *body);

// Function designed for chat between client and server.
int process(int *fd, char *name)
{
    /* Declare variables  */
    int sock = *fd, i = 0, pret, minor_version;
    char buf[8096] = "", *method = NULL, *path = NULL, cleanPath[4096] = "", *params = NULL, cleanParams[4096] = "", *token = NULL, args[4096] = "", *body = NULL, body2[4096] = "";
    struct phr_header headers[100];
    size_t buflen = 0, prevbuflen = 0, method_len, path_len, num_headers;
    ssize_t rret;
        while (1)
        {            
            // read the request
            while ((rret = read(sock, buf + buflen, sizeof(buf) - buflen)) == -1 && errno == EINTR)
                ;
            if (rret <= 0)
                return IOError;
            prevbuflen = buflen;
            buflen += rret;
            // parse the request 
            num_headers = sizeof(headers) / sizeof(headers[0]);
            pret = phr_parse_request(buf, buflen, &method, &method_len, &path, &path_len,
                                     &minor_version, headers, &num_headers, prevbuflen);
            if (pret > 0)
                break; // successfully parsed the request 
            else if (pret == -1)
                return ParseError;
            // request is incomplete, continue the loop 
            assert(pret == -2);
            if (buflen == sizeof(buf))
                return RequestIsTooLongError;
            
            
        }

        /* We check if the connection is suposed to remain open */
        for (int i = 0; i < (int)num_headers; i++)
        {
            if (strncmp(headers[i].name, "Connection", headers[i].name_len) == 0)
            {
                /* If it is not, we close it  */
                if (strncmp(headers[i].value, "close", headers[i].value_len) == 0)
                {
                    //return 0;
                }
            }
        }

        /* We make a clean path */
        strncpy(cleanPath, path, path_len);
        cleanPath[path_len] = '\0';
        /* if the path is '/' we redirect it to index */
        if (strcmp(cleanPath, "/") == 0 || path == NULL)
        {
            strcpy(cleanPath, "/index.html");
            path_len += strlen(cleanPath) - 1;
        }
        // printf("cleanPath: %s\n", cleanPath);

        /* Check request type */
        sprintf(method, "%.*s", (int)method_len, method);

        /* Reset args */
        args[0] = '\0';

        if (strcmp(method, "GET") == 0)
        {

            if (strchr(cleanPath, '?') != NULL)
            {
                strcpy(args, strchr(cleanPath, '?') + 1);
                cleanPath[strchr(cleanPath, '?') - cleanPath] = '\0';
                MakeArguments(cleanParams, args);

                get(sock, cleanPath, name, cleanParams);
            }
            else
            {
                get(sock, cleanPath, name, NULL);
            }
        }
        else if (strcmp(method, "POST") == 0)
        {
            body = buf + pret;
            strncpy(body2, body, buflen - pret);
            strcpy(args, " ");

            MakeArguments(args, body2);

            post(sock, cleanPath, name, args);
        }
        else if (strcmp(method, "OPTIONS") == 0)
        {
            options(sock, name);
        }
        free(params);
        free(token);
}

void get(int sock, char *path, char *name, char *args)
{

    exttype *exttype = et;
    FILE *f = NULL;
    struct stat sb;
    int len, totalLen;
    char bf[2000];
    char *ext;
    char date[2000];
    char contentType[2000] = "";
    char response[4096];
    char route[1000];
    int script = 0;
    char args2[4096];
    char command[4096];
    char scriptResponse[4096] = "";
    int scriptdp = 0;

    if (args != NULL)
    {
        strcpy(args2, args);
    }
    else
    {
        args2[0] = ' ';
        args2[1] = '\0';
    }

    /* We get the extension of the file */
    if (strchr(path, '.') != NULL)
    {
        ext = strchr(path, '.');
    }

    /* Find route to file */
    strcpy(route, "www/");
    strcat(route, path);

    if (access(route, F_OK) == -1)
    {
        error(sock, NOT_FOUND, name);
        return;
    }

    /* In case file is script, run script */
    strcpy(command, "./");
    if (strcmp(ext, ".py") == 0)
    {
        strcpy(command, "python3");
        script = 1;
    }
    if (strcmp(ext, ".php") == 0)
    {
        strcpy(command, "php");
        script = 1;
    }

    /* Open file */
    f = fopen(route, "r");
    if (!f)
    {
        printf("Could not open the file");
        return;
    }

    /* Get the stats of the file */
    if (stat(route, &sb) != 0)
    {
        error(sock, BAD_REQUEST, name);
        return;
    }

    /* Get the size of the file */
    len = sb.st_size;

    /* Get the type associated with the file extension */
    while (exttype->ext)
    {

        if (strcmp(exttype->ext, ext) == 0)
        {
            sprintf(contentType, "%s", exttype->type);
            break;
        }
        exttype++;
    }
    if (strcmp(contentType, "") == 0)
    {
        error(sock, BAD_REQUEST, name);
        return;
    }

    /* Get the current date */
    get_date(date);

    /* Write the response to the client */

    if (script)
    {
        totalLen = 0;
        strcpy(scriptResponse, "");
        scriptdp = CGIScript(command, args2, route);
        while ((len = read(scriptdp, bf, sizeof(bf))) > 0)
        {
            totalLen += len;
            strcat(scriptResponse, bf);
        }
        close(scriptdp);

        sprintf(response, "HTTP/1.1 200 OK\r\n%s\r\nServer: %s\r\nLast-Modified: %.*s\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n", date, name, (int)strlen(ctime(&sb.st_mtime)) - 1, ctime(&sb.st_mtime), totalLen, contentType);
        if (write(sock, response, strlen(response)) == 1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        write(sock, scriptResponse, totalLen);
    }
    else
    {
        sprintf(response, "HTTP/1.1 200 OK\r\n%s\r\nServer: %s\r\nLast-Modified: %.*s\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n", date, name, (int)strlen(ctime(&sb.st_mtime)) - 1, ctime(&sb.st_mtime), len, contentType);
        if (write(sock, response, strlen(response)) == 1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        /* Send the file data */
        while (!feof(f))
        {
            len = fread(bf, sizeof(char), 1024, f);
            write(sock, bf, len);
        }
    }
    /* Close the file */
    // close(sock);

    fclose(f);
    return;
}

void post(int sock, char *path, char *name, char *args)
{

    exttype *exttype = et;
    FILE *f = NULL;
    struct stat sb;
    int len, totalLen;
    char bf[2000];
    char *ext;
    char date[2000];
    char contentType[2000] = "";
    char response[4096];
    char route[strlen(path)];

    char command[4096];
    char args2[4096];
    int script = 0;
    int scriptdp;
    char scriptResponse[4096] = "";

    if (args != NULL)
    {
        strcpy(args2, args);
    }
    else
    {
        args2[0] = ' ';
        args2[1] = '\0';
    }
    /* We get the extension of the file */
    if (strchr(path, '.') != NULL)
    {
        ext = strchr(path, '.');
    }

    /* Find route to file */
    strcpy(route, "www");
    strcat(route, path);

    if (access(route, F_OK) == -1)
    {
        error(sock, NOT_FOUND, name);
        return;
    }

    /* In case file is script, run script */
    strcpy(command, "./");
    if (strcmp(ext, ".py") == 0)
    {
        strcpy(command, "python3");
        script = 1;
    }
    if (strcmp(ext, ".php") == 0)
    {
        strcpy(command, "php");
        script = 1;
    }

    /* Get the arguments from the request body */

    /* Open file */
    f = fopen(route, "r");
    if (!f)
    {
        printf("Error oppening the file errno:");
        return;
    }

    /* Get the stats of the file */
    if (stat(route, &sb) != 0)
    {
        error(sock, BAD_REQUEST, name);
        return;
    }

    /* Get the type associated with the file extension */
    while (exttype->ext)
    {

        if (strcmp(exttype->ext, ext) == 0)
        {
            sprintf(contentType, "%s", exttype->type);
            break;
        }
        exttype++;
    }
    if (strcmp(contentType, "") == 0)
    {
        error(sock, BAD_REQUEST, name);
        return;
    }

    /* Get the current date */
    get_date(date);

    /* Write the response to the client */

    /* If script send the response */
    if (script)
    {
        totalLen = 0;
        strcpy(scriptResponse, "");
        scriptdp = CGIScript(command, args2, route);
        while ((len = read(scriptdp, bf, sizeof(bf))) > 0)
        {
            totalLen += len;
            strcat(scriptResponse, bf);
        }
        close(scriptdp);

        sprintf(response, "HTTP/1.1 200 OK\r\n%s\r\nServer: %s\r\nLast-Modified: %.*s\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n", date, name, (int)strlen(ctime(&sb.st_mtime)) - 1, ctime(&sb.st_mtime), totalLen, contentType);
        if (write(sock, response, strlen(response)) == 1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        write(sock, scriptResponse, totalLen);
    }
    else
    {
        /* Get the size of the file */
        len = sb.st_size;
        sprintf(response, "HTTP/1.1 200 OK\r\n%s\r\nServer: %s\r\nLast-Modified: %.*s\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n", date, name, (int)strlen(ctime(&sb.st_mtime)) - 1, ctime(&sb.st_mtime), len, contentType);
        if (write(sock, response, strlen(response)) == 1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        /* Send the file data */
        while (!feof(f))
        {
            len = fread(bf, sizeof(char), 1024, f);

            write(sock, bf, len);
        }
    }
    write(sock, "\r\n\r\n", strlen("\r\n\r\n"));
    fclose(f);

    /* Close the file */
    // close(sock);
}

void options(int sock, char *name)
{
    char date[600], ret[2000];
    get_date(date);
    sprintf(ret, "HTTP/1.1 204 No Content\r\nAllow: GET, POST, OPTIONS\r\nDate: %s\r\nServer: %s\r\n\r\n", date, name);
    write(sock, ret, strlen(ret));
}

char *day(int day)
{
    switch (day)
    {
    case 0:
        return "Sun";
    case 1:
        return "Mon";
    case 2:
        return "Tue";
    case 3:
        return "Wed";
    case 4:
        return "Thu";
    case 5:
        return "Fri";
    case 6:
        return "Sat";
    }
}

char *month(int month)
{
    switch (month)
    {
    case 1:
        return "Jan";
    case 2:
        return "Feb";
    case 3:
        return "Mar";
    case 4:
        return "Apr";
    case 5:
        return "May";
    case 6:
        return "Jun";
    case 7:
        return "Jul";
    case 8:
        return "Aug";
    case 9:
        return "Sep";
    case 10:
        return "Oct";
    case 11:
        return "Nov";
    case 12:
        return "Dec";
    }
}

int get_date(char *date)
{
    // return "Date: Fri, 31 Dec 1999 23:59:59 GMT\r\n"; // JEJE
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // save in ret the date in the format: "Date: Fri, 31 Dec 1999 23:59:59 GMT\r\n"
    sprintf(date, "Date: %s, %d %s %d %d:%d:%d GMT",
            day(tm.tm_wday),
            tm.tm_mday,
            month(tm.tm_mon),
            tm.tm_year + 1900,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec);
    return 0;
}

void error(int socketfd, int error, char *server)
{
    char msg[600], date[200];
    get_date(date);
    if (error == BAD_REQUEST)
    {
        sprintf(msg, "HTTP/1.1 400 Bad Request\r\nDate: %s\r\nServer: %s\r\nConnection: keep-alive\r\nContent-Type: text/html\r\nContent-Length: 196\r\n\r\n<!DOCTYPE HTML PUBLIC '-//IETF//DTD HTML 2.0//EN'><html><head><title>400 Bad Request</title></head><body><h1>Bad request</h1><p>Your user has issued a malformed or illegal request.</p></body></html>", date, server);
    }
    else if (error == NOT_FOUND)
    {
        sprintf(msg, "HTTP/1.1 404 Not found\r\nDate: %s\r\nServer: %s\r\nConnection: keep-alive\r\nContent-Type: text/html\r\nContent-Length: 189\r\n\r\n<!DOCTYPE HTML PUBLIC '-//IETF//DTD HTML 2.0//EN'><html><head><title>404 Not found</title></head><body><h1>Not found</h1><p>The requested URL was not found on this server</p></body></html>", date, server);
    }
    else if (error == INTERNAL_SERVER)
    {
        sprintf(msg, "HTTP/1.1 500 Internal Server Error\r\nDate: %s\r\nServer: %s\r\nConnection: keep-alive\r\nContent-Type: text/html\r\nContent-Length: 206\r\n\r\n<!DOCTYPE HTML PUBLIC '-//IETF//DTD HTML 2.0//EN'><html><head><title>500 Internal Server Error</title></head><body><h1>Internal server error</h1><p>There was an internal error please try again later</p></body></html>", date, server);
    }
    write(socketfd, msg, strlen(msg));
}

int CGIScript(char *command, char *arg, char *route)
{
    pid_t pid;
    int child_in[2];
    int child_out[2];
    pipe(child_in);
    pipe(child_out);
    pid = fork();

    if (pid != 0)
    {
        // Father
        // Close the child_in pipe for reading
        close(child_in[READ]);
        // Close the child_out pipe for writing
        close(child_out[WRITE]);
        // Close the stdin so the child does not lock
        close(child_in[WRITE]);
        // Wait for the child to die
        wait(NULL);
        // return child_out[READ];
        return child_out[READ];
        // Read the response from the child
        // int len = read(child_out[READ], scriptResponse, sizeof(scriptResponse));
        // close(child_out[READ]);
        // printf("%s\n", scriptResponse);
        // return len;
    }

    // Child
    // Close the child_out pipe for reading
    close(child_out[READ]);
    // Close the child_in pipe for writing
    close(child_in[WRITE]);
    // Close the stdout so the child does not lock
    close(child_in[READ]);
    // child_out to stdout
    dup2(child_out[WRITE], STDOUT_FILENO);
    if (execlp(command, command, route, arg, NULL) == -1)
    {
        perror("Error in exec.\n");
        return -1;
    }
    // Close the child_out pipe for writing
    close(child_out[WRITE]);
}

int MakeArguments(char *args, char *body)
{
    int i = 0;
    int j = 0;
    int end_flag = 0;
    if (body == NULL)
    {
        return -1;
    }
    while (body[i] != '\0')
    {

        while (body[i] != '=' || body[i] != '\0')
        {
            i++;

            if (body[i] == '=')
            {
                break;
            }
        }
        if (body[i] == '\0')
        {
            break;
        }
        i++;
        while (body[i] != '\0')
        {
            if (body[i] == ' ')
            {
                end_flag = 1;
                break;
            }
            if (body[i] == '&')
            {
                break;
            }

            if (body[i] == '+')
            {
                args[j] = ' ';
            }
            else
            {
                args[j] = body[i];
            }
            j++;
            i++;
        }
        if (end_flag == 1)
        {
            break;
        }
    }
    return 0;
}