#ifndef JEMALLOC_INTERNAL_NSTIME_H
#define JEMALLOC_INTERNAL_NSTIME_H

/* Maximum supported number of seconds (~584 years). */
#define NSTIME_SEC_MAX KQU(18446744072)
#define NSTIME_ZERO_INITIALIZER {0}

typedef struct {
	uint64_t ns;
} nstime_t;

static const nstime_t zero = NSTIME_ZERO_INITIALIZER;

void nstime_init(nstime_t *time, uint64_t ns);
void nstime_init2(nstime_t *time, uint64_t sec, uint64_t nsec);
uint64_t nstime_ns(const nstime_t *time);
uint64_t nstime_sec(const nstime_t *time);
uint64_t nstime_msec(const nstime_t *time);
uint64_t nstime_nsec(const nstime_t *time);
void nstime_copy(nstime_t *time, const nstime_t *source);
int nstime_compare(const nstime_t *a, const nstime_t *b);
void nstime_add(nstime_t *time, const nstime_t *addend);
void nstime_iadd(nstime_t *time, uint64_t addend);
void nstime_subtract(nstime_t *time, const nstime_t *subtrahend);
void nstime_isubtract(nstime_t *time, uint64_t subtrahend);
void nstime_imultiply(nstime_t *time, uint64_t multiplier);
void nstime_idivide(nstime_t *time, uint64_t divisor);
uint64_t nstime_divide(const nstime_t *time, const nstime_t *divisor);

typedef bool (nstime_monotonic_t)(void);
extern nstime_monotonic_t *JET_MUTABLE nstime_monotonic;

typedef bool (nstime_update_t)(nstime_t *);
extern nstime_update_t *JET_MUTABLE nstime_update;

bool nstime_init_update(nstime_t *time);

JEMALLOC_ALWAYS_INLINE void
nstime_init_zero(nstime_t *time) {
	nstime_copy(time, &zero);
}

JEMALLOC_ALWAYS_INLINE bool
nstime_equals_zero(nstime_t *time) {
	int diff = nstime_compare(time, &zero);
	assert(diff >= 0);
	return diff == 0;
}

#endif /* JEMALLOC_INTERNAL_NSTIME_H */
