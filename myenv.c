/*
 *  myenv.c : env コマンドのクローン
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef __linux__
#include "myputenv.h"
#endif

extern char **environ;

int main(int argc, char *argv[])
{
    int i = 1;

    /* name=value の処理 */
    while (i < argc && strchr(argv[i], '=') != NULL) {
#ifdef __linux__
        if (myputenv(argv[i]) != 0) {
            fprintf(stderr, "myenv: cannot set %s\n", argv[i]);
            return 1;
        }
#else
        putenv(argv[i]);
#endif
        i++;
    }

    /* コマンドが指定されている場合 */
    if (i < argc) {
        execvp(argv[i], &argv[i]);

        /* execvp は失敗時のみ戻る */
        perror(argv[i]);
        return 1;
    }

    /* コマンドが無い場合は環境変数一覧を表示 */
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }

    return 0;
}

/* 実行例

ここに実行例を書く

環境変数一覧を表示
% ./myenv
TMPDIR=/var/folders/1p/whzqny2s7k7_txnjx428fgcm0000gn/T/
__CFBundleIdentifier=com.apple.Terminal
XPC_FLAGS=0x0
LaunchInstanceID=16248E4D-0B82-46D7-9ACD-A7C14C7FC46D
TERM=xterm-256color
SSH_AUTH_SOCK=/var/run/com.apple.launchd.USCYSxO9Cq/
Listeners
SECURITYSESSIONID=186b7
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
COLORTERM=truecolor
OSLogRateLimit=64
TERM_PROGRAM_VERSION=470
TERM_SESSION_ID=4E25AB1A-D290-477D-AEF4-7998D24DEAAD
SHELL=/bin/zsh
HOME=/Users/nakagawaryuya
LOGNAME=nakagawaryuya
USER=nakagawaryuya
PATH=/usr/local/bin:/System/Cryptexes/App/usr/bin:/
usr/bin:/bin:/usr/sbin:/sbin:/var/run/
com.apple.security.cryptexd/codex.system/bootstrap/
usr/local/bin:/var/run/com.apple.security.cryptexd/
codex.system/bootstrap/usr/bin:/var/run/
com.apple.security.cryptexd/codex.system/bootstrap/
usr/appleinternal/bin:/opt/pkg/env/active/bin:/opt/
pmk/env/global/bin:/opt/homebrew/bin
SHLVL=1
PWD=/Users/nakagawaryuya/Syspro2/kadai09-i23nakagawa
OLDPWD=/Users/nakagawaryuya/Syspro2
LANG=ja_JP.UTF-8
_=/Users/nakagawaryuya/Syspro2/kadai09-i23nakagawa/./myenv

環境変数を追加して表示
%./myenv TEST=hello
TMPDIR=/var/folders/1p/whzqny2s7k7_txnjx428fgcm0000gn/T/
__CFBundleIdentifier=com.apple.Terminal
XPC_FLAGS=0x0
LaunchInstanceID=16248E4D-0B82-46D7-9ACD-A7C14C7FC46D
TERM=xterm-256color
SSH_AUTH_SOCK=/var/run/com.apple.launchd.USCYSxO9Cq/
Listeners
SECURITYSESSIONID=186b7
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
COLORTERM=truecolor
OSLogRateLimit=64
TERM_PROGRAM_VERSION=470
TERM_SESSION_ID=4E25AB1A-D290-477D-AEF4-7998D24DEAAD
SHELL=/bin/zsh
HOME=/Users/nakagawaryuya
LOGNAME=nakagawaryuya
USER=nakagawaryuya
PATH=/usr/local/bin:/System/Cryptexes/App/usr/bin:/
usr/bin:/bin:/usr/sbin:/sbin:/var/run/
com.apple.security.cryptexd/codex.system/bootstrap/
usr/local/bin:/var/run/com.apple.security.cryptexd/
codex.system/bootstrap/usr/bin:/var/run/
com.apple.security.cryptexd/codex.system/bootstrap/
usr/appleinternal/bin:/opt/pkg/env/active/bin:/opt/
pmk/env/global/bin:/opt/homebrew/bin
SHLVL=1
PWD=/Users/nakagawaryuya/Syspro2/kadai09-i23nakagawa
OLDPWD=/Users/nakagawaryuya/Syspro2
LANG=ja_JP.UTF-8
_=/Users/nakagawaryuya/Syspro2/kadai09-i23nakagawa/./myenv
TEST=hello

コマンドを実行
%  ./myenv TEST=hello printenv TEST 
hello

複数の環境変数
% ./myenv A=1 B=2 printenv A
1
% ./myenv A=1 B=2 printenv B
2

エラー処理
% ./myenv TEST=abc no_such_command
no_such_command: No such file or directory
% ./myenv hoge
hoge: No such file or directory


env と比較
%env TEST=abc printenv TEST
abc
% ./myenv TEST=abc printenv TEST
abc

*/
