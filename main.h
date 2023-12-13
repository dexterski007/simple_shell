#ifndef _MAIN_H_
#define _MAIN_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

/**
 * struct stringlist - list string
 * @num: num
 * @str: string
 * @next: pointer
 */
typedef struct stringlist
{
	int num;
	char *str;
	struct stringlist *next;
} list_t;

/**
 *struct passparam - pass param
 *@arg: arg
 *@argv: argv
 *@path: path
 *@argc: argc
 *@line_count: countline
 *@err_num: err num
 *@linecount_flag: flag
 *@fname: name
 *@env: env
 *@environ: copy of environ
 *@history: hist
 *@alias: alias
 *@env_changed: check env
 *@status: status
 *@buffer_cmd: buff cmd
 *@buffer_cmd_type: cmd type
 *@readfd: read fd
 *@histcount: hist count
 */
typedef struct passparam
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **buffer_cmd;
	int buffer_cmd_type;
	int readfd;
	int histcount;
} param_t;

#define param_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct integrated - integrated
 *@type: type
 *@func: funct
 */
typedef struct integrated
{
	char *type;
	int (*func)(param_t *);
} integrated_table;

char *setmemory(char *, char, unsigned int);
int freemem2(void **);
void freemem1(char **);
void *allocreac(void *, unsigned int, unsigned int);

/* hoshell.c */
int hoshell(param_t *, char **);
int find_integrated(param_t *);
void cmdseek(param_t *);
void cmddup(param_t *);

/* lenstrcalc.c */
int lenstrcalc(char *);
int comparestr(char *, char *);
char *prefi(const char *, const char *);
char *concatstr(char *, char *);

/* cmdcheck.c */
int cmdcheck(param_t *, char *);
char *chardup(char *, int, int);
char *pathseek(param_t *, char *, char *);

/* putserror.c */
void putserror(char *);
int putcharerror(char);
int filedescput(char c, int fd);
int filedescputstr(char *str, int fd);

/* copystrs.c */
char *copystrs(char *, char *);
char *doubstr(const char *);
void putsring(char *);
int altputchar(char);

/* quit.c */
char **tokenstring1(char *, char *);
char **tokenstring2(char *, char);
char *strincopy2(char *, char *, int);
char *stringconcat2(char *, char *, int);
char *stringsearch(char *, char);

/* histfileget.c */
char *histfileget(param_t *param);
int histput(param_t *param);
int histgetfile(param_t *param);
int histlistcr(param_t *param, char *buf, int linecount);
int histenum(param_t *param);

/* alias.c */
int detectchain(param_t *, char *, size_t *);
void chainchk(param_t *, char *, size_t *, size_t, size_t);
int aliasvexel(param_t *);
int varvexel(param_t *);
int strvexel(char **, char *);

/* lenlist.c */
size_t lenlist(const list_t *);
char **convliststr(list_t *);
size_t listpr(const list_t *);
list_t *prefnod(list_t *, char *, char);
ssize_t nodeinddet(list_t *, list_t *);

/* checker.c */
int checkinter(param_t *);
int checkdelim(char, char *);
int checkalph(int);
int alphatonum(char *);

/* nodeplus.c */
list_t *nodeplus(list_t **, const char *, int);
list_t *nodeplusend(list_t **, const char *, int);
size_t listprstr(const list_t *);
int noderemind(list_t **, unsigned int);
void listfree(list_t **);

/* erroralphatonum.c */
int erroralphatonum(char *);
void errexport(param_t *, char *);
int descriptpr(int, int);
char *num_conv(long int, int, int);
void comment_rem(char *);

/* integrated1.c */
int histget(param_t *);
int aliasget(param_t *);
int remalias(param_t *param, char *str);
int instalias(param_t *param, char *str);
int pralias(list_t *node);

/* integrated.c */
int quits(param_t *);
int chngedir(param_t *);
int helpget(param_t *);

/* input_buf.c */
ssize_t getprompt(param_t *);
int linegetter(param_t *, char **, size_t *);
void signal2(int);

/* reminf.c */
void reminf(param_t *);
void putinf(param_t *, char **);
void cleaninf(param_t *, int);

/* envget.c */
char *envget(param_t *, const char *);
int envdetect(param_t *);
int envset(param_t *);
int envunset(param_t *);
int listenvfill(param_t *);

/* globalget.c */
char **globalget(param_t *);
int envunset2(param_t *, char *);
int envset2(param_t *, char *, char *);

#endif
