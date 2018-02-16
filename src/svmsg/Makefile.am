noinst_PROGRAMS=slot mqctl testumask slotseq msgcreate msgsnd msgrcv msgrmid
slot_SOURCES=slot.c
slot_LDADD=$(top_srcdir)/src/lib/libunpipc.la
slot_LDFLAGS=-D_GNU_SOURCE
DEFS+=-D_GNU_SOURCE

testumask_SOURCES=testumask.c
testumask_LDADD=$(top_srcdir)/src/lib/libunpipc.la
testumask_LDFLAGS=-D_GNU_SOURCE

slotseq_SOURCES=slotseq.c
slotseq_LDADD=$(top_srcdir)/src/lib/libunpipc.la
slotseq_LDFLAGS=-D_GNU_SOURCE

mqctl_SOURCES=ctl.c
mqctl_LDADD=$(top_srcdir)/src/lib/libunpipc.la
mqctl_LDFLAGS=-D_GNU_SOURCE

msgcreate_SOURCES=msgcreate.c
msgcreate_LDADD=$(top_srcdir)/src/lib/libunpipc.la
msgcreate_LDFLAGS=-D_GNU_SOURCE

msgsnd_SOURCES=msgsnd.c
msgsnd_LDADD=$(top_srcdir)/src/lib/libunpipc.la
msgsnd_LDFLAGS=-D_GNU_SOURCE

msgrcv_SOURCES=msgrcv.c
msgrcv_LDADD=$(top_srcdir)/src/lib/libunpipc.la
msgrcv_LDFLAGS=-D_GNU_SOURCE

msgrmid_SOURCES=msgrmid.c
msgrmid_LDADD=$(top_srcdir)/src/lib/libunpipc.la
msgrmid_LDFLAGS=-D_GNU_SOURCE
