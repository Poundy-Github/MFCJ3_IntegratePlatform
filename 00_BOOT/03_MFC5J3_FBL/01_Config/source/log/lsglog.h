#ifndef LSG_LOG_H
#define LSG_LOG_H

#include <stddef.h>
#include <stdint.h>

#define LSG_SIZE 2048
struct lsg_log_t {
    uint32_t magic;
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    int      flags;
    int      options;
    uint8_t  buffer[LSG_SIZE];
};

void lsg_log_init(struct lsg_log_t *log,int options);

void lsg_log_write(struct lsg_log_t *log,const uint8_t *buff,uint32_t size);

void lsg_log_clear(struct lsg_log_t *log,const uint8_t *buff,uint32_t size);

#endif /** LSG_LOG_H */