#include "lsglog.h"

void lsg_log_init(struct lsg_log_t *log,int options){
    log->magic= 0x12150208;
    log->head = 0;
    log->tail = 0;
    log->flags = 0;
    log->size = LSG_SIZE;
    log->options = options;
}

void lsg_log_write(struct lsg_log_t *log,const uint8_t *buff,uint32_t size){
    
    for(int i = 0;i < size;i++){
        
        const int available_size = log->size - ((log->tail > log->head) ?(log->tail - log->head):((log->tail + log->size) - log->head ) % log->size);
        if( available_size > 0 ){
            log->tail = (log->tail + 1) % log->size;
        }else{
            log->head = (log->head + 1) % log->size;
            log->tail = (log->tail + 1) % log->size;
            log->flags |= 1;
        }

        log->buffer[log->tail] = buff[i];

    }

}

void lsg_log_clear(struct lsg_log_t *log,const uint8_t *buff,uint32_t size){
    log->head = 0;
    log->tail = 0;
    log->flags = 0;
}
