#ifndef LOG_H
#define LOG_H

#define LOG_LEVEL_TRACE                         0
#define LOG_LEVEL_DEBUG                         1
#define LOG_LEVEL_INFO                          2
#define LOG_LEVEL_WARNING                       3
#define LOG_LEVEL_ERROR                         4
#define LOG_LEVEL_MAX                           5

#define LOG_LEVEL                               LOG_LEVEL_INFO

#if defined(LOG_EN)
void LOG_OPEN(void);
void LOG_CLOSE(void);
void LOG(char level, const char* format, ...);
#else
static inline void LOG_OPEN(void)
{

}
static inline void LOG_CLOSE(void)
{

}
static inline void LOG(char level, const char* format, ...)
{

}
#endif

#endif /* __LOG_H__ */
