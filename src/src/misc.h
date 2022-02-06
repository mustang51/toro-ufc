// -*- mode: c++; c-file-style: "linux" -*-

#ifndef __MISC_H__
#define __MISC_H__

extern unsigned long millis(void);

/* to avoid overflow issues */
#define MAX_TIME_DIFF (1UL << 31UL)

#define __time_expired(now, due) ((due - now) > MAX_TIME_DIFF)

#define time_expired(due) (__time_expired(millis(), due))

#define time_expired_from(now, due) (__time_expired(now, due))

#define __time_remaining(now, due)			\
	(__time_expired(now, due) ? 0 : due - now)

#define time_remaining(due) (__time_remaining(millis(), due))

#define time_remaining_from(now, due) (__time_remaining(now, due))

#endif
