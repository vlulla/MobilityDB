/*****************************************************************************
 *
 * tinstant.h
 *	  Basic functions for temporal instants.
 *
 * Portions Copyright (c) 2020, Esteban Zimanyi, Arthur Lesuisse,
 *		Universite Libre de Bruxelles
 * Portions Copyright (c) 1996-2020, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *****************************************************************************/

#ifndef __TINSTANT_H__
#define __TINSTANT_H__

#include <postgres.h>
#include <catalog/pg_type.h>
#include <utils/array.h>
#include <utils/rangetypes.h>

#include "temporal.h"
#include "postgis.h"

/*****************************************************************************/
 
extern TInstant *tinstant_make(Datum value, TimestampTz t, Oid valuetypid);
extern TInstant *tinstant_copy(const TInstant *inst);
extern Datum* tinstant_value_ptr(const TInstant *inst);
extern Datum tinstant_value(const TInstant *inst);
extern Datum tinstant_value_copy(const TInstant *inst);
extern void tinstant_set(TInstant *inst, Datum value, TimestampTz t);

/* Input/output functions */

extern char *tinstant_to_string(const TInstant *inst, char *(*value_out)(Oid, Datum));
extern void tinstant_write(const TInstant *inst, StringInfo buf);
extern TInstant *tinstant_read(StringInfo buf, Oid valuetypid);

/* Intersection function */

extern bool intersection_tinstant_tinstant(const TInstant *inst1, const TInstant *inst2,
	TInstant **inter1, TInstant **inter2);

/* Append and merge functions */

extern TInstantSet *tinstant_append_tinstant(const TInstant *inst1, const TInstant *inst2);
extern Temporal *tinstant_merge(const TInstant *inst1, const TInstant *inst2);
extern TInstantSet *tinstant_merge_array(TInstant **instants, int count);

/* Cast functions */

extern TInstant *tintinst_to_tfloatinst(const TInstant *inst);
extern TInstant *tfloatinst_to_tintinst(const TInstant *inst);

/* Transformation functions */

extern TInstant *tinstantset_to_tinstant(const TInstantSet *ti);
extern TInstant *tsequence_to_tinstant(const TSequence *seq);
extern TInstant *tsequenceset_to_tinstant(const TSequenceSet *ts);

/* Accessor functions */

extern ArrayType *tinstant_values(const TInstant *inst);
extern ArrayType *tfloatinst_ranges(const TInstant *inst);
extern PeriodSet *tinstant_get_time(const TInstant *inst);
extern void tinstant_period(Period *p, const TInstant *inst);
extern ArrayType *tinstant_timestamps(const TInstant *inst);
extern ArrayType *tinstant_instants_array(const TInstant *inst);
extern TInstant *tinstant_shift(const TInstant *inst, const Interval *interval);

extern bool tinstant_ever_eq(const TInstant *inst, Datum value);
extern bool tinstant_ever_lt(const TInstant *inst, Datum value);
extern bool tinstant_ever_le(const TInstant *inst, Datum value);

extern bool tinstant_always_eq(const TInstant *inst, Datum value);
extern bool tinstant_always_lt(const TInstant *inst, Datum value);
extern bool tinstant_always_le(const TInstant *inst, Datum value);

/* Restriction Functions */

extern TInstant *tinstant_at_value(const TInstant *inst, Datum value);
extern TInstant *tinstant_minus_value(const TInstant *inst, Datum value);
extern TInstant *tinstant_restrict_values(const TInstant *inst, 
	const Datum *values, int count, bool at);
extern TInstant *tnumberinst_restrict_range(const TInstant *inst, 
	RangeType *range, bool at);
extern TInstant *tnumberinst_restrict_ranges(const TInstant *inst, 
	RangeType **normranges, int count, bool at);
	
extern TInstant *tinstant_restrict_timestamp(const TInstant *inst,
	TimestampTz t, bool at);
extern bool tinstant_value_at_timestamp(const TInstant *inst, 
	TimestampTz t, Datum *result);
extern TInstant *tinstant_restrict_timestampset(const TInstant *inst,
	const TimestampSet *ts, bool at);
extern TInstant *tinstant_restrict_period(const TInstant *inst, 
	const Period *p, bool at);
extern TInstant *tinstant_restrict_periodset(const TInstant *inst, 
	const PeriodSet *ps, bool at);

/* Intersection Functions */

extern bool tinstant_intersects_timestamp(const TInstant *inst, TimestampTz t);
extern bool tinstant_intersects_timestampset(const TInstant *inst, const TimestampSet *ts);
extern bool tinstant_intersects_period(const TInstant *inst, const Period *p);
extern bool tinstant_intersects_periodset(const TInstant *inst, const PeriodSet *ps);

/* Comparison functions */

extern int tinstant_cmp(const TInstant *inst1, const TInstant *inst2);
extern bool tinstant_eq(const TInstant *inst1, const TInstant *inst2);

/* Function for defining hash index */

extern uint32 tinstant_hash(const TInstant *inst);

/*****************************************************************************/

#endif
