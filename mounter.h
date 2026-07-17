#ifndef MOUNTER_H
#define MOUNTER_H

struct MountStruct
{
	// Device name. ("myhddriver.device")
	// Offset 0.
	const UBYTE *deviceName;
	// Unit number pointer or single integer value.
	// if >= 0x100 (256), pointer to array of ULONGs, first ULONG is number of unit numbers followed (for example { 2, 0, 1 }. 2 units, unit numbers 0 and 1).
	// if < 0x100 (256): used as a single unit number value.
	// Offset 4.
	ULONG *unitNum;
	// Name string used to set Creator field in FileSystem.resource (if KS 1.3) and in FileSystem.resource entries.
	// If NULL: use device name.
	// Offset 8.
	const UBYTE *creatorName;
	// ConfigDev: set if autoconfig board autoboot support is wanted.
	// If NULL and bootable partition found: fake ConfigDev is automatically created.
	// Offset 12.
	struct ConfigDev *configDev;
	// SysBase.
	// Offset 16.
	struct ExecBase *SysBase;
	// LUNs
	// Offset 20.
	BOOL luns;
	// Short/Long Spinup
	// Offset 22.
	BOOL slowSpinup;
	// Enahle CD Boot
	BOOL cdBoot;
	// Ignore RDBFF_LAST flag
	BOOL ignoreLast;
	// Host controller SCSI ID - set to 255 for non-SCSI controllers
	UBYTE hostId;
};

APTR W_CreateIORequest(struct MsgPort *ioReplyPort, ULONG size, struct ExecBase *SysBase);
void W_DeleteIORequest(APTR iorequest, struct ExecBase *SysBase);
struct MsgPort *W_CreateMsgPort(struct ExecBase *SysBase);
void W_DeleteMsgPort(struct MsgPort *port, struct ExecBase *SysBase);

LONG MountDrive(struct MountStruct *ms);

// ISO9660 stuff
typedef struct __attribute__((packed)) {
    uint16_t le;
    uint16_t be;
} b_int16_t;

typedef struct __attribute__((packed)) {
    uint32_t le;
    uint32_t be;
} b_int32_t;

typedef struct __attribute__((packed)) {
    uint8_t   length;
    uint8_t   extended_attr_length;
    b_int32_t extent_lba;
    b_int32_t data_length;
    uint8_t   recording_date[7];
    uint8_t   flags;
    uint8_t   file_unit_size;
    uint8_t   interleave;
    b_int16_t vol_seq_number;
    uint8_t   filename_len;
    char      filename;
} iso_dir_t;

typedef struct __attribute__((packed)) {
    uint8_t   code;
    char      identifier[5];
    uint8_t   version;
    uint8_t   unused1;
    char      sys_id[32];
    char      vol_id[32];
    uint8_t   unused2[8];
    b_int32_t vol_space_size;
    uint8_t   unused3[32];
    b_int16_t vol_set_size;
    b_int16_t vol_seq_number;
    b_int16_t log_sector_size;
    b_int32_t path_table_size;
    int32_t   loc_l_path_table;
    int32_t   loc_opt_l_path_table;
    int32_t   loc_m_path_table;
    int32_t   loc_opt_m_path_table;
    iso_dir_t root_dir;
    char      vol_set_id[128];
    char      publisher_id[128];
    char      data_preparer_id[128];
    char      application_id[128];
    char      copyright_file_id[37];
    char      abstract_file_id[37];
    char      bibliographic_file_id[37];
    char      creation_date[17];
    char      modification_date[17];
    char      expiration_date[17];
    char      effective_date[17];
    uint8_t   file_structure_version;
    uint8_t   unused4;
    uint8_t   application_used[512];
    uint8_t   reserved[653];
} iso_pvd_t;

#endif
