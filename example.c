#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>


static void createTasks();

static void vTask1(void *pvParameters);
static void vTask2(void *pvParameters);
static void vTask3(void *pvParameters);

static void getCurrentDate(char* date);
static void printDate();
static void getCurrentDate(char* data);
static void printTime();
static void getCurrentTime(char* tempo);
static void printTemperature();
static void getCurrentTemperature(char* temperatura);


SemaphoreHandle_t xSemaphore;
char buffer[100];


int main_(void)
{
    createTasks();
    vTaskStartScheduler();

    for (;; );
    return 0;
}


void createTasks()
{
    xSemaphore = xSemaphoreCreateMutex();
    xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);
    xTaskCreate(vTask3, "Task 3", 1000, NULL, 1, NULL);
}


void vTask1(void* pvParameters)
{
    for (;; )
    {
        if (xSemaphore != NULL)
        {
            if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE)
            {
                printDate();
                xSemaphoreGive(xSemaphore);
            }
        }
        else
        {
            printf("O semáforo não foi criado\n");
        }
        vTaskDelay(portTICK_RATE_MS * 100);
    }

    vTaskDelete(NULL);
}


void vTask2(void* pvParameters)
{
    for (;; )
    {
        if (xSemaphore != NULL)
        {
            if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE)
            {
                char tempo[11];
                getCurrentTime(tempo);

                sprintf(buffer, "Task 2 - ");
                vPrintString(buffer);
                vPrintString(tempo);

                xSemaphoreGive(xSemaphore);
            }
        }
        else
        {
            printf("O semáforo não foi criado\n");
        }
        vTaskDelay(portTICK_RATE_MS * 100);
    }

    vTaskDelete(NULL);
}


void vTask3(void* pvParameters)
{
    for (;; )
    {
        if (xSemaphore != NULL)
        {
            if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE)
            {
                printTemperature();
                xSemaphoreGive(xSemaphore);
            }
        }
        else
        {
            printf("O semáforo não foi criado\n");
        }
        vTaskDelay(portTICK_RATE_MS * 100);
    }

    vTaskDelete(NULL);
}


void printDate()
{
    char data[11];
    getCurrentDate(data);
    sprintf(buffer, "Task 1- ");
    vPrintString(buffer);
    vPrintString(data);
}


void getCurrentDate(char* data)
{
    int seconds = 0;
    time(&seconds);
    struct tm* datetimeNow = localtime(&seconds);
    int dia = datetimeNow->tm_mday;
    int mes = datetimeNow->tm_mon + 1;
    int ano = datetimeNow->tm_year + 1900;

    sprintf(data, "%d/%d/%d\n", dia, mes, ano);
}


void getCurrentTime(char* tempo)
{
    int segundoss;
    time(&segundoss);
    struct tm* datetimeNow = localtime(&segundoss);
    int hora = datetimeNow->tm_hour;
    int min = datetimeNow->tm_min;
    int seg = datetimeNow->tm_sec;

    sprintf(tempo, "%d:%d:%d\n", hora, min, seg);
}


void printTemperature()
{
    char temperatura[25];
    getCurrentTemperature(temperatura);
    sprintf(buffer, "Task 3 - ");
    vPrintString(buffer);
    vPrintString(temperatura);
}


void getCurrentTemperature(char* temperatura)
{
    float temp = (float)rand() / (float)(RAND_MAX) * 40.0f;
    sprintf(temperatura, "Curitiba %.2f C\n", temp);
}

