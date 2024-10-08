#ifndef MP_MSG_CONTROL_H
#define MP_MSG_CONTROL_H

#include <stdbool.h>
#include "common/msg.h"

struct mpv_global;
struct MPOpts;
void mp_msg_init(struct mpv_global *global);
void mp_msg_uninit(struct mpv_global *global);
void mp_msg_update_msglevels(struct mpv_global *global, struct MPOpts *opts);
void mp_msg_force_stderr(struct mpv_global *global, bool force_stderr);
bool mp_msg_has_status_line(struct mpv_global *global);
bool mp_msg_has_log_file(struct mpv_global *global);
void mp_msg_set_early_logging(struct mpv_global *global, bool enable);

void mp_msg_flush_status_line(struct mp_log *log);
void mp_msg_set_term_title(struct mp_log *log, const char *title);

struct mp_log_buffer_entry {
    char *prefix;
    int level;
    char *text;
};

// Use --msg-level option for log level of this log buffer
#define MP_LOG_BUFFER_MSGL_TERM (MSGL_MAX + 1)
// For --log-file; --msg-level, but at least MSGL_DEBUG
#define MP_LOG_BUFFER_MSGL_LOGFILE (MSGL_MAX + 2)

struct mp_log_buffer;
struct mp_log_buffer *mp_msg_log_buffer_new(struct mpv_global *global,
                                            int size, int level,
                                            void (*wakeup_cb)(void *ctx),
                                            void *wakeup_cb_ctx);
void mp_msg_log_buffer_destroy(struct mp_log_buffer *buffer);
struct mp_log_buffer_entry *mp_msg_log_buffer_read(struct mp_log_buffer *buffer);
void mp_msg_log_buffer_set_silent(struct mp_log_buffer *buffer, bool silent);

int mp_msg_find_level(const char *s);

extern const char *const mp_log_levels[MSGL_MAX + 1];
extern const int mp_mpv_log_levels[MSGL_MAX + 1];

#endif
