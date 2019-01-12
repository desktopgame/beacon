#include "log.h"
#include <assert.h>
#include <glib.h>
#include <stdio.h>
#include "io.h"

static const char *logPath = "./report/log.txt";
static FILE *logF = NULL;

static char *log_level_tostr(GLogLevelFlags log_level) {
        switch (log_level) {
                case G_LOG_LEVEL_MESSAGE:
                        return "message";
                case G_LOG_LEVEL_DEBUG:
                        return "debug";
                case G_LOG_LEVEL_INFO:
                        return "info";
                case G_LOG_LEVEL_WARNING:
                        return "warning";
                case G_LOG_LEVEL_ERROR:
                        return "error";
                case G_LOG_LEVEL_CRITICAL:
                        return "critical";
        }
        return "null";
}

static void log_file(const gchar *log_domain, GLogLevelFlags log_level,
                     const gchar *message, gpointer user_data) {
        fprintf(logF, "%s: %s\n", log_level_tostr(log_level), message);
}

static void log_message(const gchar *log_domain, GLogLevelFlags log_level,
                        const gchar *message, gpointer user_data) {
        log_file(log_domain, log_level, message, user_data);
}
static void log_debug(const gchar *log_domain, GLogLevelFlags log_level,
                      const gchar *message, gpointer user_data) {
        log_file(log_domain, log_level, message, user_data);
}
static void log_info(const gchar *log_domain, GLogLevelFlags log_level,
                     const gchar *message, gpointer user_data) {
        log_file(log_domain, log_level, message, user_data);
}
static void log_warn(const gchar *log_domain, GLogLevelFlags log_level,
                     const gchar *message, gpointer user_data) {
        log_file(log_domain, log_level, message, user_data);
}
static void log_error(const gchar *log_domain, GLogLevelFlags log_level,
                      const gchar *message, gpointer user_data) {
        log_file(log_domain, log_level, message, user_data);
        g_on_error_query("beacon");
}
static void log_critical(const gchar *log_domain, GLogLevelFlags log_level,
                         const gchar *message, gpointer user_data) {
        log_file(log_domain, log_level, message, user_data);
        g_on_error_query("beacon");
}

static void log_capture_all(const gchar *log_domain, GLogLevelFlags log_level,
                            const gchar *message, gpointer user_data) {
        switch (log_level) {
                case G_LOG_LEVEL_MESSAGE:
                        log_message(log_domain, log_level, message, user_data);
                        break;
                case G_LOG_LEVEL_DEBUG:
                        log_debug(log_domain, log_level, message, user_data);
                        break;
                case G_LOG_LEVEL_INFO:
                        log_info(log_domain, log_level, message, user_data);
                        break;
                case G_LOG_LEVEL_WARNING:
                        log_warn(log_domain, log_level, message, user_data);
                        break;
                case G_LOG_LEVEL_ERROR:
                        log_error(log_domain, log_level, message, user_data);
                        break;
                case G_LOG_LEVEL_CRITICAL:
                        log_critical(log_domain, log_level, message, user_data);
                        break;
        }
}

void bc_InitLog() {
        assert(logF == NULL);
        if (bc_ExistsFile(logPath)) {
                bc_DeleteFile(logPath);
        }
        logF = fopen(logPath, "w");
        g_log_set_handler(NULL,
                          G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_DEBUG |
                              G_LOG_LEVEL_INFO | G_LOG_LEVEL_WARNING |
                              G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL |
                              G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION,
                          log_capture_all, NULL);
}

void bc_DestroyLog() {
        fclose(logF);
        logF = NULL;
}