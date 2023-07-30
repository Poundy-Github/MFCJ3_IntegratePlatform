#include "log.h"
#include "board.h"
#include "printf.h"
#include "lsglog.h"

#define LOG_BUFFER_SIZE  512

static const char LogLevel[LOG_LEVEL_MAX] = {'T', 'D', 'I', 'W', 'E'};

static char LogBuffer[LOG_BUFFER_SIZE];

struct lsg_log_t g_lsg_log;

void LOG_OPEN(void)
{
//    lsg_log_init(&g_lsg_log, 0);
}

void LOG_CLOSE(void)
{

}

void LOG(char level, const char* format, ...)
{
    va_list args;
    int n1;
    int n2;

    LogBuffer[0] = '[';

    n1 = sprintf(&LogBuffer[1], "%ld", (Board_stm0->stm_tim0)/100);

    LogBuffer[n1+1] = ']';
    LogBuffer[n1+2] = '[';
    LogBuffer[n1+3] = LogLevel[level];
    LogBuffer[n1+4] = ']';
    LogBuffer[n1+5] = '[';
    LogBuffer[n1+6] = 'F';
    LogBuffer[n1+7] = 'B';
    LogBuffer[n1+8] = 'L';
    LogBuffer[n1+9] = ']';

    va_start(args, format);
    n2 = vsnprintf(&LogBuffer[n1+10], LOG_BUFFER_SIZE, format, args);
    va_end(args);

    LogBuffer[n1+n2+10] = '\r';
    LogBuffer[n1+n2+11] = '\n';

    lsg_log_write(&g_lsg_log, (const uint8_t *)LogBuffer, n1+n2+12);
}
