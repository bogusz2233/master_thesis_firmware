#include "FreeRTOS.h"
#include "string.h"
#include "task.h"

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    char task_name[configMAX_TASK_NAME_LEN];
    strncpy(task_name, pcTaskName, configMAX_TASK_NAME_LEN);
    assert(0);
}
